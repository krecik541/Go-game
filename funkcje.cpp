#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "conio2.h"
#include "funkcje.h"

void strzalki(int *pozKur_y, int *pozKur_x, int rozmiar_y, int rozmiar_x)
{
    char znak = getch();
    if(znak == ST_GORA)
    {
        if(*pozKur_y - 1 > 0)
            *pozKur_y -= 1;
    }
    else if(znak == ST_DOL)
    {
        if(*pozKur_y + 1 < rozmiar_y - 1)
            *pozKur_y += 1;
    }
    else if(znak == ST_LEWO)
    {
        if(*pozKur_x - 1 > 0)
            *pozKur_x -= 1;
    }
    else if(znak == ST_PRAWO)
    {
        if(*pozKur_x + 1 < rozmiar_x - 1)
            *pozKur_x += 1;
    }
}

void wypiszINT(int z)
{
    char txt[32];
    sprintf(txt, "%d", z);
    cputs(txt);
}

void wypiszFLOAT(float z)
{
    char txt[32];
    sprintf(txt, "%.1f", z);
    cputs(txt);
}
