#include "tablica_hashujaca.h"

tablica_hashujaca::tablica_hashujaca(){
                for(int k=0;k<30000;k++)
                {
                        poczatki[k]=NULL;
                }
        }


        tablica_hashujaca::~tablica_hashujaca(){
                wez_hash *p,*pom;
                for(int k=0;k<30000;k++)
                {
                        p=poczatki[k];
                        while(p!=NULL)
                        {
                                pom=p;
                                p=p->nastepny;
                                delete pom;

                        }

                }
        }

        void tablica_hashujaca::dodaj(moj_string &wyraz){

                int dl=wyraz.length(),wartosc=0;
                for(int k=0,z=1;k<dl;k++,z*=2)
                {
                        wartosc+=z*wyraz[k];
                }
                wartosc=wartosc%30000;

                wez_hash *p=poczatki[wartosc];
                wez_hash *poprze=NULL;
                while(p!=NULL)
                {
                        poprze=p;
                        p=p->nastepny;
                }
                p= new wez_hash;
                p->klucz=wyraz;
                p->nastepny=NULL;
                p->poprzedni=poprze;
                if(p->poprzedni==NULL)
                        poczatki[wartosc]=p;
                else
                    poprze->nastepny=p;

        }


        bool tablica_hashujaca::czy_jest(moj_string &wyraz){

                int dl=wyraz.length();
                int wartosc=0;
               for(int k=0,z=1;k<dl;k++,z*=2)
                {
                        wartosc+=z*wyraz[k];
                }
                wartosc=wartosc%30000;

                wez_hash *p=poczatki[wartosc];
                while(p!=NULL)
                {
                        if(p->klucz==wyraz)
                                return 1;
                        p=p->nastepny;
                }
                return 0;

        }

        Intiger tablica_hashujaca::podaj_wartosc(moj_string &wyraz)
        {
                Intiger moja_liczba;
                moja_liczba.czy_null=0;
                moja_liczba.wartosc=0;

                int dl=wyraz.length();
                int wartosc=0;
                for(int k=0,z=1;k<dl;k++,z*=2)
                {
                        wartosc+=z*wyraz[k];
                }
                wartosc=wartosc%30000;

                wez_hash *p=poczatki[wartosc];
                while(p!=NULL)
                {
                        if(p->klucz==wyraz)
                                return p->dane;
                        p=p->nastepny;
                }
            return moja_liczba;


        }

        void tablica_hashujaca::zmien_wartosc(moj_string &wyraz,Intiger podana_wartosc)
        {
                int dl=wyraz.length();
                int wartosc=0;
                for(int k=0,z=1;k<dl;k++,z*=2)
                {
                        wartosc+=z*wyraz[k];
                }
                wartosc=wartosc%30000;

                wez_hash *p=poczatki[wartosc];
                while(p!=NULL)
                {
                        if(p->klucz==wyraz)
                                {
                                        p->dane=podana_wartosc;
                                        return;
                                }
                        p=p->nastepny;
                }
                return ;



        }
