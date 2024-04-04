#include<iostream>
#include"bitstream.h"

int main(){
    try {
        char aa[]="1011010110101010101010101000001111101010010010101100101111111110111";
        char bb[]="111111111";

        BitSet::bits a(aa,67,'0','1');
        BitSet::bits b(bb,9,'0','1');
        BitSet::bits c;
        // a.print();
        // std::cout<<std::endl;
        // for(int i=0;i<=5;i++)
        //     std::cout<<a[i]; 
        // std::cout<<std::endl;
        // std::cout<<a.count()<<std::endl;
        // std::cout<<a.size()<<std::endl;
        // std::cout<<b.size()<<std::endl;
        // b.print();
        // std::cout<<std::endl;
        // c.print();
        // std::cout<<a.all()<<std::endl;
        // std::cout<<a.any()<<std::endl;
        // std::cout<<a.none()<<std::endl;
        // std::cout<<b.all()<<std::endl;
        // std::cout<<b.any()<<std::endl;
        // std::cout<<b.none()<<std::endl;
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