cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
if(BUILD_SOFTCAM_DRIVER)
    set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "Available configurations" FORCE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

project(softcam_without_tests CXX)

add_compile_options(/permissive /Zc:strictStrings-)
if (BUILD_SOFTCAM_DRIVER)
    add_subdirectory(examples/softcam_installer)
endif()
add_subdirectory(src/baseclasses)
add_subdirectory(src/softcam)
add_subdirectory(src/softcamcore)