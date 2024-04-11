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
        BitSet::bits b(bb,9,'0','1');
        b=a;
        b.print();
        b>>=2;
        b<<=1;
        b.print();
        std::cout<<a.compare(b)<<std::endl;
        return 0;
        auto temp=b.filp(3);
        b.print();
        auto temp2=temp.set();
        b.print();
        auto temp3=temp2.reset();
        b.print();
        std::cout<<temp3.compare(b)<<std::endl;
    } catch (const char* msg) {
        std::cerr << "Exception caught: " << msg << std::endl;
    }
    return 0;
}