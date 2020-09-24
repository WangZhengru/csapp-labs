#include <bits/stdc++.h>

#include "bits.c"

using namespace std;

int main()
{
    int MIN = INT_MIN;
    int MAX = INT_MAX;
    // printf("%x", !(MIN ^ (~MIN)));
    // printf("%x %d\n", MAX, MAX + 1);
    int x = MIN;
    // cout << (!!((~(x + 1)) ^ (x + 1))) << endl;
    // printf("%x", MIN >> 31);
    // printf("%x", ~0 + 1);
    int sgn = !(x >> 31);
    // printf("%x %x\n", f, g);
    // printf("%d\n", howManyBits(x));
    // printf("%x\n", sgn);
    // cout << howManyBits(12) << endl;
    // cout << howManyBits(298) << endl;
    // cout << howManyBits(-5) << endl;
    // cout << howManyBits(0) << endl;
    // cout << howManyBits(-1) << endl;
    // cout << howManyBits(0x80000000) << endl;
    // printf("%x", (1 << (-126)));
    cout << 0xfd << endl;
    // howManyBits(12) = 5
    // howManyBits(298) = 10
    // howManyBits(-5) = 4
    // howManyBits(0)  = 1
    // howManyBits(-1) = 1
    // howManyBits(0x80000000) = 32
    return 0;
}