#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <utility>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class rb_tree{
//helper types
public:
    struct node;
    struct const_rbt_iterator;
    struct rbt_iterator;
//special member functions
public:
    rb_tree();
    rb_tree(std::initializer_list<T> ilist);
    rb_tree(const rb_tree& src);
    rb_tree(rb_tree&& src) noexcept;
    rb_tree& operator=(const rb_tree& rhs);
    rb_tree& operator=(rb_tree&& rhs) noexcept;
    ~rb_tree() noexcept;

//modifiers
public:
    void insert(const T& key);
    void remove(const T& key);
    void swap(rb_tree& other);

//lookup
public:
    bool search(const T& key) const;

//iterators
    rbt_iterator begin();
    rbt_iterator end();
    const_rbt_iterator begin() const;
    const_rbt_iterator end() const;
    const_rbt_iterator cbegin() const;
    const_rbt_iterator cend() const;

//utility functions
private:
    void clear(node* root);
    void copy(node* src_root);
    node* get_new_node(const T& key) const;

    node* find(const T& key) const;
    node* find_min(node* root) const;
    node* find_max(node* root) const;

    node* successor(node* curr) const;
    node* predecessor(node* curr) const;

    void left_rotate(node* to_rotate);
    void right_rotate(node* to_rotate);
    void transplant(node* to_replace, node* to_transplant);

    void insert_fixup(node* inserted);

    void remove_fixup(node* child);
    
private:
    static node ks_null;   //sentinel node
    node* m_root;   
};

template <typename T>
struct rb_tree<T>::node{
public:
    node(const T& key, node* left, node* right, node* parent)
    : m_key{key}
    , m_left{left}
    , m_right{right}
    , m_parent{parent}
    , is_black{true} {}

    bool is_colored_red() const{
        return !is_black;
    }

    bool is_colored_black() const{
        return is_black;
    }

    void make_black(){
        is_black = true;
    }

    void make_red(){
        is_black = false;
    }


public:
    T m_key;
    node* m_parent;
    node* m_left;
    node* m_right;
    bool is_black;
};

template <typename T>
struct rb_tree<T>::const_rbt_iterator{
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer =const value_type*;
    using reference =const value_type&;
    using iterator_type = typename rb_tree<T>::const_rbt_iterator;

public:
    explicit const_rbt_iterator(node* ptr = &(rb_tree<T>::ks_null)): m_ptr{ptr} {}

    pointer operator->() const{
        if(m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Dereferencing an invalid iterator");
        }
        return m_ptr;
    }

    reference operator*() const{
        if(m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Dereferencing an invalid iterator");
        }

        return m_ptr->m_key;
    }

    const_rbt_iterator& operator++(){
        if(m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Incrementing an invalid iterator");
        }
        increment();
        return *this;
    }

    const_rbt_iterator operator++(int){
        if(m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Incrementing an invalid iterator");
        }
        const_rbt_iterator old{*this};
        increment();
        return old;
    }

    const_rbt_iterator& operator--(){
        if(m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Decrementing an invalid iterator");
        }
        decrement();
        return *this;
    }

    const_rbt_iterator operator--(int){
        if(m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Decrementing an invalid iterator");
        }
        const_rbt_iterator old{*this};
        decrement();
        return old;
    }

    friend bool operator==(const_rbt_iterator it1, const_rbt_iterator it2){
        return it1.m_ptr == it2.m_ptr;
    }

    friend bool operator!=(const_rbt_iterator it1, const_rbt_iterator it2){
        return it1.m_ptr != it2.m_ptr;
    }

    void increment(){
        typename rb_tree<T>::node* tmp{&(rb_tree<T>::ks_null)};
        if(m_ptr->m_right != &(rb_tree<T>::ks_null)){
            tmp = m_ptr->m_right;
            while(tmp->m_left != &(rb_tree<T>::ks_null)){
                tmp = tmp->m_left;
            }
        }else{
            tmp = m_ptr->m_parent;
            while((tmp != &(rb_tree<T>::ks_null)) && m_ptr == tmp->m_right){
                m_ptr = tmp;
                tmp = tmp->m_parent;
            }

        }
        m_ptr = tmp;
    }

    void decrement(){
        typename rb_tree<T>::node* tmp{&(rb_tree<T>::ks_null)};
        if(m_ptr->m_left != &(rb_tree<T>::ks_null)){
            tmp = m_ptr->m_left;
            while(tmp->m_right != &(rb_tree<T>::ks_null)){
                tmp = tmp->m_right;
            }
        }else{
            tmp = m_ptr->m_parent;
            while(tmp != &(rb_tree<T>::ks_null) && m_ptr == tmp->m_left){
                m_ptr = tmp;
                tmp = tmp->m_parent;
            }
        }
        m_ptr = tmp;
    }
    
    node* m_ptr;
};


template <typename T>
struct rb_tree<T>::rbt_iterator:public const_rbt_iterator{
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_type = typename rb_tree<T>::rbt_iterator;

public:
    explicit rbt_iterator(node* ptr = &(rb_tree<T>::ks_null)): const_rbt_iterator(ptr) {}

    pointer operator->(){
        return const_cast<pointer>(const_rbt_iterator::m_ptr);
    }

    reference operator*(){
        return const_cast<reference>(const_rbt_iterator::m_ptr->m_key);
    }

    rbt_iterator& operator++(){
        if(const_rbt_iterator::m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Incrementing an invalid iterator");
        }
        const_rbt_iterator::increment();
        return *this;
    }

    rbt_iterator operator++(int){
        if(const_rbt_iterator::m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Incrementing an invalid iterator");
        }
        rbt_iterator old{*this};
        const_rbt_iterator::increment();
        return old;
    }

    rbt_iterator& operator--(){
        if(const_rbt_iterator::m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Decrementing an invalid iterator");
        }
        const_rbt_iterator::decrement();
        return *this;
    }

    rbt_iterator operator--(int){
        if(const_rbt_iterator::m_ptr == &(rb_tree<T>::ks_null)){
            throw std::runtime_error("Decrementing an invalid iterator");
        }
        rbt_iterator old{*this};
        const_rbt_iterator::decrement();
        return old;
    }

    friend bool operator==(rbt_iterator it1, rbt_iterator it2){
        return it1.m_ptr == it2.m_ptr;
    }

    friend bool operator!=(rbt_iterator it1, rbt_iterator it2){
        return it1.m_ptr != it2.m_ptr;
    }
};
#include "RBTree.tpp"
#endif