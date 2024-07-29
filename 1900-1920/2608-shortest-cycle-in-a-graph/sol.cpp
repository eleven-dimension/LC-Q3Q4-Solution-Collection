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
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        Graph graph(n);

        for (auto& edge : edges) {
            graph.addEdge(edge[0], edge[1], 1);
        }

        auto calc = [&](int del_from, int del_to) {
            queue<pair<int, int>> q;
            vector<int> dist(n, INT_MAX);

            q.emplace(0, del_from);
            dist[del_from] = 0;
            while (q.size()) {
                auto [dis, u] = q.front();
                q.pop();

                if (dis > dist[u]) {
                    continue;
                }
                dist[u] = dis;

                for (auto edge : graph.getOutgoingEdges(u)) {
                    int v = edge.to;
                    if (u == del_from && v == del_to) {
                        continue;
                    }
                    if (v == del_to) {
                        return dis + 1;
                    }
                    q.emplace(dis + 1, v);
                }
            }
            return INT_MAX;
        };

        int ans = INT_MAX;
        for (int del = 0; del < m; del++) {
            int dis = calc(edges[del][0], edges[del][1]);
            if (dis != INT_MAX) {
                ans = min(ans, dis + 1);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main() {
    Solution sol;

    int n = 7;
    vector<vector<int>> edges = {{0,1},{1,2},{2,0},{3,4},{4,5},{5,6},{6,3}};
    cout << sol.findShortestCycle(n, edges);
}