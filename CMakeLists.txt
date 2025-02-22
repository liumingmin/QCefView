#
# The main config file for QCefView
#
cmake_minimum_required(VERSION 3.9.1)
project(QCefView)

option(BUILD_DEMO "Build the demo" OFF)
option(BUILD_STATIC "Build QCefView as static library" OFF)
option(USE_SANDBOX "Enable CEF Sandbox" OFF)
option(STATIC_CRT "Use MultiThreaded linkage for MSVC" OFF)

get_directory_property(QCefView_HAS_PARENT_DIRECTORY PARENT_DIRECTORY)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# C standard
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

add_definitions(-D_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING=1)

# Determine the project architecture.
if(NOT DEFINED PROJECT_ARCH)
  if(OS_WINDOWS AND "${CMAKE_GENERATOR_PLATFORM}" STREQUAL "arm64")
    set(PROJECT_ARCH "arm64")
  elseif(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PROJECT_ARCH "x86_64")
  else()
    set(PROJECT_ARCH "x86")
  endif()
endif()

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  set(OS_MACOS 1)
  set(OS_POSIX 1)
  add_definitions(-DOS_MACOS=1 -DOS_POSIX=1)

  # Target architecture.
  if(PROJECT_ARCH STREQUAL "x86_64")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
  elseif(PROJECT_ARCH STREQUAL "arm64")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
  else()
    set(CMAKE_OSX_ARCHITECTURES "i386")
  endif()
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  set(OS_LINUX 1)
  set(OS_POSIX 1)
  add_definitions(-DOS_LINUX=1 -DOS_POSIX=1)

  # Target architecture.
  if(PROJECT_ARCH STREQUAL "x86_64")
    # x86 64-bit architecture.
    add_compile_options(-m64 -march=x86-64)
    add_link_options(-m64)
  elseif(PROJECT_ARCH STREQUAL "x86")
    # x86 32-bit architecture.
    add_compile_options(-m32)
    add_link_options(-m32)
  endif()
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  set(OS_WINDOWS 1)
  add_definitions(-DOS_WINDOWS=1)
endif()

if(BUILD_STATIC)
  set(QCEFVIEW_LIB_TYPE STATIC)
  add_definitions(-DQCEFVIEW_STATIC=1)
else()
  set(QCEFVIEW_LIB_TYPE SHARED)
endif()

# Config the QT package
# ##############################################################
include(QtConfig.cmake)
message(STATUS "Qt SKD dir: " ${QT_SDK_DIR})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_SDK_DIR})
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

# ##############################################################

# Config the CEF
# ##############################################################
if(OS_WINDOWS)
  add_link_options(/DEBUG)

  # Disable the sandbox on Windows, because the sandbox.lib is MT which
  # is conflict with Qt
  set(USE_SANDBOX OFF CACHE BOOL "Disable sandbox on Windows" FORCE)
  add_compile_options("/M$<IF:$<BOOL:${STATIC_CRT}>,T,D>$<$<CONFIG:Debug>:d>")
else()
  add_compile_options(
    "-g"
    "$<$<CONFIG:DEBUG>:-O0>"
    "$<$<CONFIG:RELEASE>:-O3>"
  )
endif()

if(NOT QCefView_HAS_PARENT_DIRECTORY)
  message(STATUS "QCefView is not in subdirectory, put all output together")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/$<CONFIG>/bin)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/$<CONFIG>/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/$<CONFIG>/lib)
endif()

# Include CefViewCore
add_subdirectory(CefViewCore)
set_target_properties(CefViewCore PROPERTIES FOLDER core)

foreach(CefViewWingTarget ${CefViewCore_HELPER_APP_TARGETS})
  set_target_properties(${CefViewWingTarget} PROPERTIES FOLDER core)
endforeach(CefViewWingTarget)

set_target_properties(libcef_dll_wrapper PROPERTIES FOLDER core)

# read CEF version from cef_version.h
file(READ "${CefViewCore_CEF_INCLUDE_DIR}/cef_version.h" cef_version_content)
string(REGEX MATCH "#define CEF_VERSION_MAJOR ([0-9]+)" _ ${cef_version_content})
set(CEF_VERSION_MAJOR ${CMAKE_MATCH_1})
message(STATUS "CEF_VERSION_MAJOR: ${CEF_VERSION_MAJOR}")

string(REGEX MATCH "#define CEF_VERSION_MINOR ([0-9]+)" _ ${cef_version_content})
set(CEF_VERSION_MINOR ${CMAKE_MATCH_1})
message(STATUS "CEF_VERSION_MINOR: ${CEF_VERSION_MINOR}")

string(REGEX MATCH "#define CEF_VERSION_PATCH ([0-9]+)" _ ${cef_version_content})
set(CEF_VERSION_PATCH ${CMAKE_MATCH_1})
message(STATUS "CEF_VERSION_PATCH: ${CEF_VERSION_PATCH}")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/src/QCefView_global.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/QCefView_global.h"
  @ONLY
)

if(OS_MACOS)
  if(CEF_VERSION_MAJOR LESS 104)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11)
  else()
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13)
  endif()
endif()

# Config QCefView target
# ##############################################################
add_subdirectory(src)

# Config the Demo project
# ##############################################################
if(BUILD_DEMO)
  add_subdirectory(example/QCefViewTest)
endif()

# ##############################################################
