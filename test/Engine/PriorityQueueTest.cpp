#include "PriorityQueueTest.h"

#include <LowPriorityQueue.h>

TEST_F(PriorityQueueTest, insert) {
    std::vector<int> data;
    data.push_back(6);
    data.push_back(4);
    data.push_back(3);
    data.push_back(9);
    data.push_back(3);
    PriorityQueue<int> q(data, 10);

    q.insert(1);
    q.insert(2);
    q.insert(3);
    q.insert(4);
    q.insert(5);

    for (int i = 0; i < 5; i++)
    {
        std::cout << q.pop() << std::endl;
    }
}
