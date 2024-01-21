#ifndef BST_HPP
#define BST_HPP

#include <utility>
#include <stdexcept>

template <typename T>
class binary_search_tree{
//helper types
public:
    struct node;
    struct const_bst_iterator;
    struct bst_iterator;

//special member functions
public:
    binary_search_tree() = default;
    binary_search_tree(const binary_search_tree& src);
    binary_search_tree& operator=(const binary_search_tree& rhs);
    binary_search_tree(binary_search_tree&& src) noexcept;
    binary_search_tree& operator=(binary_search_tree&& rhs) noexcept;
    ~binary_search_tree();

//member accesss
public:
    const T& minimum() const;
    const T& maximum() const;

    //returns true if there is a node with a given key
    bool search(const T& key) const;

//modifiers
public:
    //if there is already a node with the given key returns false, otherwise inserts the node and returns true
    bool insert(const T& key);

    //if there is a node with the given key, removes it and returns true, otherwise returns false
    bool remove(const T& key);

    //swaps  two binary search trees
    void swap(binary_search_tree& other);

//iterators
public:
    bst_iterator begin();
    bst_iterator end();

    const_bst_iterator begin() const;
    const_bst_iterator end() const;

    const_bst_iterator cbegin() const;
    const_bst_iterator cend() const;


//utility functions
private:
    node* get_new_node(const T& key) const;

    void copy(node* source_root);
    void clear(node* root);

    node* find(const T& key) const;

    node* find_min(node* root) const;
    node* find_max(node* root) const;

    node* successor(node* current) const;
    node* predecessor(node* current) const;

    //replaces the subtree rooted at node u, with the subtree rooted at node v
    void transplant(node* u, node* v);

private:
    node* m_root{nullptr};
};

template <typename T>
struct binary_search_tree<T>::node{
public:
    node(const T& key)
    : m_key{key} 
    , m_parent{nullptr}
    , m_left{nullptr}
    , m_right{nullptr} {}

    const T& key() const{
        return m_key;
    }

    T& key(){
        return const_cast<T&>(std::as_const(*this).key());
    }

    node* m_parent;
    node* m_left;
    node* m_right;
    T m_key;
};

template <typename T>
struct binary_search_tree<T>::const_bst_iterator{
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer =const value_type*;
    using reference =const value_type&;
    using iterator_type = typename binary_search_tree<T>::const_bst_iterator;

public:
    explicit const_bst_iterator(node* ptr = nullptr): m_ptr{ptr} {}

    pointer operator->() const{
        if(m_ptr == nullptr){
            throw std::runtime_error("Dereferencing an invalid iterator");
        }
        return m_ptr;
    }

    reference operator*() const{
        if(m_ptr == nullptr){
            throw std::runtime_error("Dereferencing an invalid iterator");
        }

        return m_ptr->key();
    }

    const_bst_iterator& operator++(){
        if(m_ptr == nullptr){
            throw std::runtime_error("Incrementing an invalid iterator");
        }
        increment();
        return *this;
    }

    const_bst_iterator operator++(int){
        if(m_ptr == nullptr){
            throw std::runtime_error("Incrementing an invalid iterator");
        }
        const_bst_iterator old{*this};
        increment();
        return old;
    }

    const_bst_iterator& operator--(){
        if(m_ptr == nullptr){
            throw std::runtime_error("Decrementing an invalid iterator");
        }
        decrement();
        return *this;
    }

    const_bst_iterator operator--(int){
        if(m_ptr == nullptr){
            throw std::runtime_error("Decrementing an invalid iterator");
        }
        const_bst_iterator old{*this};
        decrement();
        return old;
    }

    friend bool operator==(const_bst_iterator it1, const_bst_iterator it2){
        return it1.m_ptr == it2.m_ptr;
    }

    friend bool operator!=(const_bst_iterator it1, const_bst_iterator it2){
        return it1.m_ptr != it2.m_ptr;
    }

    void increment(){
        typename binary_search_tree<T>::node* tmp{nullptr};
        if(m_ptr->m_right != nullptr){
            tmp = m_ptr->m_right;
            while(tmp->m_left != nullptr){
                tmp = tmp->m_left;
            }
        }else{
            tmp = m_ptr->m_parent;
            while((tmp != nullptr) && m_ptr == tmp->m_right){
                m_ptr = tmp;
                tmp = tmp->m_parent;
            }

        }
        m_ptr = tmp;
    }

    void decrement(){
        typename binary_search_tree<T>::node* tmp{nullptr};
        if(m_ptr->m_left != nullptr){
            tmp = m_ptr->m_left;
            while(tmp->m_right != nullptr){
                tmp = tmp->m_right;
            }
        }else{
            tmp = m_ptr->m_parent;
            while(tmp != nullptr && m_ptr == tmp->m_left){
                m_ptr = tmp;
                tmp = tmp->m_parent;
            }
        }
        m_ptr = tmp;
    }
    
    node* m_ptr;
};

template <typename T>
struct binary_search_tree<T>::bst_iterator:public const_bst_iterator{
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_type = typename binary_search_tree<T>::bst_iterator;

public:
    explicit bst_iterator(node* ptr = nullptr): const_bst_iterator(ptr) {}

    pointer operator->(){
        return const_cast<pointer>(const_bst_iterator::m_ptr);
    }

    reference operator*(){
        return const_cast<reference>(const_bst_iterator::m_ptr->key());
    }

    bst_iterator& operator++(){
        if(const_bst_iterator::m_ptr == nullptr){
            throw std::runtime_error("Incrementing an invalid iterator");
        }
        const_bst_iterator::increment();
        return *this;
    }

    bst_iterator operator++(int){
        if(const_bst_iterator::m_ptr == nullptr){
            throw std::runtime_error("Incrementing an invalid iterator");
        }
        bst_iterator old{*this};
        const_bst_iterator::increment();
        return old;
    }

    bst_iterator& operator--(){
        if(const_bst_iterator::m_ptr == nullptr){
            throw std::runtime_error("Decrementing an invalid iterator");
        }
        const_bst_iterator::decrement();
        return *this;
    }

    bst_iterator operator--(int){
        if(const_bst_iterator::m_ptr == nullptr){
            throw std::runtime_error("Decrementing an invalid iterator");
        }
        bst_iterator old{*this};
        const_bst_iterator::decrement();
        return old;
    }

    friend bool operator==(bst_iterator it1, bst_iterator it2){
        return it1.m_ptr == it2.m_ptr;
    }

    friend bool operator!=(bst_iterator it1, bst_iterator it2){
        return it1.m_ptr != it2.m_ptr;
    }
};
#include "BST.tpp"
#endif