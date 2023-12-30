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

//iterators
public:

    //const_iterator
    struct const_vector_iterator{
        using iterator = typename vector<T>::vector_iterator;
        using const_iterator =typename vector<T>::const_vector_iterator;

        using value_type = typename vector<T>::value_type;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_type = typename vector<T>::const_vector_iterator;

        const_vector_iterator(pointer ptr): m_ptr{ptr} {}

        reference operator*() const
        {
            return (*m_ptr);
        }

        pointer operator->() const{
            return m_ptr;
        }

        const_vector_iterator& operator++()
        {
            ++m_ptr;
            return *this;
        }

        const_vector_iterator operator++(int)
        {
            const_vector_iterator tmp(m_ptr);
            ++m_ptr;
            return tmp;
        }

        const_vector_iterator& operator--()
        {
            --m_ptr;
            return *this;
        }

        const_vector_iterator operator--(int)
        {
            const_vector_iterator tmp(m_ptr);
            --m_ptr;
            return tmp;
        }

        const_vector_iterator operator+(difference_type n)
        {
            return const_vector_iterator(m_ptr + n);
        }

        const_vector_iterator operator-(difference_type n)
        {
            return const_vector_iterator(m_ptr - n);
        }

        difference_type operator-(const const_vector_iterator& other)
        {
            return (m_ptr - other.m_ptr);
        }

        const_vector_iterator& operator+=(difference_type n)
        {
            m_ptr += n;
            return *this;
        }

        const_vector_iterator& operator-=(difference_type n)
        {
            m_ptr -= n;
            return *this;
        }

        reference operator[](difference_type pos)
        {
            return m_ptr[pos];
        }

        friend bool operator==(const const_vector_iterator& it1, const const_vector_iterator& it2)
        {
            return (it1.m_ptr == it2.m_ptr);
        }

        friend bool operator<(const const_vector_iterator& it1, const const_vector_iterator& it2)
        {
            return (it1.m_ptr < it2.m_ptr);
        }

        friend bool operator>(const const_vector_iterator& it1, const const_vector_iterator& it2)
        {
            return (it1.m_ptr > it2.m_ptr);
        }

        friend bool operator>=(const const_vector_iterator& it1, const const_vector_iterator& it2)
        {
            return (it1.m_ptr >= it2.m_ptr);
        }

        friend bool operator<=(const const_vector_iterator& it1, const const_vector_iterator& it2)
        {
            return (it1.m_ptr <= it2.m_ptr);
        }

        friend bool operator!=(const const_vector_iterator& it1, const const_vector_iterator& it2)
        {
            return (it1.m_ptr != it2.m_ptr);
        }

    protected:
        pointer m_ptr{nullptr};
    };

public:   
    //iterator
    struct vector_iterator:public const_vector_iterator{
        using value_type = typename vector<T>::value_type;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_type = typename vector<T>::vector_iterator;

        vector_iterator(pointer ptr):const_vector_iterator(ptr) {}

        reference operator*()
        {
            return const_cast<reference>(*(const_vector_iterator::m_ptr));
        }

        pointer operator->()
        {
            return const_cast<pointer>(this->const_vector_iterator::m_ptr);
        }

        vector_iterator& operator++()
        {
            ++const_vector_iterator::m_ptr;
            return *this;
        }

        vector_iterator operator++(int)
        {
            vector_iterator tmp(const_vector_iterator::m_ptr);
            ++const_vector_iterator::m_ptr;
            return tmp;
        }

        vector_iterator& operator--()
        {
            --const_vector_iterator::m_ptr;
            return *this;
        }

        vector_iterator operator--(int)
        {
            vector_iterator tmp(const_vector_iterator::m_ptr);
            --const_vector_iterator::m_ptr;
            return tmp;
        }

        vector_iterator operator+(difference_type n)
        {
            return vector_iterator(const_vector_iterator::m_ptr + n);
        }

        vector_iterator operator-(difference_type n)
        {
            return vector_iterator(const_vector_iterator::m_ptr - n);
        }

        difference_type operator-(const const_vector_iterator& other)
        {
            return (const_vector_iterator::m_ptr - other.const_vector_iterator::m_ptr);
        }

        vector_iterator& operator+=(difference_type n)
        {
            const_vector_iterator::m_ptr += n;
            return *this;
        }

        vector_iterator& operator-=(difference_type n)
        {
            this->const_vector_iterator::m_ptr -= n;
            return *this;
        }

        reference operator[](difference_type pos)
        {
            return const_cast<reference>(const_vector_iterator::m_ptr[pos]);
        }

        friend bool operator==(const vector_iterator& it1, const vector_iterator& it2)
        {
            return (it1.const_vector_iterator::m_ptr == it2.const_vector_iterator::m_ptr);
        }

        friend bool operator<(const vector_iterator& it1, const vector_iterator& it2)
        {
            return (it1.const_vector_iterator::m_ptr < it2.const_vector_iterator::m_ptr);
        }

        friend bool operator>(const vector_iterator& it1, const vector_iterator& it2)
        {
            return (it1.const_vector_iterator::m_ptr > it2.const_vector_iterator::m_ptr);
        }

        friend bool operator>=(const vector_iterator& it1, const vector_iterator& it2)
        {
            return (it1.const_vector_iterator::m_ptr >= it2.const_vector_iterator::m_ptr);
        }

        friend bool operator<=(const vector_iterator& it1, const vector_iterator& it2)
        {
            return (it1.const_vector_iterator::m_ptr <= it2.const_vector_iterator::m_ptr);
        }

        friend bool operator!=(const vector_iterator& it1, const vector_iterator& it2)
        {
            return (it1.const_vector_iterator::m_ptr != it2.const_vector_iterator::m_ptr);
        }
    };

//iterator functions
public:
    vector_iterator begin();
    vector_iterator end();

    const_vector_iterator begin() const;
    const_vector_iterator end() const;

    const_vector_iterator cbegin() const;
    const_vector_iterator cend() const;

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