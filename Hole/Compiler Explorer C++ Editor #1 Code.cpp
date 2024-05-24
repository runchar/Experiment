#include <iostream>
#include <stdexcept>
#include <cstring>

void judge(const char* s)
{
        if(s=="Hello")
    {
        std::cout<<"Yes"<<std::endl;
    }else{
        std::cout<<"No"<<std::endl;
    };
}

int main(){
    judge("Hello");
    return 0;
}



