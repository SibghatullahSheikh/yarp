// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2009 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#ifndef YARPDB_SUBSCRIBER_INC
#define YARPDB_SUBSCRIBER_INC

#include "NameService.h"
#include "ConnectThread.h"

#include <yarp/os/ConstString.h>
#include <yarp/os/Vocab.h>

/**
 *
 * Abstract interface for maintaining persistent connections.
 *
 */
class Subscriber : public NameService {
private:
    NameStore *store;
    ConnectManager manager;
public:
    Subscriber() : store(0/*NULL*/) {}

    void setStore(NameStore& store) { this->store = &store; }
    NameStore *getStore() { return store; }

    void connect(const yarp::os::Contact& src,
                 const yarp::os::Contact& dest,
                 const yarp::os::ConstString& carrier) {
        manager.connect(src,dest,carrier);
    }

    virtual bool addSubscription(const char *src,
                                 const char *dest,
                                 const char *carrier) = 0;

    virtual bool removeSubscription(const char *src,
                                    const char *dest) = 0;

    virtual bool listSubscriptions(const char *src,
                                   yarp::os::Bottle& reply) = 0;

    virtual bool welcome(const char *port) = 0;

    virtual bool apply(yarp::os::Bottle& cmd, 
                       yarp::os::Bottle& reply, 
                       yarp::os::Bottle& event,
                       yarp::os::Contact& remote) {
        yarp::os::ConstString tag = cmd.get(0).asString();
        bool ok = false;
        if (tag=="subscribe"||tag=="unsubscribe"||tag=="announce") {
            printf("-> %s\n", cmd.toString().c_str());
        }
        if (tag=="subscribe") {
            yarp::os::ConstString src = cmd.get(1).asString();
            yarp::os::ConstString dest = cmd.get(2).asString();
            yarp::os::ConstString carrier = cmd.get(3).asString();
            if (dest!="") {
                ok = addSubscription(src,
                                     dest,
                                     carrier);
                reply.clear();
                reply.addVocab(ok?VOCAB2('o','k'):VOCAB4('f','a','i','l'));
                return ok;
            } else {
                // list subscriptions
                listSubscriptions(src,reply);
            }
            return true;
        }
        if (tag=="unsubscribe") {
            ok = removeSubscription(cmd.get(1).asString().c_str(),
                                    cmd.get(2).asString().c_str());
            reply.clear();
            reply.addVocab(ok?VOCAB2('o','k'):VOCAB4('f','a','i','l'));
            return ok;
        }
        if (tag=="announce") {
            welcome(cmd.get(1).asString().c_str());
            reply.clear();
            reply.addVocab(VOCAB2('o','k'));
            return true;
        }
        return ok;
    }

    virtual void onEvent(yarp::os::Bottle& event) {
        // put this in for compatibility with old YARP modules -
        // remove after some time, once all ports generate announce
        // messages

        yarp::os::ConstString tag = event.get(0).toString();
        yarp::os::ConstString port = event.get(1).toString();
        if (tag=="add") {
            welcome(port.c_str());
        }
    }
};


#endif