# -------------------------------------------------------------------------------------------------
# MGE Core Target
# -------------------------------------------------------------------------------------------------
add_library(MGE_Core INTERFACE)
add_library(MGE::Core ALIAS MGE_Core)

target_sources(MGE_Core INTERFACE
  # -----------------------------------------------------------------------------------------------
	# Common
  # -----------------------------------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/public/common/types.hpp
  # -----------------------------------------------------------------------------------------------
	# HAL
  # -----------------------------------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/public/hal/architecture.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/hal/compiler.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/hal/platform.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/hal/platform_types.hpp
)

# -------------------------------------------------------------------------------------------------
# Include Directories (Public boundaries)
# -------------------------------------------------------------------------------------------------
target_include_directories(MGE_Core
  INTERFACE
	  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
)

if(MGE_ENABLE_TESTING)
  # -----------------------------------------------------------------------------------------------
  # Core Unit Tests
  # -----------------------------------------------------------------------------------------------
  add_executable(MGE_Core_Tests
    # ---------------------------------------------------------------------------------------------
    # Common
    # ---------------------------------------------------------------------------------------------
    test/common/types.test.cpp
  )

  target_link_libraries(MGE_Core_Tests
    PRIVATE
      MGE::Core
      Catch2::Catch2WithMain
  )

  # Register with CTest
  add_test(NAME MGE_Core_Tests COMMAND MGE_Core_Tests)
endif()
