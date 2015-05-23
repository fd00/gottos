
pkglib_LTLIBRARIES = malloc.la

malloc_la_CFLAGS = $(GLIB_CFLAGS)
malloc_la_CPPFLAGS = -I$(top_srcdir)/include
malloc_la_LDFLAGS = -no-undefined -module -avoid-version
malloc_la_LIBADD = $(GLIB_LIBS)
malloc_la_SOURCES = malloc.c

if USE_GC
pkglib_LTLIBRARIES += gc.la
gc_la_CFLAGS = $(GC_CFLAGS) $(GLIB_CFLAGS)
gc_la_CPPFLAGS = -I$(top_srcdir)/include
gc_la_LDFLAGS = -no-undefined -module -avoid-version
gc_la_LIBADD = $(GC_LIBS) $(GLIB_LIBS)
gc_la_SOURCES = gc.c
endif
