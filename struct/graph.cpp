#include<string>
#include<vector>
#include<iostream>
#include<algorithm>

const int Infinity = 65536;

struct Edge {
public:
	int start;
	int end;
	int weight;
	Edge (int start_, int end_, int weight_)
		: start (start_), end (end_), weight (weight_) {}
};

class Graph {
public:
	Graph (int size);
	void create_matrix ();
	static bool cmp (Edge a, Edge b);
	int find_father (std::vector<int> father, int x);
	void display (std::string &s);
	~Graph ();

private:
	int size_;
	int **matrix_;
	int edge_num_;
	std::vector<int> min_set_;
	std::vector<std::string> vertex_;
	std::vector<Edge> edge_;
	std::vector<int> ver_;
	int get_index (std::string &s1);
	void kruskal ();
	int prim (std::string &s);
	int find_sets (std::vector<int> sets,int ver,int value);
};

Graph::Graph (int size)
    :size_(size),edge_num_(0){
	matrix_ = new int *[size_];
	for (int i = 0; i < size_; ++i) {
		matrix_[i] = new int[size_];
	}
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j) {
			matrix_[i][j] = 0;
		}
	}
}


void Graph::create_matrix () {
	for (int i = 0; i < size_; ++i) {
		std::string ver;
		std::cin >> ver;
		vertex_.push_back (ver);
	}
	std::cin >> edge_num_; //边数
	for (int j = 0; j < edge_num_; ++j) {
		std::string v1;
		std::string v2;
		std::cin >> v1 >> v2;
		int height;
		std::cin >> height;
		matrix_[get_index (v1)][get_index (v2)] = height;
		matrix_[get_index (v2)][get_index (v1)] = height;
		edge_.push_back ({ get_index (v1), get_index (v2), height });
	}

	for (int i = 0; i < size_; i++) {
		for (int j = 0; j < size_; j++) {
			if (i!=j&&matrix_[i][j] == 0) {
				matrix_[i][j] = Infinity;
			}
		}
	}
	
}

bool Graph::cmp (Edge a, Edge b) {
	return a.weight < b.weight;
}

int Graph::find_father (std::vector<int> father, int x) {
	int a = x;
	while (x != father[x])
		x = father[x];
	while (a != father[a]) {
		int z = a;
		a = father[a];
		father[z] = x;
	}
	return x;
}

void Graph::display (std::string & s) {
	std::cout << prim (s)<<std::endl;
	std::vector<int> sets;
	sets.push_back (get_index (s));
	std::cout << "prim:" << std::endl;
	for (int i = 0; i < size_-1; i++) {
		int v = find_sets (sets, ver_[i], min_set_[i]);
		int u = ver_[i];
		std::cout << vertex_[v] << " "
			<< vertex_[u] << " "
			<< min_set_[i] << std::endl;
		sets.push_back (ver_[i]);
	}
	kruskal ();
}

void Graph::kruskal () {
	std::vector<int> father;
	int edge_num = 0;
	for (int i = 0; i < size_; ++i) {
		father.push_back (i);
	}
	std::sort(edge_.begin (), edge_.end (), cmp);
	std::cout << "kruskal:" << std::endl;
	for (int i = 0; i < edge_num_; ++i) {
		int father_u = find_father (father, edge_[i].start);
		int father_v = find_father (father, edge_[i].end);
		if (father_u != father_v) {
			father[father_u] = father_v;
			int v = edge_[i].start < edge_[i].end ? edge_[i].start : edge_[i].end;
			int u= edge_[i].start > edge_[i].end ? edge_[i].start : edge_[i].end;
			std::cout << vertex_[v] << " "
				<< vertex_[u]
				<< " "
				<< edge_[i].weight << std::endl;
			if (edge_num == size_ - 1)
				break;
		}
	}
}

int Graph::prim (std::string &s) {
	std::vector<bool> vis (size_);
	std::vector<int>  dis (size_);
	std::fill(dis.begin (), dis.end (), Infinity);
	dis[get_index(s)] = 0;
	int sum = 0;
	for (int i = 0; i < size_; ++i) {
		int u = -1;
		int MIN = Infinity;
		for (int j = 0; j < size_; ++j) {
			if (vis[j] == false && dis[j] < MIN) {
				MIN = dis[j];
				u = j;
			}
		}
		if (u == -1)
			return -1;
		vis[u] = true;
		if (i != 0) {
			ver_.push_back (u);          //一个顶点
			min_set_.push_back (MIN);    //长度最小的边
		}
		sum += dis[u];
		for (int v = 0; v < size_; ++v) {
			if (vis[v] == false && matrix_[u][v] != Infinity && matrix_[u][v] < dis[v])
				dis[v] = matrix_[u][v];
		}
	}
	return sum;
}

int Graph::find_sets (std::vector<int> sets, int ver, int value) {
	for (int i = 0; i < sets.size(); i++) {
		if (matrix_[sets[i]][ver] == value) {
			return sets[i];
		}
	}
	return -1;
}

int Graph::get_index (std::string &s1) {
	for (int i = 0; i < vertex_.size (); ++i) {
		if (vertex_[i] == s1) {
			return i;
		}
	}
	return -1;
}

Graph::~Graph () {
	for (int i = 0; i < size_; ++i) {
		delete[] matrix_[i];
	}
}




int main () {
	int size;
	std::cin >> size;
	Graph graph (size);
	graph.create_matrix ();
	std::string s;
	std::cin >> s;
	graph.display (s);
	return 0;
}




