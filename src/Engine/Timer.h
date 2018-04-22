#ifndef ALOGDAT_LABYRINTH_TIMER_H
#define ALOGDAT_LABYRINTH_TIMER_H

#include <csignal>
#include <ctime>
#include <chrono>

#include "Platform.h"

template <int64_t res>
struct resolution {
    static constexpr int64_t value = res;
};

using nano = resolution<1000000000>;
using micro = resolution<1000000>;
using milli = resolution<1000>;
using centi = resolution<100>;
using second = resolution<1>;

template <typename platform> struct timer_traits;

template <>
struct timer_traits<windows> {
    using time_point = int64_t;
    using clock_period = int64_t;
    using duration = int64_t;

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

// TODO: Add MacOS to supported os

// TODO: Add C++ standard way for high-resolution timer
template <>
struct timer_traits<linux> {
    using time_point = int64_t;
    using clock_period = intmax_t;
    using duration = int64_t;

    static time_point now() {
        return std::chrono::system_clock::now().time_since_epoch().count();
    }

    static clock_period period() {
        return std::chrono::system_clock::period::den;
    }
};

template <typename Platform>
class timer_basic {
public:
    using traits = timer_traits<Platform>;
    using time_point = typename traits::time_point;
    using clock_period = typename traits::clock_period;
    using duration = typename traits::duration;

    explicit timer_basic(bool startNow = false) : m_start(0), m_end(0), m_running(false) {
        if (startNow)
            start();
    }

    void start() {
        if (m_running)
            return;
        m_running = true;
        m_start = traits::now();
    }

    void stop() {
        if (!m_running)
            return;
        m_running = false;
        m_end = traits::now();
    }

    template<typename T = double, typename Resolution = nano>
    T elapsedTime() const {
        if (m_running)
            return duration(0);
        clock_period period = traits::period();
        duration elapsed_time = ((m_end - m_start)*Resolution::value) / period;
        return static_cast<T>(elapsed_time);
    }

private:
    time_point m_start, m_end;
    bool m_running;
};


using stopwatch = timer_basic<platform_type>;

#endif //ALOGDAT_LABYRINTH_TIMER_H
