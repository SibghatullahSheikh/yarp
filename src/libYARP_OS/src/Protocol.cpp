// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */


#include <yarp/Protocol.h>

using namespace yarp;


bool Protocol::defaultSendIndex() {
    YARP_ASSERT(writer!=NULL);
    writeYarpInt(10);
    int len = writer->length();
    char lens[] = { len, 1, 
                    -1, -1, -1, -1,
                    -1, -1, -1, -1 };
    Bytes b(lens,10);
    os().write(b);
    for (int i=0; i<len; i++) {
        NetType::netInt(writer->length(i),number.bytes());
        os().write(number.bytes());
    }
    NetType::netInt(0,number.bytes());
    os().write(number.bytes());
    return os().isOk();
}


bool Protocol::defaultExpectIndex() {
    YARP_DEBUG(Logger::get(),"expecting an index");
    ACE_DEBUG((LM_DEBUG,"Protocol::expectIndex for %s", getRoute().toString().c_str()));
    // expect index header
    int r = NetType::readFull(is(),header.bytes());
    if (r!=header.length()) {
        throw_IOException("broken index");
        return false;
    }
    int len = interpretYarpNumber(header.bytes());
    if (len<0) {
        throw_IOException("broken index - header is not a number");
        return false;
    }
    if (len!=10) {
        throw_IOException("broken index - header is wrong length");
        return false;
    }
    YARP_DEBUG(Logger::get(),"index coming in happily...");
    r = NetType::readFull(is(),indexHeader.bytes());
    if (r!=indexHeader.length()) {
        throw_IOException("broken index, secondary header");
        return false;
    }
    YARP_DEBUG(Logger::get(),"secondary header came in happily...");
    int inLen = (unsigned char)(indexHeader.get()[0]);
    int outLen = (unsigned char)(indexHeader.get()[1]);
    // Big limit on number of blocks here!  Inherited from QNX.
    // should make it go away if it hurts someone.

    int total = 0;
    for (int i=0; i<inLen; i++) {
        int l = NetType::readFull(is(),number.bytes());
        if (l!=number.length()) {
            throw_IOException("bad input block length");
            return false;
        }
        int x = NetType::netInt(number.bytes());
        total += x;
    }
    for (int i2=0; i2<outLen; i2++) {
        int l = NetType::readFull(is(),number.bytes());
        if (l!=number.length()) {
            throw_IOException("bad output block length");
            return false;
        }
        int x = NetType::netInt(number.bytes());
        total += x;
    }
    messageLen = total;
    ACE_DEBUG((LM_DEBUG,"Total message length: %d\n",messageLen));
    YARP_DEBUG(Logger::get(),"got an index");
    return true;
}

bool Protocol::defaultSendAck() {
    YARP_DEBUG(Logger::get(),"sending an ack");
    if (delegate->requireAck()) {
        writeYarpInt(0);
    }
    return true;
}

