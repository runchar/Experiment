#include<bits/stdc++.h>
#include<compare> // Include the <compare> header to access the 'strong_ordering' type

int main()
{
    // freopen("test_output.txt", "w", stdout);
    std::bitset<8> a(127);   
    std::cout << a << std::endl; // Output: 00101010
    a.operator<<=(2); // Shift left by 2
    std::cout << a << std::endl; // Output: 168
//    ; // Output: 10101000
    std::cout <<  a.to_string() << std::endl; // Output: 10101000
    std::bitset<8> aa("11111110", 8, '0', '1');   
        std::cout << aa << std::endl; 
        aa.operator<<=(2); 
        std::cout << aa << std::endl; 
        std::cout <<  aa.to_string() << std::endl;
        std::cout<< (aa==a)<<std::endl;
        std::cout<< (aa!=a)<<std::endl;
        std::cout<< (aa<<1000)<<std::endl;
        std::cout<< (aa<<5)<<std::endl;
        std::cout<< (aa>>5)<<std::endl;
        std::cout<< (aa|a)<<std::endl;
        std::cout<< (aa&a)<<std::endl;
        std::cout<< (aa^a)<<std::endl;
        std::cout<< (~a)<<std::endl;
}