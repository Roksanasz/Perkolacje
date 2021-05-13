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
    plik.open ("dane_"+std::to_string(L)+".csv", std::ios::app);
   // plik <<"Wyniki dla N= "<< N <<" oraz L= "<< L << ": "<< "\n";
    for(int i = 0; i < N; i++)
        {
            Perkolacja percol{L, PC, rand};
            bool b = percol.modeluj();
            znalezione += b;


            //std::cout << "\n";


        }
        plik <<  double(znalezione)/ N<< "\t"<< N<<  "\n";
        plik.close();
        return 0;

};
int main(int argc, const char* argv[])
{

    int L= 4;
    int N = 100000000;

    if (argc >= 2) L= stoi(argv[1]);
    if (argc >= 3) N = stoi(argv[2]);
    policz(N,L);
}
