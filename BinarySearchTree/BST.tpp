#ifndef BST_TPP
#define BST_TPP

#include "BST.hpp"
#include <utility>


template <typename T>
binary_search_tree<T>::binary_search_tree(const binary_search_tree<T>& src){
    copy(src.m_root);
}

template <typename T>
binary_search_tree<T>::binary_search_tree(binary_search_tree<T>&& src) noexcept: m_root{src.m_root}{
    src.m_root = nullptr;
}

template <typename T>
binary_search_tree<T>& binary_search_tree<T>::operator=(const binary_search_tree<T>& rhs){
    binary_search_tree<T> tmp{rhs};
    swap(tmp);
    return *this;
}

template <typename T>
binary_search_tree<T>& binary_search_tree<T>::operator=(binary_search_tree<T>&& rhs) noexcept{
    if(this != &rhs){
        m_root = std::exchange(rhs.m_root, nullptr);
    }

    return *this;
}

template <typename T>
binary_search_tree<T>::~binary_search_tree(){
    clear(m_root);
}

template <typename T>
const T& binary_search_tree<T>::minimum() const{
    return *(find_min(m_root));
}

template <typename T>
const T& binary_search_tree<T>::maximum() const{
    return *(find_max(m_root));
}

template <typename T>
bool binary_search_tree<T>::search(const T& key) const{
    return (find(key) != nullptr);
}

template <typename T>
bool binary_search_tree<T>::insert(const T& key){
    node* newNode = get_new_node(key);
    node* tmp{m_root};
    node* parent{nullptr};

    while(tmp != nullptr){
        parent = tmp;
        if(key == tmp->key()){
            return false;
        }else if(key < tmp->key()){
            tmp = tmp->m_left;
        }else{
            tmp = tmp->m_right;
        }
    }
    newNode->m_parent = parent;
    if(parent == nullptr){
        m_root = newNode;
    }else if(key < parent->key()){
        parent->m_left = newNode;
    }else{
        parent->m_right = newNode;
    }
    return true;
}

template <typename T>
bool binary_search_tree<T>::remove(const T& key){
    node* to_remove{find(key)};
    if(to_remove != nullptr){
        if(to_remove->m_left == nullptr){
            transplant(to_remove,to_remove->m_right);
        }else if(to_remove->m_right == nullptr){
            transplant(to_remove,to_remove->m_left);
        }else{
            node* node_successor{find_min(to_remove->m_right)};
            if(node_successor != to_remove->m_right){
                transplant(node_successor,node_successor->m_right);
                node_successor->m_right = to_remove->m_right;
                node_successor->m_right->m_parent = node_successor;
            }
            transplant(to_remove,node_successor);
            node_successor->m_left = to_remove->m_left;
            node_successor->m_left->m_parent = node_successor;
        }

        delete to_remove;
        return true;
    }
    return false;
}

template <typename T>
void binary_search_tree<T>::swap(binary_search_tree<T>& other){
    std::swap(m_root, other.m_root);
}

template <typename T>
typename binary_search_tree<T>::bst_iterator binary_search_tree<T>::begin(){
    return bst_iterator(find_min(m_root));
}

template <typename T>
typename binary_search_tree<T>::const_bst_iterator binary_search_tree<T>::begin() const{
    return const_bst_iterator(find_min(m_root));
}

template <typename T>
typename binary_search_tree<T>::const_bst_iterator binary_search_tree<T>::cbegin() const{
    return const_bst_iterator(find_min(m_root));
}

template <typename T>
typename binary_search_tree<T>::const_bst_iterator binary_search_tree<T>::end() const{
    return const_bst_iterator(find_max(m_root)->m_right);
}

template <typename T>
typename binary_search_tree<T>::bst_iterator binary_search_tree<T>::end(){
    return bst_iterator(find_max(m_root)->m_right);
}

template <typename T>
typename binary_search_tree<T>::const_bst_iterator binary_search_tree<T>::cend() const{
    return const_bst_iterator(find_max(m_root)->m_right);
}

template <typename T>
typename binary_search_tree<T>::node* binary_search_tree<T>::get_new_node(const T& val) const{
    return (new node(val));
}

template <typename T>
void binary_search_tree<T>::clear(typename binary_search_tree<T>::node* root){
    if(root != nullptr){
        clear(root->m_left);
        clear(root->m_right);
        delete root;
    }
}

template <typename T>
typename binary_search_tree<T>::node* binary_search_tree<T>::find(const T& key) const{
    node* tmp{m_root};
    while(tmp != nullptr && key != tmp->key()){
        if(key < tmp->key()){
            tmp = tmp->m_left;
        }else{
            tmp = tmp->m_right;
        }
    }
    return tmp;
}

template <typename T>
typename binary_search_tree<T>::node* binary_search_tree<T>::find_min(typename binary_search_tree<T>::node* root) const{
    while(root -> m_left != nullptr){
        root = root -> m_left;
    }

    return root;
}

template <typename T>
typename binary_search_tree<T>::node* binary_search_tree<T>::find_max(typename binary_search_tree<T>::node* root) const{
    while(root -> m_right != nullptr){
        root = root -> m_right;
    }

    return root;
}

template <typename T>
typename binary_search_tree<T>::node* binary_search_tree<T>::successor(typename binary_search_tree<T>::node* curr) const{
    if(curr->m_right != nullptr){
        return find_min(curr->m_right);
    }

    node* tmp = curr->m_parent;
    while(tmp != nullptr && curr == tmp->m_right){
        curr = tmp;
        tmp = tmp->m_parent;
    }

    return tmp;
}

template <typename T>
typename binary_search_tree<T>::node* binary_search_tree<T>::predecessor(typename binary_search_tree<T>::node* curr) const{
    if(curr->m_left != nullptr){
        return find_max(curr->m_left);
    }

    node* tmp = curr->m_parent;
    while(tmp != nullptr && curr == tmp->m_leftt){
        curr = tmp;
        tmp = tmp->m_parent;
    }

    return tmp;
}

template <typename T>
void binary_search_tree<T>::copy(typename binary_search_tree<T>::node* source_node){
    if(source_node != nullptr){
        insert(source_node->key());
        copy(source_node->m_left);
        copy(source_node->m_right);
    }    
}

template <typename T>
void binary_search_tree<T>::transplant(typename binary_search_tree<T>::node* to_replace, typename binary_search_tree<T>::node* to_transplant){
    if(to_replace->m_parent == nullptr){
        m_root = to_transplant;
    }else if(to_replace == to_replace->m_parent->m_left){
        to_replace->m_parent->m_left = to_transplant;
    }else{
        to_replace->m_parent->m_right = to_transplant;
    }
    if(to_transplant != nullptr){
        to_transplant->m_parent = to_replace->m_parent;
    }
   
}
#endif