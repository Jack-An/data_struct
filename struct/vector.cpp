//
// Created by Jack on 2017/9/18.
//

#include<algorithm>
#include<iostream>

template<typename Object>

class Vector {
public:
    explicit Vector(int size = 0)
            : size_(size), capacity_(size + kSpaceCapacity) {
        object_ = new Object[capacity_];
    }

    Vector(const Vector &rhs)
            : size_(rhs.size_), capacity_(rhs.capacity_), object_(nullptr) {
        object_ = new Object[capacity_];
        for (int k = 0; k < size_; k++) {
            object_[k] = rhs.object_[k];
        }
    }

    Vector &operator=(const Vector &rhs) {
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    ~Vector() {
        delete[] object_;
    }

    Vector(Vector &&rhs)
            : size_(rhs.size_), capacity_(rhs.capacity_), object_(rhs.object_) {
        rhs.object_ = nullptr;
        rhs.size_ = 0;
        rhs.capacity_ = 0;
    }

    Vector &operator=(Vector &&rhs) {
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
        std::swap(object_, rhs.object_);
        return *this;
    }

    void resize(int new_size) {
        if (new_size > capacity_) {
            reserve(new_size * 2);
        }
        size_ = new_size;
    }

    void reserve(int new_capacity) {
        if (new_capacity < size_) {
            return;
        }
        Object *new_array = new Object[new_capacity];
        for (int k = 0; k < size_; k++) {
            new_array[k] = std::move(object_[k]);
        }
        capacity_ = new_capacity;
        std::swap(object_, new_array);
        delete[] new_array;
    }

    Object &operator[](int index) {
        return object_[index];
    }

    const Object &operator[](int index) const {
        return object_[index];
    }

    bool empty() const {
        return size_ == 0;
    }

    int size() const {
        return size_;
    }

    int capacity() const {
        return capacity_;
    }

    void push_back(const Object &x) {
        if (size_ == capacity_) {
            reserve(2 * capacity_ + 1);
        }
        object_[size_++] = x;
    }

    void push_back(Object &&x) {
        if (size_ == capacity_) {
            reserve(2 * capacity_ + 1);
        }
        object_[size_++] = std::move(x);
    }

    void pop_back() {
        --size_;
    }

    const Object &back() const {
        return object_[size_ - 1];
    }

    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin() {
        return &object_[0];
    }

    const_iterator begin() const {
        return &object_[0];
    }

    iterator end() {
        return &object_[size()];
    }

    const_iterator end() const {
        return &object_[size()];
    }

    static const int kSpaceCapacity = 16;

private:
    int size_;
    int capacity_;
    Object *object_;

};

int main(){


    Vector<int>  vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    for(auto iter=vec.begin();iter!=vec.end();iter++){
        std::cout<<*iter<<std::endl;
    }
     auto k=vec.back();
    std::cout<<k<<std::endl;
    Vector<int> ivec(vec);
    ivec.push_back(vec.back()+10);
    for(auto &x:ivec){
        std::cout<<x<<std::endl;
    }


    return 0;
}
