#ifndef CSTRING
#include <cstring>
#endif 

namespace BitSet{
    using storage_type = size_t;
    using storage_pointer = storage_type *;
    using ULL = unsigned long long; 

    class bits{
protected :
    const ULL length=sizeof(storage_type)*8;  //length of storage_type in bits
    ULL SizeOfType=0;  //size of storage_type
    size_t SizeOfBit;  //size of bitset in bits// uesd to judge if beyond
    storage_pointer bitset=nullptr;
public:
        bits(){
            SizeOfBit=0;
            SizeOfType=1;
            bitset = new storage_type[SizeOfType];
            memset(bitset,0,SizeOfType*sizeof(storage_type));
         }
        //fault constructor
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
        //ULL constructor
        bits( const char* s , size_t n , char zero , char one ){
            // SizeOfBit=((n-1)/length+1)*length;
            SizeOfBit=n;//special because string length may be not multiple of 64
            SizeOfType=(SizeOfBit-1)/length+1;
            bitset = new storage_type[SizeOfType];
            memset(bitset,0,SizeOfType*sizeof(storage_type));
            size_t BitsCnt=0;
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
                    {
                        throw "invalid_arguments";//????
                    }
                        BitsCnt++;;
                }
                
            }
            if(BitsCnt!=n)
                throw "wrong_length";
        }
        //string constructor

        ~bits(){
            delete[] bitset;
        }   

        bool test(size_t p){
            if(p>=SizeOfBit)
                throw "beyond";
            else
                return (bitset[p/length] & (1ull<<(p%length)));
        }

        bool operator[](size_t p){
            if(p>=SizeOfBit)
                throw "beyond";
            else
                return (bitset[p/length] & (1ull<<(p%length)));
        }
        //impletment by overload [] , same with `test`

        size_t count(){
            size_t cnt=0;
            for(ULL i=0;i<SizeOfBit;i++)
            {
                // if(bitset[i/length] & (1ull<<(i%length)))
                //     cnt++;
                if(this->operator[](i)) //another way to implement by using `this` pointer
                    cnt++;              //`this` point to the object itself
            }
            return cnt;
        }

        size_t size(){
            return sizeof(*this)+SizeOfType*sizeof(storage_type);
        }

        bool all(){
            for(ULL i=0;i<SizeOfBit;i++)
            {
                if(this->operator[](i)==0)
                    return false;
            }
            return true;
        }
       
        bool any(){
            return !none();
        }

        bool none(){
            for(ULL i=0;i<SizeOfBit;i++)
            {
                if(this->operator[](i)==1)
                    return false;
            }
            return true;
        }

        bits& filp(){
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=~bitset[i];
            }
            return *this;
        }

        bits& filp(size_t p)
        {
            if(p>=SizeOfBit)
                throw "beyond";
            else
            {
                if(this->operator[](p))
                    bitset[p/length]=bitset[p/length] & ~(1ull<<(p%length));//set 0
                else
                    bitset[p/length]=bitset[p/length] | (1ull<<(p%length));//set 1
            }
            return *this;
        }

        bits& set(){
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=~0;
            }
            return *this;
        }

        bits& reset(){
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=0;
            }
            return *this;
        }
        
        bool compare(const bits& y){
            if(SizeOfBit!=y.SizeOfBit||SizeOfType!=y.SizeOfType)
                throw "different_size";
            for(ULL i=0;i<SizeOfType;i++)
            {
                if(bitset[i]!=y.bitset[i])
                    return false;
            }
            return true;
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
            std::cout<<std::endl;
        }
        //check 
    };
}


// class A:public BitStream::bits{ };