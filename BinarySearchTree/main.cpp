#include <iostream>
#include "BST.hpp"

int main(){
    binary_search_tree<int> myTree1;
    myTree1.insert(6);
    myTree1.insert(4);
    myTree1.insert(8);
    myTree1.insert(6);

    auto iter = myTree1.begin();
    while(iter != myTree1.end()){
        std::cout<<*iter<<' ';
        ++iter;
    }
    binary_search_tree<int> myTree2(myTree1);
    myTree2.remove(6);
    myTree2.remove(4);
    myTree2.remove(8);
}