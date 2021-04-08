#ifndef PERKOLACJA_H
#define PERKOLACJA_H

#include "union_find.h"

#include <cassert>
#include <iosfwd>
#include <vector>
#include <stdio.h>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <ctime>

class Perkolacja
{
  public:
    using Node = int;
    constexpr static Node OCCUPIED = 1;      // wezel zajety
    constexpr static Node UNOCCUPIED = 0;    // wezel wolny
    constexpr static int MAX_SIZE = 100000;  // maksymalny dopuszczalny rozmiar ukladu

    Perkolacja(int N, float P1, const std::vector<unsigned>& side_1, const std::vector<unsigned>& side_2,
               const std::vector<unsigned>& side_3, std::mt19937 &rng);
    auto key(int x, int y) const
    {
        assert(y < N && x <= y && x >= 0);
        return N * y + x;
    }
    auto prob() const { return P1; }
    auto size() const { return N; }
    void print(std::ostream& out) const;
    bool add_node(int x, int y)
    {  // dodaj węzeł

        int gran = N-1;
        auto numer_wezla = key(x, y);
        if (x > 0)
        {
            auto numer_sasiada = key(x-1, y);
            uf.set_union(numer_wezla,numer_sasiada);
        }
        if (x < gran)
        {
            auto numer_sasiada = key(x+1, y);
            uf.set_union(numer_wezla,numer_sasiada);
        }
        if (y > 0)
        {
            auto numer_sasiada = key(x, y-1);
            uf.set_union(numer_wezla,numer_sasiada);
        }
        if (y < gran)
        {
            auto numer_sasiada = key(x, y+1);
            uf.set_union(numer_wezla,numer_sasiada);
        }

        node_counter++;
        return spans_3_sides(numer_wezla);
    }

    bool spans_3_sides(int numer_wezla) const
    {

        return uf.spans_3_sides(numer_wezla);
    };                // czy istnieje klaster spinający 3 krawędzie?
    int modeluj();  // dodawaj węzły z kolejka_węzłów aż spans 3_sides zwróci true, zwróć liczbę węzłów

  private:
    const int N;
    const float P1;
    int i, j;
    std::vector<std::vector<int>> siatka;
    UnionFind uf;  // poprawić później żeby można było dokonać detekcji perkolacji 3-nożnej
    std::vector<std::pair<int, int>> kolejka_wezlow;  // wszystkie punkty siatki w losowej kolejności
    int node_counter = 0;
};

#endif  // PERKOLACJA_H
