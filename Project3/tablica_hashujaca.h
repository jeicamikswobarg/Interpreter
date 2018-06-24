#ifndef TABLICA_HASHUJACA_H
#define TABLICA_HASHUJACA_H
#include "moj_string.h"
#include "struktury.h"


struct wez_hash{
        moj_string klucz;
        Intiger dane;
        wez_hash * poprzedni; wez_hash * nastepny;
};



class tablica_hashujaca{
        public:
                wez_hash *poczatki[30000];
        tablica_hashujaca();
        ~tablica_hashujaca();
        void dodaj(moj_string &wyraz);
        bool czy_jest(moj_string &wyraz);
        Intiger podaj_wartosc(moj_string &wyraz);
        void zmien_wartosc(moj_string &wyraz,Intiger podana_wartosc);

};

#endif // TABLICA_HASHUJACA_H
