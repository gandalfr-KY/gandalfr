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
