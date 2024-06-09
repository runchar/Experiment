#ifndef CSTRING
#include <cstring>
#include <string>
#endif

#include <compare>
#include <algorithm>
#include <chrono>

#ifdef __GUNC__
#define unlikely(x) __builtin_expect(!!(x), 0)
#define likely(x) __builtin_expect(!!(x), 1)
#else
#define likely(x) (x)
#define unlikely(x) (x)
#endif


class LifetimeTracker
{
private:
    static int cnt;
    std::chrono::high_resolution_clock::time_point s;
    std::chrono::steady_clock::time_point e;
    const char *name;

public:
    LifetimeTracker(const char *name)
    {
        s = std::chrono::high_resolution_clock::now();
        this->name = name;
        cnt++;
    }

    ~LifetimeTracker()
    {
        auto e = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(e - s).count();
        printf("Object %s  Lifetime:   %lf   ms  \n", name, duration * 1000);
    }

    static void GetCnt()
    {
        printf("The object has been invoked %d times\n", cnt);
    }
};

namespace BitSet
{
    template <class origin>
    class bit_reference
    {
        using storage_type = typename origin::storage_type;
        using storage_pointer = typename origin::storage_pointer;
        storage_pointer seg = nullptr;
        storage_type mask; 

        friend origin;
        bit_reference(storage_pointer _seg, storage_type _mask) : seg(_seg), mask(_mask) {}

    public:
        static bit_reference create(storage_pointer _seg, storage_type _mask)
        {
            return bit_reference(_seg, _mask);
        }

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
        storage_type mask = nullptr; // complement
        friend origin;

        // friend class bit_iterator<origin, true>;
        /*
            question:
            here when I want to use friend to let bit_iterator access bit_const_reference, the compiler tell me
            'bit_iterator' is not a class template, but I define this template next
        */

        bit_const_reference(storage_pointer _seg, storage_type _mask) : seg(_seg), mask(_mask) {}

    public:
        static bit_const_reference create(storage_pointer _seg, storage_type _mask)
        {
            return bit_const_reference(_seg, _mask);
        }

        explicit operator bool() const
        {
            return bool(*seg & mask);
        }

        bool operator~() const
        {
            return !(*seg & mask);
        }
    };

    template <class origin, bool is_const>
    class bit_iterator
    {
        using storage_type = typename origin::storage_type;
        //        using storage_pointer = typename std::conditional_t<is_const, const typename origin::storage_pointer, typename origin::storage_pointer>;
        // question ??
        using storage_pointer = typename std::conditional_t<is_const, typename origin::const_storage_pointer, typename origin::storage_pointer>;
        // using storage_pointer = typename std::conditional_t<is_const,typename const origin::storage_pointer, typename origin::storage_pointer>;
        // tags of a random access iterator
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = bool;
        using difference_type = std::ptrdiff_t;
        using pointer = bit_iterator;
        using reference = std::conditional_t<is_const, bit_const_reference<origin>, bit_reference<origin>>;

        bit_iterator(){};                                                                    // uesd in auto ??, construct a null iterator
        bit_iterator(const bit_iterator<origin, false> &x) : seg(x.seg), offset(x.offset) {} // copy constructor

        bit_iterator operator=(const bit_iterator<origin, false> &x)
        {
            seg = x.seg;
            offset = x.offset;
            return *this;
        }

        reference operator*() const
        {
            return reference::create(seg, size_t(1) << offset);
        }

        reference operator*()
        {
            return reference::create(seg, size_t(1) << offset);
        }

        /*
            question:
            in the iterator, operator like `++`,`--`,`>=`will not modify the object itself
            so all the operator should be const so that the both iterator can use it
            and `*` should be implemented in two version, one for const and one for non-const
            Right?
            Yes, it is right
        */

        /*
        request
        https://zh.cppreference.com/w/cpp/named_req/RandomAccessIterator
        */

        bit_iterator &operator++()
        {
            if (offset == origin::length - 1)
            {
                seg++;
                offset = 0;
            }
            else
            {
                offset++;
            }
            return *this;
        }

        bit_iterator operator++(int)
        {
            bit_iterator temp = *this;
            ++*this;
            return temp;
        }

        bit_iterator &operator--()
        {
            if (offset == 0)
            {
                seg--;
                offset = origin::length - 1;
            }
            else
            {
                offset--;
            }
            return *this;
        }

        bit_iterator operator--(int)
        {
            bit_iterator temp = *this;
            --*this;
            return temp;
        }

        bit_iterator &operator+=(difference_type n)
        {
            if (n < 0)
                return *this -= -n;

            difference_type seg_offset = n / origin::length;
            n %= origin::length;

            if (offset + n >= origin::length)
            {
                seg += seg_offset + 1;
                offset = offset + n - origin::length;
            }
            else
            {
                offset += n;
            }
            return *this;
        }

        bit_iterator &operator-=(difference_type n)
        {
            if (n < 0)
                return *this += -n;
            difference_type seg_offset = n / origin::length;
            n %= origin::length;

            if (offset < n)
            {
                seg -= seg_offset + 1;
                offset = offset - n + origin::length;
            }
            else
            {
                offset -= n;
            }
            return *this;
        }

        bit_iterator operator+(int n) // it+n
        {
            bit_iterator temp = *this;
            return temp += n;
        }
        template <class o, bool ic>
        friend bit_iterator<o, ic> operator+(int n, bit_iterator<o, ic> it);
        //        friend bit_iterator<origin, false> operator + (int n , bit_iterator<origin, false> it);

        bit_iterator operator-(int n)
        {
            bit_iterator temp = *this;
            return temp -= n;
        }

        difference_type operator-(const bit_iterator &it)
        {
            return (seg - it.seg) * origin::length + offset - it.offset;
        }

        reference operator[](size_t p)
        {
            return *(*this + p);
        }

        bool operator==(const bit_iterator &it) const
        {
            return (*this).seg == it.seg && (*this).offset == it.offset;
        }

        bool operator!=(const bit_iterator &it) const
        {
            return !(*this == it);
        }

        auto operator<=>(const bit_iterator &it) const
        {
            if (*this == it)
                return std::strong_ordering::equal;
            else if (this->seg > it.seg || (this->seg == it.seg && this->offset > it.offset))
                return std::strong_ordering::greater;
            else
                return std::strong_ordering::less;
        }

    private:
        storage_pointer seg = nullptr; // pointer to a storage_type 'type'
        unsigned int offset = 0;       // offset in storage_type

        friend bit_iterator<origin, true>;
        friend bit_iterator<origin, false>;
        friend origin;

        explicit bit_iterator(storage_pointer _seg, unsigned int _offset) : seg(_seg), offset(_offset) {}
    };

    template <class origin>
    bit_iterator<origin, false> operator+(int n, bit_iterator<origin, false> it)
    {
        return it += n;
    }

    template <class origin>
    bit_iterator<origin, true> operator+(int n, bit_iterator<origin, true> it)
    {
        return it += n;
    }

    template <size_t N>
    class bits
    {
    public:
        using storage_type = size_t;
        using storage_pointer = storage_type *;
        using const_storage_pointer = const storage_type *;
        using ULL = unsigned long long;
        static const ULL length = sizeof(storage_type) * 8; // length of storage_type in bits
        storage_type bitset[N];

    protected:
        ULL SizeOfType = 0; // size of storage_type
        size_t SizeOfBit;   // size of bitset in bits// uesd to judge if beyond

        // storage_pointer bitset=storage_bitset;

        using reference = bit_reference<bits<N>>;
        using const_reference = bit_const_reference<bits<N>>;
        using iterator = bit_iterator<bits<N>, false>;
        using const_iterator = bit_iterator<bits<N>, true>;

        // friend
        friend class bit_reference<bits<N>>;
        friend class bit_const_reference<bits<N>>;
        friend class bit_iterator<bits<N>, false>;
        friend class bit_iterator<bits<N>, true>;
        // friend class uint<bits<N>>

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

        const_iterator make_iter(size_t p) const
        {
            return bit_iterator<bits<N>, true>(bitset + p / length, p % length);
        }

        // const_iterator make_citer(size_t p) const {
        //     // return bit_iterator<bits<N>, true>(bitset + p / length, p % length);
        //     // Linear Algebra test like a shit QAQ --5.12
        //     // bit_iterator<bits<N>, true> const cit = bit_iterator<bits<N>, false>(bitset + p / length, p % length);
        //     bit_iterator<bits<N>, true> cit=make_iter(p);
        //     return cit;
        // }

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
                        throw std::runtime_error("invalid_arguments"); //????
                    }
                    BitsCnt++;
                }
            }
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
        {
            return (bitset[p / length] & (size_t(1) << (p % length)));
        }

        size_t count()
        {
            size_t cnt = 0;
            for (ULL i = 0; i < SizeOfBit; i++)
            {
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

        void flip(size_t p, bool x)
        {
            {
                if (x)
                    bitset[p / length] = bitset[p / length] | (size_t(1) << (p % length)); // set 1
                else
                    bitset[p / length] = bitset[p / length] & ~(size_t(1) << (p % length)); // set 0
            }
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
                if (test(i))
                    s.push_back('1');
                else
                    s.push_back('0');
            }
            return s;
        }

        virtual std::string OstreamString() const
        {
            return this->to_string();
        }

        iterator begin()
        {
            return make_iter(0);
        }

        const_iterator cbegin() const
        {
            return make_iter(0);
        }

        iterator end()
        {
            return make_iter(SizeOfBit);
        }

        const_iterator cend() const
        {
            return make_iter(SizeOfBit);
        }

        iterator make(int p)
        {
            return make_iter(p);
        }

        void print()
        {
            for (size_t i = 0; i < SizeOfBit; i++)
            {
                if (test(i))
                    std::cout << 1;
                else
                    std::cout << 0;
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
                throw std::runtime_error("different_size");
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = bitset[i] & y.bitset[i];
            }
            return *this;
        }

        bits &operator|=(const bits &y)
        {
            if (SizeOfBit != y.SizeOfBit || SizeOfType != y.SizeOfType)
                throw std::runtime_error("different_size");
            for (ULL i = 0; i < SizeOfType; i++)
            {
                bitset[i] = bitset[i] | y.bitset[i];
            }
            return *this;
        }

        bits &operator^=(const bits &y)
        {
            if (SizeOfBit != y.SizeOfBit || SizeOfType != y.SizeOfType)
                throw std::runtime_error("different_size");
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
            // LifetimeTracker lt("operator<<=");
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

        ULL getSizeOfType() const { return SizeOfType; }
        ULL getSizeOfBit() const { return SizeOfBit; }
    };

    template <size_t N>
    std::strong_ordering operator<=>(const bits<N> &x, const bits<N> &y)
    {
        long long end = x.getSizeOfType() - 1;
        for (long long i = end; i >= 0; i--)
        {
            if (x.bitset[i] > y.bitset[i])
                return std::strong_ordering::greater;
            else if (x.bitset[i] < y.bitset[i])
                return std::strong_ordering::less;
        }
        return std::strong_ordering::equal;
    }

    template <size_t N>
    std::ostream &operator<<(std::ostream &out, const bits<N> &_bit)
    {
        std::string s = _bit.OstreamString();
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

namespace Uint
{
    using namespace BitSet;
    using ULL = unsigned long long;
    template <size_t N>
    class uint : public bits<N>
    {
    public:
        uint(){};

        uint(ULL n)
        {
            bits<N> tmp(n);
            *this = tmp;
        }

        uint(const char *s, size_t n, char zero, char one)
        {
            bits<N> tmp(s, n, zero, one);
            *this = tmp;
        }

        uint(std::string s)
        {
            std::string ans0;
            long long cnt = 0;
            while (s.size())
            {
                std::string tmp;
                long long len = s.length(), r = 0;
                for (long long i = 0; i < len; i++)
                {
                    r = r * 10 + s[i] - '0';
                    if (!(tmp.length() == 0 && r < 2))
                    {
                        tmp += r / 2 + '0';
                        r = r % 2;
                    }
                }
                s = tmp;
                this->flip(cnt++, r);
            }
        }

        uint(const uint &x)
        {
            this->SizeOfType = x.getSizeOfType();
            this->SizeOfBit = x.getSizeOfBit();
            memcpy(this->bitset, x.bitset, N / 8 + 1);
        }

        ~uint() = default;

        uint &operator=(const BitSet::bits<N> &x)
        {
            this->SizeOfType = x.getSizeOfType();
            this->SizeOfBit = x.getSizeOfBit();
            memcpy(this->bitset, x.bitset, N / 8 + 1);
            return *this;
        }

        uint operator+=(const uint &y)
        {
            size_t maxx = 0;
            maxx = ~maxx;
            size_t carry = 0;
            long long end = this->getSizeOfType();
            for (long long i = 0; i < end ; i++)
            {
                if (unlikely(maxx - this->bitset[i] < y.bitset[i] + carry || maxx - y.bitset[i] < this->bitset[i] + carry || this->bitset[i] + y.bitset[i] + carry > maxx))
                {
                    this->bitset[i] = this->bitset[i] + y.bitset[i] + carry - maxx - 1;
                    carry = 1;
                }
                else
                {
                    this->bitset[i] = this->bitset[i] + y.bitset[i] + carry;
                    carry = 0;
                }
            }
            return *this;
        }

        uint operator+(const uint &y) const
        {
            uint tmp(*this);
            return tmp += y;
        }

        uint operator+(const ULL &y) const
        {
            uint tmp(y);
            return *this + tmp;
        }

        uint operator+(std::string y) const
        {
            uint tmp(y);
            uint tmp2(*this);
            return tmp2 += tmp;
        }

        uint operator-(const uint &y) const
        {
            uint tmp(*this);
            return tmp -= y;
        }

        uint operator-=(const uint &y)
        {
            // LifetimeTracker lt("operator -=");
            bool BorrowBit = false;
            // --OH--
            long long end = this->getSizeOfBit();
            for (auto i = 0; i < end; i++)
            {
                bool val_x = (this->test(i));
                bool val_y = y.test(i);
                this->flip(i, (val_x ^ val_y ^ BorrowBit));
                BorrowBit = (~val_x & val_y) | ((~val_x | val_y) & BorrowBit);
            }
            return *this;
        }

        uint operator-(const ULL &y) const
        {
            uint tmp(y);
            return *this - tmp;
        }

        uint operator-(const std::string &y) const
        {
            uint tmp(y);
            return *this - tmp;
        }
        // overflow deal same with unsigned integer

        uint operator/(const uint &divisor) const
        {
            // LifetimeTracker lt;
            return this->div(divisor).first;
        }

        uint operator%(const uint &divisor) const
        {
            // LifetimeTracker lt;
            return this->div(divisor).second;
        }

        uint operator*(const uint &y) const
        {
            uint tmp;

            long long end = this->getSizeOfBit();
            for (long long i = 0; i < end; i++)
            {
                if (this->test(i))
                {
                    uint tmp2 = y;
                    tmp2 <<= i;
                    tmp += tmp2;
                }
            }
            return tmp;
        }

        std::string to_number(const char *op) const   //translate to oct number
        {
            if (op == std::string("dec"))
            {
                uint stan(10);
                uint x (*this);
                std::string num;
                while (x > stan) // O(N <)
                {
                    int num_tmp = x.div_tran();
                    num += (char)(num_tmp + '0');
                }
                int num_tmp = std::stoi(x.to_string(), nullptr, 2);
                if (num_tmp == 10)
                {
                    num += "01";
                }
                else
                {
                    num += (char)(num_tmp + '0');
                }
                std::reverse(num.begin(), num.end());
                return num;
            }

            if (op == std::string("bin"))
            {
                return this->to_string();
            }
        }

        virtual std::string OstreamString() const
        {
            return this->to_number("dec");
        }

    private:
        int div_tran() //special div 10 function
        {
            // LifetimeTracker it("div_tran");
            int rem = 0;
            for (long long i = this->getSizeOfBit() - 1; i >= 0; i--)
            {
                rem <<= 1;
                if (this->test(i))
                    rem++;
                if (rem >= 10)
                {
                    rem -= 10;
                    this->flip(i, 1);
                }
                else
                {
                    this->flip(i, 0);
                }
            }
            return rem;
        }

        std::pair<uint, uint> div(const uint &divisor) const
        {
            // LifetimeTracker lt;
            uint divi (*this);
            uint quo;
            uint rem;
            long long end = divi.getSizeOfBit();
            for (long long i = end - 1; i >= 0; i--)
            {
                rem <<= 1;
                rem[0] = divi.test(i);
                if (rem >= divisor)
                {
                    rem -= divisor;
                    quo[i] = 1;
                }
                else
                {
                    quo[i] = 0;
                }
            }
            return {quo, rem};
        }

        friend std::ostream &operator<<(std::ostream &out, const uint &x)
        {
            // std::string s = x.OstreamString();
            std::string s(x.OstreamString());
            out << s;
            return out;
        }

        friend std::istream &operator>>(std::istream &in,uint &x)
        {
            std::string s;
            if (in >> s)
            {
                x = uint(s);
            }
            else
                throw std::runtime_error("invalid_input");
            return in;
        }
    };
}