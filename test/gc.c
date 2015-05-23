#include <gottos.h>

void test(void)
{
	g_assert_false(gottos_initialized());
	gottos_initialize();
	g_assert_true(gottos_initialized());
	Gottos g = gottos_new(GOTTOS_BACKEND_GC);
	g_assert_nonnull(g);
	GottosMalloc p = gottos_malloc(g, PATH_MAX);
	g_assert_nonnull(p);
	g_assert_false(gottos_finalized());
	gottos_finalize();
	g_assert_true(gottos_finalized());
}

int main(int argc, char** argv)
{
	g_test_init(&argc, &argv, NULL);
	g_test_add_func("/gc/test", test);
	g_test_run();
}
