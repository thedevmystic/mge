# CMake file to define Coverage helper

function(mge_coverage MAIN_TARGET)
  if(MGE_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")

      target_compile_options(${MAIN_TARGET} PUBLIC --coverage -O0 -g)
      target_link_options(${MAIN_TARGET} PUBLIC --coverage)

      foreach(target IN LISTS ARGN)
        target_compile_options(${target} PRIVATE --coverage -O0 -g)
        target_link_options(${target} PRIVATE --coverage)
      endforeach()

    else()
      message(WARNING "[MGE] - Coverage is only supported in Clang and GCC. Disabling 'MGE_ENABLE_COVERAGE'...")
      set(MGE_ENABLE_COVERAGE OFF CACHE BOOL "" FORCE)
    endif()
  endif()
endfunction()
