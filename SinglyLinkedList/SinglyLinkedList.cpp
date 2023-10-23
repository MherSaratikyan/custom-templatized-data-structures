#include <iostream>
#include "LinkedList.h"

int main(){
    LinkedList<int> myList;
    myList.push_front(12);
    myList.push_back(7);
    myList.insert(4,1);

    std::cout<<myList.getSize()<<'\n';
    myList.print();

    myList.remove(1);
    myList.print();
    
    myList.pop_front();
    myList.pop_back();
    std::cout<<myList.getSize()<<'\n';
    if(myList.isEmpty()){
        std::cout<<"\nThe list is empty!";
    }else{
        std::cout<<"\nThe list is not empty!";
    }

    myList.push_back(42);
    myList.push_front(24);
    std::cout<<"\n\nTesting copy constructor and copy assignment operator\n";
    std::cout<<"the list myList contains:\n";
    myList.print();
    LinkedList<int> myList2(myList);

    std::cout<<"\nThe list myList2 contains:\n";
    myList2.print();

    LinkedList<int> myList3;
    myList3 = myList2;
    myList3.push_front(16);
    std::cout<<"\nThe list mylist3 contains:\n";
    myList3.print();

    std::cout<<"Testing insert and remove:\n";
    std::cout<<"List: ";
    myList3.print();
    std::cout<<"Size: "<<myList3.getSize()<<'\n';
    myList3.insert(66,2);
    myList3.print();
    std::cout<<"Size: "<<myList3.getSize()<<'\n';
    myList3.remove(2);
    myList3.print();

    std::cout<<"\n\nTesting move constructor\n";
    LinkedList<int> myList4(std::move(myList3));
    std::cout<<"myList4: ";
    myList4.print();
    std::cout<<"\nNew state of myList3: ";
    myList3.print();

    std::cout<<"\n\nTesting move assignment\n";
    LinkedList<int> myList5;
    myList5 = std::move(myList4);
    std::cout<<"myList5: ";
    myList5.print();
    std::cout<<"\nNew state of myList4: ";
    myList3.print();
    
}