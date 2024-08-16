#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

struct ValPosPair {
    int val, pos;
};

class Solution {
public:
    vector<int> st;

    void build(int cur, int l, int r, vector<int>& h) {
        if (l == r) {
            st[cur] = h[l];
            return;
        }
        int m = (l + r) / 2;
        build(cur * 2, l, m, h);
        build(cur * 2 + 1, m + 1, r, h);
        st[cur] = max(st[cur * 2], st[cur * 2 + 1]);
    }

    int query(int cur, int l, int r, int ql, int v) {
        if (st[cur] <= v) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        if (ql <= m) {
            int res = query(cur * 2, l, m, ql, v);
            if (res != -1) {
                return res;
            }
        }
        return query(cur * 2 + 1, m + 1, r, ql, v);
    }

    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int n = heights.size(), m = queries.size();
        st.resize(4 * n + 430);
        build(1, 0, n - 1, heights);
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            int a = queries[i][0], b = queries[i][1];
            if (a > b) {
                swap(a, b);
            }
            if (a == b || heights[a] < heights[b]) {
                ans[i] = b;
            } else {
                ans[i] = query(1, 0, n - 1, b + 1, heights[a]);
            }
        }
        return ans;
    }
};

int main() {
    vector<int> heights = {6,4,8,5,2,7};
    vector<vector<int>> queries = {{0,1},{0,3},{2,4},{3,4},{2,2}};
}