
#include<iostream>

using namespace std;


template<typename Object>
class List {
public:
    List() {
        init();
    }

    ~List() {
        clear();
    }


    void push_back(const Object &key) {
        Node *p = new Node(key);
        Node *q = head;
        while (q->next) {
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
        theSize++;
    }

    int insert_pos(const int loc, const Object &key) {
        if (loc >= 1 && loc <= theSize + 1) {
            Node *p = new Node(key);
            Node *q = get_pre_node(loc);
            p->next = q->next;
            q->next = p;
            theSize++;
            return 0;
        }
        return -1;
    }


    const Object &get(const int pos) {
        if (pos > 0 && pos <= theSize) {
            Node *p = head;
            for (int i = 0; i < pos; i++) {
                p = p->next;
            }
            return p->data;
        }

        return Object();
    }

    int del(const int loc) {
        if (loc > 0 && loc <= theSize) {
            Node *p = get_pre_node(loc);  //前一个节点

            Node *q = p->next;   //要删除的节点
            p->next = q->next;
            delete q;
            theSize--;
            return 0;
        }
        return -1;
    }

    void display() {
        for (Node *p = head->next; p; p = p->next) {
            cout << p->data << " ";
        }
        cout << endl;
    }

private:
    struct Node {
        Object data;
        Node *next;

        Node(const Object &d = Object{}, Node *n = nullptr)
            : data(d), next(n) {}
    };

    int theSize;
    Node *head;

    void init() {
        theSize = 0;
        head = new Node;
    }

    void clear() {
        Node *p = head;
        while (p) {
            Node *q = p->next;
            delete p;
            p = q;
        }
    }

public:
    Node *get_pre_node(const int loc) {
        Node *p = head;
        for (int i = 1; i < loc; i++) {
            p = p->next;
        }
        return p;
    }

    Node *find(const Object &d) {
        Node *p = head->next;
        while (p) {
            if (p->data == d) {
                break;
            }
            p=p->next;
        }
        return p;
    }

};

int main() {

    List<string> li;
    li.push_back("aaaaaa");
    li.push_back("asasas");
    li.push_back("bbbbbbb");
    li.push_back("ccccccc");
    li.display();
    for(int i=0; i<3; i++) {
        string a;
        cin>>a;
        if(li.find(a)) {
            cout<<"yes"<<endl;
        } else {
            cout<<"no"<<endl;
        }
    }

//    List<int> li;
//    int num;
//    cin >> num;
//    while (num--) {
//        int temp;
//        cin >> temp;
//        li.push_back(temp);
//    }
//    li.display();
//    for (int i = 0; i < 2; i++) {
//        int loc;
//        int key;
//        cin >> loc >> key;
//        if (!li.insert_pos(loc, key)) {
//            li.display();
//        } else {
//            cout << "error" << endl;
//        }
//    }
//    for (int i = 0; i < 2; i++) {
//        int loc;
//        cin >> loc;
//        if (!li.del(loc)) {
//            li.display();
//        } else {
//            cout << "error" << endl;
//        }
//    }
//    for (int i = 0; i < 2; i++) {
//        int loc;
//        cin >> loc;
//        if (li.get(loc) == int()) {
//            cout << "error" << endl;
//
//        } else {
//            cout << li.get(loc) << endl;
//        }
//    }

    return 0;
}

