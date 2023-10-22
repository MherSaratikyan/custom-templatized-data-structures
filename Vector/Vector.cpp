#include <iostream>
#include "Vector.h"

template <typename T>
void infoAboutVec(const Vector<T>& v){
    std::cout<<"\nsize: "<<v.getSize()
            <<"\ncapacity: "<<v.getCapacity()
            <<"\nis empty: "<<(v.empty() ? "true" : "false")
            <<"\nElements: ";
            for(size_t i{0};i < v.getSize();++i){
                std::cout<<v[i]<<' ';
            }
}
int main(){
    Vector<int> v1;
    std::cout<<"\nv1:";
    infoAboutVec(v1);

    Vector<int> v2(10);
    std::cout<<"\nv2:";
    infoAboutVec(v2);

    Vector<int> v3(10,42);
    std::cout<<"\nv3:";
    infoAboutVec(v3);

    Vector<int> v4{v3};
    std::cout<<"\nv4:";
    infoAboutVec(v4);

    Vector<int> v5;
    v5 = v4;
    std::cout<<"\nv5:";
    infoAboutVec(v5);

    v5.push_back(12);
    std::cout<<"\nv5:";
    infoAboutVec(v5);

    std::cout<<"\nTseting move constructor:";
    std::cout<<"\nVector v5:";
    infoAboutVec(v5);

    Vector<int> v6(std::move(v5));

    std::cout<<"\nVector v6:";
    infoAboutVec(v6);

    std::cout<<"\nMoved-from v5:";
    infoAboutVec(v5);

    std::cout<<"\n\nTesting move assignment:\n";
    Vector<int> v7;
    std::cout<<"Newly created v7:";
    infoAboutVec(v7);

    v7 = std::move(v6);

    std::cout<<"\nVector v7 after assigning to it v6:";
    infoAboutVec(v7);

    std::cout<<"\nNew state of Vector v6:";
    infoAboutVec(v6);

    v7.insert(4,33);
    std::cout<<"\nVector v7 after inserting 33 at index 4:";
    infoAboutVec(v7);

    v7.remove(4);
    std::cout<<"\nVector v7 after removing element in from the index 4:";
    infoAboutVec(v7);
}