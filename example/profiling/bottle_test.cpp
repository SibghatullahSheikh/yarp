// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright: (C) 2010 RobotCub Consortium
 * Authors: Paul Fitzpatrick, Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <stdio.h>
#include <yarp/os/all.h>
using namespace yarp::os;

void net_test() {
    Network yarp;

    yarp.setLocalMode(true);

    BufferedPort<Bottle> port;
    Port port2;
    port.open("/port");
    port2.open("/port2");
    yarp.connect("/port","/port2");

    for (int k=0; k<200; k++) {
        printf("Round %d\n", k);
        Bottle& b = port.prepare();
        b.clear();
        for (int i=0; i<10000; i++) {
            b.add(Value(i));
        }
        port.write();
        Bottle b2;
        port2.read(b2);
    }
    port.close();
    port2.close();
}

void copy_test() {
    Bottle a, b, c;
    for (int i=0; i<1000; i++) {
        a.add(Value(i));
    }
    double start = Time::now();
    for (int i=0; i<10000; i++) {
        b = a;
    }
    double stop = Time::now();
    printf("Copies took about %g seconds\n", stop-start);
    printf("(but use proper profiling, not this message)\n");
}

int main() {
    printf("We don't recommend you use Bottles for large data structures\n");
    printf("But if you did, what parts gets slow first?\n");
    printf("This is a test program for profiling purposes.\n");
    printf("It doesn't do anything interest by itself.\n");

    net_test();
    //copy_test();
    return 0;
}

