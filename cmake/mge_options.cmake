# CMake file to define options

# Project Options
option(MGE_ENABLE_COVERAGE "Build code coverage." OFF)
option(MGE_ENABLE_DOCS     "Build documentation." ON)
option(MGE_ENABLE_TESTING  "Build test suites."   ON)

# Third Party Libraries Options
# Catch2
option(MGE_USE_SYSTEM_CATCH2 "Use system-installed Catch2 v3." OFF)
# IWYU
option(MGE_USE_IWYU "Use include-what-you-use (only supports system-installed)." OFF)
