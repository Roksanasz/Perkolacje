#include<stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int L=10;
int Tab[L][L];
float P1 = 0.6;
int starNo;

void percol()
{
    for(int i=1;i<=L;i++)
     {
         starNo=i-1;

         for(int j=0;j<starNo;j++)
         {
            //Tab[i][j] = 0;

            printf("%c",'*');
         }
         printf("\n");
     }
}



int main()
 {
     percol();



 }
