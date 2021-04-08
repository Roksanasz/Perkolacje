#include "Perkolacja.h"

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <ostream>

Perkolacja::Perkolacja(int N, float P1, std::mt19937 &rng)
    : N{N}, P1{P1}, uf{N * (N + 1) / 2, pozioma(), pionowa(), diag()},
      kolejka_wezlow(N*(N+1)/2)
{
    using namespace std::literals::string_literals;
    if (N <= 0 || N > MAX_SIZE) throw std::invalid_argument("N out of range in "s + __FUNCTION__);

    siatka.resize(N);
    for (auto& row : siatka)
    {
        row.resize(N);
    }
//std::pair<int, int>
    int idx = 0;
    for ( int y = 0; y < N; y++)
    {
        for ( int x = 0; x <= y; x++)
        {
            kolejka_wezlow[idx] = {x, y};
            idx++;
        }
    }
    std::shuffle(kolejka_wezlow.begin(), kolejka_wezlow.end(), rng);
}


std::vector<unsigned> Perkolacja::pionowa(){
    std::vector <unsigned> side1;
    for(int i=0; i<N;i++){
        side1.push_back(i*(i+1)/2);
    }
    return side1;
}


std::vector<unsigned> Perkolacja::diag(){
    std::vector <unsigned> side2;
    for(int i=0; i<N;i++){
        side2.push_back(i*(i+3)/2);
    }
    return side2;
}

std::vector<unsigned> Perkolacja::pozioma(){
    std::vector <unsigned> side3;
    for(int i=0; i<N;i++){
        side3.push_back((N*(N-1)/2)+i);//sprawdzić
    }
    return side3;
}

void Perkolacja::print(std::ostream& out) const
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            out << siatka[i][j];
        }
        out << "\n";
    }
}

int Perkolacja::modeluj(){

    for (unsigned long long i=0; i<kolejka_wezlow.size(); i++)
    {
        auto znaleziono = add_node(kolejka_wezlow[i].first,kolejka_wezlow[i].second);
        if (znaleziono)
        {
            return node_counter;
        }
    }

    return -1;
}


