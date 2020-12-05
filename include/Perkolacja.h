#ifndef PERKOLACJA_H
#define PERKOLACJA_H

#include "union_find.h"

#include <cassert>
#include <iosfwd>
#include <vector>

class Perkolacja
{
  public:
    using Node = int;
    constexpr static Node OCCUPIED = 1;     // wezel zajety
    constexpr static Node UNOCCUPIED = 0;   // wezel wolny
    constexpr static int MAX_SIZE = 100000; // maksymalny dopuszczalny rozmiar ukladu

    Perkolacja(int N, float P1);

    auto key(int y, int x) const
    {
        assert(y < N && x <= y && x >= 0);
        return N * y + x;
    }
    auto prob() const { return P1; }
    auto size() const { return N; }
    void print(std::ostream& out) const;

  private:
    const int N;
    const float P1;
    std::vector<std::vector<int>> siatka;
    UnionFind uf;
};

#endif  // PERKOLACJA_H
