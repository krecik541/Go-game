#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "conio2.h"
#include "funkcje.h"


void rozmiarPlanszy (int *y, int *x, char ** plansza)
{
    _setcursortype(_SOLIDCURSOR);
    rozmiarPlanszyMenu();
    char znak;
    while(true)
    {
        gotoxy(MENU_X, MENU_Y+5);
        znak = getch();
        if(znak == '1' || znak == '2' || znak == '3' || znak == '4')
            break;
        else
            cputs("BLENDNE WEJSCIE");
    }
    gotoxy(MENU_X, MENU_Y+5);
    if(znak == '1')
    {
        *y = 9;
        *x = 9;
    }
    else if(znak == '2')
    {
        *y = 13;
        *x = 13;
    }
    else if(znak == '3')
    {
        *y = 19;
        *x = 19;
    }
    else
    {
        *y = 0;
        *x = 0;
        while(true)
        {
            znak = getche();
            if(znak == ' ')//SPACJA
                break;
            *y = (*y) * 10 + ((int)znak - ZERO);
        }
        cputs("x ");
        while(true)
        {
            znak = getche();
            if((int)znak == ENTER)
                break;
            *x = (*x) * 10 + ((int)znak - ZERO);
        }
    }
    *y += 2;
    *x += 2;
    _setcursortype(_NOCURSOR);
}

void rozmiarPlanszyMenu()
{
    gotoxy(MENU_X, MENU_Y);
    cputs("Wybierz rozmiar planszy (WPISZ NUMER):");
    gotoxy(MENU_X, MENU_Y+1);
    cputs("1) 9x9");
    gotoxy(MENU_X, MENU_Y+2);
    cputs("2) 13x13");
    gotoxy(MENU_X, MENU_Y+3);
    cputs("3) 19x19");
    gotoxy(MENU_X, MENU_Y+4);
    cputs("4) Wybierz swoj rozmiar planszy (liczba SPACJA liczba)");
}

void generacjaPlanszy(int ilosc_wierszy, int ilosc_kolumn, char **plansza, char **pionki)
{
    for(int i = 2; i < ilosc_kolumn-2; i++)
    {
        plansza[1][i] = GORNA_KRAWEDZ_PLANSZY;
        plansza[ilosc_wierszy-2][i] = DOLNA_KRAWEDZ_PLANSZY;
    }

    for(int i = 2; i < ilosc_wierszy-2; i++)
    {
        plansza[i][1] = LEWA_KRAWEDZ_PLANSZY;
        plansza[i][ilosc_kolumn-2] = PRAWA_KRAWEDZ_PLANSZY;
    }

    for(int i = 2; i < ilosc_wierszy-2; i++)
    {
        for(int j = 2; j < ilosc_kolumn-2; j++)
               plansza[i][j] = SRODEK_PLANSZY;
    }

    plansza[1][1] = LEWY_GORNY_ROG;
    plansza[1][ilosc_kolumn-2] = PRAWY_GORNY_ROG;
    plansza[ilosc_wierszy-2][1] = LEWY_DOLNY_ROG;
    plansza[ilosc_wierszy-2][ilosc_kolumn-2] = PRAWY_DOLNY_ROG;

    //RAMKA
    for(int i = 0; i < ilosc_kolumn; i++)
    {
        plansza[0][i] = KRAWEDZ_RAMKI;
        plansza[ilosc_wierszy-1][i] = KRAWEDZ_RAMKI;
    }

    for(int i = 0; i < ilosc_wierszy; i++)
    {
        plansza[i][0] = BOCZNA_KRAWEDZ_RAMKI;
        plansza[i][ilosc_kolumn-1] = BOCZNA_KRAWEDZ_RAMKI;
    }

    plansza[0][0] = LEWY_GORNY_ROG;
    plansza[0][ilosc_kolumn-1] = PRAWY_GORNY_ROG;
    plansza[ilosc_wierszy-1][0] = LEWY_DOLNY_ROG;
    plansza[ilosc_wierszy-1][ilosc_kolumn-1] = PRAWY_DOLNY_ROG;


    for(int i = 0; i < ilosc_wierszy; i++)
        for(int j = 0; j < ilosc_kolumn; j++)
            pionki[i][j] = WOLNE_POLE;
}

stan_gry plansza(stan_gry gra)
{
    //TWORZE PLANSZE
    gra.plansza = planszaAlkoacja(gra.rozmiar_y, gra.rozmiar_x);
    gra.plansza_1 = planszaAlkoacja(gra.rozmiar_y, gra.rozmiar_x);
    gra.plansza_2 = planszaAlkoacja(gra.rozmiar_y, gra.rozmiar_x);
    gra.pionki = planszaAlkoacja(gra.rozmiar_y, gra.rozmiar_x);
    gra.pionki_1 = planszaAlkoacja(gra.rozmiar_y, gra.rozmiar_x);
    gra.pionki_2 = planszaAlkoacja(gra.rozmiar_y, gra.rozmiar_x);

    generacjaPlanszy(gra.rozmiar_y, gra.rozmiar_x, gra.plansza, gra.pionki);
    generacjaPlanszy(gra.rozmiar_y, gra.rozmiar_x, gra.plansza_1, gra.pionki_1);
    generacjaPlanszy(gra.rozmiar_y, gra.rozmiar_x, gra.plansza_2, gra.pionki_2);

    return gra;
}

stan_gry tworzeniePlanszy(char znak, stan_gry gra)
{
    //POBIERAM ROZMIAR PLANSZY
    if(znak == 'n' || znak == 'f')
        rozmiarPlanszy(&gra.rozmiar_y, &gra.rozmiar_x, gra.plansza);

    gra = plansza(gra);

    gra = handicap(gra);

    wypiszPLANSZA(gra.rozmiar_y, gra.rozmiar_x, gra.plansza, gra.pionki);

    return gra;
}

void legenda(bool tura, float punkty_czarne, float punkty_biale, int poz_x, int poz_y)
{
    gotoxy(LEGENDA_X, LEGENDA_Y);
    cputs("Maciej Szymczak 193456");
    gotoxy(LEGENDA_X, LEGENDA_Y + 1);
    cputs("Zaimplementowane funkcjonalnosci: a, b, c, d, e, f, g, h, j, k");
    gotoxy(LEGENDA_X, LEGENDA_Y + 2);
    cputs("strzalki - ruch po planszy");
    gotoxy(LEGENDA_X, LEGENDA_Y + 3);
    cputs("q -\t zakoncz program");
    gotoxy(LEGENDA_X, LEGENDA_Y + 4);
    cputs("n -\t rozpocznij nowa gre");
    gotoxy(LEGENDA_X, LEGENDA_Y + 5);
    cputs("enter -\t potwierdz wybor i zakoncz ture gracza");
    gotoxy(LEGENDA_X, LEGENDA_Y + 6);
    cputs("esc -\t anuluj obecna akcje");
    gotoxy(LEGENDA_X, LEGENDA_Y + 7);
    cputs("i -\t ustaw kamien na planszy");
    gotoxy(LEGENDA_X, LEGENDA_Y + 8);
    cputs("s -\t zapisz stan gry");
    gotoxy(LEGENDA_X, LEGENDA_Y + 9);
    cputs("l -\t wczytaj stan gry");
    gotoxy(LEGENDA_X, LEGENDA_Y + 10);
    cputs("f -\t zakoncz gre\n");

    gotoxy(LEGENDA_X, LEGENDA_Y + 12);
    cputs("Pozycja kursora: ");
    wINT(poz_y);
    cputs(" x ");
    wINT(poz_x);

    gotoxy(LEGENDA_X, LEGENDA_Y + 14);
    cputs("Tura: ");
    if(!tura)
    {
        cputs("CZARNE");
    }
    else
    {
        cputs("BIALE");
    }

    gotoxy(LEGENDA_X, LEGENDA_Y + 16);
    cputs("Wyniki:");
    gotoxy(LEGENDA_X, LEGENDA_Y + 17);
    cputs("CZARNE: ");
    wypiszFLOAT(punkty_czarne);
    gotoxy(LEGENDA_X, LEGENDA_Y + 18);
    cputs("BIALE: ");
    wypiszFLOAT(punkty_biale);

    return;
}

void wypiszPLANSZA(int ilosc_wierszy, int ilosc_kolumn, char **plansza, char **pionki)
{
    gotoxy(PLANSZA_X, PLANSZA_Y);
    for(int i = 0; i < ilosc_wierszy; i++)
    {
        gotoxy(PLANSZA_X, PLANSZA_Y+i);
        for(int j=0; j<ilosc_kolumn; j++)
            if(pionki[i][j])
            {
                textcolor(WHITE);
                putch(plansza[i][j]);
            }
            else
            {
                textcolor(BLACK);
                putch(plansza[i][j]);
            }
    }
}

void poczatek(stan_gry gra, int pozKur_y, int pozKur_x)
{
    textbackground(DARKGRAY);
    textcolor(WHITE);

    //CZYSZCZE KONSOLE
    clrscr();

    //WYPISUJE LEGENDE
    legenda(gra.tura, gra.punkty_czarne, gra.punkty_biale, pozKur_x, pozKur_y);

    //WYPISUJE PLANSZE
    wypiszPLANSZA(gra.rozmiar_y, gra.rozmiar_x, gra.plansza, gra.pionki);

    //WYPISUJE ZNAK NA KTORYM ZNAJDUJE SIE KURSOR
    textcolor(CYAN);
    textbackground(DARKGRAY);
    gotoxy(PLANSZA_X + pozKur_x, PLANSZA_Y + pozKur_y);
    putch(gra.plansza[pozKur_y][pozKur_x]);
}
