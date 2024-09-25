#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  using ll = long long;
  long long distinctNames(vector<string>& ideas) {
    int n = ideas.size();
    unordered_map<string_view, int> suffix_to_first;

    for (int i = 0; i < n; i++) {
      string_view suffix = string_view(ideas[i]).substr(1);
      suffix_to_first[suffix] |= 1 << (ideas[i][0] - 'a');
    }

    ll ans = 0;
    for (int c1 = 0; c1 < 26; c1++) {
      for (int c2 = 0; c2 < 26; c2++) {
        if (c1 == c2) {
          continue;
        }
        ll has_c1_cnt = 0, has_c2_cnt = 0;
        for (auto& [suffix, st] : suffix_to_first) {
          bool has_c1 = st & (1 << c1);
          bool has_c2 = st & (1 << c2);
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
