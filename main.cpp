#pragma GCC optimize (3)
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

const int N = 510;
using bits_type = BitSet::bits<N>;
// using bits_type = std::bitset<N>;
std::map<std::string, bits_type> M;
int LifetimeTracker::cnt = 0;

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
    Uint::uint<N> a(10);
    std::cout << a << std::endl;

    for(auto it=a.begin();it!=a.end();it++)
    {
        std::cout<<static_cast<bool>(*it)<<" ";
    }
    std::cout<<"run correctly in check_it"<<std::endl;
}

void check_int()
{

    // check_it();

	Uint::uint<N> a(13);
    Uint::uint<N> b=a;
    BitSet::bits aa=a;
    std::cout<<aa<<std::endl;
    aa=b;
    std::cout<<aa<<std::endl;
    Uint::uint<N> c("01111",5,'0','1');
    aa=c;
    std::cout<<aa<<std::endl;
    try{
    auto d=b+"1";
    aa=d;
    std::cout<<aa<<std::endl;
    auto e=b-"10";
    aa=e;
    std::cout<<aa<<std::endl;
    Uint::uint<N> num("123");
    std::cout<<num.to_number("dec")<<std::endl;
    std::cout<<num.to_number("bin")<<std::endl;
//    std::cout<<num.to_number("hex")<<std::endl;
    Uint::uint<N> num2("109");
    auto mul=num*num2;
    std::cout<<mul.to_number("dec")<<std::endl;
    }catch(std::exception &e){
        std::cout<<e.what()<<std::endl;
    }
    std::cout<<"run correctly"<<std::endl;
}

void checkplusstring()
{
    // LifetimeTracker it("checkplusstring");
    Uint::uint<N> a("230333443893940463737662995679631952925221036477720877113991264888593947382997597310976833412159902073652265280796997983849145792035069602497765746058");
    // a=a+"143";
    std::cout<<a<<std::endl;
    // LifetimeTracker::GetCnt();
}

// void check_ufloat()
// {
// 	Ufloat::ufloat<20> a;
// 	a=123;
// 	Ufloat::ufloat<20> b(22);
// 	a=a+b;
//     std::cout<<a<<std::endl;
// 	// a<<=1;
// }

int main()
{
//    check();
    freopen("F:/WorkSpace/OOP/Experiment2/Experiment/big_integer_test/inputs.txt","r",stdin);
    freopen("F:/WorkSpace/OOP/Experiment2/Experiment/big_integer_test/output.txt","w",stdout);
	// check_int();
    // checkplusstring();
	// check_ufloat();
    // return 0;
    Uint::uint<N> a;
    Uint::uint<N> b;
    LifetimeTracker lt("global");
    char ope;
    while(std::cin>>ope)
    {
        //  LifetimeTracker lt;
        std::cin>>a>>b;
        switch (ope)
        {
        case '+':
            std::cout<<a+b<<std::endl;
            break;
        case '-':
            std::cout<<a-b<<std::endl;
            break;
        case '*':
            std::cout<<a*b<<std::endl;
            break;
        case '/':
            std::cout<<(a/b).first<<std::endl;
            break;
        case '%':
            std::cout<<(a/b).second<<std::endl;
            break;
        default:
            break;
        }
    }
	system("pause");
    return 0;
}