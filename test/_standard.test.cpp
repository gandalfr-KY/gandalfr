#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"

#include <queue>

#include "testenv.hpp"
#include "gandalfr/other/io.hpp"
#include "gandalfr/other/RandomUtility.hpp"
#include "gandalfr/geometry/Vector.hpp"
#include "gandalfr/standard/utility.hpp"
#include "gandalfr/standard/Fraction.hpp"
#include "gandalfr/standard/RollingHash.hpp"
#include "gandalfr/standard/Grid.hpp"

using namespace gandalfr;

TEST(VECTOR_ND, OPERATOR) {
    const i32 dim = 5;
    Vector<i32, dim> vec1 = Vector<i32, dim>{0, 1, 2, 3, 4};
    Vector<i32, dim> vec2 = {4, 2, 3, 4, 0};
    Vector<i32, dim> vec3(vec1);

    for (i32 i = 0; i < dim; ++i) {
        EQ(vec1[i], i);
    }

    auto pls(+vec1), mns(-vec1);
    for (i32 i = 0; i < dim; ++i) {
        EQ(vec1[i], pls[i]);
        EQ(-vec1[i], mns[i]);
    }

    auto add(vec1 + vec2);
    auto sub(vec1 - vec2);
    auto mlt(vec1 * 5);
    auto div(vec1 / 2);
    for (i32 i = 0; i < dim; ++i) {
        EQ(add[i], vec1[i] + vec2[i]);
        EQ(sub[i], vec1[i] - vec2[i]);
        EQ(mlt[i], vec1[i] * 5);
        EQ(div[i], vec1[i] / 2);
    }

    vec1 += vec2;
    EQ(vec3, vec1 - vec2);
}

TEST(VECTOR_ND, GEOMETRIC) {
    Vector3d vec1 = {1, 2, 1};
    Vector3d vec2 = {3, -2, 1};
    NEAR(vec1.dot(vec2), 0, EPS);
    NEAR(vec1.normSq(), 6, EPS);
    NEAR(vec1.norm(), 2.44948974278, EPS);
}

TEST(VECTOR_ND, CONVERT_WITH_STDVEC) {
    const i32 dim = 5;
    std::vector<i32> stdvec(dim);
    for (i32 i = 0; i < dim; ++i) stdvec[i] = i;
    Vector<i32, dim> vec;
    vec.load(stdvec);
    EQ(stdvec, vec.toStdvec());
}

TEST(GRID, CHECK_AROUND) {
    Grid::setSize(5, 6);
    Grid g{1, 0};
    EQ(g.getIdx(), 6);
    EQ(Grid(6), g);

    std::vector<bool> v;
    for (const Grid& nx : g.getAround()) {
        v.push_back(nx.isValid());
    }
    std::vector<bool> ans = {1, 1, 0, 1, 1, 1, 0, 0};
    EQ(v, ans);
}

TEST(GRID, SOLVE_MAZE) {
    const i32 H = 5, W = 6, X = -1;
    std::vector<std::string> T{
        ".##..#",
        "....##",
        ".##...",
        "..####",
        "#....."
    };
    std::vector<std::vector<i32>> ANS{
        {0,X,X,5,6,X},
        {1,2,3,4,X,X},
        {2,X,X,5,6,7},
        {3,4,X,X,X,X},
        {X,5,6,7,8,9}
    };

    Grid::setSize(H, W);
    std::queue<Grid> q;
    q.push({0, 0});
    std::vector<std::vector<i32>> dist(H, std::vector<i32>(W, X));
    dist[0][0] = 0;
    while (!q.empty()) {
        Grid cur = q.front();
        q.pop();
        auto around = cur.getAround();
        for (i32 i = 0; i < 4; ++i) {
            Grid nxt = around[i];
            auto [nxh, nxw] = nxt;
            if (!nxt.isValid()) continue;
            if (T[nxh][nxw] == '#') continue;
            if (dist[nxh][nxw] == X) {
                dist[nxh][nxw] = dist[cur.h][cur.w] + 1;
                q.push(nxt);
            }
        }
    }
    EQ(dist, ANS);
}

TEST(UTIL, COMPRESS) {
    std::vector<i32> vec{2, 4, 5, 4, 3, 10, -1};
    std::vector<i32> ans{1, 3, 4, 3, 2, 5, 0};
    EQ(compress(vec), ans);
}

TEST(UTIL, INVERSION) {
    const i32 len = 5, rep = 10;
    std::vector<i32> rnd_vec(5);
    for (i32& x : rnd_vec) x = RandUtil::randDouble(-10, 10);
    auto num_swap = [](std::vector<i32> v) {
        i32 ret = 0;
        const i32 N = v.size();
        for(i32 i = 0; i < N; ++i) {
            for (i32 j = 0; j < N - 1; ++j) {
                if (v[j] > v[j + 1]) {
                    std::swap(v[j], v[j + 1]);
                    ++ret;
                }
            }
        }
        return ret;
    };

    for (int r = 0; r < rep; ++r) {
        for (i32 i = 0; i < len; ++i) {
            rnd_vec[i] = RandUtil::randInt(-10, 10);
        }
        EQ(inversion(rnd_vec), num_swap(rnd_vec));
    }
}

TEST(UTIL, INVERSION_WITH_TWO_ARRAY) {
    std::vector<i32> vec1{10, 2, 5, 0, 9};
    std::vector<i32> vec2{10, 0, 9, 5, 2};
    EQ(inversion(vec1, vec2), 5);
}

TEST(UTIL, LIS) {
    std::vector<i32> vec1{5, 1, 3, 3, 2, 4};
    EQ(lis(vec1, true), 3);
    EQ(lis(vec1), 4);
    std::vector<i32> vec2{1, 1, 1};
    EQ(lis(vec2, true), 1);
    EQ(lis(vec2), 3);
}

TEST(FRACTION, OPERATOR) {
    Fraction a(1, 2), b(-1, 3), c(4, -2);
    EQ(-a, Fraction(-1, 2));
    EQ(a + b, Fraction(1, 6));
    EQ(a - b, Fraction(5, 6));
    EQ(a * c + 1, 0);
    EQ(a / b + c, Fraction(-7, 2));
    a += 2 * b;
    EQ(a, Fraction(-1, 6));
    b -= a;
    EQ(b, Fraction(-1, 6));
    a *= b + 1;
    EQ(a, Fraction(-5, 36));
    a /= Fraction(10, -36);
    EQ(a, Fraction(1, 2));
}

TEST(FRACTION, INFTY) {
    Fraction inf(1, 0), minf(-1, 0);
    EQ(inf - INT64_MAX, inf);
    EQ(inf / 0, inf);
    EQ(minf / 0, minf);
    EQ(1 / inf, 0);
    try {
        inf + minf;
        EQ(true, false);
    } catch (IndeterminateOperationException& e) {
    }
    try {
        inf - inf;
        EQ(true, false);
    } catch (IndeterminateOperationException& e) {
    }
    try {
        inf * 0;
        EQ(true, false);
    } catch (IndeterminateOperationException& e) {
    }
    try {
        inf / minf;
        EQ(true, false);
    } catch (IndeterminateOperationException& e) {
    }
}

TEST(ROLLING_HASH, TEST) {
    std::string str = "ABBABABAABABABABBA";
    std::string sb = "ABA";
    RollingHash STR(str);
    RHCode SUBSTR(sb);
    for (u32 i = 0; i < str.size() - sb.size() + 1; ++i) {
        if (str.substr(i, 3) == sb) {
            EQ(STR.getCode(i, i + 3), SUBSTR);
        } else {
            NEQ(STR.getCode(i, i + 3), SUBSTR);
        }
    }
}

int main() {
    RunAllTests<false>();
    return 0;
}
