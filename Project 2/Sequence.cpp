#include "Sequence.h"
#include <iostream>

using namespace std;

/** Default contructor creates a first and last node and then points them at each other. Sets the size to 0 **/
Sequence::Sequence() {
    first = new Node("first");
    last = new Node("last");
    
    first->next = last;
    last->previous = first;
    m_size = 0;
}

/** @param s (Sequence)
 
    Copy constructor creates a new Sequence by copying the elements of a given sequence into a new sequence.
 **/

Sequence::Sequence(const Sequence& s) {
    first = new Node(s.first->data);
    last = new Node(s.last->data);
    m_size = s.m_size;
    
    first->next = last;
    last->previous = first;
    
    int i = 0;
    
    ItemType val;
    
    Node* p = s.first;
    p = p->next;
    for (; p != s.last; p = p->next) {
        s.get(i, val);
        insert(i, val);
        ++i;
    }
    
}

/** Destructor deletes all the nodes off the heap. **/
Sequence::~Sequence() {
    Node* p = first;
    while (p != nullptr) {
        Node* temp = p->next;
        delete p;
        p = temp;
    }
}

/** Creates a new sequence object equal to a given Sequence object by first erasing the lhs object, then using the copy constructor and swap function to assign the lhs Sequence values.
 **/
Sequence& Sequence::operator=(const Sequence &s) {
    if (this != &s) {
        for (int i = -1; i < m_size; ++i) {
            erase(i);
        }
        Sequence temp(s);
        swap(temp);
    }
    return *this;
}

/** @return m_size == 0 (bool)
    
    @brief  If the size of the list is 0, the function will
            return true indicating that there are no elements 
            in the list.
 **/

bool Sequence::empty() const {
    return m_size == 0;
}

/** @return m_size (int)
    
    @brief  The function returns the m_size private variable.
            This function can be used for accessing the size of the list.
 **/

int Sequence::size() const {
    return m_size;
}

/** @param pos (int)
    @param value (ItemType)
 
    @brief  This function inserts a node at the position indicated by pos. The
            function first checks to make sure that pos is an accessible point within
            the list, then it creates a node and inserts it at the given one Node before the
            given position. It then increments m_size.
 **/

bool Sequence::insert(int pos, const ItemType &value) {
    if (0 <= pos && pos <= m_size) {
        Node* new_node = new Node(value);
        
        int i = -1;
        Node* p = first;
        for (; p != last && i != pos; p = p->next) {
            ++i;
        }
        Node* before = p->previous;
        Node* after = p;
        
        new_node->previous = before;
        new_node->next = after;
        
        before->next = new_node;
        after->previous = new_node;
        
        ++m_size;
        return true;
    }
    
    else {
        return false;
    }
}

/** @param value (ItemType)
 
    @brief  The function inserts a Node at the first position where
            value is less than the current Node. If value is the largest data member
            within the list, the function will insert the new node at the end of the list.
 **/

int Sequence::insert(const ItemType &value) {

    int i = -1;
    Node* p = first;
    bool to_end = false;
    for (; p != last && !to_end; p = p->next) {
        if (value < p->data) {
            insert(i, value);
            to_end = true;
        }
        ++i;
    }
    
    if (!to_end) {
        i = m_size;
        insert(m_size, value);
    }
    
    return i;
}

/** @param pos (int)
    
    @brief Erases a Node at a given position. First checks to see if the position is within bounds, then moves a pointer to said Node and erases it.
 **/
bool Sequence::erase(int pos) {
    if (0 <= pos && pos <= m_size) {
        int i = -1;
        Node* p = first;
        for (; p != last && i != pos; p = p->next) {
            ++i;
        }
        Node* before = p->previous;
        Node* after = p->next;

        before->next = after;
        after->previous = before;
        
        delete p;
        
        --m_size;
        return true;
    }
    
    else {
        return false;
    }
}

/** @param value (ItemType)
    @return erase_count (int)
    
    @brief  Erases all instances of a particular value by way of the erase function. Then returns the number of times
            the value was erased.
 **/
int Sequence::remove(const ItemType &value) {
    Node* p = first;
    int i = -1;
    int erase_count = 0;
    for (; p != last; p = p->next) {
        if (p->data == value) {
            erase(i);
            ++erase_count;
        }
        ++i;
    }
    return erase_count;
}

/** @param pos (int)
    @param value (ItemType)
 
    @brief  The function checks if the position is within bounds. If the psoition is within bounds,
            then a Node pointer moves to that position and reassigns value with the data that is within
            the given Node.
 **/
bool Sequence::get(int pos, ItemType &value) const {
    if (0 <= pos && pos <= m_size) {
        Node* p = first;
        int i = -1;
        for (; p!= last && i <= pos; p = p->next) {
            if (i == pos) {
                value = p->data;
            }
            ++i;
        }
        return true;
    }
    else
        return false;
}

/** @param pos (int)
    @param value (ItemType)
 
    @brief  The function checks if the position is within bounds. If the psoition is within bounds,
            then a Node pointer moves to that position and resets the data of the given Node with value.
 **/

bool Sequence::set(int pos, const ItemType &value) {
    if (0 <= pos && pos < m_size) {
        Node* p = first;
        int i = -1;
        
        for (; p != last && i != pos; p = p->next) {
            if (i == pos) {
                p->data = value;
            }
            ++i;
        }
        return true;
    }
    else
        return false;
}

/** @param value (ItemType)
    @return i (int)
    
    @brief Moves a pointer throughout the Sequence and returns the position of the first occurance of value
 **/
int Sequence::find(const ItemType &value) const {
    Node* p = first;
    int i = -1;
    bool to_end = false;
    for (; p != last && !to_end; p = p->next) {
        if (value == p->data) {
            to_end = true;
        }
        if (to_end) {
            --i;
        }
        ++i;
    }
    return i;
}

/** @param other (Sequence)
    
    @brief Swaps the first and last Nodes of a given function. No further action is necessary, since a Sequence is a collection of Nodes that point to each other.
 **/
void Sequence::swap(Sequence &other) {
    Node* temp_first = first;
    Node* temp_last = last;
    
    first = other.first;
    last = other.last;
    
    other.first = temp_first;
    other.last = temp_last;
}

/** @brief Writes the contents of a Sequence to cerr to be used for testing. **/
void Sequence::dump() const {
    int i = 0;
    Node* p = first->next;
    
    for (; i != m_size; p = p->next) {
        cerr << p->data << " ";
        ++i;
    }
}

/** @param seq1 (Sequence)
    @param seq2 (Sequence);
 
    @return return_val (int)
 
    @brief  Takes a sequence and finds the first instance of a subsequence of the other Sequence. If the data in a sequence matches the other sequence in value and order, then that Sequence is considered a subsequence. The function returns the index of where the subsequence begins in seq1.
 **/

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    ItemType val1;
    ItemType val2;
    
    int j = 0;
    int return_val = 0;
    
    for (int i = 0; i < seq1.size(); ++i) {
        seq1.get(i, val1);
        seq2.get(j, val2);
        
        if (val1 == val2) {
            if (j == 0) {
                return_val = i;
            }
            if (j < seq2.size())
                ++j;
        }
        else
            j = 0;
    }
    return return_val;
}

/** @param seq1 (Sequence)
    @param seq2 (Sequence)
    @param result (Sequence)
 
    @brief This fills the result sequence with alternating values from seq1 and seq2.
 **/

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    int m = seq1.size();
    int n = seq2.size();
    
    ItemType val1;
    ItemType val2;
    
    Sequence new_seq; // will be used later to swap with result
    
    if (m == n) { // if the sizes of seq1 and seq2 are equal
        int j = 0; // used to access the data within the sequences
        for (int i = 0; j < m; i+=2) { // i+=2 so that when the for loop reloops, it does not overwrite data at a given position
            seq1.get(j, val1);
            seq2.get(j, val2);
            new_seq.insert(i, val1); // inserts from seq1 first
            new_seq.insert(i+1, val2); //then inserts data from seq2
            ++j;
        }
    }
    
    else if (m < n) { // if seq1 is smaller than seq2
        int i = 0;
        int j = 0;
        for (; j < m; i+=2) { // i+=2 so that when the for loop reloops, it does not overwrite data at a given
            seq1.get(j, val1);
            seq2.get(j, val2);
            new_seq.insert(i, val1);
            new_seq.insert(i+1, val2);
        }
        for (; j < n; ++i) { // when seq1 runs out of values
            seq2.get(j, val2);
            new_seq.insert(i, val2);
        }
    }
    
    else if (n < m) { // if seq2 is smaller than seq1
        int i = 0;
        int j = 0;
        for (; j < n; i+=2) { // i+=2 so that when the for loop reloops, it does not overwrite data at a given position
            seq1.get(j, val1);
            seq2.get(j, val2);
            new_seq.insert(i, val1);
            new_seq.insert(i+1, val2);
            ++j;
        }
        for (; j < m; ++i) { // when seq2 runs out of values
            seq1.get(j, val1);
            new_seq.insert(i, val1);
            ++j;
        }
    }

    result.swap(new_seq); // swaps new_seq and result so that the correct values for result is passed back to main
}
