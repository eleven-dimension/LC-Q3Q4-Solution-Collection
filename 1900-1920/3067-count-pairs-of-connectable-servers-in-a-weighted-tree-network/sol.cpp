#include <bits/stdc++.h>
using namespace std;

struct Edge {
    size_t to;
    size_t weight;

    Edge(size_t to, size_t weight) : to(to), weight(weight) {}

    bool operator==(const Edge& other) const {
        return to == other.to && weight == other.weight;
    }
};

enum class EdgeType { DIRECTED, UNDIRECTED };

class Graph {
public:
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
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {
        int n = edges.size() + 1;
        Graph graph(n);

        for (auto& edge : edges) {
            graph.addEdge(edge[0], edge[1], edge[2]);
        }

        vector<int> ans(n);
        for (int source = 0; source < n; source++) {
            priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> q;
            vector<int> distance(n, INT_MAX);

            const auto& edges_from_src = graph.getOutgoingEdges(source);
            int branch_size = edges_from_src.size();
            vector<int> cnt(branch_size);

            q.emplace(0, source, -1);
            distance[source] = 0;
            bool is_first = true;

            while (q.size()) {
                auto [cur_dis, cur_node, branch] = q.top();
                q.pop();

                if (cur_dis > distance[cur_node]) {
                    continue;
                }

                int cur_branch = 0;
                for (const auto& edge : graph.getOutgoingEdges(cur_node)) {
                    int new_dis = cur_dis + edge.weight;
                    if (new_dis < distance[edge.to]) {
                        distance[edge.to] = new_dis;
                        if (new_dis % signalSpeed == 0) {
                            if (is_first) {
                                cnt[cur_branch]++;
                            } else {
                                cnt[branch]++;
                            }
                        }

                        if (is_first) {
                            q.emplace(new_dis, edge.to, cur_branch++);
                        } else {
                            q.emplace(new_dis, edge.to, branch);
                        }
                    }
                }
                is_first = false;
            }

            int sum = accumulate(cnt.begin(), cnt.end(), 0);
            int cur_ans = 0;
            for (int i = 0; i < cnt.size(); i++) {
                cur_ans += (sum - cnt[i]) * cnt[i];
            }
            ans[source] = cur_ans / 2;
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> edges = {{0,1,1},{1,2,5},{2,3,13},{3,4,9},{4,5,2}};
    int signalSpeed = 1;
    Solution sol;
    auto&& ans = sol.countPairsOfConnectableServers(edges, signalSpeed);
    for (auto& x : ans) {
        cout << x << " ";
    }
}