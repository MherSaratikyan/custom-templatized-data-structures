#ifndef LIST_H
#define LIST_H

#include "ListNode.h"
#include <iostream>

template<typename NODETYPE>
class LinkedList{
public:

    LinkedList<NODETYPE>(): first{nullptr}, last{nullptr} {};

    LinkedList<NODETYPE>(const LinkedList<NODETYPE>& rhs){
        copy(rhs);
    }

    const LinkedList<NODETYPE>& operator=(const LinkedList<NODETYPE>& rhs){
        if(this != &rhs){
            cleanUp();

           copy(rhs);
        }

        return *this;
    }
    

    bool isEmpty() const{
        return (nullptr == first);
    }

    void push_front(const NODETYPE& val){
        Node<NODETYPE>* newNode = getNewNode(val);
        if(isEmpty()){
            first = last = newNode;
        }else{
            newNode -> next = first;
            first = newNode;
        }

        
        ++size;
    }

    bool pop_front(){
        if(!isEmpty()){
            if(first == last){
                delete first;
                first = last = nullptr;
            }else{
                Node<NODETYPE>* tmp{first};
                first = first -> next;
                delete tmp;
            }
            --size;
            return true;
        }

        return false;
    }

    void push_back(const NODETYPE& val){
        Node<NODETYPE>* newNode = getNewNode(val);
        if(isEmpty()){
            last = first = newNode;
        }else{
            last -> next = newNode;
            last = newNode;
        }

        
        ++size;
    }

    bool pop_back(){
        if(!isEmpty()){
            if(first == last){
                delete last;
                last = first = nullptr;
            }else{
                Node<NODETYPE>* tmp{first};
                while(tmp -> next != last){
                    tmp = tmp -> next;
                }

                delete last;
                last = tmp;
                tmp -> next = nullptr;
                
            }
            --size;
            return true;
        }

        return false;
    }

    bool insert(const NODETYPE& val,size_t index){

        if(index < 0 || index > size){
            return false;
        }

        if(index == 0){
            push_front(val);
        }else if(index == size){
            push_back(val);
        }else{
            Node<NODETYPE>* newNode = getNewNode(val);
            Node<NODETYPE>* tmp{first};

            for(size_t i = 0;i < index - 1;++i){
                tmp = tmp -> next;
            }

            newNode -> next = tmp -> next;
            tmp -> next = newNode;
            ++size;
        }
            return true;
    }

    bool remove(size_t index){
        if(index < 0 && index > size){
            return false;
        }

        if(index == 0){
            pop_front();
        }else if(index == size){
            pop_back();
        }else{
            
            Node<NODETYPE>* tmp{first};
            for(size_t i{0};i < index - 1;++i){
                tmp = tmp -> next;
            }

            Node<NODETYPE>* rem{tmp -> next};
            tmp -> next = rem -> next;
            delete rem;
            --size;
        }

        return true;
    }

    size_t getSize() const{
        return size;
    }

    void print() const{
        Node<NODETYPE>* tmp{first};
        while(tmp != nullptr){
            std::cout<<tmp -> getValue()<<" -> ";
            tmp = tmp -> next;
        }
        std::cout<<"nullptr\n";
    }

    ~LinkedList<NODETYPE>(){
        cleanUp();
    }
    
private:
    //utility function
    Node<NODETYPE>* getNewNode(const NODETYPE& val) const{
        Node<NODETYPE>* newNode = new Node<NODETYPE>(val);
        return newNode;
    }

    //data members
    size_t size{0};
    Node<NODETYPE>* first{nullptr};
    Node<NODETYPE>* last{nullptr};

    void cleanUp(){
        if(!isEmpty()){
            Node<NODETYPE>* tmp{first};
            while(first != nullptr){
                first = first -> next;
                delete tmp;
                tmp = first;
            }
        }
    }

    void copy(const LinkedList<NODETYPE>& rhs){
        Node<NODETYPE>* tmp = rhs.first;
        while(tmp != nullptr){
            push_back(tmp -> getValue());
            tmp = tmp -> next;
        }
    }
};
#endif