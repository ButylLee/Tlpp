#ifndef TLPP_CONFIG_H
#define TLPP_CONFIG_H

#ifdef _WIN64 || __x86_64__ || __LP64__
#define TLPP_64
#endif

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

#if defined _WIN32 || defined _WIN64
#define TLPP_WIN
#elif defined __linux__
#define TLPP_LINUX
#elif defined __APPLE__
#define TLPP_APPLE
#endif

#if !defined NDEBUG || defined _DEBUG
#define TLPP_DEBUG
#endif

#endif // TLPP_CONFIG_H