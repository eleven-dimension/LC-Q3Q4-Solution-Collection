#include <bits/stdc++.h>
using namespace std;

template <class WeightType>
class FloydWarshall {
public:
    FloydWarshall(size_t number_of_vertices,
                  WeightType inf_weight = std::numeric_limits<WeightType>().max() / 2)
        : inf_weight_(inf_weight),
          distance_(number_of_vertices, std::vector<WeightType>(number_of_vertices, inf_weight)) {
        for (size_t i = 0; i < number_of_vertices; ++i) {
            distance_[i][i] = 0;
        }
    }

    void addDirectedEdge(size_t from, size_t to, WeightType weight) {
        distance_[from][to] = std::min(distance_[from][to], weight);
    }

    void addBidirectedEdge(size_t from, size_t to, WeightType weight) {
        addDirectedEdge(from, to, weight);
        addDirectedEdge(to, from, weight);
    }

    void addEdge(size_t from, size_t to, WeightType weight, bool bidirected) {
        if (bidirected) {
            addBidirectedEdge(from, to, weight);
        } else {
            addDirectedEdge(from, to, weight);
        }
        // (bidirected ? addBidirectedEdge : addDirectedEdge)(from, to, weight);
    }

    void computeShortestPaths() {
        const size_t num = number_of_vertices();
        for (size_t k = 0; k < num; ++k) {
            for (size_t i = 0; i < num; ++i) {
                for (size_t j = 0; j < num; ++j) {
                    distance_[i][j] = std::min(distance_[i][j], distance_[i][k] + distance_[k][j]);
                }
            }
        }
    }

    WeightType getDistance(size_t from, size_t to) const {
        return distance_[from][to] == std::numeric_limits<WeightType>().max() / 2 ? std::numeric_limits<WeightType>().max() : distance_[from][to];
    }

private:
    size_t number_of_vertices() const {
        return distance_.size();
    }

    std::vector<std::vector<WeightType>> distance_;

    const WeightType inf_weight_;
};

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        unordered_map<int, list<int>> stop_to_cluster;
        int n = routes.size();
        for (int i = 0; i < n; i++) {
            for (auto& stop : routes[i]) {
                stop_to_cluster[stop].emplace_back(i);
            }
        }

        FloydWarshall<int> f(n);
        for (int i = 0; i < n; i++) {
            for (auto& stop : routes[i]) {
                for (auto& cluster : stop_to_cluster[stop]) {
                    if (i == cluster) continue;
                    // cout << i << " " << cluster << endl;
                    f.addDirectedEdge(i, cluster, 1);
                }
            }
        }
        f.computeShortestPaths();

        int ans = INT_MAX;
        for (auto& source_cluster : stop_to_cluster[source]) {
            for (auto& target_cluster : stop_to_cluster[target]) {
                // cout << "cluster: " << source_cluster << " " << target_cluster << endl;
                ans = min(ans, f.getDistance(source_cluster, target_cluster));
            }
        }
        if (source == target) return 0;
        if (ans == INT_MAX) return -1;
        return ans + 1;
    }
};