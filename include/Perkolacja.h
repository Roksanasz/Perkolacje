#ifndef PERKOLACJA_H
#define PERKOLACJA_H

#include "union_find.h"

#include <cassert>
#include <iosfwd>
#include <vector>
#include <stdio.h>
#include <gsl/gsl_rng.h>


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
    void add_node(int x, int y);  // dodaj węzeł
    bool spans_3_sides() const;   // czy istnieje klaster spinający 3 krawędzie?
    int modeluj(); // dodawaj węzły z kolejka_węzłów aż spans 3_sides zwróci true, zwróć liczbę węzłów
    int ListaSasiadow();

  private:
    const int N;
    const float P1;
    int i,j;
    int Tab[N][N]={0}; //lista wspolrzednych obsadzonych wezlow
    std::vector<std::vector<int>> siatka;
    UnionFind uf;  // poprawić później żeby można było dokonać detekcji perkolacji 3-nożnej
    std::vector<std::pair<int,int>> kolejka_wezlow; // wszystkie punkty siatki w losowej kolejności
    int node_counter = 0;
    std::vector<wspolrzedne> sasiedzi;
    std::vector<wspolrzedne> emptysasiedzi;

    void add_node(){
        const gsl_rng_type * T;
        gsl_rng * r;
        gsl_rng_env_setup();

        T = gsl_rng_default;
        r = gsl_rng_alloc (T);


        for(int i=1;i<=N;i++)
         {
             int Nm1=i-1;
             for(int j=0;j<Nm1;j++)    //jak to inaczej zapełnić?
             {
                double u = gsl_rng_uniform (r);
                if (u <= P1) {
                       Tab[i][j] = 1;
                 else {
                       Tab[i][j] = 0;
                       }
             }
           }
           printf("\n");
       }
       gsl_rng_free (r);

    }

    void ListaSasiadow()
    {
        sasiedzi.clear();

        for(int i=1; i<N-1; i++)
        {
            int Nm1=i-1;
            for(int j=0; j<Nm1; j++)//warunki brzegowe
            {
                if(Tab[i][j]==1)
                {
                    if(Tab[i+1][j]==0)
                        sasiedzi.push_back(wspolrzedne(i+1,j));

                    if(Tab[i-1][j]==0)
                        sasiedzi.push_back(wspolrzedne(i-1,j));

                    if(Tab[i][j+1]==0)
                        sasiedzi.push_back(wspolrzedne(i,j+1));

                    if(Tab[i][j-1]==0)
                        sasiedzi.push_back(wspolrzedne(i,j-1));
                }
            }
        }
    }

    int modeluj(){


        if spans_3_sides()=False{
                add_node();}
        else{size();}


    }

};

#endif  // PERKOLACJA_H
