#include "interface.h"
#include <stdlib.h>

void gottos_backend_initialize()
{

}

void gottos_backend_finalize()
{

}

void* gottos_backend_malloc(size_t size)
{
	return malloc(size);
}

void gottos_backend_free(void* ptr)
{
	free(ptr);
}

void* gottos_backend_realloc(void* ptr, size_t size)
{
	return realloc(ptr, size);
}
