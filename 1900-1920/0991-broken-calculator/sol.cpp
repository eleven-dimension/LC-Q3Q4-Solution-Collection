#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int brokenCalc(int start, int end) {
        if (end <= start) return start - end;
        if (end % 2 == 0) {
            return 1 + brokenCalc(start, end / 2);
        }
        return 1 + brokenCalc(start, end + 1);
    }
};

int main() {
    Solution sol;
    cout << sol.brokenCalc(1, 19260817); // 39
}