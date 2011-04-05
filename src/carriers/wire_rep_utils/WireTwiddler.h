// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2011 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef YARP2_WIRETWIDDLER
#define YARP2_WIRETWIDDLER

#include <yarp/os/Bottle.h>
#include <yarp/os/ManagedBytes.h>
#include <yarp/os/NetInt32.h>

#include <yarp/os/impl/SizedWriter.h>
#include <yarp/os/impl/InputStream.h>
#include <yarp/os/Bytes.h>

#include <vector>

class WireTwiddlerGap {
public:
    int buffer_start;
    int buffer_length;
    int length;
    int unit_length;
    char *byte_start;
    int byte_length;
    yarp::os::ConstString origin;
    WireTwiddlerGap() {
        buffer_start = 0;
        buffer_length = 0;
        length = 0;
        unit_length = 0;
        byte_start = 0/*NULL*/;
        byte_length = 0;
    }

    char *getStart() const { return byte_start; }
    int getLength() const { return byte_length; }
    int getUnitLength() const { return unit_length; }
    int getExternalLength() const { return unit_length; }
    const yarp::os::ConstString& getOrigin() const { return origin; }
};


class WireTwiddler {
public:
    WireTwiddler() {
        buffer_start = 0;
    }

    bool configure(const char *txt);

private:

    int buffer_start;
    std::vector<yarp::os::NetInt32> buffer;
    std::vector<WireTwiddlerGap> gaps;

public:
    void show();
    int configure(yarp::os::Bottle& desc, int offset);

    int getGapCount() {
        return (int)gaps.size();
    }

    void clear() {
        buffer_start = 0;
        buffer.clear();
        gaps.clear();
    }

    const WireTwiddlerGap& getGap(int index) {
        return gaps[index];
    }

    yarp::os::ConstString toString() const;

    bool read(yarp::os::Bottle& bot, const yarp::os::Bytes& data);

    bool write(yarp::os::Bottle& bot, yarp::os::ManagedBytes& data);
};


/*

  State:
  index, sent

 */

class WireTwiddlerReader : public yarp::os::impl::InputStream {
private:
    yarp::os::impl::InputStream& is;
    WireTwiddler& twiddler;
    char *cursor;
    int sent;
    int consumed;
    int override_length;
    int index;
    bool recite;
    yarp::os::NetInt32 lengthBuffer;
    int pending_length;
    int pending_strings;
    int pending_string_length;
    int pending_string_data;
public:
    WireTwiddlerReader(yarp::os::impl::InputStream& is, 
                       WireTwiddler& twiddler) : is(is),
                                                 twiddler(twiddler) {
        reset();
    }

    void reset() {
        recite = false;
        index = -1;
        sent = 0;
        consumed = 0;
        cursor = 0 /*NULL*/;
        pending_length = 0;
        pending_strings = 0;
        pending_string_length = 0;
        pending_string_data = 0;
        override_length = -1;
    }

    virtual ~WireTwiddlerReader() {}

    virtual int read(const yarp::os::Bytes& b);

    virtual void close() { is.close(); }

    virtual bool isOk() { return is.isOk(); }
};


class WireTwiddlerWriter : public yarp::os::impl::SizedWriter {
private:
    yarp::os::impl::SizedWriter& parent;
    WireTwiddler& twiddler;
    std::vector<yarp::os::Bytes> srcs;
public:
    WireTwiddlerWriter(yarp::os::impl::SizedWriter& parent,
                       WireTwiddler& twiddler) : parent(parent),
                                                 twiddler(twiddler) {
        update();
    }

    void update();

    virtual ~WireTwiddlerWriter() {}

    virtual int length() { 
        return (int)srcs.size(); 
    }

    virtual int headerLength() {
        return parent.headerLength();
    }

    virtual int length(int index)  { 
        return srcs[index].length(); 
    }

    virtual const char *data(int index) {
        return srcs[index].get(); 
    }

    virtual yarp::os::PortReader *getReplyHandler() {
        return parent.getReplyHandler();
    }
    
    virtual yarp::os::Portable *getReference() {
        return parent.getReference();
    }

    bool pass(int len);

    bool skip(int len);

};

#endif
