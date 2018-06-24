#ifndef STRUKTURY_H
#define STRUKTURY_H
#include"moj_string.h"




struct Intiger{
        int wartosc;bool czy_null;
        Intiger operator =( Intiger const & x)
        {
                wartosc=x.wartosc;
                czy_null=x.czy_null;
                return *this;
        }
};

struct slowo{
        int poczatek;int koniec;char *tekst;int *co_jest;

};


struct czynnik{
    bool czy_operacja;bool czy_liczba; bool czy_zmienna;
    moj_string operacja;Intiger liczba; moj_string zmienna;
     czynnik& operator =( czynnik const & x)
        {
                czy_operacja=x.czy_operacja;
                czy_liczba=x.czy_liczba;
                czy_zmienna=x.czy_zmienna;
                operacja=x.operacja;
                liczba=x.liczba;
                zmienna=x.zmienna;
                return *this;
        }


};

struct wezel{
        czynnik wartosc; wezel * nastepny; wezel *poprzedni;

        wezel & operator++(){
                this->wartosc=nastepny->wartosc;
                this->poprzedni=nastepny->poprzedni;
                this->nastepny=nastepny->nastepny;
                return *(this);
        }
        wezel & operator--(){
                this->wartosc=poprzedni->wartosc;
                this->nastepny=poprzedni->nastepny;
                this->poprzedni=poprzedni->poprzedni;
                return *(this);
        }

        bool operator != (wezel &w)
        {
                if(this->nastepny!=NULL&&w.nastepny!=NULL)
                {
                        if(this->nastepny==w.nastepny)
                                return 0;
                }
                if(this->poprzedni!=NULL&&w.poprzedni!=NULL)
                {
                        if(this->poprzedni==w.poprzedni)
                                return 0;
                }
                return 1;
        }
         bool operator == (wezel w)
        {
                if(this->nastepny!=NULL&&w.nastepny!=NULL)
                {
                        if(this->nastepny==w.nastepny)
                                return 1;
                }
                if(this->poprzedni!=NULL&&w.poprzedni!=NULL)
                {
                        if(this->poprzedni==w.poprzedni)
                                return 1;
                }
                if(this->nastepny==NULL&&w.nastepny==NULL)
                {
                                return 1;
                }
                if(this->poprzedni==NULL&&w.poprzedni==NULL)
                {
                                return 1;
                }
                return 0;
        }
        wezel * next()
        {
            return this->nastepny;

        }
        wezel * back()
        {
            return this->poprzedni;

        }

};

#endif // STRUKTURY_H
