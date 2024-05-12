#ifndef CSTRING
#include <cstring>
#include <string>
#endif

#include <compare>
#include <algorithm>

namespace BitSet
{

    template <class origin>
    class bit_reference
    {
        using storage_type = typename origin::storage_type;
        using storage_pointer = typename origin::storage_pointer; // why???
        storage_pointer seg=nullptr;
        storage_type mask; // complement

        friend origin;
        bit_reference(storage_pointer _seg, storage_type _mask) : seg(_seg), mask(_mask) {}

    public:
        explicit operator bool() const
        {
            return bool(*seg & mask);
        }

        bool operator~() const
        {
            return !(*seg & mask);
        }

        bit_reference &operator=(bool x)
        { // consider pipe
            if (x)
                *seg |= mask;
            else
                *seg &= ~mask;
            return *this;
        }

        bit_reference &operator=(int x)
        { // consider to implement literal constant to bitset
            return *this = bool(x);
        }

        bit_reference &operator=(const bit_reference &x)
        {
            return *this = bool(x);
        }
    };

    template <class origin>
    class bit_const_reference
    {
    protected:
        using storage_type = typename origin::storage_type;
        using storage_pointer = const storage_type *; // why???
        storage_pointer seg;
        storage_type mask=nullptr; // complement
        friend origin;
        friend class bit_iterator<origin, true>;

        bit_const_reference(storage_pointer _seg, storage_type _mask) : seg(_seg), mask(_mask) {}

    public:
        explicit operator bool() const
        {
            return bool(*seg & mask);
        }

        bool operator~() const
        {
            return !(*seg & mask);
        }
    };

    template <class origin,bool is_const>
    class bit_iterator
    {
    // tags of a random access iterator
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = bool;
        using difference_type = std::ptrdiff_t;
        using pointer = bit_iterator;
        using reference = std::conditional_t<is_const, bit_const_reference<origin>, bit_reference<origin>>;

        bit_iterator(){};// uesd in auto ??, construct a null iterator
        bit_iterator(const bit_iterator<origin, false> &x) : seg(x.seg), offset(x.offset) {} // copy constructor

        bit_iterator operator = (const bit_iterator<origin, false> &x)
        {
            seg = x.seg;
            offset = x.offset;
            return *this;
        }

        reference operator*() const
        {
            return bit_const_reference<origin>(seg,size_t(1)<<offset);
        }

    private:
        using storage_type = typename origin::storage_type;
        using storage_pointer = typename std::conditional_t<is_const, const typename origin::storage_pointer, typename origin::storage_pointer> ;

        storage_pointer seg=nullptr;// pointer to a storage_type 'type'
        unsigned int offset=0;// offset in storage_type

        friend origin;
        bit_iterator(storage_pointer _seg, unsigned int _offset) : seg(_seg), offset(_offset) {}

    };

    template <size_t N>
    class bits
    {
    public:
        using storage_type = size_t;
        using storage_pointer = storage_type *;
        using ULL = unsigned long long;
        static const ULL length = sizeof(storage_type) * 8; // length of storage_type in bits
    protected:
        ULL SizeOfType = 0; // size of storage_type
        size_t SizeOfBit;   // size of bitset in bits// uesd to judge if beyond
        storage_type bitset[1000];
        // storage_pointer bitset=storage_bitset;

        using reference = bit_reference<bits<N>>;
        using const_reference = bit_const_reference<bits<N>>;
        using iterator = bit_iterator<bits<N>, false>;
        using const_iterator = bit_iterator<bits<N>, true>;

        // friend
        friend class bit_reference<bits<N>>;

        template <size_t M>
        friend std::strong_ordering operator<=>(const bits<M> &x, const bits<M> &y);
        template <size_t M>
        friend bits<M> operator<<(const bits<M> &_a, const size_t b);
        template <size_t M>
        friend bits<M> operator>>(const bits<M> &_a, const size_t b);
        template <size_t M>
        friend bits<M> operator|(const bits<M> &_a, const bits<M> &_b);
        template <size_t M>
        friend bits<M> operator&(const bits<M> &_a, const bits<M> &_b);
        template <size_t M>
        friend bits<M> operator^(const bits<M> &_a, const bits<M> &_b);
        template <size_t M>
        friend bits<M> operator~(const bits<M> &_a);

        reference make_ref(size_t p)
        {
            return reference(bitset + p / length, size_t(1) << (p % length));
        }

        const_reference make_cref(size_t p) const
        {
            return const_reference(bitset + p / length, size_t(1) << (p % length));
        }

        iterator make_iter(size_t p)
        {
            return bit_iterator<bits<N>, false>(bitset + p / length, p % length);
        }

        const_iterator make_citer(size_t p) const
        {
//            return bit_iterator<bits<N>, true>(bitset + p / length, p % length);
            auto cit=bit_iterator<bits<N>, false>(bitset + p / length, p % length);
            return cit;
        }


    public:
        /*
        constructors
        1. default constructor
        2. ULL constructor
        3. string constructor
        4. copy constructor
        5. destructor
        */

        bits()
        { // fault constructor
            SizeOfBit = N;
            SizeOfType = (SizeOfBit - 1) / length + 1;
            memset(bitset, 0, sizeof(bitset));
        }

        bits(ULL n)
        { // ULL constructor
            memset(bitset, 0, sizeof(bitset));
            SizeOfBit = N;
            SizeOfType = (SizeOfBit - 1) / length + 1;
            for (ULL i = 0; i < SizeOfType; i++)
            {
                for (ULL j = 0; j < length; j++)
                {
                    if (i * length + j >= SizeOfBit)
                        break;
                    if (n & 1)
                        bitset[i] = bitset[i] | (size_t(1) << j);
                    else
                        bitset[i] = bitset[i] & ~(size_t(1) << j);
                    n >>= 1;
                }
            }
        }

        bits(const char *s, size_t n, char zero, char one)
        { // string constructor
            // SizeOfBit=((n-1)/length+1)*length;
            memset(bitset, 0, sizeof(bitset));
            SizeOfBit = N; // special because string length may be not multiple of 64
            SizeOfType = (SizeOfBit - 1) / length + 1;
            size_t BitsCnt = 0;
            for (ULL i = 0; i < SizeOfType; i++)
            {
                for (ULL j = 0; j < length; j++)
                {
                    if (i * length + j >= n)
                        break;
                    if (s[n - i * length - j - 1] == zero)
                    {
                        bitset[i] = bitset[i] & ~(size_t(1) << j);
                    }
                    else if (s[n - i * length - j - 1] == one)
                    {
                        bitset[i] = bitset[i] | (size_t(1) << j);
                    }
                    else
                    {
                        throw "invalid_arguments"; //????
                    }
                    BitsCnt++;
                    ;
                }
            }
            // if(BitsCnt!=n)
            //     throw "wrong_length";
        }

        // copy constructor
        bits(const bits &y)
        {
            SizeOfBit = y.SizeOfBit;
            SizeOfType = y.SizeOfType;
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = y.bitset[i];
            }
        }

        ~bits() = default;

        /*--------------------------------------------------------------------*/

        /*
        member functions
        */

        bool test(size_t p) const
        { // compare with [] ,test is read only
            // if(p>=SizeOfBit)
            //     throw "beyond";
            // else
            return (bitset[p / length] & (size_t(1) << (p % length)));
        }

        size_t count()
        {
            size_t cnt = 0;
            for (ULL i = 0; i < SizeOfBit; i++)
            {
                // if(bitset[i/length] & (size_t(1)<<(i%length)))
                //     cnt++;
                // if(this->operator[](i)) //anotherd way to implement by using `this` pointer
                // cnt++;              //`this` point to the object itself
                if (test(i))
                    cnt++;
            }
            return cnt;
        }

        size_t size()
        {
            return sizeof(*this) + SizeOfType * sizeof(storage_type);
        }

        bool all()
        {
            for (ULL i = 0; i < SizeOfBit; i++)
            {
                if (test(i) == 0)
                    return false;
            }
            return true;
        }

        bool any()
        {
            return !none();
        }

        bool none()
        {
            for (ULL i = 0; i < SizeOfBit; i++)
            {
                if (test(i) == 1)
                    return false;
            }
            return true;
        }

        bits &flip()
        {
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = ~bitset[i];
            }

            for (long long i = SizeOfType * length - 1; i >= (long long)SizeOfBit; i--) // solve :  rest unues bits  was fliped
            {
                if (test(i))
                    flip(i);
            }
            return *this;
        }

        bits &flip(size_t p)
        {
            {
                if (test(p))
                    bitset[p / length] = bitset[p / length] & ~(size_t(1) << (p % length)); // set 0
                else
                    bitset[p / length] = bitset[p / length] | (size_t(1) << (p % length)); // set 1
            }
            return *this;
        }

        bits &set()
        {
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = ~size_t(0);
            }

            for (long long i = SizeOfType * length - 1; i >= (long long)SizeOfBit; i--) // solve :  rest unues bits  was fliped
            {
                if (test(i))
                    flip(i);
            }
            return *this;
        }

        bits &reset()
        {
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = 0;
            }
            return *this;
        }

        bool compare(const bits &y) const
        {
            // if(SizeOfBit!=y.SizeOfBit||SizeOfType!=y.SizeOfType)
            //     throw "different_size";// why throw exception cause runtime error
            // return false;
            for (ULL i = 0; i < SizeOfType; i++) // !!!compare with B may compare uesless bits
            {                                    // has been solved ^_^
                if (bitset[i] != y.bitset[i])
                    return false;
            }
            return true;
            // I think it has no ues
        }

        std::string to_string() const
        {
            std::string s;
            for (long long i = SizeOfBit - 1; i >= 0; i--)
            {
                if (make_cref(i))
                    s.push_back('1');
                else
                    s.push_back('0');
            }
            return s;
        }

        iterator begin()
        {
            return make_iter(0);
        }

        void print()
        {
            for (size_t i = 0; i < SizeOfBit; i++)
            {
                if (test(i))
                    std::cout << 1;
                else
                    std::cout << 0;
                // std::cout<<std::endl;
            }
            std::cout << std::endl;
        }
        // check
        /*-----------------------------------------------------------------------*/
        /*
        here is some overload operator
        `=` is been overload
        &= |= ^= <<= >>= is self-assignment operator
        `<=>`  could implement  other compare operator
        */

        reference operator[](size_t p)
        {
            return make_ref(p);
        }

        // overload operator=

        bits &operator=(const bits &y)
        {
            if (this == &y)
                return *this;
            SizeOfBit = y.SizeOfBit;
            SizeOfType = y.SizeOfType;
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = y.bitset[i];
            }
            return *this;
        }

        bits &operator&=(const bits &y)
        {
            if (SizeOfBit != y.SizeOfBit || SizeOfType != y.SizeOfType)
                throw "different_size";
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = bitset[i] & y.bitset[i];
            }
            return *this;
        }

        bits &operator|=(const bits &y)
        {
            if (SizeOfBit != y.SizeOfBit || SizeOfType != y.SizeOfType)
                throw "different_size";
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = bitset[i] | y.bitset[i];
            }
            return *this;
        }

        bits &operator^=(const bits &y)
        {
            if (SizeOfBit != y.SizeOfBit || SizeOfType != y.SizeOfType)
                throw "different_size";
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = bitset[i] ^ y.bitset[i];
            }
            return *this;
        }

        bits &operator>>=(size_t n)
        {
            if (n >= SizeOfBit)
            {
                this->reset();
                return *this;
            }
            for (long long i = n; i < (long long)SizeOfBit; i++)
            {
                if (test(i) != test(i - n))
                    flip(i - n);
            }
            for (long long i = SizeOfBit - 1, boundary_temp = (long long)SizeOfBit - n; i >= boundary_temp; i--)
            {
                if (test(i))
                    flip(i);
            }
            return *this;
        }

        bits &operator<<=(size_t n)
        {
            if (n >= SizeOfBit)
            {
                this->reset();
                return *this;
            }

            for (long long i = SizeOfBit - n - 1; i >= 0; i--)
            {
                if (test(i) != test(i + n))
                    flip(i + n);
            }
            for (long long i = 0; i < (long long)n; i++)
            {
                if (test(i))
                    flip(i);
            }
            return *this;
        }

        bool operator==(bits &y) const
        {
            return *this <=> y == 0;
        }

        bool operator!=(bits &y) const
        {
            return *this <=> y != 0;
        }
        /*
        some friend functions
        some function need be implemented out of class

        */
    };

    template <size_t N>
    std::strong_ordering operator<=>(const bits<N> &x, const bits<N> &y)
    {
        // wait to be implemented
        std::string compare_temp_x = x.to_string();
        std::string compare_temp_y = y.to_string();
        if (compare_temp_x == compare_temp_y)
            return std::strong_ordering::equal;
        else if (compare_temp_x > compare_temp_y)
            return std::strong_ordering::greater;

        else
            return std::strong_ordering::less;
    }

    template <size_t N>
    std::ostream &operator<<(std::ostream &out, const bits<N> &_bit)
    {
        std::string s = _bit.to_string();
        out << s;
        return out;
    }

    template <size_t N>
    bits<N> operator<<(const bits<N> &_a, const size_t b)
    {
        bits<N> temp = _a;
        temp <<= b;
        return temp;
    }

    template <size_t N>
    bits<N> operator>>(const bits<N> &_a, const size_t b)
    {
        bits<N> temp = _a;
        temp >>= b;
        return temp;
    }

    template <size_t N>
    bits<N> operator|(const bits<N> &_a, const bits<N> &_b)
    {
        bits<N> temp = _a;
        temp |= _b;
        return temp;
    }

    template <size_t N>
    bits<N> operator&(const bits<N> &_a, const bits<N> &_b)
    {
        bits<N> temp = _a;
        temp &= _b;
        return temp;
    }

    template <size_t N>
    bits<N> operator^(const bits<N> &_a, const bits<N> &_b)
    {
        bits<N> temp = _a;
        temp ^= _b;
        return temp;
    }

    template <size_t N>
    bits<N> operator~(const bits<N> &_a)
    {
        bits<N> temp = _a;
        temp.flip();
        return temp;
    }
}

// []  &
// constructor (ULL)
