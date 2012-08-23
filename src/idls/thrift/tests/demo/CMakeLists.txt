cmake_minimum_required(VERSION 2.8)

enable_testing()

find_package(YARP REQUIRED)
include(${YARP_MODULE_PATH}/YarpIDL.cmake)

set(generated_libs_dir "${CMAKE_CURRENT_BINARY_DIR}")
yarp_idl_to_dir(demo.thrift ${generated_libs_dir})

include_directories(${generated_libs_dir}/demo)
include_directories(${YARP_INCLUDE_DIRS})
add_executable(demo_test main.cpp ${generated_libs_dir}/demo/Demo.h ${generated_libs_dir}/demo/Demo.cpp)
target_link_libraries(demo_test ${YARP_LIBRARIES})

add_test(demo_basic demo_test --help)

