#include <bits/stdc++.h>
using namespace std;

template <class T>
size_t HashCombine(size_t seed, const T& value) {
    return seed ^ (std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

struct TupleHash {
    size_t operator()(const auto& tuple) const {
        size_t res = 0;
        std::apply([&res](const auto&... args) { ((res = HashCombine(res, args)), ...); }, tuple);
        return res;
    }
};

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        if (n == 1) return 0;
        int kState = (1 << n);
        queue<pair<int, int>> q;
        unordered_map<pair<int, int>, int, TupleHash> dis;
        for (int node = 0; node < n; node++) {
            dis.emplace(pair<int, int>{1 << node, node}, 0);
            q.emplace(1 << node, node);
        }
        int ans = INT_MAX;
        while (q.size()) {
            auto [state, cur] = q.front();
            q.pop();
            for (auto& nxt : graph[cur]) {
                int next_state = state | (1 << nxt);
                if (dis.contains({next_state, nxt})) {
                    continue;
                }
                int cur_dis = dis[{state, cur}];
                if (next_state == (1 << n) - 1) {
                    ans = min(ans, cur_dis + 1);
                }
                dis[{next_state, nxt}] = cur_dis + 1;
                q.emplace(next_state, nxt);
            }
        }
        return ans;
    }
};