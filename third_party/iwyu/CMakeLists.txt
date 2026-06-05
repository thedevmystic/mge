# CMake file for IWYU (Include What You Use)

# If not set return
if(NOT MGE_USE_IWYU)
	return()
endif()

# Since include-what-you-use is tightly coupled with system libraries, we have to use
# system-installed version, compiling it on fly id not worth it.
message(STATUS "[MGE] - Searching for system-installed include-what-you-use...")
find_program(IWYU_LOCAL_PATH NAMES include-what-you-use iwyu)

# Check if it was found
if(IWYU_LOCAL_PATH)
  message(STATUS "[MGE] - System-installed include-what-you-use found.")
else()
	message(FATAL_ERROR "[MGE] - System-installed include-what-you-use was not found.")
endif()

# Configure arguments
message(STATUS "[MGE] - Configuring include-what-you-use...")

# Stores mappings into /iwyu_mappings in build dir
set(IWYU_MAPPINGS_DIR "${CMAKE_BINARY_DIR}/iwyu_mappings")

# Move Project's mappings
file(COPY "${CMAKE_SOURCE_DIR}/third_party/iwyu/mappings/"
 DESTINATION ${IWYU_MAPPINGS_DIR}
 FILES_MATCHING PATTERN "*.imp"
)

# Generate Standard Library mappings on fly
execute_process(
	COMMAND ${IWYU_LOCAL_PATH} --export_mappings ${IWYU_MAPPINGS_DIR}
	OUTPUT_QUIET
	ERROR_QUIET
)

# Configure iwyu mapping arguments
set(IWYU_LOCAL_ARGS
  "-Xiwyu" "--mapping_file=${IWYU_MAPPINGS_DIR}/iwyu.mge.imp"
)

# Based on Standard Library Vendor specify other entry point
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	list(APPEND IWYU_LOCAL_ARGS "-Xiwyu" "--mapping_file=${IWYU_MAPPINGS_DIR}/iwyu.msvc.imp")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	list(APPEND IWYU_LOCAL_ARGS "-Xiwyu" "--mapping_file=${IWYU_MAPPINGS_DIR}/iwyu.gcc.imp")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	list(APPEND IWYU_LOCAL_ARGS "-Xiwyu" "--mapping_file=${IWYU_MAPPINGS_DIR}/libcxx.imp")
else()
	message(FATAL_ERROR "[MGE] - Non supported compiler.")
endif()

# Promote to Global variables for later consumption in [ROOT]/CMakeLists.txt
set(IWYU_PATH "{LOCAL_IWYU_PATH}" CACHE INTERNAL "Path to IWYU executable.")
set(IWYU_ARGS "{LOCAL_IWYU_ARGS}" CACHE INTERNAL "Arguments given to IWYU executable.")

# IWYU is setup globally in [ROOT]/CMakeLists.txt, so we'll continue for now.
message(STATUS "[MGE] - Include-what-you-use configuration completed.")
