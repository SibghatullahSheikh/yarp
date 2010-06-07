// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2010 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#ifndef YARPCXX_ConnectionReader_INC
#define YARPCXX_ConnectionReader_INC

#include <yarp/yarpcxx.h>

namespace yarpcxx {
    namespace os {
        class ConnectionReader;
    }
}

class yarpcxx::os::ConnectionReader {
public:
    ConnectionReader(yarpReaderPtr handle) : impl(handle) {}

    int expectInt() {
        int x = 0;
        yarpReaderExpectInt(impl,&x);
        return x;
    }
private:
    yarpReaderPtr impl;
};

#endif