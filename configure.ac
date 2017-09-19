# Copyright 2017
#   Pawel Herman - Karlsruhe Institute of Technology - pherman@ira.uka.de
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

AC_INIT(libhappah-graphics, 0.0, pherman@ira.uka.de)
AC_CONFIG_AUX_DIR(build)
AC_CONFIG_MACRO_DIR(m4)
AC_ENABLE_SHARED
AC_DISABLE_STATIC

AM_INIT_AUTOMAKE(foreign subdir-objects)

LT_INIT

AC_PROG_CXX
AM_PROG_LIBTOOL
PKG_PROG_PKG_CONFIG

AC_LANG_PUSH([C++])
AC_CHECK_HEADER([happah/Happah.hpp], [], [AC_MSG_ERROR([Could not find happah/Happah.hpp])])
AC_LANG_POP([C++])
AX_BOOST_BASE([1.62])
AX_BOOST_IOSTREAMS
AX_BOOST_PROGRAM_OPTIONS
#PKG_CHECK_MODULES([happah], [happah])

AC_CONFIG_FILES(Makefile lib/Makefile)
AC_OUTPUT

