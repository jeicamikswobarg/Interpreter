#ifndef MOJ_STRING_H
#define MOJ_STRING_H
#include<iostream>

using namespace std;

class moj_string
{

    public:
        char tekst[10];int dl;
        moj_string();
        moj_string(const char*x);
        int length();
         moj_string  & operator =( moj_string const & x);
         moj_string & operator =( const char * x);
         moj_string & operator =( moj_string & x);
         moj_string operator +( char z);
         char & operator []( int index);
         friend ostream & operator <<(ostream & strumien_wy, const moj_string & mstring);
         void clear();
         bool operator ==( const char * x);
         bool operator ==( moj_string & x);
        bool operator <( moj_string const & x);
    protected:

    private:
};

    bool operator <( moj_string const & x,moj_string const & y);
#endif // MOJ_STRING_H
