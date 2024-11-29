# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.31.0)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(pybind11_fetch-populate NONE)

include(ExternalProject)
ExternalProject_Add(pybind11_fetch-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/pybind/pybind11" "GIT_TAG" "v2.13.5"
                    SOURCE_DIR          "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-src"
                    BINARY_DIR          "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
