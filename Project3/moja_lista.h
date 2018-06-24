#ifndef MOJA_LISTA_H
#define MOJA_LISTA_H
#include "struktury.h"



class moja_lista{
        public:
        int size;//begin,size,end,push_back,erase,empty
        wezel *poczatek;wezel *koniec;
        moja_lista();
        ~moja_lista();
        wezel * begin();
        wezel * end();
        bool empty();
        void push_back(czynnik w);
        void erase(wezel *w);
        void clear();

};


#endif // MOJA_LISTA_H
