#ifndef GCDLCM
#define GCDLCM

namespace internal{
    template<class T> T _gcd(T a, T b){
        if(a % b == 0) return b;
        return _gcd(b, a % b); 
    }
}

// 絶対値の GCD を返す。片方が 0 ならもう一方の引数の絶対値を返す。
template<class T> T _gcd(T a, T b){
    if(b == 0) return (a >= 0 ? a : -a);
    return internal::_gcd((a >= 0 ? a : -a), (b >= 0 ? b : -b));
}

// 片方が 0 なら 0 が返る。
template<class T>
T _lcm(T a, T b) {
    if(b == 0) return 0;
    a = (a >= 0 ? a : -a);
    b = (b >= 0 ? b : -b);
    return a / internal::_gcd(a, b) * b ;
}

template<class T>
T _extgcd(T a, T b, T &s, T &t){
    if(b == 0){
        s = 1;
        t = 0;
        return a;
    }
    else{
        T tmp = _extgcd<T>(b, a % b, t, s);
        t -= a / b * s;
        return tmp;
    }
}

#endif