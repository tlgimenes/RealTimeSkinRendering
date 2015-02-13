# - Try to find libJPEG
# This module tries to find the libjpeg in your system. It was tested on the following systems
#
# Arch Linux - Kernel 3.18.6-1
#
# To set manually the paths, define these environment variables:
# jpeg_INCPATH    - Include path (e.g. jpeg_INCPATH=/usr/include)
# jpeg_LIBPATH    - Library path (e.h. jpeg_LIBPATH=/usr/lib)
#
# Once done this will define
#  LIBJPEG_FOUND - System has libjpeg
#  LIBJPEG_INCLUDE_DIRS - The libjpeg include directories
#  LIBJPEG_LIBRARIES - The libraries needed to use libjpeg
#  LIBJPEG_DEFINITIONS - Compiler switches required for using libjpeg


FIND_PACKAGE(PkgConfig)

SET (JPEG_VERSION_STRING "0.1-1")
SET (JPEG_VERSION_MAJOR 0)
SET (JPEG_VERSION_MINOR 1)
SET (JPEG_VERSION_PATCH 0)

pkg_check_modules(JPEG QUIET jpeg)
set(LIBJPEG_DEFINITIONS ${JPEG_CFLAGS_OTHER})

find_path(LIBJPEG_INCLUDE_DIR jpeglib.h
    HINTS ${LIBJPEG_INCLUDEDIR} ${LIBJPEG_INCLUDE_DIRS}
    PATH_SUFFIXES libjpeg )

find_library(LIBJPEG_LIBRARY NAMES jpeg 
    HINTS ${PC_LIBJPEG_LIBDIR} ${PC_LIBJPEG_LIBRARY_DIRS})

set(LIBJPEG_LIBRARIES ${LIBJPEG_LIBRARY})
set(LIBJPEG_INCLUDE_DIRS ${LIBJPEG_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBJPEG_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(jpeg  DEFAULT_MSG
    LIBJPEG_LIBRARY LIBJPEG_INCLUDE_DIR)

mark_as_advanced(LIBJPEG_INCLUDE_DIR LIBJPEG_LIBRARY)

