
#ifndef UltraCore_hash_h
#define UltraCore_hash_h

#include <vector>

/*
Myrvold & Ruskey Hash Function
http://citeseerx.ist.psu.edu/viewdoc/download;jsessionid=D01128EA46AB84979443C3FD5A092A22?doi=10.1.1.43.4521&rep=rep1&type=pdf
*/
template<typename T>
size_t mr_hash(int n, T & Pi, T & PiInv)
{
    if(n == 1)
        return 0;

    int s = Pi[n-1];
    std::swap(Pi[n-1], Pi[PiInv[n-1]]);
    std::swap(PiInv[s], PiInv[n-1]);
    return s + n * mr_hash(n-1, Pi, PiInv);
}

template<typename T>
size_t mr_hash(int _n, T & Pi, T & PiInv, std::vector<size_t> & cache)
{
    size_t res(0);
    for (int n = _n; n > 1; --n)
    {
        int s = Pi[n - 1];
        std::swap(Pi[n - 1], Pi[PiInv[n - 1]]);
        std::swap(PiInv[s], PiInv[n - 1]);
        cache[n - 2] = s;
    }

    for (int i = 0; i < _n-1; ++i)
        res = cache[i] + (i+2) * res;

    return res;
}

#endif
