# Copyright: (C) 2010 RobotCub Consortium
# Authors: Paul Fitzpatrick
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 

GET_PROPERTY(YARP_TREE_INCLUDE_DIRS TARGET YARP_OS PROPERTY INCLUDE_DIRS)
INCLUDE_DIRECTORIES(${YARP_TREE_INCLUDE_DIRS})
include_directories(${ACE_INCLUDE_DIRS})
get_filename_component(YARP_CPP yarp.cpp ABSOLUTE) # make absolute for later reference
ADD_EXECUTABLE(yarp ${YARP_CPP})
TARGET_LINK_LIBRARIES(yarp YARP_OS YARP_init)

SET(YARPSERVER_NAME yarpserver2)
IF (YARP_USE_PERSISTENT_NAMESERVER)
  INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/yarpserver/include)
ELSE ()
  SET(YARPSERVER_NAME yarpserver)
ENDIF ()

ADD_EXECUTABLE(${YARPSERVER_NAME} yarpserver.cpp)
TARGET_LINK_LIBRARIES(${YARPSERVER_NAME} YARP_OS YARP_init)

IF (YARP_USE_PERSISTENT_NAMESERVER)
  SET_PROPERTY(SOURCE ${YARP_CPP} APPEND PROPERTY COMPILE_DEFINITIONS YARP_USE_PERSISTENT_NAMESERVER=1)
  TARGET_LINK_LIBRARIES(yarp YARP_serversql)
ENDIF ()

install(TARGETS yarp ${YARPSERVER_NAME} COMPONENT utilities DESTINATION ${CMAKE_INSTALL_BINDIR})

include_directories(${CMAKE_SOURCE_DIR}/extern/diff_match_patch)
ADD_EXECUTABLE(yarp-config yarpconfig.cpp yarpcontext.cpp yarpcontext.h yarprobot.cpp yarprobot.h yarpcontextutils.cpp yarpcontextutils.h)
TARGET_LINK_LIBRARIES(yarp-config YARP_OS YARP_init ${ACE_LIBRARIES})
install(TARGETS yarp-config COMPONENT utilities DESTINATION ${CMAKE_INSTALL_BINDIR})
