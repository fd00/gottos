#include "interface.h"
#include <gc.h>

void gottos_backend_initialize()
{
	GC_INIT();
}

void gottos_backend_finalize()
{

}

void*
gottos_backend_malloc(size_t size)
{
	return GC_malloc(size);
}

void gottos_backend_free(void* ptr)
{
	GC_free(ptr);
}

void*
gottos_backend_realloc(void* ptr, size_t size)
{
	return GC_realloc(ptr, size);
}
