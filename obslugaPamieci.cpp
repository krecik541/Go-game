#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "conio2.h"
#include "funkcje.h"

char**planszaAlkoacja(int rozmiar_y, int rozmiar_x)
{
    char**plansza = new char* [rozmiar_y];
    for(int i = 0; i < rozmiar_y; i++)
        plansza[i] = new char [rozmiar_x];
    return plansza;
}

void dealokowanieB(bool **t, int y, int x)
{
    for(int i = 0; i < y; i++)
        delete [] t[i];

    delete [] t;
}

void dealokowanieC(char **t, int y, int x)
{
    for(int i = 0; i < y; i++)
        delete [] t[i];

    delete [] t;
}

