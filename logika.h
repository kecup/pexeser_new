#ifndef LOGIKA_H
#define LOGIKA_H
#include <math.h>
#include <algorithm>
#include <vector>
#include <time.h>
#include <iostream>

class gameData{
private:
   int *pole;
   int velikost;
public:
    std::vector<int> inPlay;
    gameData(int a)
    {
        velikost=a;
        pole=new int[velikost*velikost];
        srand(time(NULL));
        int generovano;
        std::vector<int> vector;
        for(int i=0; i<velikost*velikost/2; i++)
        {
            vector.push_back(i);
            vector.push_back(i);
        }

        for(int i=0; i<velikost*velikost; i++)
        {
            inPlay.push_back(i);
            generovano=rand()%(velikost*velikost-i);
            pole[i]=vector[generovano];
            vector.erase(vector.begin()+generovano);
        }

    }
    ~gameData()
    {
        delete [] pole;
    }

    int index(int i, int j)
    {return i*velikost+j;}

    int getValue(int r, int s)
    {
        return (pole[index(r,s)]);
    }

    int getValue(int a)
    {
        return (pole[a]);
    }
};

class PChrac{
private:
    int *pole;//pole uchovávající -1 pro neznámé a čísla pro známé indexy
    std::vector<int> vNezname;//vektor uchovavajici nezname indexy
    int velikost;//velikost pole
    double diff;//obtiznost
    bool prvni;//prvni tah
public:
    int lastIndex;//prvni otočená karta v tahu
    int lastValue;

    bool getPrvni()
    {
        return prvni;
    }

    PChrac(int a, double obtiznost)
    {
        velikost=a;
        diff=obtiznost;
        pole=new int[velikost*velikost];
        for(int i=0; i<velikost*velikost; i++)
        {
            pole[i]=-1;
            vNezname.push_back(i);
        }
        prvni=true;
        lastIndex=-1;
        lastValue=-1;
    }

    int prvniTah()
    {
        for(int i=0; i<velikost*velikost; i++)
        {
            if(pole[i]>=0)
            {
                if(double(rand())/RAND_MAX<diff)
                {
                    pole[i]=-1;
                    vNezname.push_back(i);
                    std::sort (vNezname.begin(),vNezname.end());
                }
            }
        }
        std::vector<int> dva;
        for(int h=0; h<velikost*velikost; h++)
        {
            if(pole[h]>=0)
                dva.push_back(pole[h]);
        }
        std::sort(dva.begin(),dva.end());
        int znamy_index;
        prvni=false;
        if(dva.size()>1)
        {
            for(unsigned int k=0; k<dva.size()-1;k++)
            {
                if(dva[k]==dva[k+1])
                {
                    for(int b=0; b<velikost*velikost; b++)
                        if(pole[b]==dva[k])
                        {
                            znamy_index=b;
                            break;
                        }
                    return(znamy_index);
                }
            }
        }

       return(vNezname[rand()%vNezname.size()]);
    }

    int druhyTah()// vola se kdyz prvni=false
    {
        int index=-1;
        for(int i=0; i<velikost*velikost; i++)
        {
            if(i!=lastIndex)
            {
                if(pole[i]==lastValue)
                    index=i;
            }
        }
        if(index==-1)
            index=vNezname[rand()%vNezname.size()];
        prvni=true;
        lastIndex=-1;
        lastValue=-1;
        return index;
    }

    void otocenaKarta(int index, int value)// vola se vždy když se otočí karta
    {
        for(unsigned int i=0; i<vNezname.size(); i++)
        {
           if(vNezname[i]==index)
           {
               pole[index]=value;
               vNezname.erase(vNezname.begin()+i);
               break;
           }
        }
    }

    void vyhrano(int a, int b)
    {
       pole[a]=-2;
       pole[b]=-2;
       /*for(unsigned int k=0; k<vNezname.size(); k++)
       {
           if(vNezname[k]==a||vNezname[k]==b)
               vNezname.erase(vNezname.begin()+k);
       }*/
    }

    ~PChrac()
    {
        delete [] pole;
    }

};

class human{
public:
    int body;
    human()
    {
        body=0;
    }
};

#endif // LOGIKA_H
