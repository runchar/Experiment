#ifndef CSTRING
#include <cstring>
#include <string>
#endif 

#include <compare>
#include <algorithm>

namespace BitSet{
    using storage_type = size_t;
    using storage_pointer = storage_type *;
    using ULL = unsigned long long; 

    class bits{
protected :
    const ULL length=sizeof(storage_type)*8;  //length of storage_type in bits
    ULL SizeOfType=0;  //size of storage_type
    size_t SizeOfBit;  //size of bitset in bits// uesd to judge if beyond
    storage_type bitset[1000];
    // storage_pointer bitset=storage_bitset;
public:
/*
constructors
1. default constructor
2. ULL constructor
3. string constructor
4. copy constructor
5. destructor
*/
        bits(){ //fault constructor
            SizeOfBit=0;
            SizeOfType=1;
         }
       
        bits( ULL n ){ //ULL constructor
            SizeOfBit=sizeof(ULL)*8;
            SizeOfType=(SizeOfBit-1)/length+1;
            for(ULL i=0;i<SizeOfType;i++)
            {
                for(ULL j=0;j<length;j++)
                {
                    if(i*length+j>=sizeof(ULL))
                        break;
                    if(n & (1<<(i*length+j)))
                        bitset[i]=bitset[i] | (size_t(1)<<j);
                    else
                        bitset[i]=bitset[i] & ~(size_t(1)<<j);
                }
            }
        }

        bits( const char* s , size_t n , char zero , char one ){    //string constructor
            // SizeOfBit=((n-1)/length+1)*length;
            SizeOfBit=n;//special because string length may be not multiple of 64
            SizeOfType=(SizeOfBit-1)/length+1;
            size_t BitsCnt=0;
            for(ULL i=0;i<SizeOfType;i++)
            {
                for(ULL j=0;j<length;j++)
                {
                    if(i*length+j>=n)
                        break;
                    if(s[i*length+j]==zero)
                    {
                        bitset[i]=bitset[i] & ~(size_t(1)<<j);
                    }
                    else if(s[i*length+j]==one)
                    {
                        bitset[i]=bitset[i] | (size_t(1)<<j);
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
        
        //copy constructor
        bits( const BitSet ::bits &y){
            SizeOfBit=y.SizeOfBit;
            SizeOfType=y.SizeOfType;
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=y.bitset[i];
            }
        }

        ~bits()=default; 

/*--------------------------------------------------------------------*/

/*
member functions
*/

        bool test(size_t p)const {//compare with [] ,test is read only
            if(p>=SizeOfBit)
                throw "beyond";
            else
                return (bitset[p/length] & (size_t(1)<<(p%length)));
        }

        size_t count(){
            size_t cnt=0;
            for(ULL i=0;i<SizeOfBit;i++)
            {
                // if(bitset[i/length] & (size_t(1)<<(i%length)))
                //     cnt++;
                if(this->operator[](i)) //anotherd way to implement by using `this` pointer
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

            for(long long i=SizeOfType*length-1;i>=(long long)SizeOfBit;i--)// solve :  rest unues bits was filped
            {
                if(test(i))
                    filp(i);
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
                    bitset[p/length]=bitset[p/length] & ~(size_t(1)<<(p%length));//set 0
                else
                    bitset[p/length]=bitset[p/length] | (size_t(1)<<(p%length));//set 1
            }
            return *this;
        }

        bits& set(){
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=~size_t(0);
            }

            for(long long i=SizeOfType*length-1;i>=(long long)SizeOfBit;i--)// solve :  rest unues bits was filped
            {
                if(test(i))
                    filp(i);
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
        
        bool compare(const bits& y) const {
            //if(SizeOfBit!=y.SizeOfBit||SizeOfType!=y.SizeOfType)
            //    throw "different_size";// why throw exception cause runtime error
                //return false;
            for(ULL i=0;i<SizeOfType;i++)   // !!!compare with B may compare uesless bits
            {                               // has been solved ^_^
                if(bitset[i]!=y.bitset[i])
                    return false;
            }
            return true;
        }

        std::string to_string() const {
            std::string s;
            for(ULL i=0;i<SizeOfBit;i++)
            {
                if(test(i))
                    s.push_back('1');
                else
                    s.push_back('0');
            }
            return s;
        }

        void print(){
            for(ULL i=0;i<SizeOfType;i++)
            {
                for(ULL j=0;j<length;j++)
                {
                    if(i*length+j>=SizeOfBit)
                        break;
                    if(bitset[i] & (size_t(1)<<j))
                        std::cout<<1;
                    else
                        std::cout<<0;
                }
            }
            std::cout<<std::endl;
        }
        //check 
/*-----------------------------------------------------------------------*/
/*
here is some overload operator
`=` is been overload
&= |= ^= <<= >>= is self-assignment operator
`<=>`  could implement  other compare operator
*/

        // [] get bit in position p
        // you should inplement & later!!!!
        bool operator[](size_t p){
            if(p>=SizeOfBit)
                throw "beyond";
            else
                return (bitset[p/length] & (size_t(1)<<(p%length)));
        }

        //overload operator= 
        bits& operator=(const BitSet ::bits &y){
            if(this==&y)
                return *this;
            SizeOfBit=y.SizeOfBit;
            SizeOfType=y.SizeOfType;
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=y.bitset[i];
            }
            return *this;
        }

        bits& operator&=(const BitSet::bits& y){
            if(SizeOfBit!=y.SizeOfBit||SizeOfType!=y.SizeOfType)
                throw "different_size";
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=bitset[i] & y.bitset[i];
            }
            return *this;
        }

        bits& operator|=(const BitSet::bits& y){
            if(SizeOfBit!=y.SizeOfBit||SizeOfType!=y.SizeOfType)
                throw "different_size";
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=bitset[i] | y.bitset[i];
            }
            return *this;
        }

        bits& operator^=(const BitSet::bits& y){
            if(SizeOfBit!=y.SizeOfBit||SizeOfType!=y.SizeOfType)
                throw "different_size";
            for(ULL i=0;i<SizeOfType;i++)
            {
                bitset[i]=bitset[i] ^ y.bitset[i];
            }
            return *this;
        }
        bits& operator<<=(size_t n){
            if(n>=SizeOfBit)
                this->reset();
            for(long long i=n;i<(long long)SizeOfBit;i++)
            {
                if(test(i)!=test(i-n))
                    filp(i-n);
            }
            for(long long i=SizeOfBit-1,boundary_temp=(long long)SizeOfBit-n;i>=boundary_temp;i--)
            {
                if(test(i))
                    filp(i);
            }
            return *this;
        }

        bits& operator>>=(size_t n){
            if(n>=SizeOfBit)
                this->reset();
            for(long long i=SizeOfBit-n-1;i>=0;i--)
            {
                if(test(i)!=test(i+n))
                    filp(i+n);
            }
            for(long long i=0;i<(long long)n;i++)
            {
                if(test(i))
                    filp(i);
            }
            return *this;
        }
        
/*
some friend functions 
some function need be implemented out of class

*/
        friend std::strong_ordering operator <=>(const bits& x , const bits& y);
    };

    std::strong_ordering operator <=>(const bits& x , const bits& y){
        //wait to be implemented
        std::string compare_temp_x=x.to_string();
        std::string compare_temp_y=y.to_string();
        if(compare_temp_x==compare_temp_y)
            return std::strong_ordering::equal;
        else if(compare_temp_x>compare_temp_y)
            return std::strong_ordering::greater;
        else
            return std::strong_ordering::less;
    }
}


// class A:public BitStream::bits{ };
        //copy constructor
        //compare 