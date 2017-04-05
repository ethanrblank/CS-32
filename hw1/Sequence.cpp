#include "Sequence.h"


Sequence::Sequence() {
    m_size = 0;
}

bool Sequence::empty() const {
    return m_size == 0;
}

int Sequence::size() const {
    return m_size;
}

bool Sequence::insert(int pos, const ItemType& value) {
    if (0 <= pos && pos <= m_size) {
        for (int i = m_size-1; i >= pos; --i) {
            m_container[i+1] = m_container[i];
        }
        m_container[pos] = value;
        ++m_size;
        return true;
    }
    else {
        return false;
    }
}

int Sequence::insert(const ItemType &value) {
    for (int i = 0; i < m_size; ++i) {
        if (value <= m_container[i]) {
            insert(i, value);
            return i;
        }
    }
    if (insert(m_size, value))
        return m_size;
    else
        return 1;
}

bool Sequence::erase(int pos) {
    if (0 <= pos && pos < m_size) {
        for (int i = pos; i < m_size; ++i) {
            m_container[i] = m_container[i+1];
        }
        --m_size;
        return true;
    }
    else
        return false;
}

int Sequence::remove(const ItemType &value) {
    int erase_count = 0;
    for (int i = 0; i < m_size; ++i) {
        if (m_container[i] == value) {
            ++erase_count;
            erase(i);
        }
    }
    return erase_count;
}

bool Sequence::get(int pos, ItemType& value) {
    if (0 <= pos && pos < m_size) {
        value = m_container[pos];
        return true;
    }
    
    else
        return false;
}

bool Sequence::set(int pos, const ItemType &value) {
    if (0 <= pos && pos < m_size) {
        m_container[pos] = value;
        return true;
    }
    
    else
        return false;
}

int Sequence::find(const ItemType &value) {
    for (int i = 0; i < m_size; ++i) {
        if (m_container[i] == value) {
            return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence &other) {
    Sequence temp = *this;
    *this = other;
    other = temp;
}
