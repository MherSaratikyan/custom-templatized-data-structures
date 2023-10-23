#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>
#include "ListNode.h"

template <typename T>
class DoublyLinkedList{
public:

    DoublyLinkedList<T>(): first{nullptr}, last{nullptr}, size{0} {}
    DoublyLinkedList<T>(const DoublyLinkedList<T>& rhs){
        copy(rhs);
    }

    DoublyLinkedList<T>(DoublyLinkedList<T>&& rhs): first{rhs.first}, last{rhs.last}, size{rhs.size}{
        rhs.first = nullptr;
        rhs.last = nullptr;
        rhs.size = 0;
    }

    const DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& rhs){
        if(this != &rhs){
            cleanUp();
            copy(rhs);
        }

        return *this;
    }

    const DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& src){
        if(this != &src){
            cleanUp();
            first = src.first;
            src.first = nullptr;
            last = src.last;
            src.last = nullptr;
            size = src.size;
            src.size = 0;
        }

        return *this;
    }

    bool isEmpty() const{
        return (first == nullptr);
    }

    void push_front(const T& value){

        ListNode<T>* newNode = getNewNode(value);
        if(isEmpty()){
            first = last = newNode;
        }else{
            first->previousNode = newNode;
            newNode->nextNode = first;
            first = newNode;
        }
       ++size;
    }

    bool pop_front(T& holder){
        if(!isEmpty()){
            if(first == last){
                holder = first->getValue();
                delete first;
                last = first = nullptr;
            }else{
                ListNode<T>* tmp = first;
                first = first -> nextNode;
                holder = tmp->getValue();
                delete tmp;
                first->previousNode = nullptr;
                --size;
                return true;
            }
        }

        return false;
    }

    void push_back(const T& value){
        ListNode<T>* newNode = getNewNode(value);
        if(isEmpty()){
            last = first = newNode;
        }else{
             newNode -> previousNode = last;
            last -> nextNode = newNode;
            last = newNode;
        }

       
        ++size;
    }

    bool pop_back(T& holder){
        if(!isEmpty()){
            if(last == first){
                holder = last -> getValue();
                delete last;
                first = last = nullptr;
            }else{
                ListNode<T>* tmp = last;
                holder= tmp->getValue();
                last = tmp->previousNode;
                delete tmp;
                last->nextNode = nullptr;
                --size;
                return true;
            }
        }
        return false;
    }

    bool insertAtIndex(int index, const T& value){
        if(index < 0 || index > size){
            return false;
        }

        if(index == 0){
            push_front(value);
        }else if(index == size){
            push_back(value);
        }else{

            ListNode<T>* newNode = getNewNode(value);
            ListNode<T>* tmp{first};
            for(int i{0};i < index - 1;++i){
                tmp = tmp -> nextNode;
            }

            newNode->nextNode = tmp->nextNode;
            tmp->nextNode->previousNode = newNode;
            tmp->nextNode = newNode;
            newNode->previousNode = tmp;
            
        }
        ++size;
        return true;
    }

    bool removeFromIndex(int index,T& holder){
        if(index < 0 || index > size){
            return false;
        }

         if(index == 0){
            pop_front(holder);
        }else if(index == size){
            pop_back(holder);
        }else{
            ListNode<T>* tmp{first};
            for(int i{0};i < index;++i){
                tmp = tmp -> nextNode;
            }

            tmp->previousNode->nextNode = tmp->nextNode;
            tmp->nextNode->previousNode = tmp->previousNode;
            holder = tmp->getValue();
            delete tmp;
        }
        --size;
        return true;
    }

    int getSize() const{
        return size;
    }

    void print() const{
        if(!isEmpty()){
            ListNode<T>* tmp{first};
            std::cout<<"nullptr <- ";
            while(tmp -> nextNode != nullptr){
                std::cout<<tmp->getValue()<<" <-> ";
                tmp = tmp -> nextNode;
            }

            std::cout<<tmp->getValue()<<" -> nullptr";
        }
    }

    ~DoublyLinkedList(){
        cleanUp();
    }

private:
   ListNode<T>* first{nullptr};
   ListNode<T>* last{nullptr}; 
    int size{0};

   ListNode<T>* getNewNode(const T& value) const{
        ListNode<T>* newNode = new ListNode<T>(value);
        return newNode;
   }

   void cleanUp(){
        if(!isEmpty()){
            ListNode<T>* cleaner{first};
            while(cleaner != nullptr){
                first = first -> nextNode;
                delete cleaner;
                cleaner = first;
            }
        }
   }

   void copy(const DoublyLinkedList<T>& rhs){
        ListNode<T>* tmp = rhs.first;
        while(tmp != nullptr){
            this->push_back(tmp->getValue());
            tmp = tmp -> nextNode;
        }
   }
};
#endif