#ifndef ALOGDAT_LABYRINTH_LOWPRIORITYQUEUE_H
#define ALOGDAT_LABYRINTH_LOWPRIORITYQUEUE_H

#include <algorithm>
#include <cassert>

inline static int parent(int i) {
    return i/2;
}

inline static int left(int i) {
    return 2*i;
}

inline static int right(int i) {
    return 2*i + 1;
}

template <typename T>
class PriorityQueue {
private:
    std::vector<T>& m_data;
    std::vector<int> m_heap;
    int m_size;
    int m_max_size;

public:

    void swap(int id1, int id2) {
        std::swap(m_heap[id1], m_heap[id2]);
    }

    PriorityQueue(std::vector<T>& keys, unsigned int max_size)
            : m_data(keys), m_size(0), m_max_size(max_size) {
        m_heap.assign(max_size+1, 0);
        }

    /**
     * Inserts an element.
     * @param index
     */
    void insert(const int item) {
        assert(m_size+1 <= m_max_size);
        m_heap[m_size] = item;
        m_size++;
        reorder_upwards(m_size);
    }

    /**
     * Is the priority queue empty?
     * @return empty, or not.
     */
    bool empty() const { return m_size == 0; }

    /**
     * Returns the element with lowest priority.
     * @return
     */
    T minimum() {
        return m_heap[0];
    }

    /**
     * deletes and returns the element with the lowest priority.
     * @return
     */
    int pop() {
        swap(0, m_size-1);
        reorder_downwards(0);

        int ret = m_heap[m_size];
        --m_size;
        return ret;
    }

    void reorder_upwards(int idx) {
        while ((idx > 1) && (m_data[m_heap[parent(idx)]] > m_data[m_heap[idx]])) {
            std::swap(m_heap[parent(idx)], m_heap[idx]);

            idx = parent(idx);
        }
    }

    void reorder_downwards(int idx) {
        while (left(idx) <= m_size)
        {
            int l = left(idx);

            if ((l < m_max_size) && (m_data[m_heap[l]] > m_data[m_heap[l+1]]))
                ++l;

            if (m_data[m_heap[idx]] > m_data[m_heap[l]])
            {
                swap(l, idx);
                idx = l;
            }

            else {
                break;
            }
        }
    }

    void min_heapify(int i) {
        int l = left(i);
        int r = right(i);
        int maximum;

        if (l <= m_max_size && (m_heap[l]>=m_heap[i]))
            maximum = l;
        else
            maximum = i;

        if (r <= m_max_size && m_heap[r] > m_heap[maximum])
            maximum = r;

        if (maximum != i)
            swap(i, maximum);
    }
};
#endif //ALOGDAT_LABYRINTH_LOWPRIORITYQUEUE_H
