#include <queue>

#include "testenv.hpp"
#include "../standard/GeoVector.hpp"
#include "../standard/compress.hpp"

using namespace gandalfr;

TEST(VECTOR_ND, OPERATOR) {
    const f32 dim = 5;
    GeoVector<f32, dim> vec1 = GeoVector<f32, dim>{0, 1, 2, 3, 4};
    GeoVector<f32, dim> vec2 = {4, 2, 3, 4, 0};
    GeoVector<f32, dim> vec3(vec1);

    for (f32 i = 0; i < dim; ++i) {
        EQ(vec1[i], i);
    }

    auto pls(+vec1), mns(-vec1);
    for (f32 i = 0; i < dim; ++i) {
        EQ(vec1[i], pls[i]);
        EQ(-vec1[i], mns[i]);
    }

    auto add(vec1 + vec2);
    auto sub(vec1 - vec2);
    auto mlt(vec1 * 5);
    auto div(vec1 / 2);
    for (f32 i = 0; i < dim; ++i) {
        EQ(add[i], vec1[i] + vec2[i]);
        EQ(sub[i], vec1[i] - vec2[i]);
        EQ(mlt[i], vec1[i] * 5);
        EQ(div[i], vec1[i] / 2);
    }

    vec1 += vec2;
    EQ(vec3, vec1 - vec2);
}

TEST(VECTOR_ND, GEOMETRIC) {
    Point3d vec1 = {1, 2, 1};
    Point3d vec2 = {3, -2, 1};
    NEAR(vec1.dot(vec2), 0, EPS);
    NEAR(vec1.normSq(), 6, EPS);
    NEAR(vec1.norm(), 2.44948974278, EPS);
}

TEST(VECTOR_ND, CONVERT_WITH_STDVEC) {
    const f32 dim = 5;
    std::vector<f32> stdvec(dim);
    for (f32 i = 0; i < dim; ++i) stdvec[i] = i;
    GeoVector<f32, dim> vec;
    vec.load(stdvec);
    EQ(stdvec, vec.to_stdvec());
}

TEST(GRID, CHECK_AROUND) {
    PointGrid::set_size(5, 6);
    PointGrid g{1, 0};
    EQ(g.toIdx(), 6);
    EQ(toPointGrid(6), g);

    std::vector<bool> v;
    for (const PointGrid& d : GAROUND) {
        PointGrid nx = g + d;
        v.push_back(nx.isValid());
    }
    std::vector<bool> ans = {1, 1, 1, 0, 1, 1, 1, 0, 0};
    EQ(v, ans);
}

TEST(GRID, SOLVE_MAZE) {
    const f32 H = 5, W = 6, X = -1;
    std::vector<std::string> T{
        ".##..#",
        "....##",
        ".##...",
        "..####",
        "#....."
    };
    std::vector<std::vector<f8>> ANS{
        {0,X,X,5,6,X},
        {1,2,3,4,X,X},
        {2,X,X,5,6,7},
        {3,4,X,X,X,X},
        {X,5,6,7,8,9}
    };

    PointGrid::set_size(H, W);
    std::queue<PointGrid> q;
    q.push({0, 0});
    std::vector<std::vector<f8>> dist(H, std::vector<f8>(W, X));
    dist[0][0] = 0;
    while (!q.empty()) {
        PointGrid cur = q.front();
        q.pop();
        for (f32 i = 1; i <= 4; ++i) {
            auto d = GAROUND[i];
            PointGrid nxt = cur + d;
            if (!nxt.isValid()) continue;
            if (T[nxt.h()][nxt.w()] == '#') continue;
            if (dist[nxt.h()][nxt.w()] == X) {
                dist[nxt.h()][nxt.w()] = dist[cur.h()][cur.w()] + 1;
                q.push(nxt);
            }
        }
    }
    EQ(dist, ANS);
}

TEST(UTIL, COMPRESS) {
    std::vector<f32> vec{2, 4, 5, 4, 3, 10, -1};
    std::vector<f32> ans{1, 3, 4, 3, 2, 5, 0};
    EQ(compress(vec), ans);
}

int main() {
    RunAllTests();
    return 0;
}
