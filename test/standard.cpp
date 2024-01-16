#include "testenv.hpp"
#include "../standard/vector_nd.hpp"
#include "../standard/grid.hpp"

using namespace gandalfr;

TEST(VECTOR_ND, OPERATOR) {
    const int dim = 5;
    vector_nd<int, dim> vec1 = {0, 1, 2, 3, 4};
    vector_nd<int, dim> vec2 = {4, 2, 3, 4, 0};
    vector_nd<int, dim> vec3(vec1);

    for (int i = 0; i < dim; ++i) {
        EQ(vec1[i], i);
    }

    auto pls(+vec1), mns(-vec1);
    for (int i = 0; i < dim; ++i) {
        EQ(vec1[i], pls[i]);
        EQ(-vec1[i], mns[i]);
    }

    auto add(vec1 + vec2);
    auto sub(vec1 - vec2);
    auto mlt(vec1 * 5);
    auto div(vec1 / 2);
    for (int i = 0; i < dim; ++i) {
        EQ(add[i], vec1[i] + vec2[i]);
        EQ(sub[i], vec1[i] - vec2[i]);
        EQ(mlt[i], vec1[i] * 5);
        EQ(div[i], vec1[i] / 2);
    }

    vec1 += vec2;
    EQ(vec3, vec1 - vec2);
}

TEST(VECTOR_ND, GEOMETRIC) {
    point3d vec1 = {1, 2, 1};
    point3d vec2 = {3, -2, 1};
    NEAR(vec1.dot(vec2), 0, EPS);
    NEAR(vec1.norm_sq(), 6, EPS);
    NEAR(vec1.norm(), 2.44948974278, EPS);
}

TEST(VECTOR_ND, CONVERT_WITH_STDVEC) {
    const int dim = 5;
    std::vector<int> stdvec(dim);
    for (int i = 0; i < dim; ++i) stdvec[i] = i;
    vector_nd<int, dim> vec;
    vec.load(stdvec);
    EQ(stdvec, vec.to_stdvec());
}

TEST(GRID, CHECK_AROUND) {
    gpoint::set_size(5, 6);
    gpoint g{1, 0};
    EQ(g.to_idx(), 6);
    EQ(to_gpoint(6), g);

    std::vector<bool> v;
    for (const gpoint& d : GAROUND) {
        gpoint nx = g + d;
        v.push_back(nx.is_valid());
    }
    std::vector<bool> ans = {1, 1, 1, 0, 1, 1, 1, 0, 0};
    EQ(v, ans);
}

int main() {
    RunAllTests();
    return 0;
}
