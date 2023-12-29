#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "Vector.hpp"

template <typename T>
vector<T>::vector()
: m_size{0}
, m_capacity{0}
, m_vec{nullptr} 
{}

template <typename T>
vector<T>::vector(size_type count)
: m_size{count}
, m_capacity{count}
, m_vec{new T[count]{}} 
{}

template <typename T>
vector<T>::vector(size_type count, const T& value)
: m_size{count}
, m_capacity{count}
, m_vec{new T[count]} 
{
    for(int i{0};i < m_size; ++i){
        m_vec[i] = value;
    }
}

template <typename T>
vector<T>::vector(std::initializer_list<T> init)
: m_size{0}
, m_capacity{init.size()}
, m_vec{new T[init.size()]}
{
    
    for(const auto& elem : init){
        push_back(elem);
    }
}

template <typename T>
vector<T>::vector(const vector<T>& other)
: m_size{other.m_size}
, m_capacity{other.m_size}
, m_vec{new T[other.m_size]}
{
    copy(other);
}

template <typename T>
vector<T>::vector(vector<T>&& other) noexcept
: m_size{other.m_size}
, m_capacity{other.m_capacity}
, m_vec{other.m_vec} 
{
    other.m_capacity = 0;
    other.m_size = 0;
    other.m_vec = nullptr;
}

template <typename T>
vector<T>::~vector()
{
    delete[] m_vec;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other)
{
    vector<T> tmp(other);
    swap(tmp);
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) noexcept
{
    m_size = std::exchange(other.m_size, 0);
    m_capacity = std::exchange(other.m_capacity, 0);
    m_vec = std::exchange(other.m_vec, nullptr);
    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(std::initializer_list<T> init)
{
    vector<T> tmp(init);
    swap(tmp);
    return *this;
}

template <typename T>
void vector<T>::assign(size_type count, const T& value)
{
    if(count > m_capacity){
        realloc(count);
    }
    m_size = 0;
    push_back(value);

}

template <typename T>
void vector<T>::assign(std::initializer_list<T> init)
{
    if(init.size() > m_capacity){
        realloc(init.size());
    }

    m_size = 0;
    for(const auto& elem : init){
        push_back(elem);
    }
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const
{
    if(pos < 0 || pos >= m_size){
        throw std::out_of_range("Attempt to access a subscript out of range");
    }

    return m_vec[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos)
{
    return const_cast<T&>(std::as_const(*this).at(pos));
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const
{
    return m_vec[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos)
{
    return const_cast<T&>(std::as_const(*this)[pos]);
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const
{
    return m_vec[0];
}

template <typename T>
typename vector<T>::reference vector<T>::front()
{
    return const_cast<T&>(std::as_const(*this).front());
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const
{
    return m_vec[m_size - 1];
}

template <typename T>
typename vector<T>::reference vector<T>::back()
{
    return const_cast<T&>(std::as_const(*this).back());
}

template <typename T>
const T* vector<T>::data() const
{
    return m_vec;
}

template <typename T>
T* vector<T>::data()
{
    return const_cast<T*>(std::as_const(*this).data());
}


template <typename T>
bool vector<T>::empty() const
{
    return (m_size == 0);
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const
{
    return m_size;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
void vector<T>::reserve(size_type new_cap)
{
    realloc(new_cap);
}

template <typename T>
void vector<T>::shrink_to_fit()
{
    realloc(m_size);
}

template <typename T>
void vector<T>::push_back(const T& value)
{
    if(m_size == m_capacity){
        realloc(2 * m_capacity);
    }

    m_vec[m_size] = value;
    ++m_size;
}

template <typename T>
void vector<T>::pop_back()
{
    if(empty()){
        throw std::out_of_range("Attempt to call pop_back on an empty vector");
    }

    --m_size;
}

template <typename T>
void vector<T>::insert(size_type pos, const T& value)
{

    if(pos < 0 || pos >= m_size){
        throw std::out_of_range("Subscript out of range");
    }
    if(m_size == m_capacity){
        realloc(2 * m_capacity);
    }

    for(int i{m_size};i > pos; --i){
        m_vec[i] = m_vec[i - 1];
    }

    m_vec[pos] = value;
    ++m_size;
}

template <typename T>
void vector<T>::clear()
{
    m_size = 0;
    m_capacity = 0;
    delete[] m_vec;
    
}

template <typename T>
void vector<T>::swap(vector<T>& other)
{
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_vec, other.m_vec);
}

template <typename U>
bool operator==(const vector<U>& lhs, const vector<U>& rhs)
{
    if(lhs.size() != rhs.size()){
        return false;
    }

    for(int i{0};i < rhs.size(); ++i){
        if(lhs[i] != rhs[i]){
            return false;
        }
    }

    return true;
}

template <typename T>
void vector<T>::realloc(size_type new_cap){
    if(new_cap == 0){
        new_cap = 1;
    }

    T* tmp = new T[new_cap];
    for(int i{0};i < m_size; ++i){
        tmp[i] = m_vec[i];
    }

    delete[] m_vec;
    m_vec = tmp;
}

template <typename T>
void vector<T>::copy(const vector<T>& other){
    for(int i{0};i < m_size; ++i){
        m_vec[i] = other.m_vec[i];
    }
}

#endif