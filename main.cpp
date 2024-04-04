#include<iostream>
#include"bitstream.h"

int main(){
    try {
        char aa[]="1111000";
        BitStream::bits a(aa,7,'0','1');
        BitStream::bits b(127);
        BitStream::bits c;
        int i=1;
        i++;
        a.print();
        std::cout<<std::endl;
        b.print();
        std::cout<<std::endl;
        c.print();
    } catch (const char* msg) {
        std::cerr << "Exception caught: " << msg << std::endl;
    }
    return 0;
}