//
// Created by Jack on 2017/10/23.
//

#include <iostream>
/**
 *
 * @tparam Comparable
 * 这里使用Comparable而不使用Object的原因是进行find操作是给定的元素是可以进行比较的
 * 如果给定的元素是Object，那么就要求元素已经定义了比较的方法
 * 则该类相应的内容也应该进行修改
 */
template <typename Comparable>
class BinarySearchTree{
public:
    BinarySearchTree(){
        root_=nullptr;
    }
    BinarySearchTree(const BinarySearchTree &rhs)
        :root_(nullptr){
        root_=clone(rhs.root_);
    }
    BinarySearchTree(BinarySearchTree &&rhs) noexcept
            :root_(std::move(rhs.root_)){}
    ~BinarySearchTree(){
        makeEmpty();
    }
/**
 * findMax & findMin方法用于寻找二叉查找树中的最大最小元素
 * findMin例程中用到了递归
 * findMax例程中使用了非递归实现
 * @return
 */
    const Comparable& findMin() const{
        auto node=findMin(root_);     //private findMin例程返回了指向最小元素的指针
        return node->element_;
    }
    const Comparable& findMax() const{
        auto node=findMax(root_);
        return node->element_;
    }
    bool contains(const Comparable &x) const{
        return contains(x,root_);
    }
    bool isEmpty() const{
        return root_==nullptr;
    }
    void printTree(std::ostream &out=std::cout) const{
        printTree(root_,std::cout);
    }

    void makeEmpty(){
        makeEmpty(root_);
    }
    //
    //将x插入到树中，忽略重复元
    //
    void insert(const Comparable &x){
        insert(x,root_);
    }
    void insert(Comparable &&x){
        insert(std::move(x),root_);
    }
    //
    //将x从树中删除，如果没找到x，则什么都不做
    //
    void remove(const Comparable &x){
        remove(x,root_);
    }

    BinarySearchTree& operator= (const BinarySearchTree &rhs){
        BinarySearchTree copy=rhs;
        std::swap(*this,copy);
        return *this;
    }
   BinarySearchTree& operator= (BinarySearchTree &&rhs) noexcept {
       std::swap(root_,rhs.root_);
       return *this;
   }

private:
    struct BinaryNode{
        Comparable element_;
        BinaryNode *left_;
        BinaryNode *right_;
        BinaryNode(const Comparable &element,BinaryNode *left,BinaryNode *right)
                :element_(element),left_(left),right_(right){}
        BinaryNode(Comparable &&element,BinaryNode *left,BinaryNode *right)
                :element_(std::move(element)),left_(left),right_(right){}
    };
    BinaryNode *root_;

    void insert(const Comparable &x,BinaryNode *&t){
        if(t==nullptr){
            t=new BinaryNode(x,nullptr, nullptr);
        }else if(x < t->element_){
            insert(x,t->left_);
        }else if(x > t->element_){
            insert(x,t->right_);
        }else
            ;             //重复元，什么都不做，分号表示空语句
    }

    void insert(Comparable &&x,BinaryNode *&t){
        if(t==nullptr){
            t=new BinaryNode(std::move(x),nullptr, nullptr);
        }else if(x < t->element_){
            insert(std::move(x),t->left_);
        }else if(x > t->element_){
            insert(std::move(x),t->right_);
        }else
            ;             //重复元，什么都不做，分号表示空语句
    }
    void remove(const Comparable &x,BinaryNode *&t){
        if(t == nullptr){
            return;
        }
        if(x < t->element_){
            remove(x,t->left_);
        }else if(x > t->element_){
            remove(x,t->right_);
        }else if(t->left_!=nullptr && t->right_!=nullptr){
            t->element_=findMin(t->right_)->element_;
            remove(t->element_,t->right_);
        }else{
            BinaryNode *old=t;
            t=(t->left_ != nullptr) ? t->left_ : t->right_;
            delete old;
        }
    }
    BinaryNode* findMin(BinaryNode *t) const{
        if(t==nullptr){
            return nullptr;
        }
        if(t->left_== nullptr){
            return t;
        }
        return findMin(t->left_);
    }
    BinaryNode* findMax(BinaryNode *t) const{
        if(t!= nullptr){
            while(t->right_!= nullptr){
                t=t->right_;
            }
        }
        return t;
    }
    /**
     *
     * @param x
     * @param t
     * @return
     * 在这里使用尾递归是合理的，因为使用的栈空间只是O(log N)
     *
     */
    bool contains(const Comparable &x,BinaryNode *t) const{
        if(t== nullptr){
            return false;
        }else if(x<t->element_){          // 如果小于t->element,则一定在t的左孩子里面
            return contains(x,t->left_);
        }else if(x>t->element_){
            return contains(x,t->right_);
        }else{
            return true;                //表示t->element == x  返回true
        }
    }
    void makeEmpty(BinaryNode *&t){
        if(t!= nullptr){
            makeEmpty(t->left_);
            makeEmpty(t->right_);
            delete t;
        }
        t=nullptr;
    }
    /**
     * 这里用到先序遍历，可以根据需要修改该例程来实现不同的遍历方法
     * @param t
     * @param out
     */
    void printTree(BinaryNode *t,std::ostream &out) const{
        if(t) {
            out << t->element_<<" ";
            printTree(t->left_, out);
            printTree(t->right_, out);
        }
    }
    BinaryNode* clone(BinaryNode *t) const{
        if(t == nullptr){
            return nullptr;
        }else{
            return new  BinaryNode(t->element_,clone(t->left_),clone(t->right_));
        }
    }

};

int main(){
    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(4);
    tree.insert(3);
    tree.printTree(std::cout);
    std::cout<<std::endl;
    std::cout<<tree.findMin()<<std::endl;
    std::cout<<tree.findMax()<<std::endl;
    std::cout<<tree.contains(8)<<std::endl;
    std::cout<<tree.contains(9)<<std::endl;
    tree.remove(2);
    tree.printTree(std::cout);
    std::cout<<std::endl;

    return 0;


}

