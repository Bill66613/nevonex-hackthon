#==============================================================================
# C O P Y R I G H T
#------------------------------------------------------------------------------
# Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
#
# This file is property of Robert Bosch GmbH. Any unauthorized copy, use or
# distribution is an offensive act against international law and may be
# prosecuted under federal law. Its content is company confidential.
#==============================================================================

cmake_minimum_required (VERSION 3.0)

project (NevonexHackathon VERSION 1.1.0 LANGUAGES CXX)

SET(TARGET_NAME ${PROJECT_NAME}_${PROJECT_VERSION})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS) #required

include_directories(src/)

add_executable(
    ${TARGET_NAME}
    src/main.cpp
    src/Handler.cpp
    src/Server.cpp
)
