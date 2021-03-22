#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "union_find.h"
#include "Perkolacja.h"
#include <algorithm>
#include <array>
#include <cassert>

using namespace std;

void sprawdz(UnionFind& uf)
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
    //int i;
    int N = 10;
    std::vector<unsigned> side1,side2,side3;

    //int pionowa(int i), pozioma(int i),diag(int i);


    /*pionowa(i)
    {
        return i*(i+N)/2;
    }
    diag(i)
    {
        return i*(i+3)/2;
    }
    pozioma(i)
    {
        return // tu przedział od N(N-1)/2 DO (N(N+1)/2)-1...
    }
    for(int i=0; i<=N;i++){
        side1.push_back(pionowa(i));
    }

   for(int i=0; i<=N;i++){
     side2.push_back(diag(i));
    }
   for(int i=0; i<=N;i++){
     side3.push_back(pozioma(i));
    }*/

    std::vector<unsigned> pionowa ={0};
    for(int i=0; i<=N;i++){
        pionowa.push_back(i*(i+2)/2);
    }
    std::vector<unsigned> diag ={0};
    for(int i=0; i<N;i++){
        diag.push_back(i*(i+3)/2);
    }
    std::vector<unsigned> pozioma ={pionowa.back()};
    for(int i=0; i<N;i++){
        pozioma.push_back(pozioma.back()+i);
    }


    Perkolacja percol{10, 0.6, side1, side2, side3};
    percol.print(std::cout);
}
