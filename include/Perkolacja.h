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

    Perkolacja(int N, double P1, std::mt19937 &rng);
    auto key(int x, int y) const
    {
        if(!(y < N && x <= y && x >= 0))
        {
            std::cout<< " mmm"<< std::endl;
        }
        assert(y < N && x <= y && x >= 0);
        return y * (y + 1) / 2 + x;
    }
    std::vector<unsigned>pionowa();
    std::vector<unsigned>diag();
    std::vector<unsigned>pozioma();
    auto prob() const { return P1; }
    auto size() const { return N; }
    void print(std::ostream& out) const;
    bool add_node(int x, int y)
    {  // dodaj węzeł


        assert (siatka [y][x] == 0);
        siatka[y][x] = 1;
        int gran = N-1;

        auto numer_wezla = key(x, y);

        if (x > 0)
        {
            auto numer_sasiada = key(x - 1, y);
            if(siatka[y][x-1] != 0)
            {
                uf.set_union(numer_wezla,numer_sasiada);
            }
        }
        if (x < y)
        {
            auto numer_sasiada = key(x + 1, y);
            if (siatka[y][x + 1] !=0)
            {
                uf.set_union(numer_wezla, numer_sasiada);
            }

        }
        if (y > 0 && y != x)
        {
            auto numer_sasiada = key(x, y - 1);
            if (siatka[y - 1][x] !=0)
            {
                uf.set_union(numer_wezla, numer_sasiada);
            }

        }
        if (y < gran)
        {
            auto numer_sasiada = key(x, y + 1);
            if (siatka[y + 1][x] != 0)
            {
              uf.set_union(numer_wezla, numer_sasiada);
            }

        }

        node_counter++;
        return spans_3_sides(numer_wezla);
    }

    bool spans_3_sides(int numer_wezla)
    {

        return uf.spans_3_sides(numer_wezla);
    };                // czy istnieje klaster spinający 3 krawędzie?
    bool modeluj();  // dodawaj węzły z kolejka_węzłów aż spans 3_sides zwróci true, zwróć liczbę węzłów

  private:
    const int N;
    const double P1;
    std::vector<std::vector<int>> siatka;
    UnionFind uf;
    std::vector<std::pair<int, int>> kolejka_wezlow;  // wszystkie punkty siatki w losowej kolejności
    int node_counter = 0;
};

#endif  // PERKOLACJA_H
