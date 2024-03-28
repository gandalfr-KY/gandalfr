#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"

#include <algorithm>

#include "testenv.hpp"
#include "gandalfr/other/RandomUtility.hpp"
#include "gandalfr/data_structure/BinaryTrie.hpp"

using namespace std;
using namespace gandalfr;

TEST(DATA_STRUCTURE, BINARY_TRIE) {

    std::vector<u32> A;
    BinaryTrie<32> BT;
    rep(i,0,100) {
        u32 x = RandUtil::randInt(0, 10000000);
        A.push_back(x);
        BT.insert(x);
    }
    rep(i,0,10000) {
        u32 q = RandUtil::randInt(0, 5);
        u32 x = RandUtil::randInt(0, 10000000);
        switch (q) {
        case 0:
            A.push_back(x);
            BT.insert(x);   
            break;
        case 1:
            A.erase(remove_if(all(A), [&](u32 a) { return a == x; }), A.end());
            BT.erase(x);
            break;
        case 2:
            for (auto& a : A) a ^= x;
            BT.applyXor(x);
            break;
        case 3:
            sort(all(A));
            assert(std::lower_bound(all(A), x) - A.begin() == BT.lowerBound(x));
            assert(std::upper_bound(all(A), x) - A.begin() == BT.upperBound(x));
            break;
        case 4:
            if (x >= A.size()) break;
            sort(all(A));
            assert(A[x] == BT.nthElement(x));
            break;
        case 5:
            assert(count(all(A), x) == BT.count(x));
            break;
        case 6:
            assert(A.size() == BT.size());
        default:
            break;
        }
    }
}

int main() {
    RunAllTests<false>();
    return 0;
}
