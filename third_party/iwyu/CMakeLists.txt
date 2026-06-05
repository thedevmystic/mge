# CMake file for IWYU (Include What You Use)

# If not set return
if(NOT MGE_USE_IWYU)
	return()
endif()

# To use iwyu we have to clang++ since it heavily depends on its hooks
if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	message(FATAL_ERROR "[MGE] - To use iwyu you must use clang++.")
endif()

# Find LLVM and Clang packages
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# Add add_llvm_executable
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

# Build Options
set(IWYU_ENABLE_TESTS   OFF CACHE BOOL "" FORCE)
set(LLVM_INCLUDE_TESTS  OFF CACHE BOOL "" FORCE)
set(CLANG_INCLUDE_TESTS OFF CACHE BOOL "" FORCE)
set(LLVM_INCLUDE_DOCS   OFF CACHE BOOL "" FORCE)
set(LLVM_ENABLE_DOXYGEN OFF CACHE BOOL "" FORCE)
set(LLVM_ENABLE_SPHINX  OFF CACHE BOOL "" FORCE)

# Version Git Tag
string(REPLACE "." ";" IWYU_CXX_COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
list(GET IWYU_CXX_COMPILER_VERSION 0 IWYU_CXX_COMPILER_MAJOR_VERSION)
set(IWYU_VERSION "clang_${IWYU_CXX_COMPILER_MAJOR_VERSION}")

include(mge_third_party_config)
# Since we can't use IWYU_VERSION in find_package, just find for any iwyu binary (it is dev's responsibility).
mge_third_party_config("iwyu" "${IWYU_VERSION}" "https://github.com/include-what-you-use/include-what-you-use.git" OFF)
