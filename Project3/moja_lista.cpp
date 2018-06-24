#include "moja_lista.h"

moja_lista::moja_lista()
{
        size=0;poczatek=NULL;koniec=NULL;
}

wezel * moja_lista::begin()
{
        return poczatek;
}

wezel  *moja_lista::end()
{
        return koniec;
}

bool moja_lista::empty()
{
        if(size==0)
                return true;
        return false;
}

void moja_lista::push_back(czynnik w)
{
        size++;
        if(size==1)
        {
                poczatek=new wezel;koniec=new wezel;
                koniec->wartosc.czy_liczba=0;koniec->wartosc.czy_operacja=0;koniec->wartosc.czy_zmienna=0;
                poczatek->wartosc=w;
                poczatek->poprzedni=NULL;
                poczatek->nastepny=koniec;
                koniec->poprzedni=poczatek;
                koniec->nastepny=NULL;
        }
        else
        {

                wezel *nowy=new wezel;
                koniec->wartosc=w;
                koniec->nastepny=nowy;
                nowy->poprzedni=koniec;
                nowy->nastepny=NULL;
                koniec=nowy;
                 koniec->wartosc.czy_liczba=0;koniec->wartosc.czy_operacja=0;koniec->wartosc.czy_zmienna=0;

        }

}

void moja_lista::erase(wezel *w){
        size--;
        wezel * pom;wezel * nast;wezel * poprz;
        poprz=w->poprzedni;
        nast=w->nastepny;
        if(poprz==NULL)
        {
                nast->poprzedni=NULL;
                this->poczatek=nast;
                delete w;
        }
        else
        {
                poprz->nastepny=nast;
                nast->poprzedni=poprz;
                delete w;
        }
}


void moja_lista::clear(){
    wezel *pocz;
        while(this->empty()==false)
        {
           pocz=this->begin();
                erase(pocz);
        }
        delete koniec;
        size=0;poczatek=NULL;koniec=NULL;
}

moja_lista::~moja_lista(){
    this->clear();
}


