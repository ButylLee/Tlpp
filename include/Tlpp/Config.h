#ifndef TLPP_CONFIG_H
#define TLPP_CONFIG_H

#if defined _WIN64 || defined __x86_64__ || defined __LP64__
#define TLPP_64
#endif

#ifndef TLPP_TEST_CONFIG

#if defined _MSC_VER
#define TLPP_MSVC
#elif defined __clang__
#define TLPP_CLANG
#elif defined __ICC || defined __ICL || defined __INTEL_
#define TLPP_ICC
#elif defined __GNUC__
#define TLPP_GCC
#else
#error "Unknown Compiler"
#endif

#if defined WIN32 || defined _WIN32 || defined _WIN64 || defined __MINGW32__
#define TLPP_WIN
#elif defined linux || defined __linux || defined __linux__
#define TLPP_LINUX
#elif defined __APPLE__
#define TLPP_APPLE
#endif

#endif // TLPP_TEST_CONFIG

#if !defined NDEBUG || defined _DEBUG
#define TLPP_DEBUG
#endif

#endif // TLPP_CONFIG_H