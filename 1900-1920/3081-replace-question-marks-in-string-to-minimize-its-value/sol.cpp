#include <bits/stdc++.h>
using namespace std;

struct CharCnt {
    char c;
    int cnt;

    bool operator<(const CharCnt& ano) const {
        return ano.cnt == cnt ? c > ano.c : cnt > ano.cnt;
    }
};

class Solution {
public:
    string minimizeStringValue(string s) {
        int n = s.size();
        const int N = 26;
        vector<int> cnt(N);
        int undecided = 0;
        for (auto& c : s) {
            if (c == '?') {
                undecided++;
            } else {
                cnt[c - 'a']++;
            }
        }

        priority_queue<CharCnt> q;
        for (int i = 0; i < N; i++) {
            q.emplace('a' + i, cnt[i]);
        }
        
        string ans;
        for (int i = 1; i <= undecided; i++) {
            auto [cur_c, cur_cnt] = q.top();
            ans += cur_c;
            q.pop();
            q.emplace(cur_c, cur_cnt + 1);
        }

        sort(ans.begin(), ans.end());
        for (int j = 0, i = 0; i < n; i++) {
            if (s[i] == '?') {
                s[i] = ans[j++];
            }
        }
        return s;
    }
};

int main() {
    string s = "abcdefghijklmnopqrstuvwxy??";
    Solution sol;
    cout << sol.minimizeStringValue(s);
}