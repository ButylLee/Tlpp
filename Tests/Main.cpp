#include <Tlpp/Config.h>
#include <Tlpp/Test/Test.hpp>

#ifdef TLPP_WIN
#include <crtdbg.h>
#include <cassert>
#include <cstdlib>
#endif

#ifdef TLPP_MSVC
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#ifdef TLPP_WIN
	assert(!std::atexit([] { assert(!_CrtDumpMemoryLeaks()); }));
#endif
	return tl::test::Test::RunAndDispose(argc, argv);
}