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
  # -----------------------------------------------------------------------------------------------
  # Traits
  # -----------------------------------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/public/traits/core.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/traits/cv_traits.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/traits/logical_operators.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/traits/member_introspection.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/traits/pointer_transformations.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/traits/primary_classification.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/traits/reference_transformations.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/public/traits/secondary_classification.hpp
  # -----------------------------------------------------------------------------------------------
  # Utility
  # -----------------------------------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/public/utility/declval.hpp
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
    # -----------------------------------------------------------------------------------------------
    # Traits
    # -----------------------------------------------------------------------------------------------
    test/traits/core.test.cpp
    test/traits/cv_traits.test.cpp
    test/traits/logical_operators.test.cpp
    test/traits/member_introspection.test.cpp
    test/traits/primary_classification.test.cpp
    test/traits/pointer_transformations.test.cpp
    test/traits/reference_transformations.test.cpp
    test/traits/secondary_classification.test.cpp
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
