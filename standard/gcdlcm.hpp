#ifndef GCDLCM
#define GCDLCM

template<class T>
T _gcd(T a, T b){
    if(a % b == 0) { return(b); }
    else{ return _gcd(b, T(a % b)); }
}

template<class T>
T _lcm(T a, T b) { return a / _gcd(a, b) * b ; }

#endif