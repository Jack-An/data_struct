//
// Created by Jack on 2017/11/30.
//

#include <iostream>

template<typename T>
class BinarySortTree                                               {
public:
    BinarySortTree();
    void insert(T element);
    void del(T element);
    T *search(T element);
    void traversal();
    ~BinarySortTree();

private:
    struct BinarySortTreeNode {
        T element_;
        BinarySortTreeNode *left_;
        BinarySortTreeNode *right_;
    };
    BinarySortTreeNode *root_;
    void del(BinarySortTreeNode *&p);
    T *search(BinarySortTreeNode *p, T element);
    void insert(BinarySortTreeNode *&p, T element);
    void del(BinarySortTreeNode *&p, T element);
    void traversal(BinarySortTreeNode *p);
    void erase(BinarySortTreeNode *&p);
};


template<typename T>
BinarySortTree<T>::BinarySortTree() {
    root_ = nullptr;
}


template<typename T>
void BinarySortTree<T>::insert(T element) {
    insert(root_, element);
}

template<typename T>
void BinarySortTree<T>::insert(BinarySortTree::BinarySortTreeNode *&p, T element) {
    if (!p) {
        auto *s = new BinarySortTreeNode;
        s->element_ = element;
        s->right_ = s->left_ = nullptr;
        p = s;
    } else if (element < p->element_) {
        insert(p->left_, element);
    } else {
        insert(p->right_, element);
    }
}

template<typename T>
void BinarySortTree<T>::del(T element) {
    del(root_, element);
}

template<typename T>
void BinarySortTree<T>::del(BinarySortTree::BinarySortTreeNode *&p) {
    BinarySortTreeNode *q = nullptr;
    BinarySortTreeNode *s = nullptr;
    if (!p->right_) {
        q = p;
        p = p->left_;
        delete q;
    } else if (!p->left_) {
        q = p;
        p = p->right_;
        delete q;
    } else {
        q = p;
        s = p->left_;
        while (s->right_) {
            q = s;
            s = s->right_;
        }
        p->element_ = s->element_;
        if (q != p) {
            q->right_ = s->left_;
        } else {
            q->left_ = s->left_;
        }
        delete s;
    }
}

template<typename T>
void BinarySortTree<T>::del(BinarySortTree::BinarySortTreeNode *&p, T element) {
    if (!p) {
        return;
    } else {
        if (element == p->element_) {
            del(p);
        } else if (element < p->element_) {
            del(p->left_, element);
        } else {
            del(p->right_, element);
        }
    }
}

template<typename T>
T *BinarySortTree<T>::search(T element) {
    return search(root_, element);
}

template<typename T>
T *BinarySortTree<T>::search(BinarySortTree::BinarySortTreeNode *p, T element) {
    if ((!p) || element == p->element_) {
        if (!p) {
            return nullptr;
        } else {
            return &p->element_;
        }
    } else if (element < p->element_) {
        search(p->left_, element);
    } else {
        search(p->right_, element);
    }
}

template<typename T>
void BinarySortTree<T>::traversal() {
    traversal(root_);
}

template<typename T>
void BinarySortTree<T>::traversal(BinarySortTree::BinarySortTreeNode *p) {
    if (!p) return;
    traversal(p->left_);
    std::cout << p->element_ << " ";
    traversal(p->right_);
}

template <typename T>
void BinarySortTree<T>::erase(BinarySortTreeNode *&p) {
   if(p!=nullptr){
       erase(p->left_);
       erase(p->right_);
       delete p;
   }
    p= nullptr;
}

template<typename T>
BinarySortTree<T>::~BinarySortTree() {
    erase(root_);
}




int main() {
    BinarySortTree<int> a;
    a.insert(10);
    a.insert(20);
    a.insert(30);
    a.insert(2);
    a.insert(5);
    a.traversal();
    std::cout << std::endl;
    a.del(20);
    a.traversal();
    auto item = a.search(10);
    std::cout << item << std::endl;
    return 0;

}





