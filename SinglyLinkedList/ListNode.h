#ifndef NODE_H
#define NODE_H

template <typename NODETYPE> class LinkedList;

template <typename NODETYPE>
class Node{
    friend LinkedList<NODETYPE>;
public:
    Node<NODETYPE>(const NODETYPE& val) : value(val),next{nullptr} {}
    const NODETYPE& getValue() const{
        return value;
    }

private:
    NODETYPE value;
    Node<NODETYPE>* next;
};
#endif