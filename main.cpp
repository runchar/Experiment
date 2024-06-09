#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("omit-frame-pointer")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
// #pragma GCC target("avx,avx2,fma")
#include <iostream>
#include <map>
#include <compare>
#include <algorithm>
#include <cstring>
#include <string>
#include "bitstream.h"

const int N = 1001;
using bits_type = BitSet::bits<N>;
std::map<std::string, bits_type> M;
int LifetimeTracker::cnt = 0;

int main()
{
    freopen("./inputs.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(0);
    // std::cout.tie(0);
    Uint::uint<N> a;
    Uint::uint<N> b;
    LifetimeTracker lt("global");
    char ope;
    while (std::cin >> ope)
    {
        //  LifetimeTracker lt("cla");
        std::cin >> a >> b;
        switch (ope)
        {
        case '+':
            std::cout << a + b << "\n";
            break;
        case '-':
            std::cout << a - b << "\n";
            break;
        case '*':
            std::cout << a * b << "\n";
            break;
        case '/':
            std::cout << (a / b).first << "\n";
            break;
        case '%':
            std::cout << (a / b).second << "\n";
            break;
        default:
            break;
        }
    }
    system("pause");
    return 0;
}