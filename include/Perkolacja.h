#ifndef PERKOLACJA_H
#define PERKOLACJA_H


class Perkolacja
{

    const int N = 100;
    float P1 = 0.6;

    public:

        void Perkolacja()               //rysuje o jedno pole za du¿o - ostatnia linia -??
        {
            for(int i=1;i<=N;i++)
             {
                 int starNo=i-1;

                 for(int j=0;j<starNo;j++)
                 {
                    Tab[i][j] = 0;
                    double pg = rand() / float(RAND_MAX);

                    if (pg <= P1) {
                            printf("%c",'*');
                           Tab[i][j] = -1;
                         //  cout<<Tab[i][j];
                                  }
                    else{

                            printf("%c",'0');
                            Tab[i][j] = 0;
                           //  cout<<Tab[i][j];
                        }

                 }
                 printf("\n");
             }
        }

    protected:

    private:
    std::vector<size_t> siatka;
};

#endif // PERKOLACJA_H
