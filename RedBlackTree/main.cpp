#include <iostream>
#include "RBTree.hpp"

template <typename T>
void printInfo(const rb_tree<T>& RBTree){
    std::cout<<"\nInorder tree walk: ";
    auto citer = RBTree.cbegin();
    while(citer != RBTree.cend()){
        std::cout<<*citer<<' ';
        ++citer;
    }
}

int main(){
    std::cout<<"Testing ctors\n";
    std::cout<<"\nDefault ctor:";
    rb_tree<int> rb_tree_dc;
    printInfo(rb_tree_dc);

    std::cout<<"\ninitializer_list ctor:";
    rb_tree<int> rb_tree_ilc{34, 19, 8, 45, 69, 20, 98, 56, 89, 72};
    printInfo(rb_tree_ilc);

    std::cout<<"\ncopy ctor:";
    rb_tree<int> rb_tree_cc(rb_tree_ilc);
    printInfo(rb_tree_cc);

    std::cout<<"\nmove ctor(moving from copy constructed rb_tree):";
    rb_tree<int> rb_tree_mc(std::move(rb_tree_cc));
    printInfo(rb_tree_mc);
    std::cout<<"\nmoved from state of rb_tree:";
    printInfo(rb_tree_cc);

    
    std::cout<<"\nTesting assignment operators\n";
    std::cout<<"\nCopy assignment operator:";
    rb_tree_dc = rb_tree_ilc;
    printInfo(rb_tree_dc);
    
    std::cout<<"\nmove assignment operator:";
    rb_tree<int> rb_tree_ma;
    rb_tree_ma = std::move(rb_tree_mc);
    printInfo(rb_tree_ma);
    std::cout<<"\nmoved from state of rb_tree:";
    printInfo(rb_tree_mc);

    std::cout<<"\n\nTesting node adding and node remoine member functions:\n";
    printInfo(rb_tree_ilc);
    rb_tree_ilc.insert(84);
    rb_tree_ilc.insert(88);
    printInfo(rb_tree_ilc);

    rb_tree_ilc.remove(89);
    rb_tree_ilc.remove(19);
    printInfo(rb_tree_ilc);
   
}