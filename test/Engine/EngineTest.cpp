#include "EngineTest.h"
#include <Graph.h>
#include <Timer.h>
#include <thread>
#include <chrono>
#include <iostream>

TEST_F(EngineTest, TimerStart) {
    stopwatch<std::ratio<1,100>> watch;
    watch.start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    watch.stop();
    EXPECT_DOUBLE_EQ(std::round(watch.elapsedTime().count()/100), 3);
}

