#ifndef ARRAY_H
#define ARRAY_H
#include <stddef.h>
#include <initializer_list>
#include <stdexcept>

template <typename T,size_t size>
class Array{
public:
    //default ctor
    Array<T,size>(): m_size{size}, m_arr{new T[m_size]{}} {}

    //ctors with params
    explicit Array<T,size>(const T& fillerValue): m_size{size}, m_arr{new T[size]} {
        for(size_t i{0};i < m_size;++i){
            m_arr[i] = fillerValue;
        }
    }
    explicit Array<T,size>(const std::initializer_list<T>& initList): m_size{size},m_arr{new T[size]}{
        if(m_size != initList.size()){
            throw std::invalid_argument("The size of initializer list mus tbe equal to the size of array");
        }

        auto itr = initList.begin();
        for(size_t i{0};i < m_size;++i){
            m_arr[i] = *itr;
            ++itr;
        }
    }

    //copy ctor
    Array<T,size>(const Array<T,size>& src): m_size{src.m_size}, m_arr{new T[src.m_size]{}}{
        for(size_t i{0};i < m_size;++i){
            m_arr[i] = src.m_arr[i];
        }
    }

    //move ctor
    Array<T,size>(Array<T,size>&& rhs): m_size{rhs.m_size},m_arr{rhs.m_arr} {
        rhs.m_size = 0;
        rhs.m_arr = nullptr;
    }

    //dtor
    ~Array<T,size>(){
        delete[] m_arr;
    }

    //copy operator=
    //returning const to avoid (a = b) = c
    const Array<T,size>& operator=(const Array<T,size>& rhs){
        if(this != &rhs){
            for(size_t i{0};i < size;++i){
                m_arr[i] = rhs.m_arr[i];
            }
        }

        return *this;
    }

    //move = operator
    const Array<T,size>& operator=(Array<T,size>&& rhs){
        if(this != &rhs){
            delete[] this->m_arr;
            this->m_size = rhs.m_size;
            this->m_arr = rhs.m_arr;
            rhs.m_size = 0;
            rhs.m_arr = nullptr;
        }

        return *this;
    }

    void fill(const T& fillerValue){
        for(size_t i{0};i < m_size;++i){
            m_arr[i] = fillerValue;
        }
    }
    size_t Size() const{
        return m_size;
    }
    
    const T& operator[](size_t subscript) const{
        if(subscript >= m_size){
            throw std::out_of_range("Subscript out of range");
        }

        return m_arr[subscript];
    }

     T& operator[](size_t subscript) {
        if(subscript >= m_size){
            throw std::out_of_range("Subscript out of range");
        }

        return m_arr[subscript];
    }

    bool operator==(const Array<T,size>& rhs) const{
        if(m_size != rhs.m_size){
            return false;
        }

        for(size_t i{0};i < m_size;++i){
            if(m_arr[i] != rhs.m_arr[i]){
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Array<T,size>& rhs) const{
        return (!(*this == rhs));
    }
    
    

private:
    size_t m_size;
    T* m_arr;

};
#endif