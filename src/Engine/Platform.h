#ifndef ALOGDAT_LABYRINTH_PLATFORM_H
#define ALOGDAT_LABYRINTH_PLATFORM_H

struct windows {};
struct macosx {};
struct linux {};

#if !defined(WIN32)
    void QueryPerformanceCounter(void*);
    void QueryPerformanceFrequency(void*)
    union LARGE_INTEGER;
    typedef LARGE_INTEGER PLARGE_INTEGER;
#endif

#if defined(WIN32)
#include <windows.h>
using platform_type = windows;
#elif defined(__APPLE__)
using platform_type = macosx;
#else
using platform_type = linux;
#endif

#endif //ALOGDAT_LABYRINTH_PLATFORM_H
