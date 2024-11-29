# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-src")
  file(MAKE_DIRECTORY "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-src")
endif()
file(MAKE_DIRECTORY
  "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-build"
  "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-subbuild/pybind11_fetch-populate-prefix"
  "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-subbuild/pybind11_fetch-populate-prefix/tmp"
  "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-subbuild/pybind11_fetch-populate-prefix/src/pybind11_fetch-populate-stamp"
  "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-subbuild/pybind11_fetch-populate-prefix/src"
  "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-subbuild/pybind11_fetch-populate-prefix/src/pybind11_fetch-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-subbuild/pybind11_fetch-populate-prefix/src/pybind11_fetch-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/yadanilka/Projects/quansim/bulid/_deps/pybind11_fetch-subbuild/pybind11_fetch-populate-prefix/src/pybind11_fetch-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
