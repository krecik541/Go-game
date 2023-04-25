#pragma once
#define PLANSZA_X 55//X-OWA WSPOLRZEDNA LEWEGO GORENGO ROGU PLANSZY
#define PLANSZA_Y 5//Y-OWA WSPOLRZEDNA LEWEGO GORENGO ROGU PLANSZY

#define MENU_X 10//X-OWA WSPOLRZEDNA LEWEGO GORENGO ROGU WYBORU WIELKOSCI
#define MENU_Y 10//Y-OWA WSPOLRZEDNA LEWEGO GORENGO ROGU WYBORU WIELKOSCI

#define wINT wypiszINT//Y-OWA WSPOLRZEDNA LEWEGO GORENGO ROGU WYBORU WIELKOSCI

#define LEGENDA_X 1//X-OWA WSPOLRZEDNA LEWEGO GORENGO ROGU LEGENDY
#define LEGENDA_Y 1//Y-OWA WSPOLRZEDNA LEWEGO GORENGO ROGU LEGENDY

#define PION -8//ZNAK ASCII PIONKA
#define ENTER 13//ZNAK ASCII ENTER
#define ESC 27//ZNAK ASCII ESC
#define LEWY_GORNY_ROG -38//ZNAK ASCII LEWEGO GORNEGO ROGU PLANSZY
#define PRAWY_GORNY_ROG -65//ZNAK ASCII PRAWEGO GORNEGO ROGU PLANSZY
#define LEWY_DOLNY_ROG -64//ZNAK ASCII LEWEGO DOLNEGO ROGU PLANSZY
#define PRAWY_DOLNY_ROG -39//ZNAK ASCII DOLNEGO GORNEGO ROGU PLANSZY
#define SRODEK_PLANSZY -59//ZNAK ASCII SRODKA PLANSZY
#define LEWA_KRAWEDZ_PLANSZY -61//ZNAK ASCII PRAWEJ KRAWEDZI PLANSZY
#define PRAWA_KRAWEDZ_PLANSZY -76//ZNAK ASCII LEWEJ KRAWEDZI PLANSZY
#define DOLNA_KRAWEDZ_PLANSZY -63//ZNAK ASCII DOLNEJ KRAWEDZI PLANSZY
#define GORNA_KRAWEDZ_PLANSZY -62//ZNAK ASCII GORNEJ KRAWEDZI PLANSZY
#define KRAWEDZ_RAMKI -60//ZNAK ASCII GORNEJ/DOLNEJ KRAWEDZI RAMKI PLANSZY
#define BOCZNA_KRAWEDZ_RAMKI -77//ZNAK ASCII BOCZNEJ KRAWEDZI RAMKI PLANSZY

#define ST_GORA 72//STRZALKA W GORE
#define ST_DOL 80//STRZALKA W DOL
#define ST_LEWO 75//STRZALKA W LEWO
#define ST_PRAWO 77//STRZALKA W PRAWO

#define ZERO 48//ZNAK ASCII 0

#define WOLNE_POLE 2//POLE NIEZAJETE PRZEZ KAMIENIE
#define BIALY 1//POLE ZAJETE PRZEZ KAMIENIE BIALE
#define CZARNY 0//POLE ZAJETE PRZEZ KAMIENIE CZARNE

struct stan_gry{
    int rozmiar_x, rozmiar_y;//ROZMIAR PLANSZY
    char **plansza;
    char **plansza_1;
    char **plansza_2;
    char **pionki;//0 - CZARNE, 1 - BIALE, 2 - PUSTE POLE
    char **pionki_1;
    char **pionki_2;
    bool tura;//0 - CZARNE, 1 - BIALE
    float punkty_biale, punkty_czarne;//PUNKTY
};

//POBIERA OD GRACZA ROZMIAR PLANSZY
void rozmiarPlanszy (int *where_x, int *where_y, char ** plansza);
//WYPISUJE MENU DO WYBORU ROZMIARU
void rozmiarPlanszyMenu();
//WYPELNIA TABLICE ODPOWIEDNIMI ZNAKAMI ASCII
void generacjaPlanszy(int ilosc_wierszy, int ilosc_kolumn, char **plansza, char **pionki);
//TWORZY I WYPELNIA PLANSZE
stan_gry plansza(stan_gry gra);
//OBSLUGUJE CALY MODUL TWORZENIA PLANSZY DO GRY
stan_gry tworzeniePlanszy(char znak, stan_gry gra);
//WYPISUJE LEGENDE
void legenda(bool tura, float punkty_czarne, float punkty_biale, int poz_x, int poz_y);
//WYPISUJE PLANSZE
void wypiszPLANSZA(int ilosc_wierszy, int ilosc_kolumn, char  **plansza, char **pionki);
//WYPISUJE LEGENDE, PLANSZE I PODSWIETLA POZYCJE KURSORA (ZAWIERA DWIE POWYZSZE FUNKCJE)
void poczatek(stan_gry gra, int pozKur_y, int pozKur_x);

//WYPISUJE INTA
void wypiszINT(int z);
//WYPISUJE FLOATA
void wypiszFLOAT(float z);

//ZAPISUJE STAN GRY DO PLIKU
void zapisywanie(stan_gry gra);
//ODCZYTUJE STAN GRY Z PLIKU
stan_gry odczyt(stan_gry gra, bool*odczyt_plik);

//SPRAWDZA, CZY POSTAWIONY KAMIEN BEDZIE MIAL ODDECHY(NIE BEDZIE POPELNIAL SAMOBOJSTWA)
bool oddechy(stan_gry gra, int pozKur_y, int pozKur_x, bool **czyOdwiedzone);
//TWORZY TABLICE POZYCJI KAMIENI, KTORE ZOSTALY ZABITE
bool brakoddechy(stan_gry gra, int y, int x, bool **czyOdwiedzone);
//USUWA ZABITE KAMIENIE Z TABLICY
stan_gry usuwanie(stan_gry gra, bool ** czyOdwiedzone);
//SPRAWDZA, CZY DANY KAMIEN ZOSTAL ZABITY I W RAZIE POTRZEBY USUWA GO (ZAWIERA DWIE POWYZSZE FUNKCJE)
stan_gry zabijanie(stan_gry gra, int pozKur_y, int pozKur_x, bool** czyOdwiedzone);
//ODPOWIADA ZA DZIALANIE ZASADY KO
stan_gry ko(stan_gry gra);
//OBSLUGUJE CALY MODUL STAWIANIA KAMIENI (ZA POMOCA POWYZSZYCH FUNKCJI)
stan_gry kamien(stan_gry gra, int pozKur_y, int pozKur_x);

//RUCH STRZALKAMI
void strzalki(int *pozKur_y, int *pozKur_x, int rozmiar_y, int rozmiar_x);


//ALOKUJE PAMIEC DLA PLANSZY O PODANYCH ROZMIARACH
char** planszaAlkoacja(int rozmiar_y, int rozmiar_x);
//ZWALNIA PAMIEC TABLICY BOOLI
void dealokowanieB(bool **t, int y, int x);
//ZWALNIA PAMIEC TABLICY CHAROW
void dealokowanieC(char **t, int y, int x);

//DZIALANIE HANDICAPA
stan_gry handicap(stan_gry gra);
//WYPISUJE MENU HANDICAPA
void handicap_legenda();
