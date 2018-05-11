#ifndef ALOGDAT_LABYRINTH_PLATFORM_H
#define ALOGDAT_LABYRINTH_PLATFORM_H

struct windows_tag {};
struct macosx_tag {};
struct linux_tag {};

#if !defined(WIN32)
    void QueryPerformanceCounter(void*);
    void QueryPerformanceFrequency(void*);
    typedef void* PLARGE_INTEGER;
#endif

#if !defined(__linux__)
    void gettimeofday(void *, void*);
#endif

#if !defined(__APPLE__)
#endif

#if defined(WIN32)
    #include <windows.h>
    using platform_type = windows_tag;
#elif defined(__APPLE__)
    using platform_type = macosx_tag;
#else
    #include <sys/time.h>
    using platform_type = linux_tag;
#endif

#endif //ALOGDAT_LABYRINTH_PLATFORM_H
