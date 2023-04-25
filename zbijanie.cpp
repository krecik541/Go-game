#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "conio2.h"
#include "funkcje.h"

bool oddechy(stan_gry gra, int y, int x, bool **czyOdwiedzone)
{
    czyOdwiedzone[y][x] = true;

    if((gra.plansza[y - 1][x] != PION && gra.plansza[y - 1][x] != KRAWEDZ_RAMKI) || (gra.plansza[y + 1][x] != PION && gra.plansza[y + 1][x] != KRAWEDZ_RAMKI) || (gra.plansza[y][x - 1] != PION && gra.plansza[y][x - 1] != BOCZNA_KRAWEDZ_RAMKI) || (gra.plansza[y][x + 1] != PION && gra.plansza[y][x + 1] != BOCZNA_KRAWEDZ_RAMKI))
    {
            return true;
    }

    if(gra.plansza[y - 1][x] == PION && gra.pionki[y - 1][x] == gra.tura && czyOdwiedzone[y - 1][x] == false)
    {
        if(oddechy(gra, y - 1, x, czyOdwiedzone))
            return true;
    }

    if(gra.plansza[y + 1][x] == PION && gra.pionki[y + 1][x] == gra.tura && czyOdwiedzone[y + 1][x] == false)
    {
        if(oddechy(gra, y + 1, x, czyOdwiedzone))
            return true;
    }

    if(gra.plansza[y][x - 1] == PION && gra.pionki[y][x - 1] == gra.tura && czyOdwiedzone[y][x - 1] == false)
    {
        if(oddechy(gra, y, x - 1, czyOdwiedzone))
            return true;
    }

    if(gra.plansza[y][x + 1] == PION && gra.pionki[y][x + 1] == gra.tura && czyOdwiedzone[y][x + 1] == false)
    {
        if(oddechy(gra, y, x + 1, czyOdwiedzone))
            return true;
    }
    return false;
}

bool brakoddechy(stan_gry gra, int y, int x, bool **czyOdwiedzone)
{
    czyOdwiedzone[y][x] = true;

    char kolor;
    if(gra.tura)
        kolor = BIALY;
    else
        kolor = CZARNY;

    if(gra.plansza[y - 1][x] != PION && gra.plansza[y - 1][x] != KRAWEDZ_RAMKI)
        return true;
    if(gra.plansza[y + 1][x] != PION && gra.plansza[y + 1][x] != KRAWEDZ_RAMKI)
        return true;
    if(gra.plansza[y][x - 1] != PION && gra.plansza[y][x - 1] != BOCZNA_KRAWEDZ_RAMKI)
        return true;
    if(gra.plansza[y][x + 1] != PION && gra.plansza[y][x + 1] != BOCZNA_KRAWEDZ_RAMKI)
        return true;

    if(gra.plansza[y - 1][x] == PION && gra.pionki[y - 1][x] != kolor && czyOdwiedzone[y - 1][x] == false)
    {
        if(brakoddechy(gra, y - 1, x, czyOdwiedzone))
            return true;
    }
    if(gra.plansza[y + 1][x] == PION && gra.pionki[y + 1][x] != kolor && czyOdwiedzone[y + 1][x] == false)
    {
        if(brakoddechy(gra, y + 1, x, czyOdwiedzone))
            return true;
    }
    if(gra.plansza[y][x - 1] == PION && gra.pionki[y][x - 1] != kolor && czyOdwiedzone[y][x - 1] == false)
    {
        if(brakoddechy(gra, y, x - 1, czyOdwiedzone))
            return true;
    }
    if(gra.plansza[y][x + 1] == PION && gra.pionki[y][x + 1] != kolor && czyOdwiedzone[y][x + 1] == false)
    {
        if(brakoddechy(gra, y, x + 1, czyOdwiedzone))
            return true;
    }

    return false;
}

stan_gry usuwanie(stan_gry gra, bool ** czyOdwiedzone)
{
    float * punkty;
    if(gra.tura)
        punkty = &gra.punkty_biale;
    else
        punkty = &gra.punkty_czarne;



    for(int i = 2; i < gra.rozmiar_y-2; i++)
        if(czyOdwiedzone[1][i])
        {
            (*punkty)++;
            gra.plansza[1][i] = GORNA_KRAWEDZ_PLANSZY;
            gra.pionki[1][i] = 2;
        }

    for(int i = 2; i < gra.rozmiar_y-2; i++)
        if(czyOdwiedzone[gra.rozmiar_x-2][i])
        {
            (*punkty)++;
            gra.plansza[gra.rozmiar_x-2][i] = DOLNA_KRAWEDZ_PLANSZY;
            gra.pionki[gra.rozmiar_x-2][i] = 2;
        }

    for(int i = 2; i < gra.rozmiar_x-2; i++)
        if(czyOdwiedzone[i][1])
        {
            (*punkty)++;
            gra.plansza[i][1] = LEWA_KRAWEDZ_PLANSZY;
            gra.pionki[i][1] = 2;
        }

    for(int i = 2; i < gra.rozmiar_x-2; i++)
        if(czyOdwiedzone[i][gra.rozmiar_y-2])
        {
            (*punkty)++;
            gra.plansza[i][gra.rozmiar_y-2] = PRAWA_KRAWEDZ_PLANSZY;
            gra.pionki[i][gra.rozmiar_y-2] = 2;
        }

    for(int i = 2; i < gra.rozmiar_x-2; i++)
    {
        for(int j = 2; j < gra.rozmiar_y-2; j++)
            if(czyOdwiedzone[i][j])
            {
               (*punkty)++;
               gra.plansza[i][j] = SRODEK_PLANSZY;
               gra.pionki[i][j] = 2;
            }
    }

    if(czyOdwiedzone[1][1])
    {
        (*punkty)++;
        gra.plansza[1][1] = LEWY_GORNY_ROG;
        gra.pionki[1][1] = 2;
    }
    if(czyOdwiedzone[1][gra.rozmiar_y-2])
    {
        (*punkty)++;
        gra.plansza[1][gra.rozmiar_y-2] = PRAWY_GORNY_ROG;
        gra.pionki[1][gra.rozmiar_y-2] = 2;
    }
    if(czyOdwiedzone[gra.rozmiar_x-2][1])
    {
        (*punkty)++;
        gra.plansza[gra.rozmiar_x-2][1] = LEWY_DOLNY_ROG;
        gra.pionki[gra.rozmiar_x-2][1] = 2;
    }
    if(czyOdwiedzone[gra.rozmiar_x-2][gra.rozmiar_y-2])
    {
        (*punkty)++;
        gra.plansza[gra.rozmiar_x-2][gra.rozmiar_y-2] = PRAWY_DOLNY_ROG;
        gra.pionki[gra.rozmiar_x-2][gra.rozmiar_y-2] = 2;
    }
    return gra;
}

stan_gry zabijanie(stan_gry gra, int pozKur_y, int pozKur_x, bool** czyOdwiedzone)
{
    for(int i = 0; i < gra.rozmiar_y; i++)
        for(int j = 0; j < gra.rozmiar_x; j++)
            czyOdwiedzone[i][j] = false;
    if(!brakoddechy(gra, pozKur_y, pozKur_x, czyOdwiedzone))
    {
        gra = usuwanie(gra, czyOdwiedzone);
    }
    return gra;
}

stan_gry ko(stan_gry gra)
{
    bool rownosc = true;
    for(int i = 0; i < gra.rozmiar_y; i++)
    {
        for(int j = 0; j < gra.rozmiar_x; j++)
        {
            if(gra.plansza[i][j] == gra.plansza_2[i][j])
                continue;
            else
            {
                rownosc = false;
                break;
            }
        }
    }
    if(rownosc)
    {
        for(int i = 0; i < gra.rozmiar_y; i++)
        {
            for(int j = 0; j < gra.rozmiar_x; j++)
            {
                gra.plansza[i][j] = gra.plansza_1[i][j];
                gra.pionki[i][j] = gra.pionki_1[i][j];
            }
        }
        gra.tura = (gra.tura+1) % 2;
        if(gra.tura)
            gra.punkty_biale--;
        else
            gra.punkty_czarne--;
    }
    else
    {
        for(int i = 0; i < gra.rozmiar_y; i++)
        {
            for(int j = 0; j < gra.rozmiar_x; j++)
            {
                gra.plansza_2[i][j] = gra.plansza_1[i][j];
                gra.pionki_2[i][j] = gra.pionki_1[i][j];
                gra.plansza_1[i][j] = gra.plansza[i][j];
                gra.pionki_1[i][j] = gra.pionki[i][j];
            }
        }
    }
    return gra;
}

stan_gry kamien(stan_gry gra, int pozKur_y, int pozKur_x)
{
    textbackground(DARKGRAY);
    textcolor(GREEN);
    gotoxy(LEGENDA_X, LEGENDA_Y + 21);
    cputs("ZATWIERDZ ENTER");
    textcolor(WHITE);
    cputs("/");
    textcolor(RED);
    cputs("ANULUJ ESC");

    if(gra.tura == false)
        textcolor(BLACK);
    else
        textcolor(WHITE);

    gotoxy(PLANSZA_X + pozKur_x, PLANSZA_Y + pozKur_y);

    char temp = gra.plansza[pozKur_y][pozKur_x];

    gra.plansza[pozKur_y][pozKur_x] = PION;
    gra.pionki[pozKur_y][pozKur_x] = gra.tura;

    putch(PION);

    while(true)
    {
        textcolor(WHITE);
        char znak = getch();
        if(znak == ENTER)
        {
            bool **czyOdwiedzone = new bool* [gra.rozmiar_y];
            for(int i = 0; i < gra.rozmiar_y; i++)
                czyOdwiedzone[i] = new bool [gra.rozmiar_x];

            if(pozKur_y - 1 > 0 && gra.pionki[pozKur_y - 1][pozKur_x] != gra.tura && gra.pionki[pozKur_y - 1][pozKur_x] != WOLNE_POLE)
                gra = zabijanie(gra, pozKur_y - 1, pozKur_x, czyOdwiedzone);

            if(pozKur_y + 1 < gra.rozmiar_y - 1 && gra.pionki[pozKur_y + 1][pozKur_x] != gra.tura && gra.pionki[pozKur_y + 1][pozKur_x] != WOLNE_POLE)
                gra = zabijanie(gra, pozKur_y + 1, pozKur_x, czyOdwiedzone);

            if(pozKur_x - 1 > 0 && gra.pionki[pozKur_y][pozKur_x - 1] != gra.tura && gra.pionki[pozKur_y][pozKur_x - 1] != WOLNE_POLE)
                gra = zabijanie(gra, pozKur_y, pozKur_x - 1, czyOdwiedzone);

            if(pozKur_x + 1 < gra.rozmiar_x - 1 && gra.pionki[pozKur_y][pozKur_x + 1] != gra.tura && gra.pionki[pozKur_y][pozKur_x + 1] != WOLNE_POLE)
                gra = zabijanie(gra, pozKur_y, pozKur_x + 1, czyOdwiedzone);

            if(!oddechy(gra, pozKur_y, pozKur_x, czyOdwiedzone))
            {
                gra.plansza[pozKur_y][pozKur_x] = temp;
                gra.pionki[pozKur_y][pozKur_x] = true;
                break;
            }

            dealokowanieB(czyOdwiedzone, gra.rozmiar_y, gra.rozmiar_x);
            gra.pionki[pozKur_y][pozKur_x] = gra.tura;
            gra.tura = (gra.tura+1) % 2;
            gra = ko(gra);
            break;
        }
        else if(znak == ESC)
        {
            gra.plansza[pozKur_y][pozKur_x] = temp;
            gra.pionki[pozKur_y][pozKur_x] = true;
            break;
        }
    }

    gotoxy(LEGENDA_X, LEGENDA_Y + 21);
    delline();
    return gra;
}
