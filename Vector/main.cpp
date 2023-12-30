#include <iostream>
#include "Vector.hpp"
#include <vector>

template <typename T>
void printInfo(const vector<T>& vec){
    std::cout<<"\nSize: "<<vec.size()
            <<"\nCapacity: "<<vec.capacity()
            <<"\nElements: ";
    for(int i{0};i < vec.size();++i){
        std::cout<<vec[i]<<' ';
    }
}

int main(){
    std::cout<<"\nTesting constructors\n\n";
    vector<int> vec_dc;
    std::cout<<"\nDefault ctor: ";
    printInfo(vec_dc);

    vector<int> vec_opc(10);
    std::cout<<"\nOne parameter ctor: ";
    printInfo(vec_opc);

    vector<int> vec_tpc(10,10);
    std::cout<<"\nTwo parameter ctor: ";
    printInfo(vec_tpc);

    vector<int> vec_ilc{0,1,2,3,4,5,6,7,8,9};
    std::cout<<"\ninitializer list ctor: ";
    printInfo(vec_ilc);

    vector<int> vec_cc(vec_tpc);
    std::cout<<"\nCopy ctor: ";
    printInfo(vec_cc);

    vector<int> vec_mc(std::move(vec_ilc));
    std::cout<<"\nMove ctor: ";
    printInfo(vec_mc);

    std::cout<<"\nMoved-from state of initializer list constructed vector:";
    printInfo(vec_ilc);

    
    std::cout<<"\n\nTesting asignment operators\n\n";
    std::cout<<"\nCopy assignment";
    vec_opc = vec_tpc;
    printInfo(vec_opc);

    std::cout<<"\nMove assighment";
    vec_ilc = std::move(vec_mc);
    printInfo(vec_ilc);
    printInfo(vec_mc);

    std::cout<<"\nAssigning iniializer list to vector";
    vec_mc = {1,2,3,4,5,6,7,8,9};
    printInfo(vec_mc);

    std::cout<<"\n\nTesting assign member function\n\n";
    std::cout<<"\nAssign with two params";
    vec_ilc.assign(20,12);
    printInfo(vec_ilc);

    std::cout<<"\nAssign with initializer_list param";
    vec_tpc.assign({12,43,54,65});
    printInfo(vec_tpc);

    std::cout<<"\nTesting element access functions\n\n";
    try{
        printInfo(vec_tpc);
        
        std::cout<<"\noperator[]: "<<vec_tpc[2]
                <<"\nfront: "<<vec_tpc.front()
                <<"\nback: "<<vec_tpc.back()
                <<"\nat: "<<vec_tpc.at(15);
    }catch(std::out_of_range& e){
        std::cout<<"\nException occured: "<<e.what();
    }

    std::cout<<"\n\nTesting member functions related to the capacity and modifiers\n\n";
    vector<double> vec_d;
    printInfo(vec_d);
    vec_d.reserve(10);
    for(int i{0};i < 10;++i){
        vec_d.push_back(3.14);
    }
    printInfo(vec_d);

    for(int i{0}; i < 5; ++i){
        vec_d.pop_back();
    }

    vec_d.insert(4, 2.71);
    vec_d.shrink_to_fit();
    printInfo(vec_d);

    std::cout<<"\n\nTesting iterators\n\n";
    vector<char> vec_it{'a','b','c','d','e','f','g','h'};
    auto iter = vec_it.begin();
    while(iter != vec_it.end()){
        std::cout<<(*iter)<<' ';
        ++iter;
    }

}