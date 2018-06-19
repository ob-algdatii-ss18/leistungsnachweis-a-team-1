#ifndef ALOGDAT_LABYRINTH_LOWPRIORITYQUEUE_H
#define ALOGDAT_LABYRINTH_LOWPRIORITYQUEUE_H

#include <algorithm>
#include <cassert>
#include <iostream>

/**
 * Gib den Eltern Index   zurück.
 * @param i
 * @return
 */
inline static int parent(int i) {
    return i/2;
}

/**
 * Gib den Index des Linken Kind Elements zurück
 * @param i
 * @return
 */
inline static int left(int i) {
    return 2*i;
}

/**
 * Gibt den Index des rechten Kind Elements zurück.
 * @param i
 * @return
 */
inline static int right(int i) {
    return 2*i + 1;
}

/**
 * Eine Min-Heapsort-Warteschlange.
 * Sortiert die Knoten-Kosten nach aufsteigender Reihenfolge,
 * also das niedrigste Element zuerst.
 * @tparam T
 */
template <typename T>
class PriorityQueue {
private:
    std::vector<T>& m_data;
    std::vector<int> m_heap;
    std::vector<int> m_inv_heap;
    int m_size;
    int m_max_size;

public:

    void swap(int id1, int id2) {
        std::swap(m_heap[id1], m_heap[id2]);

        m_inv_heap[m_heap[id1]] = id1;
        m_inv_heap[m_heap[id2]] = id2;
    }

    PriorityQueue(std::vector<T>& keys, unsigned int max_size)
            : m_data(keys), m_size(0), m_max_size(max_size) {
        m_heap.assign(max_size+1, 0);
        m_inv_heap.assign(max_size+1,0);
        }

    /**
     * Inserts an element.
     * @param index
     */
    void insert(const int item) {
        std::cout << "insert" << std::endl;
        std::cout << "assert" << std::endl;
        assert(m_size+1 <= m_max_size);
        std::cout << "inc" << std::endl;
        ++m_size;
        std::cout << "sheap" << std::endl;
        m_heap[m_size] = item;
        std::cout << "s inv heap" << std::endl;
        m_inv_heap[item] = m_size;
        std::cout << "reorder" << std::endl;
        //reorder_upwards(m_size);
        std::cout << "ready" << std::endl;
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
        swap(1, m_size);
        reorder_downwards(1, m_size-1);

        return m_heap[m_size--];
    }

    void reorder_upwards(int idx) {
        while ((idx > 1) && (m_data[m_heap[parent(idx)]] > m_data[m_heap[idx]])) {
            swap(parent(idx), idx);

            idx = parent(idx);
        }
    }

    void change_priority(const int idx) {
        reorder_upwards(idx);
    }

    void reorder_downwards(int idx, int size) {
        while (left(idx) <= size)
        {
            int child = left(idx);

            // bestimme, welches der kind elemente kleiner ist.
            if ((child < size) && (m_data[m_heap[child]] > m_data[m_heap[child+1]]))
                ++child;

            // wenn Eltern-element größer als Kind tausche sie.
            if (m_data[m_heap[idx]] > m_data[m_heap[child]])
            {
                swap(child, idx);
                idx = child;
            }

            else {
                break;
            }
        }
    }
};
#endif //ALOGDAT_LABYRINTH_LOWPRIORITYQUEUE_H
