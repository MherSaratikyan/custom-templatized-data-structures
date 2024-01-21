#ifndef LIST_TPP
#define LIST_TPP

#include "list.hpp"


template <typename T>
list<T>::list(size_type count, const T& val)
{
    for(int i{0};i < count;++i){
        push_back(val);
    }
}

template <typename T>
list<T>::list(size_type count): list(count, T{}) {}

template <typename T>
list<T>::list(const list& src)
{
    copy(src);
}

template <typename T>
list<T>::list(list&& src) noexcept
: m_head{src.m_head}
, m_tail{src.m_tail}
, m_size{src.m_size}
{
    src.m_head = nullptr;
    src.m_tail = nullptr;
    src.m_size = 0;
}

template <typename T>
list<T>::list(std::initializer_list<T> ilist)
{
    for(const auto& item : ilist){
        push_back(item);
    }
}

template <typename T>
list<T>::~list(){
    clear();
}


template <typename T>
list<T>& list<T>::operator=(const list<T>& rhs){
    list<T> tmp(rhs);
    swap(tmp);
    return *this;
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& rhs) noexcept{
    if(this != &rhs){
        m_head = std::exchange(rhs.m_head, nullptr);
        m_tail = std::exchange(rhs.m_tail, nullptr);
        m_size = std::exchange(rhs.m_size, 0);
    }

    return *this;
}

template <typename T>
list<T>& list<T>::operator=(std::initializer_list<T> ilist){
    list<T> tmp(ilist);
    swap(tmp);
    return *this;
}


template <typename T>
const T& list<T>::front() const{
    return *m_head;
}

template <typename T>
T& list<T>::front(){
    return const_cast<T&>(std::as_const(*this).front());
}

template <typename T>
const T& list<T>::back() const{
    return *m_tail;
}

template <typename T>
T& list<T>::back(){
    return const_cast<T&>(std::as_const(*this).back());
}

template <typename T>
bool list<T>::empty() const{
    return m_size == 0;
}

template <typename T>
std::size_t list<T>::size() const{
    return m_size;
}

template <typename T>
void list<T>::push_front(const T& val){
    list_node* newNode  = getNewNode(val);
    if(empty()){
        m_head = m_tail = newNode;
    }else{
        newNode -> m_next = m_head;
        m_head -> m_prev = newNode;
        m_head = newNode;
    }

    ++m_size;
}

template <typename T>
void list<T>::pop_front(){
    if(!empty()){
        if(m_head == m_tail){
            delete m_head;
            m_head = m_tail = nullptr;
        }else{
            list_node* tmp{m_head};
            m_head = m_head -> m_next;
            delete tmp;
            m_head -> m_prev = nullptr;
        }
        --m_size;
    } 
}

template <typename T>
void list<T>::push_back(const T& val){
    list_node* newNode = getNewNode(val);
    if(empty()){
        m_head = m_tail = newNode;
    }else{
        m_tail -> m_next = newNode;
        newNode -> m_prev = m_tail;
        m_tail = newNode;
    }

    ++m_size;
}

template <typename T>
void list<T>::pop_back(){
    if(!empty()){
        if(m_head == m_tail){
            delete m_tail;
            m_head = m_tail = nullptr;
        }else{
            list_node* tmp{m_tail};
            m_tail = m_tail->m_prev;
            delete tmp;
            m_tail->m_next = nullptr;
        }

        --m_size;
    }
}

template <typename T>
void list<T>::insert(const_list_iterator pos, const T& val){
    if(pos == cbegin()){
        push_front(val);
    }else if(pos == cend()){
        push_back(val);
    }else{
        list_node* newNode = getNewNode(val);
        newNode -> m_next = pos.m_ptr;
        newNode -> m_prev = pos.m_ptr->m_prev;
        (pos.m_ptr)->m_prev->m_next = newNode;
        (pos.m_ptr)->m_prev = newNode;
        ++m_size;
    }
}

template <typename T>
void list<T>::insert(const_list_iterator pos, size_type count, const T& val){
    for(int i = 0;i < count;++i){
        insert(pos, val);
        --pos;
    }
}

template <typename T>
void list<T>::erase(const_list_iterator pos){
    if(pos == cbegin()){
        pop_front();
    }else if(pos == cend()){
        pop_back();
    }else{
        list_node* tmp = pos.m_ptr;
        tmp -> m_next -> m_prev = tmp -> m_prev;
        tmp ->m_prev -> m_next = tmp -> m_next;
        delete tmp;
        --m_size;
    }
}

template <typename T>
void list<T>::clear(){
    while(m_head != nullptr){
        list_node* tmp = m_head;
        m_head = m_head -> m_next;
        delete tmp;
    }
}

template <typename T>
void list<T>::swap(list<T>& other){
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

template <typename T>
void list<T>::copy(const list<T>& other){
    list_node* tmp{other.m_head};
    while(tmp != nullptr){
        push_back(tmp->value());
        tmp = tmp -> m_next;
    }
}

template <typename T>
typename list<T>::list_node* list<T>::getNewNode(const T& val) const{
    list_node* newNode = new list_node(val);
    return newNode;
}

template <typename T>
typename list<T>::const_list_iterator list<T>::begin() const{
    return const_list_iterator(m_head);
}

template <typename T>
typename list<T>::const_list_iterator list<T>::end() const{
    list_node* ptr = (m_head == nullptr) ? m_tail : m_tail->m_next;
    return const_list_iterator(ptr);
}

template <typename T>
typename list<T>::const_list_iterator list<T>::cbegin() const{
    return const_list_iterator(m_head);
}

template <typename T>
typename list<T>::const_list_iterator list<T>::cend() const{
    list_node* ptr = (m_head == nullptr) ? m_tail : m_tail->m_next;
    return const_list_iterator(ptr);
}

template <typename T>
typename list<T>::list_iterator list<T>::begin(){
    return list_iterator(m_head);
}

template <typename T>
typename list<T>::list_iterator list<T>::end(){
    list_node* ptr = (m_head == nullptr) ? m_tail : m_tail->m_next;
    return list_iterator(ptr);
}

#endif