//
// Created by Jack on 2017/9/22.
//


#include<algorithm>
#include<cstdio>

template<typename Object>

class List {
private:
    struct Node {
        Object data;
        Node *prev;
        Node *next;

        Node(const Object &d = Object(), Node *p = nullptr, Node *n = nullptr)
                : data(d), prev(p), next(n) {}

        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
                : data(std::move(d)), prev(p), next(n) {}
    };
public:
    class const_iterator {
    public:
        const_iterator()
                : current(nullptr) {};

        const Object &operator*() const {
            return retrieve();
        }

        const_iterator &operator++() {       //后置++
            current = current->next;
            return *this;
        }

        const_iterator operator++(int) {        //前置++
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }

    protected:
        Node *current;

        Object &retrieve() const {
            return current->data;
        }

        const_iterator(Node *p)
                : current(p) {}

        friend class List<Object>;
    };


    class iterator : public const_iterator {
    public:
        iterator() {}

        Object &operator*() {
            return const_iterator::retrieve();
        }

        const Object &operator*() const {
            return const_iterator::operator*();
        }

        iterator &operator++() {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

    protected:
        iterator(Node *p) : const_iterator(p) {}

        friend class List<Object>;
    };

public:
    List() {
        init();
    }

    List(const List &rhs) {
        init();
        for (auto &x:rhs) {
            push_back(x);
        }
    }

    ~List() {
        clear();
        delete head_;
        delete tail_;
    }

    List &operator=(const List &rhs) {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }


    List(List &&rhs)
            : size_(rhs.size_), head_(rhs.head_), tail_(rhs.tail_) {
        rhs.size_ = 0;
        rhs, head_ = nullptr;
        rhs.tail_ = nullptr;
    }


    List &operator=(List &&rhs) {
        std::swap(size_, rhs.size_);
        std::swap(head_, rhs.head_);
        std::swap(tail_, rhs.tail_);
        return *this;
    }

    iterator begin() {
        return {head_->next};
    }


    const_iterator begin() const {
        return {head_->next};
    }

    iterator end() {
        return {tail_};
    }

    const_iterator end() const {
        return {tail_};
    }

    int size() const {
        return size_;
    }


    bool empty() const{
        return size() == 0;
    }


    void clear() {
        while (!empty()) {
            pop_front();
        }
    }


    Object &front() {
        return *begin();
    }


    const Object &front() const {
        return *begin();
    }

    Object &back() {
        return *(--end());
    }

    const Object &back() const {
        return *(--end());
    }

    void push_front(const Object &x) {
        insert(begin(), x);
    }

    void push_front(Object &&x) {
        insert(begin(), std::move(x));
    }

    void push_back(const Object &x) {
        insert(end(), x);
    }

    void push_back(Object &&x) {
        insert(end(), std::move(x));
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        erase(--end());
    }

    //在itr处插入x
    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.current;
        size_++;
        return {p->prev = p->prev->next = new Node(x, p->prev, p)};
    }

    iterator insert(iterator itr, Object &&x) {               //右值引用
        Node *p = itr.current;
        size_++;
        return {p->prev = p->prev->next = new Node(std::move(x), p->prev, p)};
    }

    //删除在itr处的项
    iterator erase(iterator itr) {
        Node *p = itr.current;
        iterator ret_val(p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        size_--;
        return ret_val;
    }

    iterator erase(iterator from, iterator to) {
        for(iterator itr=from;itr !=to;){
            itr=erase(itr);
        }
        return to;
    }



private:
    int size_;
    Node *head_;
    Node *tail_;

    void init() {
        size_ = 0;
        head_ = new Node;
        tail_ = new Node;
        head_->next = tail_;
        tail_->prev = head_;
    }

};


int main(){
    List<int> li;
    li.push_back(10);
    li.push_back(20);
    li.push_back(30);
    li.push_back(40);
    for(auto &x:li){
        printf("%d \n",x);
    }
    printf("%d \n",li.size());
    return 0;
}
