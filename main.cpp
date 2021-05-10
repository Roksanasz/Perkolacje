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
int policz(int N, int L)
{
    std::random_device rd;
    std::mt19937 rand(rd());
    int znalezione = 0;
    std::ofstream plik;
    plik.open ("dane.txt", std::fstream::app);
    plik <<"Wyniki dla N= "<< N <<" oraz L= "<< L << ": "<< "\n";
    for(int i = 0; i < N; i++)
        {
            Perkolacja percol{L, PC, rand};
            bool b = percol.modeluj();
            znalezione += b;

            std::cout << b << " "  << double(znalezione)/(i+1.0)<<  "\n";
            //std::cout << "\n";

    plik <<  b << " "  << double(znalezione)/(i+1.0)<<  "\n";
        }

        plik.close();
        return 0;

};
int main()
{
    //int i;




    // funkcja od N i L, wynik do pliku
    // zrobić jakieś symulacje dla kilku różnych L, np. 8, 16, 32, 64, 128, 256
    // N rzędu 10^8
    // wyznaczyc
    const int L = 4;

    int N = 100000000;

    policz(N,L);
}
