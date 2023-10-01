#ifndef LISTNODE_H
#define LISTNODE_H

template <typename T>
class DoublyLinkedList;

template <typename T>
class ListNode{
friend DoublyLinkedList<T>;
public:
ListNode<T>(const T& value): n_value{value}, nextNode{nullptr}, previousNode{nullptr} {}

const T& getValue() const{
    return n_value;
}

private:
    ListNode<T>* previousNode;
    ListNode<T>* nextNode;
    T n_value;
};
#endif