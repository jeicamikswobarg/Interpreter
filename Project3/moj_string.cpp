#include "moj_string.h"

moj_string::moj_string()
{
    dl=0;
    for(int k=0;k<10;k++)
        tekst[k]=0;
}

int moj_string::length(){
    for(int k=0;k<10;k++)
        if(tekst[k]==0)
            return k;
    return 0;

}

 moj_string& moj_string::operator =( moj_string const & x)
        {
            this->clear();
                dl=x.dl;
                for(int k=0;k<dl;k++)
                    tekst[k]=x.tekst[k];
                return *this;
        }

moj_string & moj_string:: operator =( moj_string & x){
    this->clear();
                dl=x.dl;
                for(int k=0;k<dl;k++)
                    tekst[k]=x.tekst[k];
                return *this;

}

moj_string moj_string::operator +( char z)
        {
           moj_string h;
           h.dl=this->dl;
           for(int k=0;k<dl;k++)
           	h.tekst[k]=this->tekst[k];
           	h.dl+=1;
           	h[dl]=z;
           	return h;
        }

char& moj_string::operator []( int index)
{

    return tekst[index];
}

ostream & operator <<(ostream &strumien_wy, const moj_string& mstring){
    strumien_wy<<mstring.tekst;
    return strumien_wy;

}

moj_string &moj_string::operator =( const char * x){
    int dlug;
    for(int k=0;;k++)
        if(x[k]==0)
        {
            dlug=k;
            break;
        }
    for(int k=0;k<=dlug;k++)
        tekst[k]=x[k];
    dl=dlug;
    return *this;
}

bool moj_string::operator ==( const char * x){
    int dlug;
    for(int k=0;;k++)
        if(x[k]==0)
        {
            dlug=k;
            break;
        }
        if(dlug!=dl)
            return false;
    for(int k=0;k<=dlug;k++)
        if(tekst[k]!=x[k])
            return false;
    return true;
}
bool moj_string::operator ==( moj_string & x){
    int dlug=x.length();

        if(dlug!=dl)
            return false;

    for(int k=0;k<dlug;k++)
        if(tekst[k]!=x[k])
            return false;
    return true;
}

moj_string::moj_string(const char*x){
    int dlug;
    for(int k=0;;k++)
        if(x[k]==0)
        {
            dlug=k;
            break;
        }
    for(int k=0;k<=dlug;k++)
        tekst[k]=x[k];
    dl=dlug;

}

bool moj_string::operator <( moj_string const & x){
    int dl1=dl,dl2=x.dl,dl3;
    if(dl1<dl2)
        dl3=dl1;
    else
        dl3=dl2;

    for(int k=0;k<dl3;k++)
    {
        if(this->tekst[k]<x.tekst[k])
            return 1;
        if(this->tekst[k]>x.tekst[k])
            return 0;
    }
    if(dl1<dl2)
        return 1;
    return 0;

}

void moj_string::clear(){
    for(int k=0;k<dl;k++)
            tekst[k]=0;
            dl=0;

}


