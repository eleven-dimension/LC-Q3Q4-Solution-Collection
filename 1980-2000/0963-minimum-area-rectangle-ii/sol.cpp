#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        std::size_t seed = 0x20000430;
        std::hash<int> hash_int;
        seed ^= hash_int(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash_int(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};


class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        unordered_set<pair<int, int>, PairHash> points_set;
        for (auto& point : points) {
            points_set.emplace(point[0], point[1]);
        }

        auto is_right_angle = [&] (pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
            int dx1 = p2.first - p1.first;
            int dx2 = p3.first - p2.first;
            int dy1 = p2.second - p1.second;
            int dy2 = p3.second - p2.second;

            if (dx1 * dx2 + dy1 * dy2 == 0) {
                return true;
            }
            return false;
        };

        auto get_4 = [&] (pair<int, int> p1, pair<int, int> p2, pair<int, int> p3) {
            int dx = p3.first - p2.first;
            int dy = p3.second - p2.second;
            return make_pair(dx + p1.first, dy + p1.second);
        };

        auto dis = [&] (pair<int, int> p1, pair<int, int> p2) {
            int dx = p1.first - p2.first;
            int dy = p1.second - p2.second;
            return sqrt(dx * dx + dy * dy);
        };

        int n = points.size();
        double ans = 1e18;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (i == j || i == k || j == k) continue;
                    if (is_right_angle(
                        {points[i][0], points[i][1]},
                        {points[j][0], points[j][1]},
                        {points[k][0], points[k][1]}
                    )) {
                        auto [x4, y4] = get_4(
                            {points[i][0], points[i][1]},
                            {points[j][0], points[j][1]},
                            {points[k][0], points[k][1]}
                        );
                        if (points_set.contains({x4, y4})) {
                            auto len1 = dis({points[i][0], points[i][1]}, {points[j][0], points[j][1]});
                            auto len2 = dis({points[j][0], points[j][1]}, {points[k][0], points[k][1]});
                            ans = min(ans, len1 * len2);
                        }
                    }
                }
            }
        }

        return ans == 1e18 ? 0 : ans;
    }
};

int main() {
    vector<vector<int>> points = {{1,2},{2,1},{1,0},{0,1}};
    Solution sol;
    cout << sol.minAreaFreeRect(points);
}