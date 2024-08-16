#include <bits/stdc++.h>
using namespace std;

template <class T>
T FastPow(T base, size_t exponent, const T& one = 1) {
    T res{one};
    for (; exponent > 0; exponent /= 2) {
        if (exponent % 2) {
            res *= base;
        }
        base *= base;
    }
    return res;
}

template <class T>
struct BiggerInteger {
    using Type = __int128_t;
};

template <>
struct BiggerInteger<int32_t> {
    using Type = int64_t;
};

template <auto Mod, class T = decltype(Mod), bool Safer = true>
class ModInteger final {
    static_assert(Mod > 0);

public:
    using Type = ModInteger<Mod, T>;
    using BiggerType = ModInteger<Mod, typename BiggerInteger<T>::Type>;

    constexpr ModInteger(T val = 0) : val_(val) {
        TuneValue();
    }

    constexpr ModInteger(const Type& mod_value) : val_(mod_value.val_) {}

    template <class U>
    constexpr ModInteger(ModInteger<Mod, U> mod_value) : ModInteger(mod_value.val()) {}

    constexpr Type& operator=(Type rhs) {
        this->val_ = rhs.val_;
        return *this;
    }

    constexpr void TuneValue() {
        while (val_ < 0) {
            val_ += kMaxMultiple;
        }
        if (val_ >= Mod) {
            val_ %= Mod;
        }
    }

    constexpr T val() const {
        return val_;
    }

    constexpr Type operator+(const Type& rhs) const {
        return val_ + rhs.val_;
    }

    constexpr Type operator-(const Type& rhs) const {
        return val_ - rhs.val_;
    }

    constexpr Type operator*(const Type& rhs) const {
        if constexpr (Safer) {
            if (rhs.val_ != 0 && val_ < std::numeric_limits<T>::max() / rhs.val_) {
                return val_ * rhs.val_;
            }
            return BiggerType(val_) * BiggerType(rhs.val_);
        } else {
            return val_ * rhs.val_;
        }
    }

    constexpr Type operator/(const Type& rhs) const {
        return *this * (rhs ^ (Mod - 2));
    }

    constexpr Type operator^(size_t exponent) const {
        return FastPow(*this, exponent);
    }

    constexpr Type& operator+=(const Type& rhs) {
        return *this = *this + rhs;
    }

    constexpr Type& operator-=(const Type& rhs) {
        return *this = *this - rhs;
    }

    constexpr Type& operator*=(const Type& rhs) {
        return *this = *this * rhs;
    }

    constexpr Type& operator/=(const Type& rhs) {
        return *this = *this / rhs;
    }

    constexpr Type& operator^=(const Type& rhs) {
        return *this = *this ^ rhs;
    }

    template <class OStream>
    friend OStream& operator<<(OStream& output_stream, const Type& mod_value) {
        return output_stream << mod_value.val_;
    }

private:
    static constexpr T kMaxMultiple = std::numeric_limits<T>::max() / Mod * Mod;

    T val_ = 0;
};

struct StopWatch {
    StopWatch() : start_time_(std::chrono::system_clock::now()) {}

    ~StopWatch() {
        const auto end_time = std::chrono::system_clock::now();
        const auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_);
        std::cout << duration.count() << "us\n";
    }

private:
    std::chrono::time_point<std::chrono::system_clock> start_time_;
};

template <class T>
size_t HashCombine(size_t seed, const T& value) {
    return seed ^ (std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

struct TupleHash {
    size_t operator()(const auto& tuple) const {
        size_t res = 0;
        std::apply([&res](const auto&... args) { ((res = HashCombine(res, args)), ...); }, tuple);
        return res;
    }
};

template <class>
class Cache {};

template <class R, class... Args>
class Cache<R(Args...)> {
    using This = Cache<R(Args...)>;

public:
    Cache(auto func) : func_(func) {}

    const auto& operator()(const auto&... args) {
        const auto args_tuple = std::make_tuple(args...);
        auto iter = value_map_.find(args_tuple);
        if (iter != value_map_.end()) {
            return iter->second;
        }
        return value_map_.emplace(args_tuple, func_(*this, args...)).first->second;
    }

private:
    std::function<R(This&, Args...)> func_;

    std::unordered_map<std::tuple<Args...>, R, TupleHash> value_map_;
};


class Solution {
public:
    const int Mod = 1e9 + 7;
    using ModBig = ModInteger<1000000007>;
    int numberOfStableArrays(int zero, int one, int limit) {
        int n = zero + one;
        auto f = Cache<int(int, int, int)>([&](
            auto& self, int zero_num, int one_num, int last_bit) -> int {
                if (zero_num == 0) {
                    if (last_bit == 0 || one_num > limit) {
                        return 0;
                    }
                    return 1;
                } else if (one_num == 0) {
                    if (last_bit == 1 || zero_num > limit) {
                        return 0;
                    }
                    return 1;
                }

                int res = 0;
                if (last_bit == 0) {
                    res = (self(zero_num - 1, one_num, 0) + self(zero_num - 1, one_num, 1)) % Mod;
                    if (zero_num > limit) {
                        res = (res - self(zero_num - limit - 1, one_num, 1) + Mod) % Mod;
                    }
                } else {
                    res = (self(zero_num, one_num - 1, 0) + self(zero_num, one_num - 1, 1)) % Mod;
                    if (one_num > limit) {
                        res = (res - self(zero_num, one_num - limit - 1, 0) + Mod) % Mod;
                    }
                }
                return res;
            }
        );

        return (f(zero, one, 0) + f(zero, one, 1)) % Mod;
    }
};