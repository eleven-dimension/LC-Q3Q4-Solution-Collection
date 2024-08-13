#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) {
        int m = queries.size();
        vector<int> ans(m);
        for (int i = 0; i < m; i++) {
            int cnt = 0;
            int x = queries[i][0], y = queries[i][1];
            while (x != y) {
                if (x > y) {
                    x /= 2;
                } else if (x < y) {
                    y /= 2;
                } 
                cnt++;
            }
            ans[i] = cnt + 1;
        }
        return ans;
    }
};