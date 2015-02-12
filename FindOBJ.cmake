# - Try to find libOBJ
# This module tries to find the libobj in your system. It was tested on the following systems
#
# Arch Linux - Kernel 3.18.6-1
#
# To set manually the paths, define these environment variables:
# obj_INCPATH    - Include path (e.g. obj_INCPATH=/usr/include)
# obj_LIBPATH    - Library path (e.h. obj_LIBPATH=/usr/lib)
#
# Once done this will define
#  LIBOBJ_FOUND - System has libobj
#  LIBOBJ_INCLUDE_DIRS - The libobj include directories
#  LIBOBJ_LIBRARIES - The libraries needed to use libobj
#  LIBOBJ_DEFINITIONS - Compiler switches required for using libobj


FIND_PACKAGE(PkgConfig)

SET (OBJ_VERSION_STRING "0.1-1")
SET (OBJ_VERSION_MAJOR 0)
SET (OBJ_VERSION_MINOR 1)
SET (OBJ_VERSION_PATCH 0)

pkg_check_modules(OBJ QUIET obj)
set(LIBOBJ_DEFINITIONS ${OBJ_CFLAGS_OTHER})

find_path(LIBOBJ_INCLUDE_DIR obj.hpp
    HINTS ${LIBOBJ_INCLUDEDIR} ${LIBOBJ_INCLUDE_DIRS}
    PATH_SUFFIXES libobj )

find_library(LIBOBJ_LIBRARY NAMES obj 
    HINTS ${PC_LIBOBJ_LIBDIR} ${PC_LIBOBJ_LIBRARY_DIRS})

set(LIBOBJ_LIBRARIES ${LIBOBJ_LIBRARY})
set(LIBOBJ_INCLUDE_DIRS ${LIBOBJ_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBOBJ_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(obj  DEFAULT_MSG
    LIBOBJ_LIBRARY LIBOBJ_INCLUDE_DIR)

mark_as_advanced(LIBOBJ_INCLUDE_DIR LIBOBJ_LIBRARY)

