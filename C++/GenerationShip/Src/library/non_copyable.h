#ifndef __Generation_Ship__NonCopyable__
#define __Generation_Ship__NonCopyable__

#include <stdio.h>

class NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
    
    NonCopyable(NonCopyable const &) = delete;
    void operator=(NonCopyable const &x) = delete;
};

#endif