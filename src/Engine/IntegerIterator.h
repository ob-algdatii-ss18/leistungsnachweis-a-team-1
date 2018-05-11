#ifndef ALOGDAT_LABYRINTH_INTEGERITERATOR_H
#define ALOGDAT_LABYRINTH_INTEGERITERATOR_H

#include <type_traits>

template<typename TInteger>
struct Integer_iterator {
    static_assert(std::is_integral<TInteger>::value, "Kein Integer-Typ");

    using self = Integer_iterator<TInteger>;
    using value_type = TInteger;
    using reference = TInteger;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    using pointer = TInteger;

    Integer_iterator() : m_value() {}

    explicit Integer_iterator(value_type value) : m_value(value) {}

    self &operator++() {
        ++m_value;
        return *this;
    }

    self &operator++(int) {
        TInteger tmp = m_value;
        ++m_value;
        return Integer_iterator(tmp);
    }

    difference_type operator-(const Integer_iterator &other) const {
        return -distance_to(other);
    }

    difference_type distance_to(const Integer_iterator &other) const {
        return std::is_signed<value_type>::value ?
               (other.m_value - m_value) :
               (other.m_value >= m_value) ?
               static_cast<difference_type>(other.m_value - m_value) :
               -static_cast<difference_type>(m_value - other.m_value);
    }

    self &operator--() {
        --m_value;
        return *this;
    }

    self &operator--(int) {
        TInteger tmp = m_value;
        --m_value;
        return Integer_iterator(tmp);
    }

    reference operator*() const {
        return m_value;
    }

    self &operator+(difference_type offset) {
        m_value += offset;
        return *this;
    }

    self &operator+=(difference_type offset) {
        m_value += offset;
        return *this;
    }

    self &operator-(difference_type offset) {
        m_value -= offset;
        return *this;
    }

    self &operator-=(difference_type offset) {
        m_value -= offset;
        return *this;
    }

    bool operator==(const self &other) const {
        return m_value == other.m_value;
    }

    bool operator!=(const self &other) const {
        return m_value != other.m_value;
    }

protected:
    value_type m_value;
};

template<typename TIterator>
class Iterator_range {
public:
    Iterator_range() {}

    template<typename Iterator>
    Iterator_range(Iterator first, Iterator last)
            : m_begin(first), m_end(last) {}

    TIterator begin() const {
        return m_begin;
    }

    TIterator end() const {
        return m_end;
    }

    bool empty() const {
        return m_begin == m_end;
    }

protected:
    TIterator m_begin;
    TIterator m_end;
};

template<typename Integer>
class Integer_range : public Iterator_range<Integer_iterator<Integer>> {
    using iterator_t = Integer_iterator<Integer>;
    using mybase = Iterator_range<iterator_t>;
public:
    Integer_range(Integer first, Integer last)
            : mybase(iterator_t(first), iterator_t(last)) {}

};


#endif //ALOGDAT_LABYRINTH_INTEGERITERATOR_H
