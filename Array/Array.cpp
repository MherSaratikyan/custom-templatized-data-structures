#include <iostream>
#include <utility>
#include "Array.h"

template <typename T,size_t size>
void printArray(const Array<T,size>& arr){
    for(size_t i{0};i < arr.Size();++i){
        std::cout<<arr[i]<<' ';
    }

    std::cout<<'\n';
}

int main(){
    const size_t size1{10};
    const size_t size2{15};
    const size_t size3{5};

    //testing default ctor
    std::cout<<"\nDefault ctor:"
            <<"\narr1:\n";
    Array<int,size1> arr1;
    printArray(arr1);

    //testing ctor with filler value param
    std::cout<<"\nCtor with fillerValue param"<<"\narr2:\n";
    Array<int,size2> arr2(42);
    printArray(arr2);

    //testing ctor with initializer_list param
    std::cout<<"\nCtor with std::initializer_list param:"<<"\narr3:\n";
    Array<double,size3> arr3{1.3, 85.4, 3.14, 1.653, 2.171};
    printArray(arr3);

    //testing copy ctor
    Array<double,size3> arr4{arr3};
    std::cout<<"\nCopy ctor:"<<"\narr4:\n";
    printArray(arr4);

    Array<int,size2> arr5;
    std::cout<<"\narr5 is:\n";
    printArray(arr5);
    std::cout<<"\nTesting copy assignment operator:"<<"\nafter arr5 = arr2,arr5 is:\n";
    
    arr5 = arr2;
    printArray(arr5);

    std::cout<<"\nTesting member function fill:\n";
    Array<int,size3> arr6;
    std::cout<<"\narr6 is:\n";
    printArray(arr6);

    std::cout<<"\nAfter call to member function fill,ar6 is:\n";
    arr6.fill(22);
    printArray(arr6);

    std::cout<<"\n\nTesting move constructor\n:";
    std::cout<<"Array6:\n";
    printArray(arr6);

    Array<int,size3> arr7{std::move(arr6)};
    std::cout<<"\nAfter Array<int,size3> arr7{std::move(arr6)},"
            <<"arr6 contains:\n";
            printArray(arr6);
    std::cout<<"\narr7 contains:\n";
    printArray(arr7);
    

    std::cout<<"\n\nTetsting move assignment operator:\n";
    Array<int,size3> arr8;
    arr8 = std::move(arr7);
    std::cout<<"\narr7 after\n"
            <<"arr8 = std::move(arr7):";
            printArray(arr7);
    std::cout<<"\narr8:\n";
    printArray(arr8);

    return 0;    
}