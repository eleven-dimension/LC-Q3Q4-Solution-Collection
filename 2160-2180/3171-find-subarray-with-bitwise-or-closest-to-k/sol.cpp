#include <bits/stdc++.h>
using namespace std;

template <class T, auto op, auto e>
class SparseTable {
    static_assert(std::is_convertible_v<decltype(op), std::function<T(T, T)>>, "op must work as T(T, T)");
    static_assert(std::is_convertible_v<decltype(e), std::function<T()>>, "e must work as T()");

public:
    SparseTable() : SparseTable(0) {}
    SparseTable(size_t n) : SparseTable(std::vector<T>(n, e())) {}
    SparseTable(const std::vector<T>& v) : n_(v.size()), m_(log2(v.size())) {
        table_ = std::vector<std::vector<T>>(n_, std::vector<T>(m_ + 1, e()));
        for (size_t i = 0; i < n_; i++) {
            table_[i][0] = v[i];
        }
        for (size_t j = 1; j <= m_; j++) {
            for (size_t i = 0; i <= n_ - (1 << j); i++) {
                table_[i][j] = op(table_[i][j - 1], table_[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(size_t l, size_t r) {
        assert(0 <= l && l < r && r <= n_);
        size_t len = log2(r - l);
	    return op(table_[l][len], table_[r - (1 << len)][len]);
    }

private:
    std::vector<std::vector<T>> table_;
    size_t n_;
    size_t m_;
};

#include <ranges>

template <std::ranges::range Range>
auto FirstFalse(Range&& range, auto condition) {
    return std::ranges::lower_bound(range, 0, [&](int l, auto) {
        return condition(l);
    });
}

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        auto or_ = [](int a, int b) { return a | b; };
        auto e = []() { return 0; };
        SparseTable<int, or_, e> st(nums);
        
        int n = nums.size();
        int ans = numeric_limits<int>::max();
        for (int r = 0; r < n; r++) {
            auto range = std::views::iota(0, r + 1);
            // auto l_iter = std::ranges::lower_bound(range, 0, [&](int l, auto) { return st.query(l, r + 1) >= k; });
            auto l_iter = FirstFalse(range, [&](int l) { return st.query(l, r + 1) >= k; });
            auto update = [&](auto iter) { ans = std::min(ans, std::abs(k - st.query(*iter, r + 1))); };
            if (l_iter != range.end()) {
                update(l_iter);
            }
            if (l_iter != range.begin()) {
                update(--l_iter);
            }
        }
        return ans;
    }
};