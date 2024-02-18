################################################################################
## File      : CMakeLists.txt
## Contents  : tests CMakeLists
##
## Author    : TheBigFred - thebigfred.github@gmail.com
## URL       : https://github.com/TheBigFred/libconsole
##
##-----------------------------------------------------------------------------
##  LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
##-----------------------------------------------------------------------------
################################################################################

include(../cmake/googletest.cmake)

# ==============================================================================
# == Define the project targets
# ==============================================================================

set(PROJECT_TESTS ${PROJECT_NAME}-tests)

add_executable(${PROJECT_TESTS}
   main.cpp
   options.cpp
)

add_test(
   NAME ${PROJECT_NAME}
   COMMAND $<TARGET_FILE:${PROJECT_TESTS}>
)

# ==============================================================================
# == Build flags
# ==============================================================================

libconsole_build_flags(${PROJECT_TESTS})

target_compile_definitions(${PROJECT_TESTS}
   PRIVATE
      STATICLIB_DEFINE
)

target_include_directories(${PROJECT_TESTS}
   PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src>
)

# ==============================================================================
# == Linker
# ==============================================================================

target_link_libraries(${PROJECT_TESTS}
   PRIVATE
      ${LIBNAME_STATIC}
      gtest
)
