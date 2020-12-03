#include<stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "union_find.h"
#include "Perkolacja.h"
#include <algorithm>
#include <array>
#include <cassert>


using namespace std;


size_t key(size_t y, size_t x) { return N * y + x; }

void sprawdz(UnionFind & uf)
{

    auto size = uf.size();
    std::vector<size_t> cluster_store(size);
    for (size_t i = 0; i < size; i++)
    {
        cluster_store[i] = uf.set_find(i);
    }
    std::sort(cluster_store.begin(), cluster_store.end());
    auto iter = std::unique(cluster_store.begin(), cluster_store.end());
   // std::cout << "\nTrojkat o wymiarach:\n";
    auto cluster_cnt = std::distance(cluster_store.begin(), iter);
    std::cout << "liczba klastrow wynosi " << cluster_cnt << "\n";
}

int main()
{
    std::array<std::string, N> {percol()}; //sprawdzic jak to porownac
    std::vector<std::vector<int>> klucze(N);
    for (auto& vec : klucze) vec.resize(N, -1);

    size_t liczba_elementow = 0;
    for (size_t y = 0; y < N; y++)
    {
        assert(percol[y].length() == N);
        for (size_t x = 0; x < N; x++)
        {
            if (percol[y][x] != '0')
            {
                klucze[y][x] = liczba_elementow;
                liczba_elementow++;
            }
        }
    }

    UnionFind uf(liczba_elementow);
    for (size_t y = 0; y < N; y++)
    {
        for (size_t x = 0; x < N; x++)
        {
            auto current_key = klucze[y][x];
            if (current_key < 0)
            {
                continue;
            }
            if (y > 0 && klucze[y - 1][x] >= 0)
            {
                uf.set_union( klucze[y - 1][x], current_key);
            }
            if (x > 0 && klucze[y][x - 1] >= 0)
            {
                uf.set_union(klucze[y][x - 1], current_key);
            }
        }
    }
    auto klucz_0 = klucze[0][0];
    auto klucz_1 = klucze[N - 1][N - 1];

    std::cout << "a:\n";
    if (klucz_0 < 0 || klucz_1 < 0)
        std::cout << "narozniki nie sa polaczone\n";
    else
    {
        auto root_0 = uf.set_find(klucze[0][0]);
        auto root_1 = uf.set_find(klucze[N - 1][N - 1]);
        if (root_0 == root_1)
            std::cout << "narozniki sa polaczone\n";
        else
            std::cout << "narozniki nie sa polaczone\n";
    }

    std::cout << "\nb:\n";
    std::vector<size_t> top_roots;
    std::vector<size_t> bottom_roots;
    for (int i = 0; i < N; i++)
    {
        if (klucze[0][i] >= 0) top_roots.push_back(uf.set_find(klucze[0][i]));
        if (klucze[N - 1][i] >= 0) bottom_roots.push_back(uf.set_find(klucze[N - 1][i]));
    }
    std::sort(top_roots.begin(), top_roots.end());
    std::sort(bottom_roots.begin(), bottom_roots.end());
    auto it = std::unique(top_roots.begin(), top_roots.end());
    top_roots.resize(std::distance(top_roots.begin(), it));
    it = std::unique(bottom_roots.begin(), bottom_roots.end());
    bottom_roots.resize(std::distance(bottom_roots.begin(), it));

    std::vector<size_t> shared_roots;
    std::set_intersection(top_roots.begin(), top_roots.end(), bottom_roots.begin(), bottom_roots.end(),
                          std::back_inserter(shared_roots));
    if (shared_roots.empty())
        std::cout << "gorny i dolny wiersz nie są połączone\n";
    else
        std::cout << "gorny i dolny wiersz są połączone " << shared_roots.size() << " klastrami\n";

    sprawdz(uf);
}






