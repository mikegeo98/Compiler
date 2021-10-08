#include <bits/stdc++.h>
#define FIRST smt
#define SECOND smt2
#define THIRD smt3

using namespace std;


enum operations{
    FIRST,
    SECOND,
    THIRD
};

istream& operator>>( std::istream& is, operations& i )
{
    int tmp ;
    if ( is >> tmp )
        i = static_cast<operations>( tmp ) ;
    return is ;
}

int main()
{
    while(true)
    {
        operations op;
        cin>>op;
        switch(op)
        {
            case FIRST:
                cout<<"f";
                break;
            case SECOND:
                cout<<"s";
                break;
            case THIRD:
                cout<<"t";
                break;
            default :
                cout<<"not recognized op\n";
                break;
        }
    }
}