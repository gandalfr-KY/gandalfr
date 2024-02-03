#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"

#include <queue>

#include "testenv.hpp"
#include "gandalfr/types.hpp"
#include "gandalfr/other/io.hpp"
#include "gandalfr/other/RandomUtility.hpp"
#include "gandalfr/math/utility.hpp"
#include "gandalfr/math/Matrix.hpp"

using namespace gandalfr;

TEST(UTIL, CONBINATORICS) {
    for (int i = 1; i < 100; ++i) {
        EQ(i, 1 / inv998(i)); 
        EQ(fact998(i), 1 / invFact998(i)); 
    }
    // 7C4
    EQ(7 * 6 * 5 * 4 / (4 * 3 * 2 * 1), comb998(7, 4));
    EQ(1, comb998(723948, 0));
    EQ(1, comb998(12298, 12298));
    EQ(comb998(223298, 12298), comb998(223298, 223298 - 12298));
    // 15P4
    EQ(15 * 14 * 13 * 12, perm998(15, 4));
    EQ(perm998(23456, 23456), fact998(23456));
    EQ(1, perm998(1324, 0));
    // 4H6
    EQ(9 * 8 * 7 * 6 * 5 * 4 / (6 * 5 * 4 * 3 * 2 * 1), homo998(4, 6));
}

TEST(MATRIX, OPERATOR) {
    Matrix<int> A(3, 4);
    A[0] = {1, 2, 3, 4};
    A[1] = {1, 2, 2, 0};
    A[2] = {2, 0, -3, 1};

    Matrix<int> B(4, 2);
    B[0] = {0, 1};
    B[1] = {2, 1};
    B[2] = {0, -1};
    B[3] = {1, 1};

    Matrix<int> AMultB(3, 2);
    AMultB[0] = {8, 4};
    AMultB[1] = {4, 1};
    AMultB[2] = {1, 6};
    EQ(A * B, AMultB);

    Matrix<int> C(3, 4);
    C[0] = {0, 1, 1, 0};
    C[1] = {1, 0, 0, 1};
    C[2] = {1, 1, 1, 1};

    Matrix<int> AplusC(3, 4);
    AplusC[0] = {1, 3, 4, 4};
    AplusC[1] = {2, 2, 2, 1};
    AplusC[2] = {3, 1, -2, 2};
    EQ(A + C, AplusC);

    Matrix<int> D(3, 4);
    D[0] = {0, 2, 3, 4};
    D[1] = {1, 1, 2, 0};
    D[2] = {2, 0, 3, 1};

    Matrix<int> AminusD(3, 4);
    AminusD[0] = {1, 0, 0, 0};
    AminusD[1] = {0, 1, 0, 0};
    AminusD[2] = {0, 0, -6, 0};
    EQ(A - D, AminusD);

    Matrix<int> E(2, 2);
    E[0] = {1, 1};
    E[1] = {1, 0};

    Matrix<int> E_squared(2, 2);
    E_squared[0] = {2, 1};
    E_squared[1] = {1, 1};

    Matrix<int> E_cubed(2, 2);
    E_cubed[0] = {3, 2};
    E_cubed[1] = {2, 1};

    EQ(E.power(0), Matrix<int>::E(2));
    EQ(E.power(1), E);
    EQ(E.power(2), E_squared);
    EQ(E.power(3), E_cubed);
}

int main() {
    RunAllTests<false>();
    return 0;
}
