cmake_minimum_required(VERSION 3.14.6)

###############################################################################
# Policy
###############################################################################
cmake_policy(SET CMP0115 OLD) # explicit source file extention symbol

# <= CMake3.*.*でAppleClangをコンパイラIDとして認識させる
# Report AppleClang separately from Clang. Their version numbers are different.
# https://cmake.org/cmake/help/v3.0/policy/CMP0025.html
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif()

###############################################################################
# Device Check
###############################################################################
# Platform
if(WIN32)
    message(STATUS "Platform: Windows ${CMAKE_SYSTEM_VERSION}")
elseif(APPLE)
    message(STATUS "Platform: macOS ${CMAKE_SYSTEM_VERSION}")
elseif(UNIX AND NOT APPLE) # Linux
    message(STATUS "Platform: Linux ${CMAKE_SYSTEM_VERSION}")
else()
    message(FATAL_ERROR "Platform: Not match platforms [Windows, macOS, Linux]. Given platform is ${CMAKE_SYSTEM_NAME}")
endif()

# Processor
message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}")

# Generator
# https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html
message(STATUS "Generator: ${CMAKE_GENERATOR}")

###############################################################################
# Top-level Project Name
###############################################################################
project(HowToEigen LANGUAGES CXX VERSION 0.1.0)

###############################################################################
# Compiler Option for All Target (Easy configration)
###############################################################################
message(STATUS "========== [START] C++ All Target Options ==========")

# ZERO_CHECKプロジェクトの有無
if(NOT BUILD_CPP_ZERO_CHECK)
    set(CMAKE_SUPPRESS_REGENERATION true)
endif()

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

message(STATUS "---------- Compiler options ----------")
message(STATUS ">>>>> C++ version: ${CMAKE_CXX_STANDARD}")
message(STATUS ">>>>> C++ compiler id: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS ">>>>> C++ compiler path: ${CMAKE_CXX_COMPILER}")
message(STATUS ">>>>> C++ compiler `Common` flags: ${CMAKE_CXX_FLAGS}")
message(STATUS ">>>>> C++ compiler `Debug` flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS ">>>>> C++ compiler `Release` flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS ">>>>> C++ compiler `Minsizerel` flags: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
message(STATUS ">>>>> C++ compiler `Relwithdebinfo` flags: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")

message(STATUS "========== [END] C++ All Target Options ==========")

###############################################################################
# Test Sample Dirs
###############################################################################

include_directories(${CMAKE_SOURCE_DIR}) # test_utils.hpp

add_subdirectory(BasicOperation)
add_subdirectory(LinAlg)
add_subdirectory(Mapping)
add_subdirectory(Geometry)
# add_subdirectory()
# add_subdirectory()
# add_subdirectory()


# add_executable(matrix_features
#     main_matrix_features.cpp
# )