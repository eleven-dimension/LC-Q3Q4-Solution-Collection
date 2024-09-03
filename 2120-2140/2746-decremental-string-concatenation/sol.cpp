#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    int minimizeConcatenatedLength(vector<string>& words) {
        int n = words.size();
        int f[1010][30][30];
        fill(&f[0][0][0], &f[0][0][0] + 1010 * 30 * 30, 0x3f3f3f3f);
        
        int front = words[0].front() - 'a', tail = words[0].back() - 'a';
        f[0][front][tail] = words[0].size();
        for (int i = 1; i < n; i++) {
            for (int fr = 0; fr < 26; fr++) {
                for (int ta = 0; ta < 26; ta++) {
                    if ('a' + ta == words[i].front()) {
                        int new_ta = words[i].back() - 'a';
                        f[i][fr][new_ta] = min(f[i][fr][new_ta], f[i - 1][fr][ta] + (int)words[i].size() - 1);
                    } else {
                        int new_ta = words[i].back() - 'a';
                        f[i][fr][new_ta] = min(f[i][fr][new_ta], f[i - 1][fr][ta] + (int)words[i].size());
                    }

                    if ('a' + fr == words[i].back()) {
                        int new_fr = words[i].front() - 'a';
                        f[i][new_fr][ta] = min(f[i][new_fr][ta], f[i - 1][fr][ta] + (int)words[i].size() - 1);
                    } else {
                        int new_fr = words[i].front() - 'a';
                        f[i][new_fr][ta] = min(f[i][new_fr][ta], f[i - 1][fr][ta] + (int)words[i].size());
                    }
                }
            }
            // for (int b = 0; b < 3; b++) {
            //     for (int c = 0; c < 3; c++) {
            //         cout << f[i][b][c] << " ";
            //     }
            // }
            // cout << endl;
        }
        int ans = INT_MAX;
        for (int fr = 0; fr < 26; fr++) {
            for (int ta = 0; ta < 26; ta++) {
                ans = min(ans, f[n - 1][fr][ta]);
            }
        }
        return ans;
    }
};