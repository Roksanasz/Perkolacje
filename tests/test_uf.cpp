#include <cmath>
#include <limits>
#include <gtest/gtest.h>
#include <exception>
#include <vector>

#include "union_find.h"

TEST(UnionFind, simple)
{
    const int N = 5;  // Zbiór 5-elementowy

    UnionFind uf(N, {}, {}, {});
    EXPECT_EQ(uf.size(), N);

    // W pustym uf każdy rodzic jest swoim rodzicem
    for (int i = 0; i < N; i++)
    {
        EXPECT_EQ(uf.set_find(i), i);
    }

    // łączymy węzły 0 i 1
    uf.set_union(0, 1);

    // węzły 0 i 1 muszą mieć tego samego rodzica
    EXPECT_EQ(uf.set_find(0), uf.set_find(1));

    // "rank" węzła informuje, ile razy do poddrzewa zawierające ten węzeł dołaczano inne poddrzewa
    EXPECT_NE(uf.get_rank(0), uf.get_rank(1));

    // rodzicem 0 jest 0 lub 1; rodzicem 1 jest 0 lub 1
    EXPECT_TRUE(uf.set_find(0) == 0 || uf.set_find(0) == 1);
    EXPECT_TRUE(uf.set_find(1) == 0 || uf.set_find(1) == 1);
    for (int i = 2; i < N; i++)
    {
        EXPECT_EQ(uf.set_find(i), i);
    }
}

TEST(UnionFind, connect3sides)
{
    const int N = 7;
    std::vector<unsigned> horizontal_nodes = {0};
    std::vector<unsigned> vertical_nodes = {1};
    std::vector<unsigned> diagonal_nodes = {3, 6};

    UnionFind uf(N, horizontal_nodes, vertical_nodes, diagonal_nodes);

    // łączymy 0 i 1. To łączy zbiór "horizontal" z "diagonal"
    uf.set_union(0, 1);
    EXPECT_FALSE(uf.spans_3_sides(1));

    // 3 i 6 są w diagonal
    uf.set_union(3, 6);
    EXPECT_FALSE(uf.spans_3_sides(3));

    // 5 nie należy do klastra ani do żadnej krawędzi; po połączniu należy do klastra 3-5-6
    uf.set_union(3, 5);
    EXPECT_FALSE(uf.spans_3_sides(5));

    // 1 nie należy do klastra ani do krawędzi; po połączenia nalezy do klastra 0-1-4
    uf.set_union(4, 1);
    EXPECT_FALSE(uf.spans_3_sides(1));

    // łącząc 3 i 4, tworzymy klaster 0-1-3-4-5-6 łączący węzły "poziome" (0), "pionowe" (1) i diagonalne (3 lub 6).
    // Ten klaster dotyka więc 3 krawędzi
    uf.set_union(4, 3);
    for (auto i : {0, 1, 3, 4, 5, 6})
    {
        EXPECT_TRUE(uf.spans_3_sides(i));
    }

    // węzeł 2 wciąż niepołączony
    EXPECT_FALSE(uf.spans_3_sides(2));
    EXPECT_EQ(uf.set_find(2), 2);
}
