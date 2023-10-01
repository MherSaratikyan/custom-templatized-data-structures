#include <iostream>
#include "Vector.h"

template <typename T>
void infoAboutVec(const Vector<T>& v){
    std::cout<<"\nsize: "<<v.Size()
            <<"\ncapacity: "<<v.Capacity()
            <<"\nis empty: "<<(v.empty() ? "true" : "false")
            <<"\nElements: ";
            for(size_t i{0};i < v.Size();++i){
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



}