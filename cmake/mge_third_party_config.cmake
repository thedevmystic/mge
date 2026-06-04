# CMake file to define how to include a third party dependency

# LIB_NAME: Normal name of the library, e.g., Catch2
# GIT_TAG: Library's Git Tag.
# GITHUB_URL: GitHub URL of the repository.
function(mge_third_party_config LIB_NAME GIVEN_TAG GITHUB_URL)
  string(TOUPPER "${LIB_NAME}" LIB_NAME_UPPER)
  string(REGEX REPLACE "^[^0-9]+" "" LIB_VER "${GIVEN_TAG}")

  # Check for system-installed if option is set
  if(MGE_USE_SYSTEM_${LIB_NAME_UPPER})
    message(STATUS "[MGE] - Searching for system-installed ${LIB_NAME} ${LIB_VER}...")
    find_package(${LIB_NAME} ${LIB_VER} REQUIRED GLOBAL)
    message(STATUS "[MGE] - System-installed ${LIB_NAME} ${LIB_VER} found.")
  else()
    # Fetch from GitHub
    message(STATUS "[MGE] - Fetching ${LIB_NAME} ${LIB_VER}...")
    include(FetchContent)
    FetchContent_Declare(
      ${LIB_NAME}
        GIT_REPOSITORY ${GITHUB_URL}
        GIT_TAG        ${GIVEN_TAG}
    )
    FetchContent_MakeAvailable(${LIB_NAME})
    message(STATUS "[MGE] - ${LIB_NAME} ${LIB_VER} fetched.")
  endif()
endfunction()

# If we have to pass build flags to a library define them before using this.
# Example:
# set(MY_LIB_TEST OFF CACHE INTERNAL "Turn off my_lib's test suites.")
# ...
# include(mge_third_party_config)
# mge_third_party_config("my_lib" "v1.2.3" "https://github.com/username/repo.git")
