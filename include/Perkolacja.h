#ifndef PERKOLACJA_H
#define PERKOLACJA_H

#include "union_find.h"

#include <cassert>
#include <iosfwd>
#include <vector>
#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>


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
    void add_node(int x, int y){            // dodaj węzeł

        std::vector<int> kolejka_wezlow = {1,3,4,9};//przykładowe węzły

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(kolejka_wezlow.begin(), kolejka_wezlow.end(), g);

    }
    bool spans_3_sides() const;   // czy istnieje klaster spinający 3 krawędzie?
    int modeluj(){}; // dodawaj węzły z kolejka_węzłów aż spans 3_sides zwróci true, zwróć liczbę węzłów

  private:
    const int N;
    const float P1;
    int i,j;
    std::vector<std::vector<int>> siatka;
    UnionFind uf;  // poprawić później żeby można było dokonać detekcji perkolacji 3-nożnej
    std::vector<std::pair<int,int>> kolejka_wezlow; // wszystkie punkty siatki w losowej kolejności
    int node_counter = 0;

};

#endif  // PERKOLACJA_H
