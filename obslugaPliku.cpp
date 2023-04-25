#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "conio2.h"
#include "funkcje.h"

void zapisywanie(stan_gry gra)
{
    textbackground(DARKGRAY);
    textcolor(RED);
    char nazwa_pliku[100];
    for(int i=0; i < 100; i++)
    {
        nazwa_pliku[i] = 0;
    }

    gotoxy(LEGENDA_X, LEGENDA_Y + 20);
    cputs("WPROWADZ NAZWE PLIKU (LACZNIE Z ROZSZERZENIEM):");
    gotoxy(LEGENDA_X, LEGENDA_Y + 21);

    for(int i=0; i < 100; i++)
    {
        nazwa_pliku[i] = getche();
        if(nazwa_pliku[i] == ENTER)
        {
            nazwa_pliku[i] = '\0';
            break;
        }
    }

    FILE *plik = fopen(nazwa_pliku, "w");
    fprintf(plik, "%d\n", gra.rozmiar_y);
    fprintf(plik, "%d\n", gra.rozmiar_x);
    for(int i=0; i<gra.rozmiar_y; i++)
    {
        for(int j=0; j<gra.rozmiar_x; j++)
            fprintf(plik, "%d", gra.plansza[i][j]);
        fprintf(plik, "\n");
    }
    for(int i=0; i<gra.rozmiar_y; i++)
    {
        for(int j=0; j<gra.rozmiar_x; j++)
            fprintf(plik, "%d", gra.plansza_1[i][j]);
        fprintf(plik, "\n");
    }
    for(int i=0; i<gra.rozmiar_y; i++)
    {
        for(int j=0; j<gra.rozmiar_x; j++)
            fprintf(plik, "%d", gra.plansza_2[i][j]);
        fprintf(plik, "\n");
    }
    for(int i=0; i<gra.rozmiar_y; i++)
    {
        for(int j=0; j<gra.rozmiar_x; j++)
            fprintf(plik, "%d", gra.pionki[i][j]);
        fprintf(plik, "\n");
    }
    for(int i=0; i<gra.rozmiar_y; i++)
    {
        for(int j=0; j<gra.rozmiar_x; j++)
            fprintf(plik, "%d", gra.pionki_1[i][j]);
        fprintf(plik, "\n");
    }
    for(int i=0; i<gra.rozmiar_y; i++)
    {
        for(int j=0; j<gra.rozmiar_x; j++)
            fprintf(plik, "%d", gra.pionki_2[i][j]);
        fprintf(plik, "\n");
    }
    fprintf(plik, "%d\n%f%f", gra.tura, gra.punkty_biale, gra.punkty_czarne);

    fclose(plik);
}

stan_gry odczyt(stan_gry gra, bool *odczyt_plik)
{
    textbackground(DARKGRAY);
    textcolor(RED);
    char nazwa_pliku[104];

    gotoxy(LEGENDA_X, LEGENDA_Y + 20);
    cputs("WPROWADZ NAZWE PLIKU Z ZAPISEM:         ");
    gotoxy(LEGENDA_X, LEGENDA_Y + 21);

    for(int i=0; i < 100; i++)
    {
        nazwa_pliku[i] = getche();
        if(nazwa_pliku[i] == ENTER)
        {
            nazwa_pliku[i] = '\0';
            break;
        }
    }

    FILE *plik = fopen(nazwa_pliku, "r");
    if(plik == NULL)
    {
        *odczyt_plik = true;
        return gra;
    }

    dealokowanieC(gra.plansza, gra.rozmiar_y, gra.rozmiar_x);
    dealokowanieC(gra.plansza_1, gra.rozmiar_y, gra.rozmiar_x);
    dealokowanieC(gra.plansza_2, gra.rozmiar_y, gra.rozmiar_x);
    dealokowanieC(gra.pionki, gra.rozmiar_y, gra.rozmiar_x);
    dealokowanieC(gra.pionki_1, gra.rozmiar_y, gra.rozmiar_x);
    dealokowanieC(gra.pionki_2, gra.rozmiar_y, gra.rozmiar_x);

    fscanf(plik, "%d\n", &(gra.rozmiar_y));
    fscanf(plik, "%d\n", &(gra.rozmiar_x));

    gra = plansza(gra);

    for(int i=0; i < gra.rozmiar_y; i++)
    {
        for(int j=0; j < gra.rozmiar_x; j++)
            fscanf(plik, "%d", &(gra.plansza[i][j]));
        fscanf(plik, "\n");
    }

    for(int i=0; i < gra.rozmiar_y; i++)
    {
        for(int j=0; j < gra.rozmiar_x; j++)
            fscanf(plik, "%d", &(gra.plansza_1[i][j]));
        fscanf(plik, "\n");
    }

    for(int i=0; i < gra.rozmiar_y; i++)
    {
        for(int j=0; j < gra.rozmiar_x; j++)
            fscanf(plik, "%d", &(gra.plansza_2[i][j]));
        fscanf(plik, "\n");
    }

    for(int i=0; i < gra.rozmiar_y; i++)
    {
        for(int j=0; j < gra.rozmiar_x; j++)
        {
            char y;
            fscanf(plik, "%c", &y);
            gra.pionki[i][j] = y - ZERO;
        }
        fscanf(plik, "\n");
    }

    for(int i=0; i < gra.rozmiar_y; i++)
    {
        for(int j=0; j < gra.rozmiar_x; j++)
        {
            char y;
            fscanf(plik, "%c", &y);
            gra.pionki_1[i][j] = y - ZERO;
        }
        fscanf(plik, "\n");
    }

    for(int i=0; i < gra.rozmiar_y; i++)
    {
        for(int j=0; j < gra.rozmiar_x; j++)
        {
            char y;
            fscanf(plik, "%c", &y);
            gra.pionki_2[i][j] = y - ZERO;
        }
        fscanf(plik, "\n");
    }

    char p;

    fscanf(plik, "%c\n%f\n%f", &p, &gra.punkty_biale, &gra.punkty_czarne);

    if(p == 0)
        gra.tura = true;
    else
        gra.tura = false;

    fclose(plik);

    *odczyt_plik = false;
    return gra;
}
