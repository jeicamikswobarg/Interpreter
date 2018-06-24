#pragma once
#include<iostream>   //zamienic na <string>
#include<cmath>
#include<map>
#include "moja_lista.h"
#include "moj_string.h"
#include "tablica_hashujaca.h"

bool operator <( moj_string const & x,moj_string const & y){
    int dl1=x.dl,dl2=y.dl,dl3;
    if(dl1<dl2)
        dl3=dl1;
    else
        dl3=dl2;

    for(int k=0;k<dl3;k++)
    {
        if(x.tekst[k]<y.tekst[k])
            return 1;
        if(x.tekst[k]>y.tekst[k])
            return 0;
    }
    if(dl1<dl2)
        return 1;
    return 0;

}

int strlen(char *tekst)
{
   for(int k=0;;k++)
    {
        if(tekst[k]==0)
            return k;
    }
}

//usunac stringa, zrobic drzewo, liste
//using namespace std;

struct do_funkcji{wezel *p;wezel *k;};

moja_lista lista_czynnikow;
int priorytet[100000];
tablica_hashujaca zmienne;
moj_string pom;
czynnik pom_czynnik;
Intiger pusty;
 //0 - nie ma nic , 1 - jest znak, 2 - jest liczba, 3 - jest zmienna , 4 - nawias poczatek  5- nawias koniec  6- nowalinia
int pom_int=0;
int moj_licznik=0,instrukcje_max;

void wstepne_przetworzenie(slowo &moj_tekst){
        for(int k=moj_tekst.poczatek;k<=moj_tekst.koniec;k++)
        {
                if((moj_tekst.tekst[k]>='A'&&moj_tekst.tekst[k]<='Z')||(moj_tekst.tekst[k]>='a'&&moj_tekst.tekst[k]<='z'))
                        moj_tekst.co_jest[k]=3;
                else
                {
                        if(moj_tekst.tekst[k]>='0'&&moj_tekst.tekst[k]<='9')
                                moj_tekst.co_jest[k]=2;
                        else
                        {
                                if(moj_tekst.tekst[k]==' ')
                                        moj_tekst.co_jest[k]=0;
                                else
                                {
                                    if(moj_tekst.tekst[k]=='(')
                                        moj_tekst.co_jest[k]=4; //pocz nawiasu
                                    else
                                    {
                                        if(moj_tekst.tekst[k]==')') //koniec nawiasu
                                            moj_tekst.co_jest[k]=5;
                                        else
                                        {
                                            if(moj_tekst.tekst[k]!='#'&&moj_tekst.tekst[k]!='{'&&moj_tekst.tekst[k]!='}')
                                                moj_tekst.co_jest[k]=1;
                                            else
                                                moj_tekst.co_jest[k]=0;
                                        }
                                    }
                                }
                        }
                }
        }
}



int hashuj(moj_string l)
{

  int dl=l.length(),wynik=0;
  for(int k=dl-1,podstawa=1;k>=0;k--,podstawa*=200)
    {
        wynik+=l.tekst[k]*podstawa;
    }
    return wynik;
}


void srodkowe_przetworzenie(slowo &moj_tekst){
        for(int k=moj_tekst.poczatek;k<=moj_tekst.koniec;k++)
        {
                if(moj_tekst.tekst[k]=='+'||moj_tekst.tekst[k]=='-')
                {
                                if((k==moj_tekst.poczatek||moj_tekst.co_jest[k-1]==1)&&moj_tekst.co_jest[k+1]==2)
                                        moj_tekst.co_jest[k]=moj_tekst.co_jest[k+1];
                }
        }
}





Intiger zamien_ze_stringa_na_liczbe(char *linijka,int poczatek,int koniec){
        int liczba=0;
        bool znak=0;
        if(linijka[poczatek]=='-')
            {znak=1;poczatek+=1;
            }

        for(int k=koniec,podstawa=1;k>=poczatek;k--,podstawa*=10)
        {
                liczba+=int(linijka[k]-48)*podstawa;
        }
        Intiger p;
        p.czy_null=0;
        p.wartosc=liczba;
        if(znak==1)
        p.wartosc*=-1;
        return p;
}

void znajdz_zmienna(char *linijka,int poczatek,int koniec,czynnik &czynn){
        moj_string zmienna;

        for(int k=poczatek;k<=koniec;k++)
        {
                zmienna=zmienna+linijka[k];
        }
        czynn.zmienna=zmienna;
}

void usun_spacje(char *tekst)
{
   int dl=strlen(tekst),j=0;
   char pomocniczy[100000];
   pomocniczy[0]=tekst[0];
 //  pomoczniczy[dl]=tekst[dl];
   for(int k=1;k<dl-1;k++)
   {
     if(tekst[k]>32)
     {  j++;
        pomocniczy[j]=tekst[k];
     }
     else
     {
        if(pomocniczy[j]>32)
        {
            j++;
            pomocniczy[j]=tekst[k];

        }

     }

   }
    j++;
    pomocniczy[j]=tekst[dl];

    for(int k=0;k<=j;k++)
        tekst[k]=pomocniczy[k];

}



void usun_doszczetnie_spacje(char *tekst)
{
   int dl=strlen(tekst),j=0;
   char pomocniczy[100000];
   pomocniczy[0]=tekst[0];
 //  pomoczniczy[dl]=tekst[dl];
   for(int k=1;k<dl-1;k++)
   {
     if(tekst[k]>32)
     {  j++;
        pomocniczy[j]=tekst[k];
     }
   }
    j++;
    pomocniczy[j]=tekst[dl];

    for(int k=0;k<=j;k++)
        tekst[k]=pomocniczy[k];

}


void przetworz_na_liste(slowo &moj_tekst){

        for(int k=moj_tekst.poczatek;k<=moj_tekst.koniec;k++)
        {
                if(moj_tekst.co_jest[k]==1)
                {
                        pom.clear();
                        while(moj_tekst.co_jest[k]==1)
                        {
                                pom=pom+moj_tekst.tekst[k];
                                k++;
                        }
                        if((pom.length()>=2 && (pom[1]=='!'||pom[1]=='+'||pom[1]=='-'))||(pom.length()>2))
                        {
                            k-=(pom.length()-1);
                            pom.clear();
                            pom=pom+moj_tekst.tekst[k-1];
                        }
                        pom_czynnik.czy_liczba=0;pom_czynnik.czy_operacja=1;pom_czynnik.czy_zmienna=0;
                        pom_czynnik.operacja=pom;
                        lista_czynnikow.push_back(pom_czynnik);
                        pom.clear();
                        k--;   //moze nie dzialac

                }
                if(moj_tekst.co_jest[k]==3)
                {
                        //przypadek Nul
                        pom_int=k;
                        while(moj_tekst.co_jest[pom_int]==3)
                        {
                                pom_int++;
                        }
                        pom_int--;
                        pom_czynnik.czy_liczba=0;pom_czynnik.czy_operacja=0;pom_czynnik.czy_zmienna=1;
                        znajdz_zmienna(moj_tekst.tekst,k,pom_int,pom_czynnik);
                        pusty.wartosc=0;pusty.czy_null=1;
                        if(zmienne.czy_jest(pom_czynnik.zmienna)==0)
                        {
                            zmienne.dodaj(pom_czynnik.zmienna);
                            zmienne.zmien_wartosc(pom_czynnik.zmienna,pusty);
                        }
                        lista_czynnikow.push_back(pom_czynnik);
                        k=pom_int;


                }
                if(moj_tekst.co_jest[k]==2)
                {
                        pom_int=k;
                        while(moj_tekst.co_jest[pom_int]==2)
                        {
                                pom_int++;
                        }
                        pom_int--;
                        pom_czynnik.czy_liczba=1;pom_czynnik.czy_operacja=0;pom_czynnik.czy_zmienna=0;
                        pom_czynnik.liczba=zamien_ze_stringa_na_liczbe(moj_tekst.tekst,k,pom_int);
                        lista_czynnikow.push_back(pom_czynnik);
                        k=pom_int;  //moze nie dzialac
                }
                if(moj_tekst.co_jest[k]==4)
                {
                   pom_czynnik.czy_liczba=0;pom_czynnik.czy_operacja=1;pom_czynnik.czy_zmienna=0;
                   pom_czynnik.operacja="(";
                    lista_czynnikow.push_back(pom_czynnik);

                }
                 if(moj_tekst.co_jest[k]==5)
                {
                    pom_czynnik.czy_liczba=0;pom_czynnik.czy_operacja=1;pom_czynnik.czy_zmienna=0;
                   pom_czynnik.operacja=")";
                    lista_czynnikow.push_back(pom_czynnik);

                }
        }
}





void wykasuj(wezel * it)
{
        (*it).wartosc.czy_liczba=0;
        (*it).wartosc.czy_operacja=0;
        (*it).wartosc.czy_zmienna=0;

}

void sklej(char *linijka,char *pomoc,int &pocz,int dl)
{
    for(int k=pocz,j=0;k<pocz+dl;k++,j++)
                linijka[k]=pomoc[j];
        linijka[pocz+dl]=' ';
        pocz+=dl+1;
}

void zrob_przerwe_pomiedzy_zmiennymi(char *linijka){
    int dl=strlen(linijka);
    bool pr1=0,pr2=0;
    for(int k=0;k<dl;k++)
    {
        if(k!=0&&k!=dl-1)
        {
            pr1=pr2=0;
            if((linijka[k-1]>='a'&&linijka[k-1]<='z')||(linijka[k-1]>='A'&&linijka[k-1]<='Z')||linijka[k-1]==')'||linijka[k-1]=='}')
                pr1=1;
            if((linijka[k+1]>='a'&&linijka[k+1]<='z')||(linijka[k+1]>='A'&&linijka[k+1]<='Z')||linijka[k+1]=='('||linijka[k+1]=='@'||linijka[k+1]=='?')
                pr2=1;
            if(linijka[k-1]>='0'&&linijka[k-1]<='9')
                pr1=1;
            if(linijka[k+1]>='0'&&linijka[k+1]<='9')
                pr2=1;

                if(pr1&&pr2&&linijka[k]==' ')
                    linijka[k]='#';
        }
    }

}

int szukaj_konca(int poczatek,char *tekst)
{
    int dl;
    dl=strlen(tekst);
    for(int k=poczatek;k<dl;k++)
    {
        if(tekst[k]=='#')
                return k-1;
    }
    return strlen(tekst)-1;
}


//operacje

void operacja_przypisania(wezel * it)
{
    moj_licznik+=1;
        wezel* poprzedni,*nastepny;
        nastepny=poprzedni=it;
       nastepny=nastepny->next();poprzedni=poprzedni->back();
        if((*poprzedni).wartosc.czy_zmienna==1)
        {

                if((*nastepny).wartosc.czy_zmienna==1)
                {
                        zmienne.zmien_wartosc((*poprzedni).wartosc.zmienna,zmienne.podaj_wartosc((*nastepny).wartosc.zmienna));
                       // zmienne[(*poprzedni).wartosc.zmienna]=zmienne[(*nastepny).wartosc.zmienna];
                }
                else //a=5;
                {
                        zmienne.zmien_wartosc((*poprzedni).wartosc.zmienna,(*nastepny).wartosc.liczba);
                        //zmienne[(*poprzedni).wartosc.zmienna]=(*nastepny).wartosc.liczba;
                }
        }
        wykasuj(it);
        (*it).wartosc.czy_zmienna=1;
        (*it).wartosc.zmienna=(*poprzedni).wartosc.zmienna;

        lista_czynnikow.erase(nastepny);
        lista_czynnikow.erase(poprzedni);
}

void operacja_alternatywa(wezel * it)
{
    moj_licznik+=1;
       wezel * poprzedni, *nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if((lewa.czy_null==0)||(prawa.czy_null==0))
        {
                (*it).wartosc.liczba.czy_null=0;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);

}



void operacja_koniunkcja(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,* nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*poprzedni).wartosc.czy_liczba=1;
        if((lewa.czy_null==0)&&(prawa.czy_null==0))
        {
                (*it).wartosc.liczba.czy_null=0;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}






void operacja_negacja(wezel * it)
{
        moj_licznik+=1;
        wezel * nastepny;
        nastepny=it;
        nastepny=nastepny->next();
        Intiger prawa;

        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(prawa.czy_null==1)
        {
                (*it).wartosc.liczba.wartosc=0;
                (*it).wartosc.liczba.czy_null=0;
        }
        else
        {
                (*it).wartosc.liczba.wartosc=0;
                (*it).wartosc.liczba.czy_null=1;
        }
        lista_czynnikow.erase(nastepny);
}


void operacja_plus(wezel * it)
{
        moj_licznik+=1;
        wezel * nastepny;
        nastepny=it;
        nastepny=nastepny->next();
        Intiger prawa;

        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(prawa.czy_null==1)
        {
                (*it).wartosc.liczba.wartosc=0;
                (*it).wartosc.liczba.czy_null=1;
        }
        else
        {
                (*it).wartosc.liczba.wartosc=prawa.wartosc;
                (*it).wartosc.liczba.czy_null=0;
        }
        lista_czynnikow.erase(nastepny);
}

void operacja_minus(wezel* it)
{
        moj_licznik+=1;
        wezel* nastepny;
        nastepny=it;
        nastepny=nastepny->next();
        Intiger prawa;

        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(prawa.czy_null==1)
        {
                (*it).wartosc.liczba.wartosc=0;
                (*it).wartosc.liczba.czy_null=1;
        }
        else
        {
                (*it).wartosc.liczba.wartosc=prawa.wartosc*(-1);
                (*it).wartosc.liczba.czy_null=0;
        }
        lista_czynnikow.erase(nastepny);
}




void operacja_rozne(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                if(lewa.wartosc!=prawa.wartosc)
                {
                        (*it).wartosc.liczba.czy_null=0;
                        (*it).wartosc.liczba.wartosc=0;
                }
                else
                {
                        (*it).wartosc.liczba.czy_null=1;
                        (*it).wartosc.liczba.wartosc=0;
                }
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}


void operacja_rowne(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                if(lewa.wartosc==prawa.wartosc)
                {
                        (*it).wartosc.liczba.czy_null=0;
                        (*it).wartosc.liczba.wartosc=0;
                }
                else
                {
                        (*it).wartosc.liczba.czy_null=1;
                        (*it).wartosc.liczba.wartosc=0;
                }
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}


void operacja_mniejsze(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                if(lewa.wartosc<prawa.wartosc)
                {
                        (*it).wartosc.liczba.czy_null=0;
                        (*it).wartosc.liczba.wartosc=0;

                }
                else
                {
                        (*it).wartosc.liczba.czy_null=1;
                        (*it).wartosc.liczba.wartosc=0;
                }
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}


void operacja_wieksze(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                if(lewa.wartosc>prawa.wartosc)
                {
                        (*it).wartosc.liczba.czy_null=0;
                        (*it).wartosc.liczba.wartosc=0;
                }
                else
                {
                        (*it).wartosc.liczba.czy_null=1;
                        (*it).wartosc.liczba.wartosc=0;
                }
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}

void operacja_mniejszerowne(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                if(lewa.wartosc<=prawa.wartosc)
                {
                        (*it).wartosc.liczba.czy_null=0;
                        (*it).wartosc.liczba.wartosc=0;
                }
                else
                {
                        (*it).wartosc.liczba.czy_null=1;
                        (*it).wartosc.liczba.wartosc=0;
                }
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}


void operacja_wiekszerowne(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                if(lewa.wartosc>=prawa.wartosc)
                {
                        (*it).wartosc.liczba.czy_null=0;
                        (*it).wartosc.liczba.wartosc=0;
                }
                else
                {
                        (*it).wartosc.liczba.czy_null=1;
                        (*it).wartosc.liczba.wartosc=0;
                }
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}

void operacja_suma(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                (*it).wartosc.liczba.czy_null=0;
                (*it).wartosc.liczba.wartosc=lewa.wartosc+prawa.wartosc;
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}

void operacja_roznica(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni, *nastepny;
        nastepny=poprzedni=it;
       nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                (*it).wartosc.liczba.czy_null=0;
                (*it).wartosc.liczba.wartosc=lewa.wartosc-prawa.wartosc;
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}

void operacja_dzielenie(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1||prawa.wartosc==0)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                (*it).wartosc.liczba.czy_null=0;
                (*it).wartosc.liczba.wartosc=lewa.wartosc/prawa.wartosc;
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}

void operacja_mnozenie(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni,*nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                (*it).wartosc.liczba.czy_null=0;
                (*it).wartosc.liczba.wartosc=lewa.wartosc*prawa.wartosc;
        }
                lista_czynnikow.erase(poprzedni);
                lista_czynnikow.erase(nastepny);
}

void operacja_modulo(wezel * it)
{
        moj_licznik+=1;
        wezel * poprzedni, *nastepny;
        nastepny=poprzedni=it;
        nastepny=nastepny->next();poprzedni=poprzedni->back();
        Intiger lewa,prawa;
        if((*poprzedni).wartosc.czy_zmienna==1)
                lewa=zmienne.podaj_wartosc((*poprzedni).wartosc.zmienna);
        else
                lewa=(*poprzedni).wartosc.liczba;
        if((*nastepny).wartosc.czy_zmienna==1)
                prawa=zmienne.podaj_wartosc((*nastepny).wartosc.zmienna);
        else
                prawa=(*nastepny).wartosc.liczba;

        wykasuj(it);
        (*it).wartosc.czy_liczba=1;
        if(lewa.czy_null==1||prawa.czy_null==1)
        {
                (*it).wartosc.liczba.czy_null=1;
                (*it).wartosc.liczba.wartosc=0;
        }
        else
        {
                (*it).wartosc.liczba.czy_null=0;
                (*it).wartosc.liczba.wartosc=lewa.wartosc%prawa.wartosc;
        }
        lista_czynnikow.erase(poprzedni);
        lista_czynnikow.erase(nastepny);
}




void zrob_operacje(wezel * it)
{
        moj_string operacja =(*it).wartosc.operacja;

        if(operacja=="=")
        {
                operacja_przypisania(it);return;
        }
        if(operacja=="|")
        {
                operacja_alternatywa(it);return;
        }
        if(operacja=="&")
        {
                operacja_koniunkcja(it);return;
        }
        if(operacja=="!=")
        {
                operacja_rozne(it);return;
        }
        if(operacja=="==")
        {
                operacja_rowne(it);return;
        }
        if(operacja=="<")
        {
                operacja_mniejsze(it);return;
        }
        if(operacja==">")
        {
                operacja_wieksze(it);return;
        }
        if(operacja=="<=")
        {
                operacja_mniejszerowne(it);return;
        }
        if(operacja==">=")
        {
                operacja_wiekszerowne(it);return;
        }
        if(operacja=="+")
        {
                operacja_suma(it);return;
        }
        if(operacja=="-")
        {
                operacja_roznica(it);   return;
        }
        if(operacja=="/")
        {
                        operacja_dzielenie(it);return;
        }
        if(operacja=="*")
        {
                operacja_mnozenie(it);return;
        }
        if(operacja=="%")
        {
                operacja_modulo(it);return;
        }
        if(operacja=="!")
        {
                operacja_negacja(it);return;
        }
}


slowo znajdz_warunek(slowo &podstawa)
{
        int pocz,kon,pom=0;
        slowo t;
        for(int k=podstawa.poczatek;k<=podstawa.koniec;k++)
        {
                if(podstawa.tekst[k]=='(')
                    {
                        if(pom==0)
                            pocz=k+1;
                        pom+=1;
                    }
                if(podstawa.tekst[k]==')')
                {
                    pom-=1;
                    if(pom==0)
                    {
                        kon=k-1;
                        break;
                    }
                }
        }
        t.tekst=podstawa.tekst;
        t.co_jest=podstawa.co_jest;
        t.poczatek=pocz;
        t.koniec=kon;
        return t;

}

slowo znajdz_kod(slowo &podstawa)
{
        int pocz,kon,pom=0;
        slowo t;
        for(int k=podstawa.poczatek;k<=podstawa.koniec;k++)
        {
                if(podstawa.tekst[k]=='{')
                    {
                        if(pom==0)
                            pocz=k+1;
                        pom+=1;
                    }
                if(podstawa.tekst[k]=='}')
                {
                    pom-=1;
                    if(pom==0)
                    {
                        kon=k-1;
                        break;
                    }
                }
        }
        t.tekst=podstawa.tekst;
        t.co_jest=podstawa.co_jest;
        t.poczatek=pocz;
        t.koniec=kon;
        return t;
}


do_funkcji szukaj_nawiasow()
{
    do_funkcji cos;
    cos.k=NULL;
    cos.p=NULL;
    if(lista_czynnikow.empty()==0)
    for(wezel * it=lista_czynnikow.begin();it!=lista_czynnikow.end();it=it->next())
    {
        if((*it).wartosc.czy_operacja==1&&(*it).wartosc.operacja=="(")
        {
            cos.p=it;
        }
        if((*it).wartosc.czy_operacja==1&&(*it).wartosc.operacja==")")
        {
            cos.k=it;
            return cos;
        }

    }
    return cos;
}



bool przetworz_linijke(slowo &moj_tekst){
    if(moj_licznik==instrukcje_max)
        return false;

    lista_czynnikow.clear();
    bool b=0;
    do_funkcji f;
    wezel * nawias_poczatek, *nawias_koniec,*pom,*pom_u1,*pom_u2;
    wezel pocz1,kon1;
        wstepne_przetworzenie(moj_tekst);
        srodkowe_przetworzenie(moj_tekst);
        przetworz_na_liste(moj_tekst);

        while(true)
        {
            f=szukaj_nawiasow();
            if(f.k!=NULL)
            {
                nawias_poczatek=f.p;
                nawias_koniec=f.k;
                if(lista_czynnikow.empty()==false)
                {
                    pom=nawias_koniec;
                    pom=pom->back();
                    for(wezel* it=pom;;it=it->back())
                    {
                        if((*it).wartosc.czy_operacja==1)
                        {
                            if(it->wartosc.operacja=="(")
                            {
                                break;
                            }
                            if(priorytet[hashuj((*it).wartosc.operacja)]==7)
                            {
                                zrob_operacje(it);
                                if(moj_licznik==instrukcje_max)
                                                return false;
                            }
                            else{
                                    pom_u1=pom_u2=it;
                                    pom_u1=pom_u1->back();pom_u2=pom_u2->next();
                                if((*it).wartosc.operacja=="+"&&(*pom_u1).wartosc.czy_operacja==1&&((*pom_u2).wartosc.czy_zmienna==1||(*pom_u2).wartosc.czy_liczba==1))
                                    operacja_plus(it);
                                else
                                {
                                   if((*it).wartosc.operacja=="-"&&(*pom_u1).wartosc.czy_operacja==1&&((*pom_u2).wartosc.czy_zmienna==1||(*pom_u2).wartosc.czy_liczba==1))
                                    operacja_minus(it);
                                }
                            }
                        }

                    }
                }
                for(int k=6;k>0;k--)
                {
                        pom=nawias_poczatek;;
                        for(wezel * it=pom;(*it)!=*(nawias_koniec);it=it->next())
                        {
                                if((*it).wartosc.czy_operacja==1)
                                {
                                        if((*it).wartosc.operacja==")")
                                        break;
                                        if(priorytet[hashuj((*it).wartosc.operacja)]==k)
                                        {
                                                zrob_operacje(it);
                                                if(moj_licznik==instrukcje_max)
                                                return false;
                                        }


                                }
                        }
                }
                if(lista_czynnikow.empty()==false)
                {
                    pom=nawias_koniec;
                    pom=pom->back();
                    for(wezel * it=pom;;it=it->back())
                    {

                        if((*it).wartosc.czy_operacja==1)
                        {
                           if(it->wartosc.operacja=="(")
                                break;

                            if(priorytet[hashuj((*it).wartosc.operacja)]==0)
                            {

                                zrob_operacje(it);
                                if(moj_licznik==instrukcje_max)
                                                return false;
                            }
                        }

                    }
                };
                lista_czynnikow.erase(nawias_koniec->nastepny->poprzedni);
                lista_czynnikow.erase(nawias_poczatek->nastepny->poprzedni);
            }
            else
            {
                if(lista_czynnikow.empty()==false)
                for(wezel * it=(lista_czynnikow.end());;it=it->back())//moze nie dzialac
                {
                    if((*it).wartosc.czy_operacja==1)
                    {
                        if(priorytet[hashuj((*it).wartosc.operacja)]==7)
                        {


                            zrob_operacje(it);
                            if(moj_licznik==instrukcje_max)
                                                return false;
                        }
                        else
                        {
                             pom_u1=pom_u2=it;
                                    pom_u1=pom_u1->back();pom_u2=pom_u2->next();
                                if((*it).wartosc.operacja=="+"&&(*pom_u1).wartosc.czy_operacja==1&&((*pom_u2).wartosc.czy_zmienna==1||(*pom_u2).wartosc.czy_liczba==1))
                                    operacja_plus(it);
                                else
                                {
                                   if((*it).wartosc.operacja=="-"&&(*pom_u1).wartosc.czy_operacja==1&&((*pom_u2).wartosc.czy_zmienna==1||(*pom_u2).wartosc.czy_liczba==1))
                                    operacja_minus(it);
                                }
                        }
                    }
                    if(it==lista_czynnikow.begin())
                        break;

                }
                if(lista_czynnikow.empty()==false)
                for(int k=6;k>0;k--)
                {
                        for(wezel * it=lista_czynnikow.begin();it!=lista_czynnikow.end();it=it->next())
                        {
                                if((*it).wartosc.czy_operacja==1)
                                {
                                        if(priorytet[hashuj((*it).wartosc.operacja)]==k)
                                        {

                                                zrob_operacje(it);
                                                if(moj_licznik==instrukcje_max)
                                                return false;
                                        }
                                }
                        }
                }
                if(lista_czynnikow.empty()==false)
                for(wezel* it=lista_czynnikow.end();;it=it->back())//moze nie dzialac
                {
                    if((*it).wartosc.czy_operacja==1)
                    {
                        if(priorytet[hashuj((*it).wartosc.operacja)]==0)
                        {

                            zrob_operacje(it);
                            if(moj_licznik==instrukcje_max)
                                                return false;
                        }
                    }
                    if(it==lista_czynnikow.begin())
                        break;

                }
                break;
            }
        }

        if(lista_czynnikow.empty()==false)
        {
        wezel * it=lista_czynnikow.begin();
        Intiger l;
        if((*it).wartosc.czy_zmienna==1)
                l=zmienne.podaj_wartosc((*it).wartosc.zmienna);
        else
                l=(*it).wartosc.liczba;



        if(l.czy_null==0)
                return true;
        else
                return false;
        }
        return false;

}


void zadecyduj(slowo &moj_tekst)
{
    if(moj_licznik==instrukcje_max)
        return;


        while(moj_tekst.tekst[moj_tekst.poczatek]<=32||moj_tekst.tekst[moj_tekst.poczatek]=='#')
            moj_tekst.poczatek+=1;
        slowo warunek,kod,pom;
        pom.co_jest=moj_tekst.co_jest;
        pom.tekst=moj_tekst.tekst;
        pom.koniec=moj_tekst.koniec;
        pom.poczatek=moj_tekst.poczatek;
        int pom_pocz;
        bool co;
        lista_czynnikow.clear();
        if(moj_tekst.tekst[moj_tekst.poczatek]=='?')
        {
                warunek=znajdz_warunek(moj_tekst);
                kod=znajdz_kod(moj_tekst);
                co=przetworz_linijke(warunek);
                if(moj_licznik==instrukcje_max)
                    return ;
                moj_licznik+=1;
                if(moj_licznik==instrukcje_max)
                                return;
                if(co==true)
                {
                     zadecyduj(kod);

                }
                pom.poczatek=kod.koniec+1;
                zadecyduj(pom);
        }
        else
        {
                if(moj_tekst.tekst[moj_tekst.poczatek]=='@')
                {
                        warunek=znajdz_warunek(moj_tekst);
                        kod=znajdz_kod(moj_tekst);
                        while(true)
                        {
                            co=przetworz_linijke(warunek);
                            if(moj_licznik==instrukcje_max)
                                return ;
                            moj_licznik+=1;
                            if(moj_licznik==instrukcje_max)
                                return;
                            if(co==false)
                                break;
                            else
                            {
                                    zadecyduj(kod);
                                    lista_czynnikow.clear();
                            }
                        }
                        pom.poczatek=kod.koniec+1;
                        zadecyduj(pom);
                }
                else
                {
                       pom.poczatek=moj_tekst.poczatek;
                        pom.co_jest=moj_tekst.co_jest;
                        pom.tekst=moj_tekst.tekst;
                        pom.koniec=szukaj_konca(pom.poczatek,moj_tekst.tekst);
                        if(pom.poczatek<=pom.koniec&&pom.poczatek<=moj_tekst.koniec)
                            przetworz_linijke(pom);
                        if(moj_licznik==instrukcje_max)
                            return ;
                        pom.poczatek=pom.koniec+2;
                        pom.koniec=moj_tekst.koniec;
                                if(pom.poczatek<=pom.koniec)
                                {
                                    zadecyduj(pom);
                                }

                }


        }

}


void wypisz_wyniki_zmiennych(char *wypisywane_zmienne){
    pom.clear();
    int dl=strlen(wypisywane_zmienne);
    for(int k=0;k<dl;k++)
    {
        if(wypisywane_zmienne[k]>32)
        {

        while(wypisywane_zmienne[k]>32)
        {
            pom=pom+wypisywane_zmienne[k];
            k++;
        }
        cout<<pom<<" ";
        if(zmienne.czy_jest(pom)==0)
            cout<<"Nul"<<endl;
        else
        {
            if(zmienne.podaj_wartosc(pom).czy_null==0)
                cout<<zmienne.podaj_wartosc(pom).wartosc<<endl;
            else
                cout<<"Nul"<<endl;
        }

            pom.clear();
        }

    }


}



int main(){
    ios_base::sync_with_stdio(0);
pusty.wartosc=0;pusty.czy_null=1;


        priorytet[hashuj(moj_string("="))]=0;
        priorytet[hashuj(moj_string("|"))]=1;
        priorytet[hashuj(moj_string("&"))]=2;
        priorytet[hashuj(moj_string("!="))]=3;
        priorytet[hashuj(moj_string("=="))]=3;
        priorytet[hashuj(moj_string("<"))]=4;
        priorytet[hashuj(moj_string(">"))]=4;
        priorytet[hashuj(moj_string("<="))]=4;
        priorytet[hashuj(moj_string(">="))]=4;
        priorytet[hashuj(moj_string("+"))]=5;
        priorytet[hashuj(moj_string("-"))]=5;
        priorytet[hashuj(moj_string("/"))]=6;
        priorytet[hashuj(moj_string("*"))]=6;
        priorytet[hashuj(moj_string("%"))]=6;
        priorytet[hashuj(moj_string("!"))]=7;

//zmienne["a"]=pusty;
      //  zmienne["b"]=pusty;

      //  zmienne["c"]=pusty;

char linijka[100000],pomoc[2000],wypisywane_zmienne[2000];
int co_jest[100000];
int dl,pocz=0,pom=0;
int ileLini;
slowo moj_tekst;
for(int k=0;k<2000;k++)
pomoc[k]=wypisywane_zmienne[k]=0;
for(int k=0;k<100000;k++)
linijka[k]=co_jest[k]=0;


cin>>instrukcje_max;cin.get();
cin.getline(wypisywane_zmienne,2000);
cin >> ileLini;
cin.get();


		for(int k=0;k<ileLini;k++)
        {
			cin.getline(pomoc, 2000);
            dl=strlen(pomoc);
            sklej(linijka,pomoc,pocz,dl);



        }

            dl=strlen(linijka);
            linijka[dl]='#';
            linijka[dl+1]=0;
            usun_spacje(linijka);
            zrob_przerwe_pomiedzy_zmiennymi(linijka);
            usun_doszczetnie_spacje(linijka);


                moj_tekst.poczatek=0;
                moj_tekst.koniec=strlen(linijka)-1;
                moj_tekst.tekst=linijka;
                moj_tekst.co_jest=co_jest;
                zadecyduj(moj_tekst);
                cout<<moj_licznik<<endl;
                wypisz_wyniki_zmiennych(wypisywane_zmienne);




        return 0;
}
