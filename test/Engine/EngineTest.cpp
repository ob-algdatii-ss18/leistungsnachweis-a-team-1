#include "EngineTest.h"
#include <Graph.h>

extern int add(int a, int b);
extern int complicated(int a);

TEST_F(EngineTest, ByDefaultTrue) {
    ASSERT_THAT(add(1, 2), 3);
}

TEST_F(EngineTest, Complicated) {
    ASSERT_TRUE(complicated(3) == 4);
}
