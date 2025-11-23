#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    int V; // 頂點數
    vector<list<int>> adj; // 使用 vector 替代動態陣列
    
public:
    // 構造函數;初始化圖
    Graph(int V) : V(V), adj(V) {} // 使用成員初始化列表
    
    // 不再需要手動釋放內存，vector 會自動管理
    
    // 加邊
    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v); // 無向圖
    }
    
    // 改良：使用 unordered_set 來快速檢查頂點是否在路徑中
    bool hamiltonianPathUtil(vector<int>& path, unordered_set<int>& visited, int pos) {
        // 如果所有頂點都已被走過，則找到哈密頓路徑
        if (pos == V) {
            return true;
        }
        
        // 取得上一個頂點
        int lastVertex = path[pos-1];
        
        // 嘗試所有與當前頂點相鄰的頂點
        for (int v : adj[lastVertex]) {
            if (visited.find(v) == visited.end()) { // 未訪問過
                path[pos] = v;
                visited.insert(v);
                
                if (hamiltonianPathUtil(path, visited, pos+1)) {
                    return true;
                }
                
                // 回溯
                visited.erase(v);
                path[pos] = -1;
            }
        }
        
        return false;
    }
    
    // 查找哈密頓路徑
    vector<int> findHamiltonianPath() {
        vector<int> path(V, -1);
        unordered_set<int> visited;
        
        // 嘗試每個頂點作為起點
        for (int start = 0; start < V; start++) {
            path[0] = start;
            visited.insert(start);
            
            if (hamiltonianPathUtil(path, visited, 1)) {
                return path;
            }
            
            // 回溯
            visited.clear();
        }
        
        return vector<int>(); // 返回空向量表示未找到
    }
    
    // 改良：查找哈密頓迴路
    vector<int> findHamiltonianCycle() {
        vector<int> path(V, -1);
        unordered_set<int> visited;
        
        // 固定從頂點 0 開始（哈密頓迴路可以從任意點開始）
        path[0] = 0;
        visited.insert(0);
        
        if (hamiltonianCycleUtil(path, visited, 1)) {
            // 檢查最後一個頂點是否與第一個頂點相連
            if (isAdjacent(path[V-1], path[0])) {
                return path;
            }
        }
        
        return vector<int>();
    }
    
    // 檢查兩個頂點是否相鄰
    bool isAdjacent(int u, int v) {
        for (int neighbor : adj[u]) {
            if (neighbor == v) return true;
        }
        return false;
    }
    
private:
    // 哈密頓迴路的遞迴函數
    bool hamiltonianCycleUtil(vector<int>& path, unordered_set<int>& visited, int pos) {
        if (pos == V) {
            // 所有頂點都已訪問，檢查是否形成迴路
            return isAdjacent(path[V-1], path[0]);
        }
        
        int lastVertex = path[pos-1];
        
        for (int v : adj[lastVertex]) {
            if (visited.find(v) == visited.end()) {
                path[pos] = v;
                visited.insert(v);
                
                if (hamiltonianCycleUtil(path, visited, pos+1)) {
                    return true;
                }
                
                // 回溯
                visited.erase(v);
                path[pos] = -1;
            }
        }
        
        return false;
    }
    
public:
    // 打印圖
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "頂點 " << i << " 的鄰居: ";
            for (int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    // 改良：打印路徑的輔助函數
    void printPath(const vector<int>& path, bool isCycle = false) {
        if (path.empty()) {
            cout << "未找到路徑" << endl;
            return;
        }
        
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        
        if (isCycle && !path.empty()) {
            cout << " -> " << path[0];
        }
        cout << endl;
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
    
    // 測試漢米頓路徑
    vector<int> path = g.findHamiltonianPath();
    cout << "漢米頓路徑: ";
    g.printPath(path);
    
    // 測試漢米頓迴路
    vector<int> cycle = g.findHamiltonianCycle();
    cout << "漢米頓迴路: ";
    g.printPath(cycle, true);
    
    return 0;
}