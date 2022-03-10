# Install script for directory: G:/ythpt/libecl-datapro-py/ecllib/ecl/python/ecl/util/geometry

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "G:/ythpt/libecl-datapro-py/ecllib/ecl/build")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/__init__.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/__init__.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/__init__.py)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/cpolyline.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/cpolyline.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/cpolyline.py)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/cpolyline_collection.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/cpolyline_collection.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/cpolyline_collection.py)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/geometry_tools.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/geometry_tools.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/geometry_tools.py)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/geo_pointset.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/geo_pointset.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/geo_pointset.py)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/geo_region.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/geo_region.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/geo_region.py)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/polyline.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/polyline.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/polyline.py)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/xyz_io.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/xyz_io.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/xyz_io.py)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/surface.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry" TYPE FILE FILES "G:/ythpt/libecl-datapro-py/ecllib/ecl/lib/python3.10/site-packages/ecl/util/geometry/surface.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND C:/Users/Work20180611/AppData/Local/Programs/Python/Python310/python.exe G:/ythpt/libecl-datapro-py/ecllib/ecl/bin/cmake_pyc_file G:/ythpt/libecl-datapro-py/ecllib/ecl/build/lib/python3.10/site-packages/ecl/util/geometry/surface.py)
endif()

