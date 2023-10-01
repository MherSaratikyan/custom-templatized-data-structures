#include <iostream>
#include "DoublyLinkedList.h"

int main(){
    DoublyLinkedList<int> myDLList;

   for(int i{0};i < 5;++i){
    myDLList.push_front(i);
   }

    for(int i{0};i < 5;++i){
        myDLList.push_back(i);
    }
    std::cout<<"Size: "<<myDLList.getSize();
   std::cout<<"\nDoubly linked list contains:\n";
   myDLList.print();
   std::cout<<"\n\n";

   
    int num;
   myDLList.pop_back(num);
   myDLList.pop_back(num);
   myDLList.pop_front(num);

   
   myDLList.insertAtIndex(3,40);
   myDLList.removeFromIndex(4,num);

   std::cout<<"Size: "<<myDLList.getSize();
   std::cout<<"\nDoubly linked list contains:\n";
   myDLList.print();
   std::cout<<"\n\n";

   std::cout<<"\n\nTesting copy constructor:\n";
   DoublyLinkedList<int> myDLList2{myDLList};
   std::cout<<"\nMyDLList2 contains:\n";
   myDLList2.print();

   std::cout<<"\n\ntesting copy assignment operator:\n";
   int holder;
   myDLList.pop_front(holder);
   myDLList.pop_front(holder);

   std::cout<<"\nMyDLList contains:\n";
   myDLList.print();

   myDLList2 = myDLList;
   std::cout<<"\nMy DLList2 con tains:\n";
   myDLList2.print();

  

}