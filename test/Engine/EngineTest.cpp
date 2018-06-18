#include <Timer.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "EngineTest.h"

/*TEST_F(EngineTest, TimerStart) {
    stopwatch watch;
    watch.start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    watch.stop();
    EXPECT_DOUBLE_EQ(std::round(watch.elapsedTime<double, centi>()/100.0), 3);
}*/