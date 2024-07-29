#include <bits/stdc++.h>
using namespace std;

struct Edge {
    size_t to;
    size_t weight;

    Edge(size_t to, size_t weight) : to(to), weight(weight) {}
};

class Graph {
public:
    enum class EdgeType { DIRECTED, UNDIRECTED };

    Graph(size_t number_of_vertices, EdgeType type = EdgeType::UNDIRECTED) : adjacency_list_(number_of_vertices), edge_type_(type) {}

    void addEdge(size_t u, size_t v, size_t weight) {
        adjacency_list_[u].emplace_back(v, weight);
        if (edge_type_ == EdgeType::UNDIRECTED) {
            adjacency_list_[v].emplace_back(u, weight);
        }
    }

    const std::vector<Edge>& getOutgoingEdges(size_t u) const {
        return adjacency_list_[u];
    }

    size_t number_of_vertices() const {
        return adjacency_list_.size();
    }

private:
    EdgeType edge_type_;
    std::vector<std::vector<Edge>> adjacency_list_;
};

class Solution {
public:
    int ans = INT_MAX;
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<int> visited_depth(n, -1);

        Graph graph(n);
        for (auto& edge : edges) {
            graph.addEdge(edge[0], edge[1], 1);
        }
        
        bool finish = false;
        while (!finish) {
            finish = true;
            for (int i = 0; i < n; i++) {
                if (visited_depth[i] == -1) {
                    finish = false;
                    visit(i, 0, visited_depth, graph);
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }

    void visit(int cur, int depth, vector<int>& visited_depth, Graph& graph) {
        if (visited_depth[cur] != -1) {
            int cycle = depth - visited_depth[cur];
            if (cycle > 2) {
                ans = min(ans, cycle);
            }
            return;
        }
        visited_depth[cur] = depth;
        auto& edges = graph.getOutgoingEdges(cur);
        for (auto& edge : edges) {
            visit(edge.to, depth + 1, visited_depth, graph);
        }
    }
};

int main() {
    Solution sol;

    int n = 7;
    vector<vector<int>> edges = {{0,1},{1,2},{2,0},{3,4},{4,5},{5,6},{6,3}};
    cout << sol.findShortestCycle(n, edges);
}