#if !defined(GOTTOS_H)
#define GOTTOS_H

#include <gmodule.h>

typedef enum
{
	GOTTOS_BACKEND_MALLOC = 0, GOTTOS_BACKEND_GC = 1,
} GottosBackendType;

typedef void*
(*GottosMalloc)(size_t);
typedef void
(*GottosFree)(void *);
typedef void*
(*GottosRealloc)(void *, size_t);

typedef gboolean GottosBoolean;
typedef gchar* GottosString;
typedef GModule* GottosModule;
typedef struct _Gottos *Gottos;

GottosBoolean
gottos_initialize();
GottosBoolean
gottos_initialized();
GottosBoolean
gottos_finalize();
GottosBoolean
gottos_finalized();

Gottos
gottos_new(GottosBackendType);
void*
gottos_malloc(Gottos, size_t);
void
gottos_free(Gottos, void*);
void*
gottos_realloc(Gottos, void*, size_t);

#endif
