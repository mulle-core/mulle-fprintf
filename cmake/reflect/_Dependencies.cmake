# This file will be regenerated by `mulle-sourcetree-to-cmake` via
# `mulle-sde reflect` and any edits will be lost.
#
# This file will be included by cmake/share/Files.cmake
#
# Disable generation of this file with:
#
# mulle-sde environment set MULLE_SOURCETREE_TO_CMAKE_DEPENDENCIES_FILE DISABLE
#
if( MULLE_TRACE_INCLUDE)
   message( STATUS "# Include \"${CMAKE_CURRENT_LIST_FILE}\"" )
endif()

#
# Generated from sourcetree: 9B1EEDAF-5103-4E5C-B280-25EB86FCA40E;mulle-sprintf;no-cmake-loader,no-cmake-searchpath,no-import,no-singlephase;
# Disable with : `mulle-sourcetree mark mulle-sprintf no-link`
# Disable for this platform: `mulle-sourcetree mark mulle-sprintf no-cmake-platform-${MULLE_UNAME}`
# Disable for a sdk: `mulle-sourcetree mark mulle-sprintf no-cmake-sdk-<name>`
#
if( NOT MULLE_SPRINTF_LIBRARY)
   if( DEPENDENCY_IGNORE_SYSTEM_LIBARIES)
      find_library( MULLE_SPRINTF_LIBRARY NAMES
         ${CMAKE_STATIC_LIBRARY_PREFIX}mulle-sprintf${CMAKE_DEBUG_POSTFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}
         ${CMAKE_STATIC_LIBRARY_PREFIX}mulle-sprintf${CMAKE_STATIC_LIBRARY_SUFFIX}
         mulle-sprintf
         NO_CMAKE_SYSTEM_PATH NO_SYSTEM_ENVIRONMENT_PATH
      )
   else()
      find_library( MULLE_SPRINTF_LIBRARY NAMES
         ${CMAKE_STATIC_LIBRARY_PREFIX}mulle-sprintf${CMAKE_DEBUG_POSTFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}
         ${CMAKE_STATIC_LIBRARY_PREFIX}mulle-sprintf${CMAKE_STATIC_LIBRARY_SUFFIX}
         mulle-sprintf
      )
   endif()
   message( STATUS "MULLE_SPRINTF_LIBRARY is ${MULLE_SPRINTF_LIBRARY}")
   #
   # The order looks ascending, but due to the way this file is read
   # it ends up being descending, which is what we need.
   #
   if( MULLE_SPRINTF_LIBRARY)
      #
      # Add MULLE_SPRINTF_LIBRARY to ALL_LOAD_DEPENDENCY_LIBRARIES list.
      # Disable with: `mulle-sourcetree mark mulle-sprintf no-cmake-add`
      #
      list( APPEND ALL_LOAD_DEPENDENCY_LIBRARIES ${MULLE_SPRINTF_LIBRARY})
      #
      # Inherit information from dependency.
      # Encompasses: no-cmake-searchpath,no-cmake-dependency,no-cmake-loader
      # Disable with: `mulle-sourcetree mark mulle-sprintf no-cmake-inherit`
      #
      # temporarily expand CMAKE_MODULE_PATH
      get_filename_component( _TMP_MULLE_SPRINTF_ROOT "${MULLE_SPRINTF_LIBRARY}" DIRECTORY)
      get_filename_component( _TMP_MULLE_SPRINTF_ROOT "${_TMP_MULLE_SPRINTF_ROOT}" DIRECTORY)
      #
      #
      # Search for "Definitions.cmake" and "DependenciesAndLibraries.cmake" to include.
      # Disable with: `mulle-sourcetree mark mulle-sprintf no-cmake-dependency`
      #
      foreach( _TMP_MULLE_SPRINTF_NAME "mulle-sprintf")
         set( _TMP_MULLE_SPRINTF_DIR "${_TMP_MULLE_SPRINTF_ROOT}/include/${_TMP_MULLE_SPRINTF_NAME}/cmake")
         # use explicit path to avoid "surprises"
         if( IS_DIRECTORY "${_TMP_MULLE_SPRINTF_DIR}")
            list( INSERT CMAKE_MODULE_PATH 0 "${_TMP_MULLE_SPRINTF_DIR}")
            #
            include( "${_TMP_MULLE_SPRINTF_DIR}/DependenciesAndLibraries.cmake" OPTIONAL)
            #
            list( REMOVE_ITEM CMAKE_MODULE_PATH "${_TMP_MULLE_SPRINTF_DIR}")
            #
            unset( MULLE_SPRINTF_DEFINITIONS)
            include( "${_TMP_MULLE_SPRINTF_DIR}/Definitions.cmake" OPTIONAL)
            list( APPEND INHERITED_DEFINITIONS ${MULLE_SPRINTF_DEFINITIONS})
            break()
         else()
            message( STATUS "${_TMP_MULLE_SPRINTF_DIR} not found")
         endif()
      endforeach()
   else()
      # Disable with: `mulle-sourcetree mark mulle-sprintf no-require-link`
      message( FATAL_ERROR "MULLE_SPRINTF_LIBRARY was not found")
   endif()
endif()
