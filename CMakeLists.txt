cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
message(STATUS "CMake version: ${CMAKE_VERSION}")

# must go before the `project()` command
set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING "Configs" FORCE)

project(umf)

set(UMF_3PTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
set(XMP_DIR ${UMF_3PTY_DIR}/xmp)
set(MODULES_DIR ${CMAKE_SOURCE_DIR}/modules)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(NOT IOS)
  option(BUILD_SHARED_LIBS "Whether or not to build UMF as shared library" ON)
  option(BUILD_SAMPLES "Whether or not to build the samples" ON)
  option(BUILD_TESTS "Whether or not to build the tests" ON)
  # Java
  find_package(Java 1.7 QUIET)
  find_package(JNI QUIET)
  if(JAVA_FOUND AND JNI_FOUND)
    option(BUILD_JAVA_API "Whether or not to build Java wrappers" ON)
  endif()
else()
  set(BUILD_SHARED_LIBS OFF)
  set(BUILD_SAMPLES OFF)
  set(BUILD_QT_SAMPLES OFF)
  set(BUILD_TESTS OFF)
endif()

if(NOT BUILD_SHARED_LIBS AND BUILD_JAVA_API)
  # JAR depends on dynamic UMF lib
  set(BUILD_JAVA_API OFF)
  message(WARNING "Java API building is disabled since it requires UMF lib to be dynamic")
endif()

if(WIN32)
  set(BUILD_INSTALLER ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  option(CODE_COVERAGE "Whether or not to build with code coverage info (disables samples)" OFF)
else()
  set(CODE_COVERAGE OFF)
endif()

if(CMAKE_GENERATOR MATCHES "Makefiles|Ninja" AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(DEFINED CMAKE_BUILD_TYPE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
endif()

if(CMAKE_COMPILER_IS_GNUCXX AND CODE_COVERAGE)
  set(BUILD_SAMPLES OFF)
  set(BUILD_QT_SAMPLES OFF)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# The version number.
set(UMF_VERSION_MAJOR "3")
set(UMF_VERSION_MINOR "0")
set(UMF_VERSION_TYPE  "RC1") # dev, alpha, beta

# adding git info to the version if possible
if(NOT COMMAND find_host_package)
  macro(find_host_package)
    find_package(${ARGN})
  endmacro()
endif()
find_host_package(Git QUIET)
if(GIT_FOUND)
  execute_process(COMMAND "${GIT_EXECUTABLE}" describe --tags --always --dirty
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE UMF_VERSION_VCS
    RESULT_VARIABLE GIT_RESULT
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(NOT GIT_RESULT EQUAL 0)
    set(UMF_VERSION_VCS "unknown")
  endif()
else()
  set(UMF_VERSION_VCS "unknown")
endif()

# reporting build settings

function(umf_status msg)
  message(STATUS "${msg}")
  file(APPEND "${umf_build_info_FILE}" "${msg}\n")
endfunction()

set(umf_build_info_FILE "${CMAKE_BINARY_DIR}/build-info.tmp")
file(REMOVE "${umf_build_info_FILE}")
file(APPEND "${umf_build_info_FILE}" "const char* umf_build_info = R\"umf_build_info(\n")

message(STATUS "*** UMF build configuration ***")
# UMF
umf_status("    UMF version: ${UMF_VERSION_MAJOR}.${UMF_VERSION_MINOR}.${UMF_VERSION_TYPE} (GIT: ${UMF_VERSION_VCS})")
# OS, HW
umf_status("    Platform:")
umf_status("      Host: ${CMAKE_HOST_SYSTEM} ${CMAKE_HOST_SYSTEM_PROCESSOR}")
if(CMAKE_CROSSCOMPILING)
  umf_status("      Target: ${CMAKE_SYSTEM} ${CMAKE_SYSTEM_PROCESSOR}")
endif()
if(ANDROID)
  umf_status("        Android native API level: android-${ANDROID_NATIVE_API_LEVEL} (${ANDROID_ABI})")
  umf_status("        NDK Toolchain: ${ANDROID_TOOLCHAIN_NAME} (NDK ${ANDROID_NDK_RELEASE}, ${ANDROID_NDK})")
endif()
# tools
umf_status("    CMake generator: ${CMAKE_GENERATOR}")
set(UMF_COMPILER_STR "(${CMAKE_CXX_COMPILER_ID}")
if(CMAKE_CXX_COMPILER_VERSION)
  set(UMF_COMPILER_STR "${UMF_COMPILER_STR} ${CMAKE_CXX_COMPILER_VERSION}")
elseif(CMAKE_COMPILER_IS_CLANGCXX)
  set(UMF_COMPILER_STR "${UMF_COMPILER_STR} ${CMAKE_CLANG_REGEX_VERSION}")
elseif(CMAKE_COMPILER_IS_GNUCXX)
  set(UMF_COMPILER_STR "${UMF_COMPILER_STR} ${CMAKE_GCC_REGEX_VERSION}")
endif()
set(UMF_COMPILER_STR "${UMF_COMPILER_STR}) ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}")
string(STRIP "${UMF_COMPILER_STR}" UMF_COMPILER_STR)
umf_status("    CMake C++ compiler: ${UMF_COMPILER_STR}")
umf_status("    CMake Linker: ${CMAKE_LINKER}")
umf_status("    CMake build tool: ${CMAKE_BUILD_TOOL}")
if(Java_JAVAC_EXECUTABLE)
  umf_status("    CMake Java compiler: ${Java_JAVAC_EXECUTABLE} (ver ${Java_VERSION})")
endif()
if(NOT CMAKE_GENERATOR MATCHES "Xcode|Visual Studio")
  message(STATUS "    CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
else()
  message(STATUS "    CMAKE_CONFIGURATION_TYPES: ${CMAKE_CONFIGURATION_TYPES}")
endif()
# build options
umf_status("    BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message(STATUS "    BUILD_SAMPLES: ${BUILD_SAMPLES}")
message(STATUS "    BUILD_QT_SAMPLES: ${BUILD_QT_SAMPLES}")
message(STATUS "    BUILD_TESTS: ${BUILD_TESTS}")
if(BUILD_JAVA_API OR ANDROID)
  message(STATUS "    BUILD_JAVA_API: ON")
else()
  message(STATUS "    BUILD_JAVA_API: OFF")
endif()
if(CMAKE_COMPILER_IS_GNUCXX)
  umf_status("    CODE_COVERAGE: ${CODE_COVERAGE}")
endif()

#if(WIN32)
    SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE INTERNAL "Install path prefix" FORCE)
#endif()

set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

if (UNIX)
    add_definitions(-D_FILE_OFFSET_BITS=64)
endif()

if(WIN32)
    add_definitions(-D_VARIADIC_MAX=10)
else()
    if(ANDROID)
        set(BUILD_SAMPLES OFF)
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm*")
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z muldefs")
        endif()
    elseif(APPLE)
        if(NOT IOS)
          if (NOT DEFINED CMAKE_MACOSX_RPATH)
            set(CMAKE_MACOSX_RPATH 0)
          endif()
        endif()
    else()
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

file(APPEND "${umf_build_info_FILE}" "    CMake version = ${CMAKE_VERSION}\n")
file(APPEND "${umf_build_info_FILE}" ")umf_build_info\";\n")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${umf_build_info_FILE}" "${CMAKE_BINARY_DIR}/build-info.inc" OUTPUT_QUIET)
message(STATUS "*** *** ***")

#enable_testing(true)

if(BUILD_TESTS)
    add_subdirectory(${UMF_3PTY_DIR}/gtest)
endif()
add_subdirectory(${UMF_3PTY_DIR}/xmp)
add_subdirectory(${UMF_3PTY_DIR}/libxml2)
add_subdirectory(${UMF_3PTY_DIR}/libjson)
add_subdirectory(${UMF_3PTY_DIR}/cryptopp)
add_subdirectory(modules)

if(BUILD_SAMPLES)
    set(CMAKE_DISABLE_FIND_PACKAGE_VMF TRUE)
    set(UMF_LIB_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(UMF_LIBS umf)
    set(UMF_INCLUDE_DIR "${MODULES_DIR}/umfcore/include" "${CMAKE_BINARY_DIR}")
    set(UMF_DATA_DIR "${CMAKE_SOURCE_DIR}/data")
    if(BUILD_JAVA_API)
      set(UMF_JAR_PATH "${CMAKE_BINARY_DIR}/bin/umf_java.jar")
    endif()
    add_subdirectory(samples)
endif()

if(NOT ANDROID)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(doc ALL
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
    endif()
endif()

if (BUILD_INSTALLER)
    set(CPACK_PACKAGE_NAME "Intel UMF SDK")
    set(CPACK_PACKAGE_VENDOR "Intel")
    set(CPACK_PACKAGE_VERSION "${UMF_VERSION_MAJOR}.${UMF_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_MAJOR ${UMF_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${UMF_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH "0")
    set(CPACK_PACKAGE_FILE_NAME "Intel-UMF-SDK-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
    if(UMF_VERSION_TYPE)
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-${UMF_VERSION_TYPE}")
    endif()
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "Intel-UMF-SDK-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
    set(CPACK_GENERATOR "WIX")
    set(CPACK_WIX_PRODUCT_GUID "F05416DA-303D-4952-BEF4-D576AE4F4A3A")
    set(CPACK_WIX_UPGRADE_GUID "4CF37946-64F6-4841-8E8C-6E7BBE2F7654")
    #set(CPACK_WIX_PRODUCT_ICON "")
    #set(CPACK_WIX_UI_BANNER "") 493x58
    #set(CPACK_WIX_UI_DIALOG "") 493x312
    #set(CPACK_WIX_TEMPLATE "") main.wxs

# android libs
    add_custom_target(ANDROID_LIBS
            build_android_libs.py
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Compiling libraries for android" VERBATIM
    )
    if(EXISTS "${CMAKE_SOURCE_DIR}/android_libs")
        install(DIRECTORY "android_libs" DESTINATION ".")
    endif()

# libs built by current project
    # installed in modules/CMakeLists.txt

# For other platforms
    if(EXISTS "${CMAKE_SOURCE_DIR}/to_be_installed")
        file(GLOB TO_BE_INSTALLED "to_be_installed/*")
        foreach(SUBDIR ${TO_BE_INSTALLED})
            install(DIRECTORY ${SUBDIR} DESTINATION ".")
        endforeach()
    endif()

# CMake files
    install(FILES "cmake/FindVMF.cmake" DESTINATION "cmake")

# samples stuff
    install(DIRECTORY "samples" DESTINATION ".")
    install(DIRECTORY "data" DESTINATION ".")
    install(FILES "cmake/FindVMF.cmake" DESTINATION "samples")

if (BUILD_JAVA_API)	
    install(FILES "${CMAKE_BINARY_DIR}/bin/umf_java.jar" DESTINATION "java")
endif()

# documentation
    install(FILES "docs/VMF_Release_Notes.pdf" DESTINATION "docs")
    install(FILES "docs/VMF_User_guide.pdf" DESTINATION "docs")
    install(FILES "docs/VMF_Specification.pdf" DESTINATION "docs")
    install(FILES "LICENSE" DESTINATION ".")
    if(DOXYGEN_FOUND)
        install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/html/" DESTINATION "docs/API-Spec")
    endif()

    include(CPack)
endif()

if(IOS)
    configure_file("${CMAKE_SOURCE_DIR}/platforms/ios/Info.plist.in"
                   "${CMAKE_BINARY_DIR}/ios/Info.plist")
endif()

