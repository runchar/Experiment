#include <bits/stdc++.h>
#include <compare> // Include the <compare> header to access the 'strong_ordering' type
#include <iostream>
#include <map>
#include "bitstream.h"

const int N = 500;
// using bits_type = std::bitset<500>;
using bits_type = std::bitset<N>;
std::map<std::string, bits_type> M;


// int main()
// {
//     // freopen("test_output.txt", "w", stdout);
//     std::bitset<500> a(127);
//     std::cout << a << std::endl;             // Output: 00101010
//     a.operator<<=(2);                        // Shift left by 2
//     std::cout << a << std::endl;             // Output: 168
//                                              //    ; // Output: 10101000
//     std::cout << a.to_string() << std::endl; // Output: 10101000
//     std::bitset<500> aa("11111110", 8, '0', '1');
//     std::cout << aa << std::endl;
//     aa.operator<<=(2);
//     std::cout << aa << std::endl;
//     std::cout << aa.to_string() << std::endl;
//     std::cout << (aa == a) << std::endl;
//     std::cout << (aa != a) << std::endl;
//     std::cout << (aa << 1000) << std::endl;
//     std::cout << (aa << 5) << std::endl;
//     std::cout << (aa >> 5) << std::endl;
//     std::cout << (aa | a) << std::endl;
//     std::cout << (aa & a) << std::endl;
//     std::cout << (aa ^ a) << std::endl;
//     std::cout << (~a) << std::endl;
//     auto aaaa=~a;
//     std::cout << aaaa.count() << std::endl;
int main()
{
    // check();
    freopen("in.txt", "r", stdin);
    // std::cout<<"hello"<<std::endl;
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
            M[x] = bits_type( s.c_str() , s.length() , z , o );
        }
        if( op == "bitset_u" ) {
            unsigned long long u;
            std::cin >> u;
            M[x] = bits_type( u );
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
            M[x].flip( );
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
            int b;
            std::cin>>a>>b;
            M[x]=M[a]<<b;
        }
        if(op=="RSS")
        {
            std::string a;
            int b;
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
        if(op=="LESS")
        {
            std::string a,b;
            std::cin>>b;
            std::cout<<(M[x].to_string()<M[b].to_string())<<std::endl;
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
            std::cout<<(M[x].to_string()>M[b].to_string())<<std::endl;
        }
    }
    return 0;
}