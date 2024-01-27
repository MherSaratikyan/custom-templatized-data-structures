#ifndef RBTREE_TPP
#define RBTREE_TPP

#include "RBTree.hpp"

template <typename T>
typename rb_tree<T>::node rb_tree<T>::ks_null = node(T{}, nullptr, nullptr, nullptr);

template <typename T>
rb_tree<T>::rb_tree()
: m_root{&ks_null} {}

template <typename T>
rb_tree<T>::rb_tree(std::initializer_list<T> ilist): rb_tree(){
    auto start = ilist.begin();
    while(start != ilist.end()){
        insert(*start);
        ++start;
    }
}

template <typename T>
rb_tree<T>::rb_tree(const rb_tree<T>& src): rb_tree(){
    copy(src.m_root);
}

template <typename T>
rb_tree<T>::rb_tree(rb_tree<T>&& src) noexcept: m_root{src.m_root}{
    src.m_root = &ks_null;
}

template <typename T>
rb_tree<T>& rb_tree<T>::operator=(const rb_tree<T>& rhs){
    rb_tree<T> tmp(rhs);
    swap(tmp);
    return *this;
}

template <typename T>
rb_tree<T>& rb_tree<T>::operator=(rb_tree<T>&& rhs) noexcept{
    if(this != &rhs){
        m_root = std::exchange(rhs.m_root, &ks_null);
    }

    return *this;
}

template <typename T>
rb_tree<T>::~rb_tree() noexcept{
    clear(m_root);
}

template <typename T>
void rb_tree<T>::insert(const T& key){
    node* parent{&ks_null};
    node* new_node = get_new_node(key);
    node* tmp{m_root};
    while(tmp != &ks_null){
        parent = tmp;
        if(new_node->m_key == tmp->m_key){
            return;
        }else if(new_node->m_key < tmp->m_key){
            tmp = tmp->m_left;
        }else{
            tmp = tmp->m_right;
        }
    }

    new_node->m_parent = parent;
    if(parent == &ks_null){
        m_root = new_node;
    }else if(new_node->m_key < parent->m_key){
        parent->m_left = new_node;
    }else{
        parent->m_right = new_node;
    }

    new_node->make_red();
    insert_fixup(new_node);
}

template <typename T>
void rb_tree<T>::insert_fixup(typename rb_tree<T>::node* inserted){
    while(inserted->m_parent->is_colored_red()){
        node* uncle{nullptr};
        if(inserted->m_parent == inserted->m_parent->m_parent->m_left){
            uncle = inserted->m_parent->m_parent->m_right;
            if(uncle->is_colored_red()){
                inserted->m_parent->make_black();
                uncle->make_black();
                inserted->m_parent->m_parent->make_red();
                inserted = inserted->m_parent->m_parent;
            }else{
                if(inserted == inserted->m_parent->m_right){
                    inserted = inserted->m_parent;
                    left_rotate(inserted);
                }
                inserted->m_parent->make_black();
                inserted->m_parent->m_parent->make_red();
                right_rotate(inserted->m_parent->m_parent);
            }
        }else{
            uncle = inserted->m_parent->m_parent->m_left;
            if(uncle->is_colored_red()){
                inserted->m_parent->make_black();
                uncle->make_black();
                inserted->m_parent->m_parent->make_red();
                inserted = inserted->m_parent->m_parent;
            }else{
                if(inserted == inserted->m_parent->m_left){
                    inserted = inserted->m_parent;
                    right_rotate(inserted);
                }
                inserted->m_parent->make_black();
                inserted->m_parent->m_parent->make_red();
                left_rotate(inserted->m_parent->m_parent);
            }
        }   
    }
    m_root->make_black();
}


template <typename T>
void rb_tree<T>::remove(const T& key){
    node* to_delete{find(key)};
    
    if(to_delete == &ks_null){
        return;
    }
    node* tmp{to_delete};
    bool tmp_was_black = tmp->is_colored_black();
    node* to_move{nullptr};
    if(to_delete->m_left == &ks_null){
        to_move = tmp->m_right;
        transplant(to_delete,to_delete->m_right);
    }else if(to_delete->m_right == &ks_null){
        to_move = tmp->m_left;
        transplant(to_delete, to_delete->m_left);
    }else{
        tmp = find_min(to_delete->m_right);
        to_move = tmp->m_right;
        tmp_was_black = tmp->is_colored_black();
        if(tmp->m_parent == to_delete){
            to_move->m_parent = tmp;
        }else{
            transplant(tmp,tmp->m_right);
            tmp->m_right = to_delete->m_right;
            tmp->m_right->m_parent = tmp;
        }
        transplant(to_delete,tmp);
        tmp->m_left = to_delete->m_left;
        tmp->m_left->m_parent = tmp;
        (to_delete->is_colored_black()) ? tmp->make_black() : tmp->make_red();
    }
    delete to_delete;
    if(tmp_was_black){
        remove_fixup(to_move);
    }
}

template <typename T>
void rb_tree<T>::remove_fixup(typename rb_tree<T>::node* to_move){
    node* sibling{nullptr};
    while((to_move != m_root) && (to_move->is_colored_black())){
        if(to_move == to_move->m_parent->m_left){
            sibling = to_move->m_parent->m_right;
            if(sibling->is_colored_red()){
                sibling->make_black();
                to_move->m_parent->make_red();
                left_rotate(to_move->m_parent);
                sibling = to_move->m_parent->m_right;
            }
            if((sibling->m_left->is_colored_black()) && (sibling->m_right->is_colored_black())){
                sibling->make_red();
                to_move = to_move->m_parent;
            }else{
                if(sibling->m_right->is_colored_black()){
                    sibling->m_left->make_black();
                    sibling->make_red();
                    right_rotate(sibling);
                    sibling = to_move->m_parent->m_right;
                }
                sibling->is_black = to_move->m_parent->is_black;
                to_move->m_parent->make_black();
                sibling->m_right->make_black();
                left_rotate(to_move->m_parent);
                to_move = m_root;
            }
        }
        else{
            sibling = to_move->m_parent->m_left;
            if(sibling->is_colored_red()){
                sibling->make_black();
                to_move->m_parent->make_red();
                left_rotate(to_move->m_parent);
                sibling = to_move->m_parent->m_left;
            }
            if((sibling->m_right->is_colored_black()) && (sibling->m_left->is_colored_black())){
                sibling->make_red();
                to_move = to_move->m_parent;
            }else{
                if(sibling->m_left->is_colored_black()){
                    sibling->m_right->make_black();
                    sibling->make_red();
                    left_rotate(sibling);
                    sibling = to_move->m_parent->m_left;
                }
                sibling->is_black = to_move->m_parent->is_black;
                to_move->m_parent->make_black();
                sibling->m_left->make_black();
                right_rotate(to_move->m_parent);
                to_move = m_root;
            }
        }
    }
    to_move->make_black();
}

template <typename T>
void rb_tree<T>::swap(rb_tree<T>& other){
    std::swap(m_root, other.m_root);
}

template <typename T>
typename rb_tree<T>::rbt_iterator rb_tree<T>::begin(){
    return rbt_iterator(find_min(m_root));
}

template <typename T>
typename rb_tree<T>::rbt_iterator rb_tree<T>::end(){
    return rbt_iterator(&ks_null);
}

template <typename T>
typename rb_tree<T>::const_rbt_iterator rb_tree<T>::begin() const{
    return const_rbt_iterator(find_min(m_root));
}

template <typename T>
typename rb_tree<T>::const_rbt_iterator rb_tree<T>::end() const{
    return const_rbt_iterator(&ks_null);
}

template <typename T>
typename rb_tree<T>::const_rbt_iterator rb_tree<T>::cbegin() const{
    return const_rbt_iterator(find_min(m_root));
}

template <typename T>
typename rb_tree<T>::const_rbt_iterator rb_tree<T>::cend() const{
    return const_rbt_iterator(&ks_null);
}


template <typename T>
bool rb_tree<T>::search(const T& key) const{
    return (find(key) != &ks_null);
}

template <typename T>
void rb_tree<T>::clear(typename rb_tree<T>::node* root){
    if(root != &ks_null){
        clear(root->m_left);
        clear(root->m_right);
        delete root;
    }
}

template <typename T>
void rb_tree<T>::copy(typename rb_tree<T>::node* src_root){
    if(src_root != &ks_null){
        insert(src_root->m_key);
        copy(src_root->m_left);
        copy(src_root->m_right);
    }
}

template <typename T>
typename rb_tree<T>::node* rb_tree<T>::get_new_node(const T& val) const{
    node* new_node = new node(val, &ks_null, &ks_null, &ks_null);
    return new_node;
}


template <typename T>
typename rb_tree<T>::node* rb_tree<T>::find(const T& val) const{
    node* tmp{m_root};
    while(tmp != &ks_null && val != tmp->m_key){
        if(val < tmp->m_key){
            tmp = tmp->m_left;
        }else{
            tmp = tmp->m_right;
        }
    }

    return tmp;
}

template <typename T>
typename rb_tree<T>::node* rb_tree<T>::find_min(typename rb_tree<T>::node* root) const{
    if(root == &ks_null){
        return &ks_null;
    }
    while(root->m_left != &ks_null){
        root = root->m_left;
    }

    return root;
}

template <typename T>
typename rb_tree<T>::node* rb_tree<T>::find_max(typename rb_tree<T>::node* root) const{
    if(root == &ks_null){
        return &ks_null;
    }
    while(root->m_right != &ks_null){
        root = root->m_right;
    }

    return root;
}

template <typename T>
typename rb_tree<T>::node* rb_tree<T>::successor(typename rb_tree<T>::node* curr) const{
    node* tmp{&ks_null};
    if(curr->m_right != &ks_null){
        tmp = find_min(curr->m_right);
    }else{
        tmp = curr->m_parent;
        while((tmp != &ks_null) && (curr == tmp->m_right)){
            curr = tmp;
            tmp = tmp->m_parent;
        }
    }

    return tmp;
}

template <typename T>
typename rb_tree<T>::node* rb_tree<T>::predecessor(typename rb_tree<T>::node* curr) const{
    node* tmp{&ks_null};
    if(curr->m_left != &ks_null){
        tmp = find_max(curr->m_left);
    }else{
        tmp = curr->m_parent;
        while((tmp != &ks_null) && (curr == tmp->m_leftt)){
            curr = tmp;
            tmp = tmp->m_parent;
        }
    }

    return tmp;
}

template <typename T>
void rb_tree<T>::left_rotate(typename rb_tree<T>::node* to_replace){
    node* to_rotate = to_replace->m_right;
    to_replace->m_right = to_rotate->m_left;
    if(to_rotate->m_left != &ks_null){
        to_rotate->m_left->m_parent = to_replace;
    }
    to_rotate->m_parent = to_replace->m_parent;
    if(to_replace->m_parent == &ks_null){
        m_root = to_rotate;
    }else if(to_replace == to_replace->m_parent->m_left){
        to_replace->m_parent->m_left = to_rotate;
    }else{
        to_replace->m_parent->m_right = to_rotate;
    }
    to_rotate->m_left = to_replace;
    to_replace->m_parent = to_rotate;
}

template <typename T>
void rb_tree<T>::right_rotate(typename rb_tree<T>::node* to_replace){
    node* to_rotate{to_replace->m_left};
    to_replace->m_left = to_rotate->m_right;
    if(to_rotate->m_right != &ks_null){
        to_rotate->m_right->m_parent = to_replace;
    }
    to_rotate->m_parent = to_replace->m_parent;
    if(to_replace->m_parent == &ks_null){
        m_root = to_rotate;
    }else if(to_replace == to_replace->m_parent->m_left){
        to_replace->m_parent->m_left = to_rotate;
    }else{
        to_replace->m_parent->m_right = to_rotate;
    }

    to_rotate->m_right = to_replace;
    to_replace->m_parent = to_rotate;
}

template <typename T>
void rb_tree<T>::transplant(typename rb_tree<T>::node* to_replace, typename rb_tree<T>::node* to_transplant){
    if(to_replace->m_parent == &ks_null){
        m_root = to_transplant;
    }else if(to_replace == to_replace->m_parent->m_left){
        to_replace->m_parent->m_left = to_transplant;
    }else{
        to_replace->m_parent->m_right = to_transplant;
    }

    if(to_transplant != &ks_null){
        to_transplant->m_parent = to_replace->m_parent;
    }
}

#endif