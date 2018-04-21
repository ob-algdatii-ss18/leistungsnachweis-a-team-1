#ifndef ALOGDAT_LABYRINTH_TIMER_H
#define ALOGDAT_LABYRINTH_TIMER_H

#include <csignal>
#include <ctime>
#include <windows.h>
#include <chrono>

template <typename Period, typename Watch>
class basic_stopwatch {
public:
    using watch_traits = typename Watch::traits;
    using time_point = typename watch_traits::time_point;
    using clock_period = typename watch_traits::clock_period;
    using period = Period;
    using duration = std::chrono::duration<double, period>;

    explicit basic_stopwatch(bool startNow = false) : m_start(0), m_end(0), m_period(0), m_running(false) {
        if (startNow)
            start();
    }

    void start() {
        if (m_running)
            return;
        m_running = true;
        m_period = Watch::period();
        m_start = Watch::now();
    }

    void stop() {
        if (!m_running)
            return;
        m_running = false;
        m_end = Watch::now();
    }

    duration elapsedTime() const {
        if (m_running)
            return duration(0);
        time_point diff = m_end - m_start;
        diff *= period::den;
        duration elapsed_time(diff / m_period);
        return elapsed_time;
    }

private:
    time_point m_start, m_end;
    clock_period m_period;
    bool m_running;
};

struct stopwatch_windows_traits {
    using time_point = __int64;
    using clock_period = __int64;
};

class stopwatch_windows
{
public:
    using traits = stopwatch_windows_traits;
    using time_point = typename traits::time_point;
    using clock_period = typename traits::clock_period ;

    static clock_period period() {
        clock_period clockPeriod;
        QueryPerformanceFrequency(reinterpret_cast<PLARGE_INTEGER>(&clockPeriod));
        return clockPeriod;
    }

    static time_point now() {
        time_point point;
        QueryPerformanceCounter(reinterpret_cast<PLARGE_INTEGER>(&point));
        return point;
    }
};

// TODO: Add Linux to supported os

// TODO: Add C++ standard way for high-resolution timer

// TODO: Logic to choose right stopwatch based on underlying operating system
template <typename Period>
using stopwatch = basic_stopwatch<Period, stopwatch_windows>;

#endif //ALOGDAT_LABYRINTH_TIMER_H
