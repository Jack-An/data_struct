//
// Created by Jack on 2017/10/18.
//
//实现将后缀表达式转化成中缀表达式树
//

#include <string>
#include <stack>
#include <iostream>

template <typename T>
struct BinaryTree{
    T data;
    BinaryTree *left;
    BinaryTree * right;
};

int main(){
    std::stack<BinaryTree<char> *> tree;
    std::string expression;
    std::cin>>expression;
    for(int i=0;i<expression.length();++i){
        if(isdigit(expression[i])){
            auto node=new BinaryTree<char>;
            node->data=expression[i];
            node->left= nullptr;
            node->right=nullptr;
            tree.push(node);
        }else{
            auto node=new BinaryTree<char>;
            node->left= nullptr;
            node->right= nullptr;
            node->data=expression[i];
            auto value1=tree.top();    //弹出的第一个元素
            tree.pop();
            auto value2=tree.top();     //弹出的第二个元素
            tree.pop();

            node->left=value1;
            node->right=value2;
            tree.push(node);
        }
    }
    auto value=tree.top();
    
    return 0;
}
