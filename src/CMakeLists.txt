################################################################################
## File      : CMakeLists.txt
## Content   : src CMakeLists
##
## Author    : TheBigFred - thebigfred.github@gmail.com
## URL       : https://github.com/TheBigFred/libconsole
##
##-----------------------------------------------------------------------------
##  LGPL V3.0 - https://www.gnu.org/licences/lgpl-3.0.txt
##-----------------------------------------------------------------------------
################################################################################

# ==============================================================================
# == Main folder files
# ==============================================================================

list(APPEND PRIVATE_INC_FILES
)

list(APPEND PUBLIC_INC_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/console.h
   ${CMAKE_CURRENT_SOURCE_DIR}/hexa.h
   ${CMAKE_CURRENT_SOURCE_DIR}/init.h
   ${CMAKE_CURRENT_SOURCE_DIR}/manipulator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/menu.h
   ${CMAKE_CURRENT_SOURCE_DIR}/options.h
   ${CMAKE_CURRENT_SOURCE_DIR}/platform.h
   ${CMAKE_CURRENT_SOURCE_DIR}/read.h
   ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

list(APPEND SRC_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/hexa.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/init.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/menu.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/options.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/read.cpp
   ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
)

# ==============================================================================
# == Generate files
# ==============================================================================

configure_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/version.h.in
   ${CMAKE_CURRENT_BINARY_DIR}/version.h @ONLY
)
configure_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/version.cpp.in
   ${CMAKE_CURRENT_BINARY_DIR}/version.cpp @ONLY
)

# ==============================================================================
# == Define the project targets
# ==============================================================================

add_library(${LIBNAME_STATIC} STATIC
   ${PRIVATE_INC_FILES}
   ${PUBLIC_INC_FILES}
   ${SRC_FILES}
)

add_library(${LIBNAME_SHARED} SHARED
   ${PRIVATE_INC_FILES}
   ${PUBLIC_INC_FILES}
   ${SRC_FILES}
)

# ==============================================================================
# == Build flags
# ==============================================================================

libconsole_build_flags(${LIBNAME_STATIC})
libconsole_build_flags(${LIBNAME_SHARED})

target_compile_definitions(${LIBNAME_STATIC}
   PRIVATE
      EXPORT_STATIC_DEFINE
)

if(MSVC)
   set(STATIC_POSTFIX "s")
endif()

set_target_properties(${LIBNAME_STATIC}
   PROPERTIES
      POSITION_INDEPENDENT_CODE    YES
      OUTPUT_NAME      ${LIBNAME}${STATIC_POSTFIX}
      DEBUG_POSTFIX    "d"
)

set_target_properties(${LIBNAME_SHARED}
   PROPERTIES
      POSITION_INDEPENDENT_CODE  YES
      CXX_VISIBILITY_PRESET      hidden
      VISIBILITY_INLINES_HIDDEN  1
      SOVERSION        ${PROJECT_VERSION_MAJOR}
      VERSION          ${PROJECT_VERSION}
      OUTPUT_NAME      ${LIBNAME}
      DEBUG_POSTFIX    "d"
)

include(GenerateExportHeader)
generate_export_header(${LIBNAME_SHARED}
   EXPORT_FILE_NAME           "${CMAKE_CURRENT_SOURCE_DIR}/export.h"
   EXPORT_MACRO_NAME          EXPORT
   DEPRECATED_MACRO_NAME      DEPRECATED
   NO_EXPORT_MACRO_NAME       NO_EXPORT
   INCLUDE_GUARD_NAME         EXPORT_H
   STATIC_DEFINE              STATICLIB_DEFINE
   NO_DEPRECATED_MACRO_NAME   NO_DEPRECATED
)


# ==============================================================================
# == Linker
# ==============================================================================

target_link_libraries(${LIBNAME_STATIC}
   PUBLIC
      ${DEP_LIBS}
)

target_link_libraries(${LIBNAME_SHARED}
   PUBLIC
      ${DEP_LIBS}
)

# ==============================================================================
# == Install Directives
# ==============================================================================

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
   ${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
   INSTALL_DESTINATION cmake
)

if (DevelPackage)
install(
   FILES
      ${PUBLIC_INC_FILES}
      ${CMAKE_CURRENT_SOURCE_DIR}/export.h
   DESTINATION
      include/${PROJECT_NAME}
)

install(
   TARGETS
      ${LIBNAME_SHARED}
      ${LIBNAME_STATIC}
   EXPORT
      ${PROJECT_NAME}
   RUNTIME
      DESTINATION         ${CMAKE_INSTALL_BINDIR}
      COMPONENT           ${PROJECT_NAME}_RunTime
   LIBRARY
      DESTINATION         ${CMAKE_INSTALL_LIBDIR}
      COMPONENT           ${PROJECT_NAME}_RunTime
   ARCHIVE
      DESTINATION         ${CMAKE_INSTALL_LIBDIR}
      COMPONENT           ${PROJECT_NAME}_Development
)

install(
   EXPORT
      ${PROJECT_NAME}
   DESTINATION
      cmake
)

install(
   FILES
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
   DESTINATION
      cmake
)

install(
   FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/dependencies.cmake
   DESTINATION
      cmake
   RENAME
      ${PROJECT_NAME}_dependencies.cmake
)

else(DevelPackage)

if (STANDALONE_${PROJECT_NAME})
install(
   TARGETS
      ${LIBNAME_SHARED}
   EXPORT
      ${PROJECT_NAME}
   LIBRARY
      DESTINATION         ${CMAKE_INSTALL_LIBDIR}
      COMPONENT           ${PROJECT_NAME}_RunTime
)
endif()
endif(DevelPackage)

# ==============================================================================
# == Striping
# ==============================================================================

# if (${CMAKE_BUILD_TYPE} STREQUAL "Release" AND NOT MSVC)

# add_custom_command(TARGET ${LIBNAME_SHARED} POST_BUILD
#    COMMAND ${CMAKE_OBJCOPY} --only-keep-debug ${PROJECT_NAME}.so ${PROJECT_NAME}.so.debug
#    COMMAND ${CMAKE_OBJCOPY} --strip-debug ${PROJECT_NAME}.so
#    COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=${PROJECT_NAME}.so.debug ${PROJECT_NAME}.so
# )

# if (DevelPackage)
# install(
#    FILES
#       ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.so.debug
#    DESTINATION
#       ${CMAKE_INSTALL_LIBDIR}
# )
# endif(DevelPackage)
# endif()
