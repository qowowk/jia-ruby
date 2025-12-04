#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    int V; // 頂點數
    list<int>* adj; // 鄰接表
    
public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    ~Graph() {
        delete[] adj;
    }
    
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v); 
    }
    
    bool isNotInPath(int v, vector<int>& path) {
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == v)
                return false;
        }
        return true;
    }
    
    bool hamiltonianPathUtil(vector<int>& path, int pos) {
        if (pos == V) {
            return true;
        }
        
        int lastVertex = (pos == 0) ? -1 : path[pos-1];

        if (lastVertex != -1) {
            for (int v : adj[lastVertex]) {
                if (isNotInPath(v, path)) {
                    path[pos] = v;
                    if (hamiltonianPathUtil(path, pos+1)) {
                        return true;
                    }
                    path[pos] = -1;
                }
            }
        } else {
            for (int v = 0; v < V; v++) {
                path[pos] = v;
                if (hamiltonianPathUtil(path, pos+1)) {
                    return true;
                }
                path[pos] = -1;
            }
        }
        
        return false;
    }
    
    vector<int> findHamiltonianPath() {
        vector<int> path(V, -1);
        
        if (hamiltonianPathUtil(path, 0)) {
            return path;
        } else {
            return vector<int>(); 
        }
    }
    
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "頂點 " << i << " 的鄰居: ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    
    cout << "圖的鄰接表表示:" << endl;
    g.printGraph();
    cout << endl;

    // 這裡開始計時
    auto t1 = std::chrono::high_resolution_clock::now();

    vector<int> path = g.findHamiltonianPath();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    cout << "執行時間: " << us << " microseconds" << endl;
    // 計時結束

    if (!path.empty()) {
        cout << "找到了 ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "未找到" << endl;
    }
    
    return 0;
}
