#include "Perkolacja.h"

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <ostream>

Perkolacja::Perkolacja(int N,                                //
                       float P1,                             //
                       const std::vector<unsigned>& side_1,  //
                       const std::vector<unsigned>& side_2,  //
                       const std::vector<unsigned>& side_3,  //
                             std::mt19937 &rng)
    : N{N}, P1{P1}, uf{N * (N + 1) / 2, side_1, side_2, side_3}
{
    using namespace std::literals::string_literals;

    if (N <= 0 || N > MAX_SIZE) throw std::invalid_argument("N out of range in "s + __FUNCTION__);

    siatka.resize(N);
    for (auto& row : siatka)
    {
        row.resize(N);
    }


    std::shuffle(kolejka_wezlow.begin(), kolejka_wezlow.end(), rng);
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

int Perkolacja::modeluj()
{

}
