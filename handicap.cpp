#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "conio2.h"
#include "funkcje.h"

stan_gry handicap(stan_gry gra)
{
    int pozKur_x = 1, pozKur_y = 1;
    clrscr();
    gotoxy(MENU_X, MENU_Y);
    cputs("NACISNIJ ENTER JEZELI CHCESZ UZYC HANDICAPA");
    gotoxy(MENU_X, MENU_Y + 1);
    cputs("NACISNIJ ESC JEZELI CHCESZ PRZEJSC DO GRY");
    while(true)
    {
        char znak = getch();
        if(znak == ENTER)
        {
            while(true)
            {
                textbackground(DARKGRAY);
                textcolor(WHITE);

                clrscr();

                handicap_legenda();

                //WYPISUJE PLANSZE
                wypiszPLANSZA(gra.rozmiar_y, gra.rozmiar_x, gra.plansza, gra.pionki);

                //WYPISUJE ZNAK NA KTORYM ZNAJDUJE SIE KURSOR
                textcolor(CYAN);
                textbackground(DARKGRAY);
                gotoxy(PLANSZA_X + pozKur_x, PLANSZA_Y + pozKur_y);
                putch(gra.plansza[pozKur_y][pozKur_x]);

                znak = getch();
                if(znak == 0)
                    strzalki(&pozKur_y, &pozKur_x, gra.rozmiar_y, gra.rozmiar_x);
                else if(znak == 'i' && gra.plansza[pozKur_y][pozKur_x] != PION)
                {
                    gra = kamien(gra, pozKur_y, pozKur_x);
                    gra.tura = (gra.tura+1) % 2;
                }
                else if(znak == 'q')
                    break;
            }
            gra.punkty_biale = 0.5;
            gra.tura = (gra.tura+1) % 2;
            return gra;
        }
        else if(znak == ESC)
            return gra;
    }
    return gra;
}

void handicap_legenda()
{
    gotoxy(LEGENDA_X, LEGENDA_Y);
    cputs("Maciej Szymczak 193456");
    gotoxy(LEGENDA_X, LEGENDA_Y + 1);
    cputs("Zaimplementowane funkcjonalnosci: a, b, c, d, e, f, g, h, j");
    gotoxy(LEGENDA_X, LEGENDA_Y + 2);
    cputs("strzalki - ruch po planszy");
    gotoxy(LEGENDA_X, LEGENDA_Y + 3);
    cputs("q -\t zakoncz handicapa");
    gotoxy(LEGENDA_X, LEGENDA_Y + 4);
    cputs("enter -\t potwierdz wybor");
    gotoxy(LEGENDA_X, LEGENDA_Y + 5);
    cputs("esc -\t anuluj obecna akcje");
    gotoxy(LEGENDA_X, LEGENDA_Y + 6);
    cputs("i -\t ustaw kamien na planszy");
}
