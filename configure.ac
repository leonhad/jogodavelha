AC_PREREQ(2.61)
AC_INIT([jogodavelha], [1.0.0], [leonhad@gmail.com])
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_HOST

# Checks for programs.
DEBUG_CFLAGS="-O2 -DNDEBUG"
dnl This mechanism allows one to enable debug compilations...
AC_ARG_ENABLE(debug,
[  --enable-debug     enable debugging and disable optimization],
[  if test "$enable_debug" = "yes"; then
      DEBUG_CFLAGS="-Wall -g3 -DDEBUG"
   fi
]
)
AM_CONDITIONAL(ENABLE_DEBUG, test "$enable_debug" = "yes")
CXXFLAGS="$DEBUG_CFLAGS $CXXFLAGS"

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for library functions.
AX_CHECK_GL
AX_CHECK_GLU
AM_PATH_SDL([2.0.0])

AC_CONFIG_FILES([Makefile
                 src/Makefile
])
AC_OUTPUT
