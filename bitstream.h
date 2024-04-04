#ifndef CSTRING
#include <cstring>
#endif 

namespace BitStream{
    using storage_type = size_t;
    using storage_pointer = storage_type *;
    using ULL = unsigned long long; 

    class bits{

    public:
    const ULL length=sizeof(storage_type)*8;  //length of storage_type in bits
    ULL SizeOfType=0;  //size of bitset in terms of storage_type
    size_t SizeOfBit;
    storage_pointer bitset=nullptr;

        bits(){
            SizeOfBit=0;
            SizeOfType=1;
            bitset = new storage_type[SizeOfType];
            memset(bitset,0,SizeOfType*sizeof(storage_type));
         }

        bits( ULL n ){
            SizeOfBit=sizeof(ULL)*8;
            SizeOfType=(SizeOfBit-1)/length+1;
            bitset = new storage_type[SizeOfType];
            memset(bitset,0,SizeOfType*sizeof(storage_type));
            for(ULL i=0;i<SizeOfType;i++)
            {
                for(ULL j=0;j<length;j++)
                {
                    if(i*length+j>=sizeof(ULL))
                        break;
                    if(n & (1<<(i*length+j)))
                        bitset[i]=bitset[i] | (1ull<<j);
                    else
                        bitset[i]=bitset[i] & ~(1ull<<j);

            // std::cout<<SizeOfBit<<" "<<length<<std::endl;
            // for(ULL i=0;i<SizeOfType;i++)
            // {
            //     for(ULL j=0;j<length;j++)
            //     {
            //         if(i*length+j>=SizeOfBit)
            //             break;
            //         if(bitset[i] & (1ull<<j))
            //             std::cout<<1;
            //         else
            //             std::cout<<0;
            //     }
            // }
            // std::cout<<std::endl;
                }
            }
        }

        bits( const char* s , size_t n , char zero , char one ){
            // SizeOfBit=((n-1)/length+1)*length;
            SizeOfBit=n;//special because string length may be not multiple of 64
            SizeOfType=(SizeOfBit-1)/length+1;
            bitset = new storage_type[SizeOfType];
            memset(bitset,0,SizeOfType*sizeof(storage_type));
            for(ULL i=0;i<SizeOfType;i++)
            {
                for(ULL j=0;j<length;j++)
                {
                    if(i*length+j>=n)
                        break;
                    if(s[i*length+j]==zero)
                    {
                        bitset[i]=bitset[i] & ~(1ull<<j);
                    }
                    else if(s[i*length+j]==one)
                    {
                        bitset[i]=bitset[i] | (1ull<<j);
                    }
                    else
                        throw "invalid_arguments";//????
                }

            }
        }

        void print(){
            for(ULL i=0;i<SizeOfType;i++)
            {
                for(ULL j=0;j<length;j++)
                {
                    if(i*length+j>=SizeOfBit)
                        break;
                    if(bitset[i] & (1ull<<j))
                        std::cout<<1;
                    else
                        std::cout<<0;
                }
            }
        }
    };
}


// class A:public BitStream::bits{ };