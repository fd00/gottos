#include <gottos.h>
#include <stdlib.h>

#define GOTTOS_PLUGIN_DIR ((const gchar*)"GOTTOS_PLUGIN_DIR")

typedef struct _Gottos
{
	GottosBackendType type;
	GottosMalloc malloc;
	GottosFree free;
	GottosRealloc realloc;
} _Gottos;

static GottosString _gottos_modules[] =
{ "malloc", "gc", "tcmalloc", };
#define GOTTOS_N_MODULES 3
static GModule* _gottos_handles[GOTTOS_N_MODULES];

static GottosBoolean _gottos_initialized = FALSE;
static GottosBoolean _gottos_finalized = FALSE;

static GModule*
_gottos_module_open(GottosString n)
{
	const gchar* bpd = g_getenv(GOTTOS_PLUGIN_DIR);
	GModule* g;
	gchar buf[PATH_MAX];

	if (bpd)
	{
		g_snprintf(buf, PATH_MAX, "%s%s%s", bpd, G_DIR_SEPARATOR_S, n);
		if ((g = g_module_open(buf, G_MODULE_BIND_MASK)))
		{
			return g;
		}
	}

	g_snprintf(buf, PATH_MAX, "%s%s%s", PKGLIBDIR, G_DIR_SEPARATOR_S, n);
	if ((g = g_module_open(buf, G_MODULE_BIND_MASK)))
	{
		return g;
	}

	return NULL;
}

GottosBoolean gottos_initialize()
{
	if (_gottos_initialized)
	{
		return FALSE;
	}
	for (int i = 0; i < GOTTOS_N_MODULES; i++)
	{
		if ((_gottos_handles[i] = _gottos_module_open(_gottos_modules[i])))
		{
			gpointer initialize;
			if (g_module_symbol(_gottos_handles[i], "gottos_backend_initialize",
					&initialize))
			{
				((void (*)()) initialize)();
			}
		}
	}
	return _gottos_initialized = TRUE;
}

GottosBoolean gottos_initialized()
{
	return _gottos_initialized;
}

GottosBoolean gottos_finalize()
{
	if (_gottos_finalized)
	{
		return FALSE;
	}
	for (int i = 0; i < GOTTOS_N_MODULES; i++)
	{
		if (_gottos_handles[i])
		{
			gpointer finalize;
			if (g_module_symbol(_gottos_handles[i], "gottos_backend_finalize",
					&finalize))
			{
				((void (*)()) finalize)();
			}
		}
	}
	return _gottos_finalized = TRUE;
}

GottosBoolean gottos_finalized()
{
	return _gottos_finalized;
}

Gottos gottos_new(GottosBackendType t)
{
	if (!_gottos_handles[t])
	{
		return NULL;
	}
	GModule* g = _gottos_handles[t];
	gpointer mallocFunction;
	if (!g_module_symbol(g, "gottos_backend_malloc", &mallocFunction))
	{
		return NULL;
	}
	gpointer freeFunction;
	if (!g_module_symbol(g, "gottos_backend_free", &freeFunction))
	{
		return NULL;
	}
	gpointer reallocFunction;
	if (!g_module_symbol(g, "gottos_backend_realloc", &reallocFunction))
	{
		return NULL;
	}

	Gottos gottos = ((GottosMalloc) mallocFunction)(sizeof(_Gottos));
	gottos->type = t;
	gottos->malloc = mallocFunction;
	gottos->free = freeFunction;
	gottos->realloc = reallocFunction;

	return gottos;
}

void*
gottos_malloc(Gottos gottos, size_t size)
{
	return gottos->malloc(size);
}

void gottos_free(Gottos gottos, void* ptr)
{
	gottos->free(ptr);
}

void*
gottos_realloc(Gottos gottos, void* ptr, size_t size)
{
	return gottos->realloc(ptr, size);
}
