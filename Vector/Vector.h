#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>
#include <initializer_list>

template<typename T>
class Vector{
public:
    //default ctor
    Vector<T>(): v_size{0}, v_capacity{0}, arr{nullptr} {}

    //ctors with params
    Vector<T>(size_t capacity):v_size{0},v_capacity{capacity},arr{new T[capacity]} {}

    Vector<T>(size_t size,const T& fillerValue): v_size{size},v_capacity{size},arr{new T[size]{}} {
        for(size_t i{0};i < v_size;++i){
            arr[i] = fillerValue;
        }
    }

    Vector<T>(const std::initializer_list<T>& list): v_size{list.size()}, v_capacity{list.size()}, arr{new T[list.size()]{}}{
        auto itr = list.begin();
        for(size_t i{0};i < v_size;++i){
            arr[i] = *itr;
            ++itr;
        }
    }

    //copy ctor
    Vector<T>(const Vector<T>& src): v_size{src.v_size}, v_capacity{src.v_size},arr{new T[src.v_size]}{
        for(size_t i{0};i < v_size;++i){
            arr[i] = src.arr[i];
        }
    }

    //copy operator=
    const Vector<T>& operator=(const Vector<T>& rhs){
        if(this != &rhs){
            if(v_capacity < rhs.v_size){
                v_size = v_capacity = rhs.v_size;
                delete[] arr;
                arr = new T[v_size];
            }

            for(size_t i{0};i < rhs.v_size;++i){
                arr[i] = rhs.arr[i];
            }
        }

        return *this;
    }

    //dtor
    ~Vector<T>(){
        delete[] arr;
    }

    void push_back(const T& value){
        if(v_size == v_capacity){
            v_capacity = (v_capacity) ? 2 * v_capacity : 1;
            T* tmp = new T[v_capacity];

            for(size_t i{0};i < v_size;++i){
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = tmp;
        }

        arr[v_size] = value;
        ++v_size;
    }

    void pop_back(){
        if(!empty()){
            --v_size;
        }
    }

    const T& operator[](int pos) const{
        if(pos < 0 || pos >= v_size){
            throw std::out_of_range("Subscript out of range");
        }

        return arr[pos];
    }

    T& operator[](int pos){
        return const_cast<T&>(
            static_cast<const Vector<T>>(*this)[pos]
        );
    }

    bool operator==(const Vector<T>& rhs) const{
        if(v_size != rhs.v_size){
            return false;
        }

        for(size_t i{0};i < v_size;++i){
            if(arr[i] != rhs.arr[i]){
                return false;
            }
        }

        return true;
    }

    void insert(int pos){
        if(pos < 0 || pos >= v_size){
            throw std::out_of_range("Subscript out of range");
        }

        
    }


    bool empty() const{
        return (v_size == 0);
    }
    
    size_t Size() const{
        return v_size;
    }

    size_t Capacity() const{
        return v_capacity;
    }
private:
    size_t v_size;
    size_t v_capacity;
    T* arr;
};
#endif