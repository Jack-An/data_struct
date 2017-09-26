#include<iostream>
#include<stack>
#include<iomanip>
#include<iterator>
#include<algorithm>
using namespace std;
struct Pos {
    int x;
    int y;
};

class Maze {
public:
    Maze(int **p, int shape);

    ~Maze();

    void find_path();

    void print();

    void show_path();

private:
    bool path_;
    stack<Pos> s_;
    int shape_;
    int **map_;

};

Maze::Maze(int **p, int shape)
        : shape_(shape), path_(false) {
    map_ = new int *[shape_ + 2];
    for (int i = 0; i < shape_ + 2; i++) {
        map_[i] = new int[shape + 2];
    }
    for (int i = 0; i < shape_ + 1; i++) {
        map_[0][i] = 1;
        map_[i][0] = 1;
    }
    for (int i = shape_ + 1; i >= 0; i--) {
        map_[shape + 1][i] = 1;
        map_[i][shape_ + 1] = 1;
    }
    for (int i = 1; i < shape_ + 1; i++) {
        for (int j = 1; j < shape_ + 1; j++) {
            map_[i][j] = p[i - 1][j - 1];
        }
    }
}


void Maze::find_path() {
    Pos move[4];
    move[0].x = 0;
    move[0].y = 1;
    move[1].x = 1;
    move[1].y = 0;
    move[2].x = 0;
    move[2].y = -1;
    move[3].x = -1;
    move[3].y = 0;
    Pos now;
    now.x = 1;
    now.y = 1;
    map_[1][1] = 1;
    int choose = 0;
    int last_choose = 3;
    while (now.x != shape_ || now.y != shape_) {
        int newr, newe;
        while (choose <= last_choose) {
            newr = now.x + move[choose].x;
            newe = now.y + move[choose].y;
            if (map_[newr][newe] == 0) {
                break;
            }
            choose++;
        }
        if (choose <= last_choose) {
            s_.push(now);
            now.x = newr;
            now.y = newe;
            map_[newr][newe] = 1;
            choose = 0;
        } else {
            if (s_.empty()) {
                path_ = false;
                return;
            }
            Pos t = s_.top();
            Pos next(t);
            s_.pop();
            if (next.x == now.x) {
                choose = 2 + next.y - now.y;
            } else {
                choose = 3 + next.x - now.x;
            }
            now = next;
        }
    }
    path_ = true;
}

Maze::~Maze() {
    for (int i = 0; i < shape_; i++) {
        delete[] map_[i];
    }
}

void Maze::print() {
    for (int i = 0; i < shape_ + 2; i++) {
        for (int j = 0; j < shape_ + 2; j++) {
            cout << map_[i][j] << " ";
        }
        cout << endl;
    }

    cout << "----" << path_ << s_.size() << "-----" << endl;
}

void Maze::show_path() {
    if (path_) {
        stack<Pos> path1;
        path1.push({shape_-1,shape_-1});
        int len = s_.size();
        for (int i = 0; i < len; i++) {
            Pos t = s_.top();
            t.x-=1;
            t.y-=1;
            path1.push(t);
            s_.pop();
        }

        int i = 0;  //以下是输出路径的代码
        Pos cpos;
        while (!path1.empty()) {
            cpos = path1.top();
            if ((++i) % 4 == 0)
                cout << '[' << cpos.x << ',' << cpos.y << ']' << "--" << endl;
            else
                cout << '[' << cpos.x << ',' << cpos.y << ']' << "--";
            path1.pop();
        }
        cout << "END" << endl;
    } else {
        cout << "no path" << endl;
    }
}

int main() {
    int test_num;
    cin >> test_num;
    while (test_num--) {
        int shape;
        cin >> shape;
        int **arr;
        arr = new int *[shape];
        for (int i = 0; i < shape; i++) {
            arr[i] = new int[shape];
        }
        for (int i = 0; i < shape; i++) {
            for (int j = 0; j < shape; j++) {
                cin >> arr[i][j];
            }
        }
        Maze maze(arr, shape);
        maze.find_path();
        maze.show_path();
    }

    return 0;
}
