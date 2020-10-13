# hook-cxa-throw
Hook __cxa_throw in gcc and clang with boost::stacktrace on linux (and msys2 on windows with dlfcn).

# Boost Stacktrace
Dont forget that you have to configure boost stacktrace.
https://www.boost.org/doc/libs/1_74_0/doc/html/stacktrace/configuration_and_build.html

# Msys2
Need libbacktrace and 
https://packages.msys2.org/package/mingw-w64-x86_64-dlfcn?repo=mingw64

# Example
```C++
#include <hook-cxa-throw/hook_cxa_throw.hpp>
#include <stdexcept>

// provide handler function.
// its called when an exception occurs.
void onThrow(boost::stacktrace::stacktrace& strace)
{
    std::cerr << strace << "\n";
}

int main()
{
    throw std::runtime_error("bla");
}
```
