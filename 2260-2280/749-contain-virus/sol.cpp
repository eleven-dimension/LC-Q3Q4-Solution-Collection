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
    int containVirus(vector<vector<int>>& isInfected) {
        int n = isInfected.size(), m = isInfected[0].size();
        auto in = [&](int x, int y) {
            return 0 <= x && x < n && 0 <= y && y < m;
        };
        const int dx[] = {0, 0, -1, 1};
        const int dy[] = {1, -1, 0, 0};

        auto game_over = [&]() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (isInfected[i][j] == 0) {
                        return false;
                    }
                }
            }
            return true;
        };

        int wall_used = 0;
        while (true) {
            vector<unordered_set<pair<int, int>, TupleHash>> id_to_neighbors(1);
            vector<int> id_to_walls(1);
            vector<vector<int>> cp_infected(isInfected);

            int cur_id = 1;
            int target_id = -1;
            int max_impact = 0;

            auto update = [&](int x, int y, int id) {
                unordered_set<pair<int, int>, TupleHash> neighbors;
                queue<pair<int, int>> q;
                int walls = 0;
                q.emplace(x, y);
                isInfected[x][y] = -cur_id;
                while (q.size()) {
                    auto [cx, cy] = q.front();
                    q.pop();
                    for (int d = 0; d < 4; d++) {
                        int nx = cx + dx[d], ny = cy + dy[d];
                        if (!in(nx, ny)) {
                            continue;
                        }
                        if (isInfected[nx][ny] == 0) {
                            neighbors.emplace(nx, ny);
                            walls++;
                        }
                        if (isInfected[nx][ny] == 1) {
                            q.emplace(nx, ny);
                            isInfected[nx][ny] = -id;
                        }
                    }
                }
                id_to_walls.emplace_back(walls);
                id_to_neighbors.emplace_back(neighbors);
                // cout << "Finish" << endl;
                // cout << walls << endl;
                // for (auto& p : neighbors) {
                //     cout << p.first << " " << p.second << endl;
                // }
            };

            bool success = true;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (isInfected[i][j] == 1) {
                        success = false;
                        update(i, j, cur_id);
                        cur_id++;
                    }
                }
            }
            if (success) {
                return wall_used;
            }

            // for (int id = 0; id < id_to_neighbors.size(); id++) {
            //     cout << id << " " << id_to_neighbors[id].size() << endl;
            // }
            // cout << "-------------" << endl;

            for (int id = 0; id < id_to_neighbors.size(); id++) {
                // cout << id << " " << id_to_neighbors[id].size() << " " << max_impact << endl;
                if (id_to_neighbors[id].size() >= max_impact) {
                    // cout << "upd" << endl;
                    // cout << id << " " << id_to_neighbors[id].size() << " " << max_impact << endl;
                    max_impact = id_to_neighbors[id].size();
                    target_id = id;
                }
            }
            wall_used += id_to_walls[target_id];
            // cout << target_id << endl;
            // cout << wall_used << endl;
            // expand
            for (int id = 0; id < id_to_neighbors.size(); id++) {
                if (id == target_id) {
                    continue;
                }
                for (auto& [x, y] : id_to_neighbors[id]) {
                    cp_infected[x][y] = 1;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (isInfected[i][j] == (-target_id)) {
                        cp_infected[i][j] = -1;
                    }
                }
            }
            isInfected = cp_infected;
            if (game_over()) {
                return wall_used;
            }
            // cout << "---------------" << endl;
            // for (int i = 0; i < n; i++) {
            //     for (int j = 0; j < m; j++) {
            //         cout << isInfected[i][j] << " ";
            //     }
            //     cout << endl;
            // }
        }
    }
};

int main() {
    // vector<vector<int>> isInfected = {{1,1,1,0,0,0,0,0,0},{1,0,1,0,1,1,1,1,1},{1,1,1,0,0,0,0,0,0}};
    vector<vector<int>> isInfected = {{0}};
    Solution s;
    cout << s.containVirus(isInfected);
}