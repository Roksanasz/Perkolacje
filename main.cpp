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

const double PC = 0.59274605079210;

int main()
{
    //int i;

    std::random_device rd;
    std::mt19937 rand(rd());


    // funkcja od N i L, wynik do pliku
    const int L = 100;
    int znalezione = 0;
    int N = 10000;
    for(int i = 0; i < N; i++)
    {
        Perkolacja percol{L, PC, rand};
        bool b = percol.modeluj();
        znalezione += b;
//        percol.print(std::cout);
        std::cout << b << " "  << double(znalezione)/(i+1.0)<<  "\n";
        std::cout << "\n";
    }
    //
}
