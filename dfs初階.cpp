#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    int V; // 頂點數
    list<int>* adj; // 鄰接表
    
public:
//構造函數;初始化圖
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V];//為每個頂點創鄰接表
    }
    //解構函數;釋放內存
    ~Graph() {
        delete[] adj;
    }
    
    // 加邊
    void addEdge(int v, int w) {
        adj[v].push_back(w);//v接到w的表
        adj[w].push_back(v); // w接到v的表(無向圖
    }
    
    // 檢查當前路徑是否包含頂點v
    bool isNotInPath(int v, vector<int>& path) {
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == v)
                return false;//在
        }
        return true;//不在
    }
    
    // dfs地回函數
    bool hamiltonianPathUtil(vector<int>& path, int pos) {
        // 如果所有頂點都已被走過，则找到
        if (pos == V) {
            return true;
        }
        
        // 試試看所有與當前頂點相鄰的頂點,若是起始點就是-1
        int lastVertex = (pos == 0) ? -1 : path[pos-1];
        //非起始點,嘗試所有與最後一個頂相鄰的頂
        if (lastVertex != -1) {
            //只考慮沒在路徑中的頂點
            for (int v : adj[lastVertex]) {
                if (isNotInPath(v, path)) {
                    path[pos] = v;//點加入路徑
                    //地回繼續找
                    if (hamiltonianPathUtil(path, pos+1)) {
                        return true;//找到
                    }
                    // 回朔
                    path[pos] = -1;
                }
            }
        } else {
            // 如果是起始點，試所有頂點作為起點
            for (int v = 0; v < V; v++) {
                path[pos] = v;
                if (hamiltonianPathUtil(path, pos+1)) {
                    return true;
                }
                // 回溯
                path[pos] = -1;
            }
        }
        
        return false;
    }
    
    // 查找hp
    vector<int> findHamiltonianPath() {
        vector<int> path(V, -1);
        
        if (hamiltonianPathUtil(path, 0)) {
            return path;
        } else {
            return vector<int>(); // 返回空向量表示未找到
        }
    }
    
    // 打印图
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
    // 這個是示範
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    
    cout << "圖的玲接表表示:" << endl;
    g.printGraph();
    cout << endl;
    
    vector<int> path = g.findHamiltonianPath();
    
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