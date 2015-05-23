
TEST_PROGS = malloc
check_PROGRAMS = $(TEST_PROGS)

malloc_CFLAGS = $(GLIB_CFLAGS)
malloc_CPPFLAGS = -I$(top_srcdir)/include
malloc_LDADD = $(top_builddir)/lib/libgottos.la
malloc_SOURCES = malloc.c

if USE_GC
TEST_PROGS += gc
gc_CFLAGS = $(GLIB_CFLAGS) $(GC_CFLAGS)
gc_CPPFLAGS = -I$(top_srcdir)/include
gc_LDADD = $(top_builddir)/lib/libgottos.la
gc_SOURCES = gc.c
endif

check: $(TEST_PROGS)
	GOTTOS_PLUGIN_DIR=$(top_builddir)/module gtester --verbose $(TEST_PROGS)
