# ~~~
# Copyright (C) Naostage - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# ~~~

set(BEZIERPP_VERSION_MAJOR 1)
set(BEZIERPP_VERSION_MINOR 0)
set(BEZIERPP_VERSION_PATCH 0)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
  execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE BEZIERPP_VERSION_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
endif()

if(NOT BEZIERPP_VERSION_TAG)
  set(BEZIERPP_VERSION_TAG 00000000)
endif(NOT BEZIERPP_VERSION_TAG)
set(BEZIERPP_VERSION_TAG_HEX 0x${BEZIERPP_VERSION_TAG})
set(BEZIERPP_VERSION ${BEZIERPP_VERSION_MAJOR}.${BEZIERPP_VERSION_MINOR}.${BEZIERPP_VERSION_PATCH})
