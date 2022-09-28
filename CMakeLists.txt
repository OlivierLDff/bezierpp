# ~~~
# Copyright 2021 Olivier Le Doeuff
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
# CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
# ~~~

cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

# ──── Include guards ────

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR "In-source builds not allowed. "
                "Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ──── Main Project behavior ────

set(BEZIERPP_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(BEZIERPP_MAIN_PROJECT ON)
endif()

# ──── Default build to Release ────

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE STRING "Choose Release or Debug" FORCE
  )
endif()

# ───── 🔧 Configuration ─────

set(BEZIERPP_TARGET
    "bezierpp"
    CACHE STRING "Target Name"
)

set(BEZIERPP_ENABLE_EXAMPLES
    OFF
    CACHE BOOL "Create an install target."
)

set(BEZIERPP_ENABLE_INSTALL
    ${BEZIERPP_MAIN_PROJECT}
    CACHE BOOL "Create an install target."
)

if(BEZIERPP_ENABLE_INSTALL)
  include(GNUInstallDirs)
endif()

# ───── Project ─────

include(cmake/Version.cmake)

project(
  ${BEZIERPP_TARGET}
  VERSION ${BEZIERPP_VERSION}
  LANGUAGES CXX
)

# ───── bezierpp::bezierpp ─────

add_library(${BEZIERPP_TARGET} INTERFACE)

add_library(${BEZIERPP_TARGET}::${BEZIERPP_TARGET} ALIAS ${BEZIERPP_TARGET})

target_sources(
  ${BEZIERPP_TARGET}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/bezierpp/bezierpp.hpp>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/bezierpp/bezierpp.hpp>
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/bezierpp/qt.hpp>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/bezierpp/qt.hpp>
)

target_compile_features(${BEZIERPP_TARGET} INTERFACE cxx_std_17)

target_include_directories(
  ${BEZIERPP_TARGET} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                               $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ───── 🚀 Examples ─────

if(BEZIERPP_ENABLE_EXAMPLES)

  find_package(Eigen3)
  if(TARGET Eigen3::Eigen)
    message(STATUS "Add bezierpp_eigen example")
    add_executable(bezierpp_eigen samples/bezierpp_eigen.cpp)
    target_link_libraries(
      bezierpp_eigen
      PRIVATE Eigen3::Eigen
      PRIVATE ${BEZIERPP_TARGET}
    )
  else()
    message(WARNING "Eigen3 not found. bezierpp_eigen won't be build")
  endif()

  find_package(Qt5 COMPONENTS Gui)
  if(TARGET Qt::Gui)
    message(STATUS "Add bezierpp_qt example")
    add_executable(bezierpp_qt samples/bezierpp_qt.cpp)
    target_link_libraries(
      bezierpp_qt
      PRIVATE Qt::Gui
      PRIVATE ${BEZIERPP_TARGET}
    )
  else()
    message(WARNING "Qt5 not found. bezierpp_qt won't be build")
  endif()

endif()

# ───── 📦️ Package Project ─────

if(BEZIERPP_ENABLE_INSTALL)

  include(cmake/CPM.cmake)
  CPMAddPackage("gh:OlivierLDff/PackageProject.cmake@1.8.0")
  packageProject(
    NAME bezierpp
    VERSION ${PROJECT_VERSION}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src
    INCLUDE_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    NAMESPACE bezierpp
    COMPATIBILITY SameMinorVersion
  )

endif()
