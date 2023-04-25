#include <stdio.h>
#include <malloc.h>
#include "conio2.h"
#include "funkcje.h"

using namespace std;

int main()
{
    settitle("Maciej Szymczak 193456");
    _setcursortype(_NOCURSOR);

    char znak = 'n';
    bool odczyt_plik = false;
    int pozKur_x = 0, pozKur_y = 0;
    stan_gry gra;

    do
    {
        pozKur_x = 1;
        pozKur_y = 1;
        gra.punkty_biale = 0;
        gra.punkty_czarne = 0;
        gra.tura = 0;

        if(znak != 'l')
            gra = tworzeniePlanszy(znak, gra);

        do
        {
            poczatek(gra, pozKur_y, pozKur_x);

            if(odczyt_plik)
            {
                gotoxy(LEGENDA_X, LEGENDA_Y + 20);
                cputs("NIE MOZNA ODCZYTAC PLIK O PODANEJ NAZWIE");
                odczyt_plik = false;
            }

            znak = getch();

            if(znak == 0)
                strzalki(&pozKur_y, &pozKur_x, gra.rozmiar_y, gra.rozmiar_x);
            else
            {
                if(znak == 'i' && gra.plansza[pozKur_y][pozKur_x] != PION)
                {
                    gra = kamien(gra, pozKur_y, pozKur_x);
                }
                else if(znak == 's')
                {
                    zapisywanie(gra);
                }
                else if(znak == 'l')
                {
                    gra = odczyt(gra, &odczyt_plik);
                }
                else if(znak == 'f')
                {
                    break;
                }
            }
        }
        while(znak != 'n' && znak != 'q' && znak != 'f');
        dealokowanieC(gra.plansza, gra.rozmiar_y, gra.rozmiar_x);
        dealokowanieC(gra.plansza_1, gra.rozmiar_y, gra.rozmiar_x);
        dealokowanieC(gra.plansza_2, gra.rozmiar_y, gra.rozmiar_x);
        dealokowanieC(gra.pionki, gra.rozmiar_y, gra.rozmiar_x);
        dealokowanieC(gra.pionki_1, gra.rozmiar_y, gra.rozmiar_x);
        dealokowanieC(gra.pionki_2, gra.rozmiar_y, gra.rozmiar_x);
        textbackground(DARKGRAY);
        textcolor(WHITE);
        clrscr();
    }
    while(znak != 'q');


    return 0;
}
