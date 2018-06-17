#include "PriorityQueueTest.h"

#include <LowPriorityQueue.h>

TEST_F(PriorityQueueTest, insert) {
    std::vector<int> data;
    data.push_back(6);
    data.push_back(4);
    PriorityQueue<int> q(data, 10);

    q.insert(1);
    q.insert(12);
    q.insert(10);
    q.insert(6);
    q.insert(3);

    for (int i = 0; i < 10; i++)
    {
        std::cout << q.pop() << std::endl;
    }
}
