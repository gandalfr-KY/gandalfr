#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include "testenv.hpp"
#include "gandalfr/data_structure/BinaryTrie.hpp"

using namespace std;
using namespace gandalfr;

int main(void) {
    
    i32 Q;
    cin >> Q;
    BinaryTrie<32> A;
    while (Q--) {
        i32 q, x;
        cin >> q >> x;
        switch (q) {
        case 0:
            if (A.count(x) == 0) {
                A.insert(x);
            }
            break;
        case 1:
            A.erase(x);
            break;
        case 2:
            A.applyXor(x);
            std::cout << A.nthElement(0) << std::endl;
            A.applyXor(x);
            break;
        }
    }

}