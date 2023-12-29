#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <utility>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class vector{

public:
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

public:
    vector();
    explicit vector(size_type count);
    vector(size_type count, const T& value);
    vector(const vector<T>& other);
    vector(vector<T>&& other) noexcept;
    vector(std::initializer_list<T> init);
    ~vector();

public:
    vector& operator=(const vector& other);
    vector& operator=(vector&& other) noexcept;
    vector& operator=(std::initializer_list<T> init);

    void assign(size_type count, const T& value);
    void assign(std::initializer_list<T> init);

//element access
public:
    //access specified element with bound checking
    const_reference at(size_type pos) const;
    reference at(size_type pos);
    
    
    //access specified element
    const_reference operator[](size_type pos) const;
    reference operator[](size_type pos);
    

    //acces the first element
    const_reference front() const;
    reference front();
    

    //access the last element
    const_reference back() const;
    reference back();
    

    //access the underlying contiguous stotage
    const T* data() const;
    T* data();
    

//Capacity
public:
    bool empty() const;
    size_type size() const;
    size_type capacity() const;
    void reserve(size_type new_cap);
    void shrink_to_fit();

//Modifiers
public:
    void push_back(const T& value);
    void pop_back();
    void insert(size_type pos, const T& value);
    void clear();
    void swap(vector& other);

//non member functions
public:
    template <typename U>
    friend bool operator==(const vector<U>& lhs, const vector<U>& rhs);


//utility functions
private:
    void copy(const vector& other);
    void realloc(size_type new_cap);

//data members
private:
    std::size_t m_size;
    std::size_t m_capacity;
    T* m_vec;
};

#include "Vector.tpp"
#endif