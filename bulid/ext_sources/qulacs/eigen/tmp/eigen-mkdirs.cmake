# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/src/eigen")
  file(MAKE_DIRECTORY "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/src/eigen")
endif()
file(MAKE_DIRECTORY
  "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/src/eigen-build"
  "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen"
  "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/tmp"
  "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/src/eigen-stamp"
  "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/src"
  "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/src/eigen-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/src/eigen-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/yadanilka/Projects/quansim/bulid/ext_sources/qulacs/eigen/src/eigen-stamp${cfgdir}") # cfgdir has leading slash
endif()
