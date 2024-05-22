#include <iostream>
#include <map>
#include <compare>
#include <algorithm>
#include <cstring>
#include <string>
#include "bitstream.h"
// []  &
// constructor (ULL)

#include <compare>
#include <algorithm>

const int N = 6;
using bits_type = BitSet::bits<N>;
// using bits_type = std::bitset<N>;
std::map<std::string, bits_type> M;

void check()
{
    try
    {
        BitSet::bits<N> a(2);
        std::cout << a << std::endl;

        // a[2]=a[1]=a[0]=true;
        for (int i = 0; i <= 499; i++)
            a[i] = 1;
        std::cout << a << std::endl;
        for (int i = 0; i <= 456; i += 5)
            a[i] = ~a[i];
        std::cout << a << std::endl;
        // return;
        // std::cout << a << std::endl;
        // a.operator<<=(2);
        // std::cout << a << std::endl;
        // std::cout << a.to_string() << std::endl;
        // BitSet::bits <500> aa("11111110", 8, '0', '1');
        // std::cout << aa << std::endl;
        // aa.operator<<=(2);
        // std::cout << aa << std::endl;
        // std::cout << aa.to_string() << std::endl;
        // std::cout << (aa == a) << std::endl;
        // // C++20 says that these are ambiguous, even though the second is reversed:gcc
        // // what is this?
        // // https://stackoverflow.com/a/60387060/22912407   hard to understanding
        // std::cout << (aa != a) << std::endl;
        // std::cout << (aa << 1000) << std::endl;
        // std::cout << (aa << 5) << std::endl;
        // std::cout << (aa >> 5) << std::endl;
        // std::cout << (aa | a) << std::endl;
        // std::cout << (aa & a) << std::endl;
        // std::cout << (aa ^ a) << std::endl;
        // std::cout << (~a) << std::endl;
        //     auto aaaa=~a;
        // std::cout << aaaa.count() << std::endl;
        // std::cout << "Hello \nthis is a check\n"<< std::endl;
        auto it=a.begin();
        std::cout<<static_cast<bool>(*it)<<std::endl;
        for(int i=0;i<100;i++)
        {
            BitSet::bit_iterator<bits_type, true> cit=it;
            std::cout<<static_cast<bool>(*it)<<static_cast<bool>(*cit)<<std::endl;
            ++it;
            if(i%10==0)
            {
                std::cout<<std::endl;
                --it;
            }
        }
        std::cout<<std::endl;
        for(int i=0;i<100;i++)
        {
            std::cout<<static_cast<bool>(a[i]);
        }
        // const auto ca=a;
        // auto cit=ca.begin();
        // std::cout<<static_cast<bool>(*cit)<<std::endl;
        // const BitSet::bits<500> ca(2);
        // auto cit=ca.begin();
        // std::cout<<static_cast<bool>(*cit)<<std::endl;
        //std::cout<<std::ptrdiff_t <<std::endl;
        std::cout<<std::endl<<"--------------------"<<std::endl;

        BitSet::bits<50> b1(0);
        BitSet::bits<20> b2(0);
        auto it_begin=b1.begin();
        auto it_plus=1+it_begin;
        for(auto it=b1.begin();it!=b1.end();it++)
        {
            std::cout<<(int)(it-it_begin)<<" >:  "<<(bool)(it>it_begin)<<" <:  "<<(bool)(it<it_begin)<<" =:  "<<(bool)(it==(it_begin+1))<<std::endl;
            if(((int)(it-it_begin))%10==0)
            {
                *it=true;
            }
//            std::cout<<()
        }
        std::cout<<static_cast<bool>(it_plus[5])<<std::endl;
        it_plus[5]= true;
        std::cout<<static_cast<bool>(it_plus[5])<<std::endl;
        for(auto it:b1)
        {
            std::cout<<static_cast<bool>(it)<<" ";
        }
    }
    catch (const char *msg)
    {
        std::cerr << "Exception caught: " << msg << std::endl;
    }
    system("pause");
}

void check_it()
{
    // BitSet::bits<N> a(10);
    Inter::Inter<N> a(10);
    std::cout << a << std::endl;

    for(auto it=a.begin();it!=a.end();it++)
    {
        std::cout<<static_cast<bool>(*it)<<" ";
    }
    std::cout<<"run correctly in check_it"<<std::endl;
}

void check_int()
{

    check_it();

	Inter::Inter<N> a(13);
    Inter::Inter<N> b=a;
    BitSet::bits aa=a;
    std::cout<<aa<<std::endl;
    aa=b;
    std::cout<<aa<<std::endl;
    Inter::Inter<N> c("01111",5,'0','1');
    aa=c;
    std::cout<<aa<<std::endl;
    try{
    auto d=b+c;
    // aa=d;
    // std::cout<<aa<<std::endl;
    }catch(std::exception &e){
        std::cout<<e.what()<<std::endl;
    }
    std::cout<<"run correctly"<<std::endl;
}

int main()
{

//    check();
	    check_int();
	system("pause");

    return 0;

    // freopen("in.txt", "r", stdin);
    std::string op;
    while (std::cin >> op)
    {
        // Part 1
        std::string x;
        std::cin >> x;
        if (op == "bitset")
        {
            M[x] = bits_type();
        }
        if (op == "bitset_s")
        {
            std::string s;
            char z, o;
            std::cin >> s >> z >> o;
            auto temp = bits_type(s.c_str(), s.length(), z, o);
            M[x] = temp;
        }
        if (op == "bitset_u")
        {
            unsigned long long u;
            std::cin >> u;
            M[x] = bits_type(u);
        }
        if (op == "test")
        {
            std::cout << M[x].to_string() << std::endl;
        }
        if (op == "count")
        {
            std::cout << M[x].count() << std::endl;
        }
        if (op == "all")
        {
            std::cout << M[x].all() << std::endl;
        }
        if (op == "any")
        {
            std::cout << M[x].any() << std::endl;
        }
        if (op == "none")
        {
            std::cout << M[x].none() << std::endl;
        }
        if (op == "flipall")
        {
            M[x].flip();
        }
        if (op == "setall")
        {
            M[x].set();
        }
        if (op == "resetall")
        {
            M[x].reset();
        }
        if (op == "less")
        {
            std::string y;
            std::cin >> y;
            std::cout << (x < y) << std::endl;
        }
        if (op == "ANDS")
        {
            std::string a, b;
            std::cin >> a >> b;
            M[x] = M[a] & M[b];
        }
        if (op == "ORS")
        {
            std::string a, b;
            std::cin >> a >> b;
            M[x] = M[a] | M[b];
        }
        if (op == "XORS")
        {
            std::string a, b;
            std::cin >> a >> b;
            M[x] = M[a] ^ M[b];
        }
        if (op == "LSS")
        {
            std::string a;
            size_t b;
            std::cin >> a >> b;
            M[x] = M[a] << b;
        }
        if (op == "RSS")
        {
            std::string a;
            size_t b;
            std::cin >> a >> b;
            M[x] = M[a] >> b;
        }
        if (op == "NOTS")
        {
            std::string a;
            std::cin >> a;
            M[x] = ~M[a];
        }
        if (op == "AND")
        {
            std::string a, b;
            std::cin >> b;
            auto temp = M[x] & M[b];
            std::cout << temp << std::endl;
        }
        if (op == "OR")
        {
            std::string a, b;
            std::cin >> b;
            auto temp = M[x] | M[b];
            std::cout << temp << std::endl;
        }
        if (op == "XOR")
        {
            std::string a, b;
            std::cin >> b;
            auto temp = M[x] ^ M[b];
            std::cout << temp << std::endl;
        }
        if (op == "NOT")
        {
            std::string a;
            auto temp = ~M[x];
            std::cout << temp << std::endl;
        }
        if (op == "LE")
        {
            std::string a, b;
            std::cin >> b;
            std::cout << (M[x] < M[b]) << std::endl;
        }
        if (op == "EQ")
        {
            std::string a, b;
            std::cin >> b;
            std::cout << (M[x] == M[b]) << std::endl;
        }
        if (op == "GR")
        {
            std::string a, b;
            std::cin >> b;
            std::cout << (M[x] > M[b]) << std::endl;
        }
    }
    return 0;
}