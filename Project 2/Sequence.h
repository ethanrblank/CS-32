#ifndef Sequence_h
#define Sequence_h

#include <string>

typedef std::string ItemType;

class Sequence {

public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& s);
    Sequence& operator=(const Sequence& s);
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
private:
    struct Node {
        inline Node() {
            next = nullptr;
            previous = nullptr;
        }
        inline Node(ItemType new_data) {
            data = new_data;
            next = nullptr;
            previous = nullptr;

        }
        ItemType data;
        Node* next;
        Node* previous;
    };
    Node* first;
    Node* last;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_h */
