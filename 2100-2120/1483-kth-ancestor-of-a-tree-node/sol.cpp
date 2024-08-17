#include <bits/stdc++.h>
using namespace std;

class TreeAncestor {
public:
    vector<vector<int>> f;
    int kDepth;
    vector<vector<int>> sons;

    TreeAncestor(int n, vector<int>& parent) : sons(n) {
        for (int i = 0; i < n; i++) {
            if (parent[i] == -1) continue;
            sons[parent[i]].emplace_back(i);
        }
        // cout << "here" << endl;
        kDepth = log2(n) + 1;
        f = vector<vector<int>>(n, vector<int>(kDepth + 5, -1));

        queue<int> q;
        q.push(0);
        while (q.size()) {
            auto cur = q.front();
            q.pop();
            for (auto& son : sons[cur]) {
                f[son][0] = cur;
                for (int step = 1; step <= kDepth; step++) {
                    if (f[son][step - 1] != -1) {
                        f[son][step] = f[f[son][step - 1]][step - 1];
                    }
                }
                q.push(son);
            }
        }

        // for (int i = 0; i < n; i++) {
        //     for (auto& x : f[i]) {
        //         cout << x << ' ';
        //     }
        //     cout << endl;
        // }
    }
    
    int getKthAncestor(int node, int k) {
        int res = node;
        int base = 0;
        while (k != 0) {
            if (res == -1) {
                return -1;
            }
            if (k & 1) {
                res = f[res][base];
            }
            base++;
            k >>= 1;
        }
        return res;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */