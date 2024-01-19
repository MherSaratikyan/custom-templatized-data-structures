#include <iostream>
#include "list.hpp"

template <typename T>
void printInfo(const list<T>& llist){
    std::cout<<"\nSize: "<<llist.size()
            <<"\nElements: ";
    auto citer = llist.cbegin();
    while(citer != llist.cend()){
        std::cout<<(*citer)<<' ';
        ++citer;
    }
}

int main(){
    std::cout<<"Testing ctors\n";
    std::cout<<"\nDefault ctor:";
    list<int> list_dc;
    printInfo(list_dc);

    std::cout<<"\nOne param ctor:";
    list<int> list_op(10);
    printInfo(list_op);

    std::cout<<"\nTwo param ctor:";
    list<int> list_tp(5,10);
    printInfo(list_tp);

    std::cout<<"\ncopy ctor:";
    list<int> list_cc(list_tp);
    printInfo(list_cc);

    std::cout<<"\nmove ctor(moving from copy constructed list):";
    list<int> list_mc(std::move(list_cc));
    printInfo(list_mc);
    std::cout<<"\nmoved from state of list:";
    printInfo(list_cc);

    std::cout<<"\ninitializer_list ctor:";
    list<int> list_ilc{1,2,3,4,5,6,7,8,9,0};
    printInfo(list_ilc);
    std::cout<<"\nTesting assignment operators\n";
    std::cout<<"\nCopy assignment operator:";
    list_op = list_tp;
    printInfo(list_op);
    std::cout<<"\nmove assignment operator:";
    list<int> list_ma;
    list_ma = std::move(list_op);
    printInfo(list_ma);
    std::cout<<"\nmoved from state of list:";
    printInfo(list_op);

    std::cout<<"\nn\nTesting node adding and node remoine member functions:\n";
    printInfo(list_ilc);
    std::cout<<"\npush_front(10) and push_back(10):";
    list_ilc.push_back(10);
    list_ilc.push_front(10);
    printInfo(list_ilc);

    std::cout<<"\npop_front() and pop_back():";
    list_ilc.pop_back();
    list_ilc.pop_front();
    printInfo(list_ilc);

    auto iter = list_ilc.cbegin();
    for(int i{0};i < 3;++i){
        ++iter;
    }

    std::cout<<"\ninsert(ilist_ilc.cbegin() + 3,40):";
    list_ilc.insert(iter,40);
    printInfo(list_ilc);

    
    std::cout<<"\ninsert(ilist_ilc.cbegin() + 3,3,33):";
    --iter;
    list_ilc.insert(iter,3,33);
    printInfo(list_ilc);
    //iter = list_ilc.cbegin() + 5;
    std::cout<<"\nerase(cbegin() + 6):";
    list_ilc.erase(iter);
    printInfo(list_ilc);

    
}