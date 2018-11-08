#include <stdio.h>
#include <stdbool.h>

char Plansza[8][8] = {

    {'-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-'},
    {'-','-','-','B','C','-','-','-'},
    {'-','-','-','C','B','-','-','-'},
    {'-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-'},
    {'-','-','-','-','-','-','-','-'},
};

int Ruchy[][8] = {
    {0, -1, -1, -1, 0, 1, 1, 1}, // przesunięcia o wektor wzdłuż osi OX danego pola
    {1, 1, 0, -1, -1, -1, 0, 1} // przesunięcia o wektor wzdłuż osi OY danego pola
};

int optKolumna, optWiersz; // zmienne przechowujące optymalny ruch gracza białego

// Funkcja sprawdzająca, czy wczytane dane są w zakresie planszy. Zwraca 1 jeśli tak i 0 jeśli nie.
int CzyWZakresie(int kolumna, int wiersz) {

    return kolumna > -1 && kolumna < 8 && wiersz > -1 && wiersz < 8;
}

// Funkcja sprawdzająca, czy wczytany ruch białych (kolor = 0) albo czarnych (kolor = 1) jest legalny.
// Jeśli jest legalny zwraca liczbę pionków, które odwróci dany ruch. W przeciwnym wypadku zwraca 0.
// Jeśli czyZamienic = 1 to funkcja wykonuje ruch odwracając odpowiednie pionki.

int CzyLegalny(int kolumna, int wiersz, int kolor, int czyZamienic) {
    char Kolory[] = {'C','B'};
    int przesunietaKolumna;
    int przesunietyWiersz;
    int ileZamieni = 0; // Ile pionków zamieni dany ruch jeśli jest legalny.

    if (Plansza[wiersz][kolumna] == '-') { // Zakładam, że wpisany ruch jest w poprawnej formie (jest w zakresie planszy).
        for (int i = 0;i < 8; i++) { // Sprawdzamy wszystkie sąsiednie pola wczytanego do funkcji.

            przesunietaKolumna = kolumna + Ruchy[0][i]; // Przesunięcie współrzędnej kolumny na jedno z sąsiadujących pól.
            przesunietyWiersz = wiersz + Ruchy[1][i]; // Przesunięcie współrzędnej wiersza na jedno z sśsiadujścych pól.

            if (CzyWZakresie(przesunietaKolumna, przesunietyWiersz) &&
                Plansza[przesunietyWiersz][przesunietaKolumna] == Kolory[kolor]) {
                while (CzyWZakresie(przesunietaKolumna, przesunietyWiersz)
                    && Plansza[przesunietyWiersz][przesunietaKolumna] == Kolory[kolor]) {

                    przesunietaKolumna+=Ruchy[0][i];
                    przesunietyWiersz+=Ruchy[1][i];
                }

                if (CzyWZakresie(przesunietaKolumna, przesunietyWiersz)
                && Plansza[przesunietyWiersz][przesunietaKolumna] == Kolory[1 - kolor]) {
                    int kolumnaKopia = kolumna;
                    int wierszKopia = wiersz;

                    while (kolumnaKopia != przesunietaKolumna || wierszKopia != przesunietyWiersz) {

                        // Wykonuje się tylko jeśli funkcja ma od razu zamienić pionki poprzez wykonanie ruchu.
                        if(czyZamienic == 1)
                            Plansza[wierszKopia][kolumnaKopia]=Kolory[1-kolor];
                        kolumnaKopia += Ruchy[0][i];
                        wierszKopia += Ruchy[1][i];
                        if(kolumnaKopia != przesunietaKolumna || wierszKopia != przesunietyWiersz)
                            ileZamieni++;
                    }
                }
            }
        }
    }
    return ileZamieni;
}

// Funkcja sprawdzająca, czy biały (kolor = 0), albo czarny (kolor = 1) może wykonać jakiś legalny ruch.
 int czyJestLegalny(int kolor) {

     for(int wiersz=0;wiersz<8;wiersz++)
     {
        for(int kolumna=0;kolumna<8;kolumna++)
        {
             if(CzyLegalny(kolumna,wiersz,kolor,0))
                return 1;
        }
     }
    return 0;
}

void wypisz() { // Funkcja wypisująca planszę.
    for (int wiersz = 0; wiersz < 8; wiersz++) {
        for (int kolumna = 0; kolumna < 8; kolumna++) {
            int a = '1' + wiersz;
            putchar(Plansza[wiersz][kolumna]);
            if (kolumna == 7) {
                putchar(a);
                putchar('\n');
            }
        }
    }
    for (int i = 'a'; i < 'i'; i++) {
        putchar(i);
    }
    putchar('\n');
}

void optruch() { // Funkcja przypisująca zmiennym optKolumna i optWiersz wartości dla optymalnego ruchu białych

    int maks = 0;
    for (int wiersz = 0; wiersz < 8; wiersz++) {
        for (int kolumna = 0; kolumna < 8; kolumna++) {
            if (CzyLegalny(kolumna, wiersz, 0, 0) > maks) {
                maks = CzyLegalny(kolumna, wiersz, 0, 0);
                optKolumna = kolumna;
                optWiersz = wiersz;
            }
        }
    }
}

int ocena() { // Funkcja obliczająca ocenę planszy.

    int ile = 0;
    for (int wiersz = 0; wiersz < 8; wiersz++) {
        for (int kolumna = 0; kolumna < 8; kolumna++) {
            if (Plansza[wiersz][kolumna] == 'C') {
                ile++;
            }
            if (Plansza[wiersz][kolumna] =='B') {
                ile--;
            }
        }
    }
    return ile;
}

void zlyRuch() { // Wypisuje nieprawidłowy ruch.
    printf("? %d\n", ocena());
    wypisz();
}

int main() {

    bool gra = true;
    char Znaki[] = {'a','b','c','d','e','f','g','h'};
    wypisz();
    while(gra) { // Główna pętla gry.
        int znak = getchar();
        if (znak == EOF) { // Pętla kończy się kiedy dojdziemy do końca danych.
            gra = false;
        }
        else
        {
            if (znak == '\n') { // Pusty wiersz jest nieprawidłowy.
                zlyRuch();
            }
            else {
                if(znak == '=') {
                    int kolejnyznak = getchar();
                    if (kolejnyznak != '\n') { // Jeśli po '=' nie ma znaku końca linii to ruch jest niepoprawny.
                        while (kolejnyznak != '\n')
                            kolejnyznak = getchar();
                        zlyRuch();
                    }
                    else {
                        if (czyJestLegalny(0)) { // Sprawdzamy czy biały może wykonać legalny ruch.

                            optruch(); // Znajduje optymalny ruch dla gracza białego.

                            if (CzyLegalny(optKolumna, optWiersz, 0, 0)) {
                                // Wykonanie ruchu Białych po rezygnacji z ruchu przez gracza Czarnego.
                                CzyLegalny(optKolumna, optWiersz, 0, 1);
                                char kol = Znaki[optKolumna]; // Zamiana liczby na znak odpowiadający danej kolumnie.
                                printf("%c %c%d %d\n", '=', kol, optWiersz + 1, ocena());
                                wypisz();
                            }
                            else {
                                zlyRuch();
                            }
                        }
                        else {
                            printf("= = %d\n", ocena()); // Jeśli gracz Biały nie może wykonać ruchu to musi z niego zrezygnować.
                            wypisz();
                        }
                    }
                }
                else {
                    if (znak - 'a' > -1 && znak - 'a' < 8) { // Sprawdzamy, czy pierwszy znak jest odpowiednią literą.

                        int kolejnyznak = getchar();
                        if (kolejnyznak - '1' > -1 && kolejnyznak - '1' < 8) { // Kolejny znak musi być odpowiednią liczbą

                            char kolumna = znak;
                            char wiersz = kolejnyznak;
                            kolejnyznak = getchar();
                            if (kolejnyznak == '\n') {
                                // Ruch poprawny czarnego musi byc również legalny.
                                if (CzyLegalny(kolumna - 'a', wiersz - '1', 1, 0)) {
                                    CzyLegalny(kolumna - 'a', wiersz - '1', 1, 1); // Ruch gracza Czarnego.
                                    optruch();
                                    if (CzyLegalny(optKolumna, optWiersz, 0, 1)) {
                                        CzyLegalny(optKolumna, optWiersz, 0, 1);
                                        char kol = Znaki[optKolumna];
                                        printf("%c%c %c%d %d\n", kolumna, wiersz, kol, optWiersz + 1, ocena());
                                        wypisz();
                                    }
                                    else {
                                        // Jeśli gracz Biały nie może wykonać ruchu.
                                        printf("%c%c %c %d\n", kolumna, wiersz, '=', ocena());
                                        wypisz();
                                    }
                                }
                                else {
                                    zlyRuch();
                                }
                            }
                            else {
                                while (kolejnyznak != '\n') { // Wczytujemy kolejne znaki aż natrafimy na koniec linii.
                                    kolejnyznak = getchar();
                                }
                                zlyRuch();
                            }
                        }
                        else {
                            while (kolejnyznak != '\n') // Wczytujemy kolejne znaki az natrafimy na koniec linii.
                                kolejnyznak=getchar();
                            zlyRuch();
                        }
                    }
                    else {
                        int kolejnyznak = getchar(); // Wczytujemy kolejne znaki az natrafimy na koniec linii.
                        while (kolejnyznak != '\n')
                            kolejnyznak = getchar();
                        zlyRuch();
                    }
                }
            }
        }
    }

    return 0;
}
