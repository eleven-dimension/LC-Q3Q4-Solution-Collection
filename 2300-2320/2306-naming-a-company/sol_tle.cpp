#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    using ll = long long;
    long long distinctNames(vector<string>& ideas) {
        int n = ideas.size();
        unordered_map<string, unordered_set<char>> suffix_to_first;

        for (int i = 0; i < n; i++) {
            string suffix = ideas[i].substr(1);
            suffix_to_first[suffix].emplace(ideas[i][0]);
        }

        ll ans = 0;
        for (char c1 = 'a'; c1 <= 'z'; c1++) {
            for (char c2 = 'a'; c2 <= 'z'; c2++) {
                if (c1 == c2) {
                    continue;
                }
                ll has_c1_cnt = 0, has_c2_cnt = 0;
                for (auto& [suffix, st] : suffix_to_first) {
                    bool has_c1 = st.contains(c1);
                    bool has_c2 = st.contains(c2);
                    if (has_c1 && !has_c2) {
                        has_c1_cnt++;
                    }
                    if (!has_c1 && has_c2) {
                        has_c2_cnt++;
                    }
                }
                ans += has_c1_cnt * has_c2_cnt;
            }
        }

        return ans;
    }
};