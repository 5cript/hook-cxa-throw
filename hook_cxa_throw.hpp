#pragma once

#include <dlfcn.h>
#include <boost/stacktrace.hpp>

#include <cstddef>
#include <exception>

extern void onThrow(boost::stacktrace::stacktrace& strace);

#ifdef __GNUC__
typedef void __attribute__((__noreturn__)) (*cxa_throw_type)(void*, void*, void(*)(void*));
#elif defined(__clang__)
typedef void __attribute__((__noreturn__)) (*cxa_throw_type)(void*, std::type_info*, void (_GLIBCXX_CDTOR_CALLABI*) (void*));
#endif
cxa_throw_type orig_cxa_throw = nullptr;

void load_orig_throw_code()
{
    orig_cxa_throw = (cxa_throw_type) dlsym(RTLD_NEXT, "__cxa_throw");
}

extern "C"
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#ifdef __clang__
void __cxa_throw(void* thrown_exception, std::type_info* typeifo, void (_GLIBCXX_CDTOR_CALLABI* dest)(void*))
#elif defined(__GNUC__)
void __cxa_throw(void* thrown_exception, void* pvtinfo, void (*dest)(void *))
#endif
{
    if (orig_cxa_throw == nullptr)
        load_orig_throw_code();

    {
        auto strace = boost::stacktrace::stacktrace();
        onThrow(strace);
    }

#ifdef __clang__
    orig_cxa_throw(thrown_exception, typeifo, dest);
#elif defined(__GNUC__)
    orig_cxa_throw(thrown_exception, pvtinfo, dest);
#endif
}
