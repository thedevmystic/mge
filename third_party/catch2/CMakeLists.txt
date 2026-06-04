# CMake file for Catch2 v3

# Check if we have to use system-installed Catch2
if(MGE_USE_SYSTEM_CATCH2)
	message(STATUS "[MGE] - Searching for system-installed Catch2 v3...")
	find_package(Catch2 3 REQUIRED GLOBAL)
	message(STATUS "[MGE] - Catch2 v3 found.")
	return()
endif()

message(STATUS "[MGE] - Fetching Catch2 v3...")
include(FetchContent)
FetchContent_Declare(
  Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG        ${MGE_CATCH2_VERSION}
)
FetchContent_MakeAvailable(Catch2)
message(STATUS "[MGE] - Catch2 v3 fetched.")
