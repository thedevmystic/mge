# CMake file to include Catch2 Library

function(include_catch2)
  # if set to use system installed version
  if(MGE_USE_SYSTEM_CATCH2)
    message(STATUS "MGE: Searching for system-installed Catch2 v3...")
    find_package(Catch2 3 REQUIRED)
    return()
  endif()

  message(STATUS "MGE: Using pre-compiled third-party Catch2 binaries...")

  # OS Detect
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(PLATFORM_OS "linux")
    set(LIB_PREFIX "lib")
    set(LIB_SUFFIX ".a")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PLATFORM_OS "windows")
    set(LIB_PREFIX "")
    set(LIB_SUFFIX ".lib")
  else()
    message(FATAL_ERROR "Unsupported OS for pre-compiled Catch2: ${CMAKE_SYSTEM_NAME}")
  endif()

  # Arch Detect
  if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64|amd64|AMD64|x64)")
    set(PLATFORM_ARCH "x64")
  elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(arm64|aarch64|ARM64)")
    set(PLATFORM_ARCH "arm64")
  else()
    message(FATAL_ERROR "Unsupported architecture for pre-compiled Catch2: ${CMAKE_SYSTEM_PROCESSOR}")
  endif()

  # Paths
  set(CATCH2_BASE_DIR "${CMAKE_SOURCE_DIR}/third_party/catch2")
  set(CATCH2_INC_DIR  "${CATCH2_BASE_DIR}/include")
  set(CATCH2_BIN_DIR  "${CATCH2_BASE_DIR}/bin/${PLATFORM_OS}/${PLATFORM_ARCH}")

  set(CATCH2_LIB_PATH      "${CATCH2_BIN_DIR}/${LIB_PREFIX}Catch2${LIB_SUFFIX}")
  set(CATCH2_MAIN_LIB_PATH "${CATCH2_BIN_DIR}/${LIB_PREFIX}Catch2Main${LIB_SUFFIX}")

  # Targets
  if(NOT TARGET Catch2::Catch2)
    add_library(Catch2::Catch2 STATIC IMPORTED GLOBAL)
    set_target_properties(Catch2::Catch2 PROPERTIES
      IMPORTED_LOCATION "${CATCH2_LIB_PATH}"
      INTERFACE_INCLUDE_DIRECTORIES "${CATCH2_INC_DIR}"
    )
  endif()

  if(NOT TARGET Catch2::Catch2WithMain)
    add_library(Catch2::Catch2WithMain STATIC IMPORTED GLOBAL)
    set_target_properties(Catch2::Catch2WithMain PROPERTIES
      IMPORTED_LOCATION "${CATCH2_MAIN_LIB_PATH}"
      INTERFACE_LINK_LIBRARIES "Catch2::Catch2"
    )
  endif()

  message(STATUS "MGE: Loaded pre-compiled Catch2 from ${CATCH2_BIN_DIR}")
endfunction()
