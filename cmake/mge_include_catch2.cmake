# CMake file to include Catch2 Library

function(include_catch2)
  find_package(Catch2 3 QUIET)

  if(NOT Catch2_FOUND)
    message(STATUS "Catch2 v3 not found locally. Fetching from GitHub...")

    include(FetchContent)
    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v3.4.0
    )
    FetchContent_MakeAvailable(Catch2)
  else()
    message(STATUS "Found local Catch2 installation: ${Catch2_VERSION}")
  endif()
endfunction()
