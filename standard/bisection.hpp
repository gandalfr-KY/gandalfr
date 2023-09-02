#include <type_traits>

template <class T, class Func>
void bisection(T &t, T &f, const Func &F) {
    static_assert(std::is_invocable_r_v<bool, Func, T>);
    assert(F(t) && !F(f));
    while (std::abs(t - f) > 1) {
        T mid = (t + f) / 2;
        (F(mid) ? t : f) = mid;
    }
}

template <class Func>
void bisection(double &t, double &f, const Func &F, double eps = 1e-10) {
    static_assert(std::is_invocable_r_v<bool, Func, double>);
    assert(F(t) && !F(f));
    while (std::abs(t - f) > eps) {
        double mid = (t + f) / 2;
        (F(mid) ? t : f) = mid;
    }
}
