AC_PREREQ([2.69])
AC_INIT([gottos], [0.0.1])
AC_CONFIG_SRCDIR([include/gottos.h])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign])

AC_PROG_CC
LT_INIT

PKG_CHECK_MODULES([GLIB], [glib-2.0 gmodule-2.0])

PKG_CHECK_MODULES([GC], [bdw-gc], [use_gc=yes], [use_gc=no])
AM_CONDITIONAL(USE_GC, test x$use_gc = xyes)

AC_CHECK_HEADERS([stdlib.h])

AC_TYPE_SIZE_T

AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 lib/Makefile
                 module/Makefile
                 test/Makefile
                 gottos.pc])
AC_OUTPUT
