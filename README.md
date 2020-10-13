# hook-cxa-throw
Hook __cxa_throw in gcc and clang with boost::stacktrace on linux (and msys2 on windows with dlfcn).

# Boost Stacktrace
Dont forget that you have to configure boost stacktrace.
https://www.boost.org/doc/libs/1_74_0/doc/html/stacktrace/configuration_and_build.html

# Example
```C++
#include <hook-cxa-throw/hook_cxa_throw.hpp>
#include <stdexcept>

// provide handler function.
// its called when an exception occurs.
void onThrow(boost::stacktrace::stacktrace& strace)
{
    std::cout << strace << "\n";
}

int main()
{
    throw std::runtime_error("bla");
}
```