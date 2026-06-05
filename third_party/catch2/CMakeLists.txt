# CMake file for Catch2 v3

# Build Options
set(CATCH_INSTALL_DOCS  OFF CACHE INTERNAL "")
set(CATCH_BUILD_TESTING OFF CACHE INTERNAL "")
set(CATCH_ENABLE_WERROR OFF CACHE INTERNAL "")

include(mge_third_party_config)
mge_third_party_config("Catch2" "v3.4.0" "https://github.com/catchorg/Catch2.git")
