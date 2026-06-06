# -------------------------------------------------------------------------------------------------
# MGE Core Target
# -------------------------------------------------------------------------------------------------
add_library(mge_core STATIC
  # -----------------------------------------------------------------------------------------------
  # Dummy
  # -----------------------------------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/public/header.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/private/header.cpp
  # -----------------------------------------------------------------------------------------------
	# Common
  # -----------------------------------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/public/common/api.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/common/attributes.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/common/byte.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/common/types.hpp
  # -----------------------------------------------------------------------------------------------
	# HAL
  # -----------------------------------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/public/hal/architecture.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/hal/compiler.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/hal/platform.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/hal/platform_types.hpp
)
add_library(MGE::Core ALIAS mge_core)

# -------------------------------------------------------------------------------------------------
# Include Directories (Public boundaries)
# -------------------------------------------------------------------------------------------------
target_include_directories(mge_core
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
  add_executable(mge_core_tests
    # ---------------------------------------------------------------------------------------------
    # Dummy
    # ---------------------------------------------------------------------------------------------
    test/header.test.cpp
    # ---------------------------------------------------------------------------------------------
    # Common
    # ---------------------------------------------------------------------------------------------
    test/common/types.test.cpp
    test/common/byte.test.cpp
  )

  target_link_libraries(mge_core_tests
    PRIVATE
      MGE::Core
      Catch2::Catch2WithMain
  )

  # Register with CTest
  add_test(NAME mge_core_tests COMMAND mge_core_tests)

  # Add Coverage
  include(mge_coverage)
  mge_coverage(mge_core mge_core_tests)
endif()
