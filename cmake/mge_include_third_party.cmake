# Runs every third party directory's CMakeLists.txt

function(mge_include_third_party ROOT_DIR)
    set(LICENSE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/licenses")
    
    message(STATUS "[MGE] - Scanning for third-party libraries in: ${ROOT_DIR}...")

    # Find all CMakeLists.txt files recursively in third_party
    file(GLOB_RECURSE CMAK_FILES RELATIVE "${ROOT_DIR}" "${ROOT_DIR}/**/CMakeLists.txt")

    foreach(CMAKE_FILE IN LISTS CMAK_FILES)
        # Get the relative directory path (e.g., "libfoo" out of "libfoo/CMakeLists.txt")
        get_filename_component(SUB_DIR "${CMAKE_FILE}" DIRECTORY)
        
        # Skip the root directory itself if it accidentally matches
        if(SUB_DIR STREQUAL "")
            continue()
        endif()

        set(FULL_SUB_DIR_PATH "${ROOT_DIR}/${SUB_DIR}")
        get_filename_component(DIR_NAME "${SUB_DIR}" NAME)

        message(STATUS "[MGE] - Processing third-party library: ${DIR_NAME}")

        # Add the subdirectory to the build layout
        add_subdirectory("${FULL_SUB_DIR_PATH}" "${CMAKE_BINARY_DIR}/third_party/${DIR_NAME}")

        # Find and copy the License file (matching *LICENSE*)
        file(GLOB LICENSE_FILES "${FULL_SUB_DIR_PATH}/*LICENSE*")

        foreach(LICENSE_FILE IN LISTS LICENSE_FILES)
            get_filename_component(LICENSE_FILENAME "${LICENSE_FILE}" NAME)
            
            # Copy the license file to the build directory immediately
            configure_file("${LICENSE_FILE}" "${LICENSE_OUTPUT_DIR}/${LICENSE_FILENAME}" COPYONLY)
        endforeach()
    endforeach()
endfunction()
