# -------------------------------------------------------------------------------------------------
# MGE Core Target
# -------------------------------------------------------------------------------------------------
add_library(MGE_Core STATIC
  # -----------------------------------------------------------------------------------------------
  # Dummy
  # -----------------------------------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/public/header.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/private/header.cpp
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
add_library(MGE::Core ALIAS MGE_Core)

# -------------------------------------------------------------------------------------------------
# Include Directories (Public boundaries)
# -------------------------------------------------------------------------------------------------
target_include_directories(MGE_Core
  PUBLIC
	  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/private
)

if(MGE_ENABLE_TESTING)
  # -----------------------------------------------------------------------------------------------
  # Core Unit Tests
  # -----------------------------------------------------------------------------------------------
  add_executable(MGE_Core_Tests
    # ---------------------------------------------------------------------------------------------
    # Dummy
    # ---------------------------------------------------------------------------------------------
    test/header.test.cpp
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
