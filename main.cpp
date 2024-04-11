#include<iostream>
#include"bitstream.h"

int main(){
    try {
        char aa[]="010110101101010101010101010000011111010100100101011001011111111101110";
        char bb[]="111111111";

        BitSet::bits a(aa,69,'0','1');
        //BitSet::bits a(17);
        a.print();
        a<<=20;
        a.print();
        BitSet::bits b(a);
        b=a;
        b.print();
        b>>=2;
        b<<=1;
        b.print();
        std::cout<<"string"<<std::endl;
        std::cout<<b.to_string()<<std::endl<<a.to_string()<<std::endl;
        std::cout<<(b.to_string()>a.to_string())<<std::endl;
        std::cout<<(a<b)<<std::endl;
        std::cout<<(a>b)<<std::endl;
        std::cout<<(a<=b)<<std::endl;
    } catch (const char* msg) {
        std::cerr << "Exception caught: " << msg << std::endl;
    }
    return 0;
}