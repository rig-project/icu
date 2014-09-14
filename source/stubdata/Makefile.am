
AM_CPPFLAGS = \
	-I$(top_srcdir) \
	-I$(top_builddir) \
	$(U_CPPFLAGS)

AM_CFLAGS = $(U_CFLAGS)

lib_LTLIBRARIES = libicudata.la

libicudata_la_LIBADD =
libicudata_la_LDFLAGS = -release $(U_MAJOR_VERSION).$(U_MINOR_VERSION)
libicudata_la_SOURCES = stubdata.c
