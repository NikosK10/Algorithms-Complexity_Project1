#include <iostream>  
#include <vector>  
#include <algorithm>  
  
using namespace std;  
  
int gcd(int a, int b) {  
    while (b != 0) {  
        int temp = b;  
        b = a % b;  
        a = temp;  
    }  
    return a;  
}  
  
struct Edge {  
    int u, v, p, w;  
    float weight;   
};  
  
struct UnionFind {  
    vector<int> parent, rank;  
  
    UnionFind(int n) {  
        parent.resize(n);  
        rank.resize(n, 0);  
        for (int i = 0; i < n; i++) parent[i] = i;  
    }  
  
    int find(int x) {  
        if (parent[x] != x) {  
            parent[x] = find(parent[x]);  
        }  
        return parent[x];  
    }  
  
    bool unite(int x, int y) {  
        int rootX = find(x);  
        int rootY = find(y);  
        if (rootX == rootY) return false;  
        if (rank[rootX] > rank[rootY]) {  
            parent[rootY] = rootX;  
        } else if (rank[rootX] < rank[rootY]) {  
            parent[rootX] = rootY;  
        } else {  
            parent[rootY] = rootX;  
            rank[rootX]++;  
        }  
        return true;  
    }  
};  
  
float kruskal(int n, vector<Edge>& edges, int c1, int c2) {  
    for (auto& edge : edges) {  
        edge.weight = c2 * edge.p - c1 * edge.w;  
    }  
  
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {  
        return a.weight > b.weight;  
    });  
  
    UnionFind uf(n);  
    int total_p = 0;  
    int total_w = 0;  
    int count = 0;  
  
    for (const auto& edge : edges) {  
        if (uf.unite(edge.u, edge.v)) {  
            total_p += edge.p;  
            total_w += edge.w;  
            count++;  
            if (count == n - 1) break;  
        }  
    }  
  
    return (total_p) * c2 - c1 * total_w;  
}  
  
pair<int, int> kruskal2(int n, vector<Edge>& edges, int best) {  
    for (auto& edge : edges) {  
        edge.weight = edge.p - best * edge.w;  
    }  
  
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {  
        return a.weight > b.weight;  
    });  
  
    UnionFind uf(n);  
    int total_p = 0;  
    int total_w = 0;  
    int count = 0;  
  
    for (const auto& edge : edges) {  
        if (uf.unite(edge.u, edge.v)) {  
            total_p += edge.p;  
            total_w += edge.w;  
            count++;  
            if (count == n - 1) break;  
        }  
    }  
  
    return make_pair(total_p, total_w);  
}  
  
pair<int, int> find_best_ratio(int p_max, int w_max, vector<Edge>& edges) {  
    float best = 0;  
    float b;  
  
  
    for (int c1 = 1; c1 <= p_max; c1++) {  
        int low = 1;  
        int high = w_max;  
        int best_c2 = 1;  
        while (low <= high) {  
            int c2 = (low + high) / 2;  
            if (kruskal(edges.size(), edges, c1, c2) > 0) {  
                best_c2 = c2;  
                high = c2 - 1;  
            } else {  
                low = c2 + 1;  
            }  
        }  
        b = c1/best_c2;  
        if(best < c1/best_c2){   
            best = c1/best_c2;  
        }  
    }  
  
    pair<int, int> result = kruskal2(edges.size(), edges, best);  
    int total_p = result.first;  
    int total_w = result.second;  
    int gcd_val = gcd(total_p, total_w);  
    return make_pair(total_p / gcd_val, total_w / gcd_val);  
}  
  
int main() {  
    int n, m;  
    cin >> n >> m;  
  
  
    vector<Edge> edges(m);  
    for (int i = 0; i < m; i++) {  
        cin >> edges[i].u >> edges[i].v >> edges[i].p >> edges[i].w;  
        edges[i].u--;  
        edges[i].v--;  
    }  
  
    int maxp = kruskal(edges.size(), edges, 0, 1);  
    int maxw = kruskal(edges.size(), edges, -1, 0);  
  
  
    pair<int, int> result = find_best_ratio(maxp, maxw, edges);  
    cout << result.first << " " << result.second << endl;  
  
    return 0;  
}  