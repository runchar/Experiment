#include <iostream>
#include <map>
#include <compare>
#include <algorithm>
#include <cstring>
#include <string>
#include"bitstream.h"
// []  &
// constructor (ULL)


const int N = 500;
using bits_type = BitSet::bits;
//using bits_type = std::bitset<N>;
std::map<std::string, bits_type> M;



void check(){
        try
    {
        BitSet::bits a(3928492, 500);
        std::cout << a << std::endl;
        return;
        std::cout << a << std::endl;
        a.operator<<=(2);
        std::cout << a << std::endl;
        std::cout << a.to_string() << std::endl;
        BitSet::bits aa("11111110", 8, 500, '0', '1');
        std::cout << aa << std::endl;
        aa.operator<<=(2);
        std::cout << aa << std::endl;
        std::cout << aa.to_string() << std::endl;
        std::cout << (aa == a) << std::endl;
        // C++20 says that these are ambiguous, even though the second is reversed:gcc
        // what is this?
        // https://stackoverflow.com/a/60387060/22912407   hard to understanding
        std::cout << (aa != a) << std::endl;
        std::cout << (aa << 1000) << std::endl;
        std::cout << (aa << 5) << std::endl;
        std::cout << (aa >> 5) << std::endl;
        std::cout << (aa | a) << std::endl;
        std::cout << (aa & a) << std::endl;
        std::cout << (aa ^ a) << std::endl;
        std::cout << (~a) << std::endl;
            auto aaaa=~a;
    std::cout << aaaa.count() << std::endl;
        std::cout << "Hello \nthis is a check\n"
                  << std::endl;
    }
    catch (const char *msg)
    {
        std::cerr << "Exception caught: " << msg << std::endl;
    }
}

int main()
{
    // check();
    // return 0;
    freopen("in.txt", "r", stdin);
    std::string op;
    while( std::cin >> op ) {
        // Part 1
        std::string x;
        std::cin >> x;
        if( op == "bitset" ) {
            M[x] = bits_type( );
        }
        if( op == "bitset_s" ) {
            std::string s; char z , o;
            std::cin >> s >> z >> o;
            M[x] = bits_type( s.c_str() , s.length() ,500, z , o );
        }
        if( op == "bitset_u" ) {
            unsigned long long u;
            std::cin >> u;
            M[x] = bits_type( u,500 );
        }
        if( op == "test" ) {
            std::cout << M[x].to_string() << std::endl;
        }
        if( op == "count" ) {
            std::cout << M[x].count( ) << std::endl;
        }
        if( op == "all" ) {
            std::cout << M[x].all( ) << std::endl;
        }
        if( op == "any" ) {
            std::cout << M[x].any( ) << std::endl;
        }
        if( op == "none" ) {
            std::cout << M[x].none( ) << std::endl;
        }
        if( op == "flipall" ) {
            M[x].filp( );
        }
        if( op == "setall" ) {
            M[x].set( );
        }
        if( op == "resetall" ) {
            M[x].reset( );
        }
        if( op == "less" ) {
            std::string y;
            std::cin >> y;
            std::cout << ( x < y ) << std::endl;
        }
        if (op == "ANDS")
        {
            std::string a,b;
            std::cin>>a>>b;
            M[x]=M[a]&M[b];
        }
        if (op == "ORS")
        {
            std::string a,b;
            std::cin>>a>>b;
            M[x]=M[a]|M[b];
        }
        if (op == "XORS")
        {
            std::string a,b;
            std::cin>>a>>b;
            M[x]=M[a]^M[b];
        }
        if(op=="LSS")
        {
            std::string a;
            size_t b;
            std::cin>>a>>b;
            M[x]=M[a]<<b;
        }
        if(op=="RSS")
        {
            std::string a;
            size_t b;
            std::cin>>a>>b;
            M[x]=M[a]>>b;
        }
        if (op == "NOTS")
        {
            std::string a;
            std::cin>>a;
            M[x]=~M[a];
        }
        if(op=="AND")
        {
            std::string a,b;
            std::cin>>b;
            auto temp=M[x]&M[b];
            std::cout<<temp<<std::endl;

        }
        if(op=="OR")
        {
            std::string a,b;
            std::cin>>b;
            auto temp=M[x]|M[b];
            std::cout<<temp<<std::endl;
        }
        if(op=="XOR")
        {
            std::string a,b;
            std::cin>>b;
            auto temp=M[x]^M[b];
            std::cout<<temp<<std::endl;
        }
        if(op=="NOT")
        {
            std::string a;
            auto temp=~M[x];
            std::cout<<temp<<std::endl;
        }
        if(op=="LE")
        {
            std::string a,b;
            std::cin>>b;
            std::cout<<(M[x]<M[b])<<std::endl;
        }
        if(op=="EQ")
        {
            std::string a,b;
            std::cin>>b;
            std::cout<<(M[x]==M[b])<<std::endl;
        }
        if(op=="GR")
        {
            std::string a,b;
            std::cin>>b;
            std::cout<<(M[x]>M[b])<<std::endl;
        }

    }
    return 0;
}