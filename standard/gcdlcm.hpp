#ifndef GCDLCM
#define GCDLCM

template<class T>
T _gcd(T a, T b){
    if(b == 0) return a;
    if(a % b == 0) return b;
    return _gcd(b, T(a % b)); 
}

template<class T>
T _lcm(T a, T b) { return a / _gcd(a, b) * b ; }

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