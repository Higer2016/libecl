#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ecl" for configuration "Release"
set_property(TARGET ecl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ecl PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/ecl.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libecl.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ecl )
list(APPEND _IMPORT_CHECK_FILES_FOR_ecl "${_IMPORT_PREFIX}/lib/ecl.lib" "${_IMPORT_PREFIX}/bin/libecl.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
