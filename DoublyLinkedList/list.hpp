#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class list{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;

public:
struct list_node;
struct const_list_iterator;
struct list_iterator;

public:
    list() = default;
    list(size_type count, const T& value);
    explicit list(size_type count);
    list(const list& src);
    list(list&& src) noexcept;
    list(std::initializer_list<T> ilist);
    ~list();

public:
    list& operator=(const list& rhs);
    list& operator=(list&& other) noexcept;
    list& operator=(std::initializer_list<T> ilist);

public:
    const_reference front() const;
    reference front();
    const_reference back() const;
    reference back();

public:
    bool empty() const;
    size_type size() const;

public:
    void push_front(const T& val);
    void pop_front();

    void push_back(const T& val);
    void pop_back();

    //inserts value before pos
    void insert(const_list_iterator pos, const T& val);

    //inserts count values before pos
    void insert(const_list_iterator pos, size_type count, const T& val);

    //removes element at pos
    void erase(const_list_iterator pos);
    
    void clear();
    void swap(list& other);
    
public:
    list_iterator begin();
    list_iterator end();

    const_list_iterator begin() const;
    const_list_iterator end() const;

    const_list_iterator cbegin() const;
    const_list_iterator cend() const;

private:
    void copy(const list& other);
    list_node* getNewNode(const T& val);

private:
    list_node* m_head{nullptr};
    list_node* m_tail{nullptr};
    std::size_t m_size{0};
};

//node
template <typename T>
struct list<T>::list_node{
    list_node(const T& val)
    : m_val{val}
    , m_next{nullptr}
    , m_prev{nullptr} {}

    const T& value() const{
        return m_val;
    }

    T& value(){
        return const_cast<T&>(std::as_const(*this).value());
    }

    T m_val;
    list_node* m_next;
    list_node* m_prev;
};

//const_iterator
template <typename T>
struct list<T>::const_list_iterator{
public:
    using value_type = typename list<T>::value_type;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = const value_type*;
    using reference = const value_type&;
    using iterator_type = typename list<T>::const_list_iterator;

public:
    explicit const_list_iterator(list_node* ptr = nullptr): m_ptr{ptr} {}

    //the behaviour is undefined if m_ptr is nullptr
    reference operator*() const{
        return m_ptr -> value();
    }

    //the behaviour is undefined if m_ptr is nullptr
    pointer operator->() const{
        return m_ptr;
    }

    const_list_iterator& operator++(){
        increment();
        return *this;
    }

    const_list_iterator operator++(int){
        const_list_iterator old(*this);
        this->increment();
        return old;
    }

    const_list_iterator& operator--(){
        decrement();
        return *this;
    }

    const_list_iterator operator--(int){
        const_list_iterator old(*this);
        this->decrement();
        return old;
    }

    friend bool operator==(const const_list_iterator& it1, const const_list_iterator it2){
        return it1.m_ptr == it2.m_ptr;
    }

    friend bool operator!=(const const_list_iterator& it1, const const_list_iterator& it2){
        return it1.m_ptr != it2.m_ptr;
    }


    list_node* m_ptr{nullptr};

    //the behaviour is undefined if m_ptr already refers to past-the-end element or otherwise invalid
    void increment(){
        m_ptr = m_ptr -> m_next;
    }

    //the behaviour is undefined if m_ptr already referes to the first element or otherwise invalid
    void decrement(){
        m_ptr = m_ptr -> m_prev;
    }
};

template <typename T>
struct list<T>::list_iterator: public const_list_iterator{
public:
    using value_type = typename list<T>::value_type;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_type = typename list<T>::iterator;

public:
    explicit list_iterator(list_node* ptr): const_list_iterator(ptr) {}

    //the behaviour is undefined if m_ptr is nullptr
    reference operator*(){
        return const_cast<reference>(const_list_iterator::m_ptr->value());
    }

    //the behaviour is undefined if m_ptr is nullptr
    pointer operator->(){
        return const_cast<pointer>(const_list_iterator::m_ptr);
    }

    list_iterator& operator++(){
        this->const_list_iterator::increment();
        return *this;
    }

    list_iterator operator++(int){
        list_iterator old(*this);
        this->const_list_iterator::increment();
        return old;
    }

    list_iterator& operator--(){
        this->const_list_iterator::decrement();
        return *this;
    }

    list_iterator operator--(int){
        list_iterator old(*this);
        this->const_list_iterator::decrement();
        return old;
    }

    friend bool operator==(const list_iterator& it1, const list_iterator& it2){
        return (it1.m_ptr == it2.m_ptr);
    }

    friend bool operator==(const list_iterator& it1, const list_iterator* it2){
        return !(it1 == it2);
    }
};

#include "list.cpp"
#endif