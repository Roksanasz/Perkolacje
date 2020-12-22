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
   Perkolacja percol {10, 0.6};
   percol.print(std::cout);


}






