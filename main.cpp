#include<iostream>
#include"bitstream.h"

int main(){
    // freopen("main_output.txt", "w", stdout);
    try {
        BitSet::bits a(127, 8);   
        // a.print();
        std::cout << a << std::endl; 
        a.operator<<=(2); 
        std::cout << a << std::endl; 
        std::cout <<  a.to_string() << std::endl; 
        BitSet::bits aa("11111110", 8, '0', '1');   
        std::cout << aa << std::endl; 
        aa.operator<<=(2); 
        std::cout << aa << std::endl; 
        std::cout <<  aa.to_string() << std::endl;
        std::cout<< (aa==a)<<std::endl;
        //C++20 says that these are ambiguous, even though the second is reversed:gcc
        //what is this? 
        //https://stackoverflow.com/a/60387060/22912407   hard to understanding
        std::cout<< (aa!=a)<<std::endl;
        std::cout<< (aa<<1000)<<std::endl;
        std::cout<< (aa<<5)<<std::endl;
        std::cout<< (aa>>5)<<std::endl;
        std::cout<< (aa|a)<<std::endl;
        std::cout<< (aa&a)<<std::endl;
        std::cout<< (aa^a)<<std::endl;
        std::cout<< (~a)<<std::endl;
        std::cout<<"Hello \nthis is a check\n"<<std::endl;

    } catch (const char* msg) {
        std::cerr << "Exception caught: " << msg << std::endl;
    }
    return 0;
}