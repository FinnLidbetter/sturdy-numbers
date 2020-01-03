#ifndef COMMON_H
#define COMMON_H

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <boost/multiprecision/gmp.hpp>

namespace mp = boost::multiprecision;

class Algorithm {
  public:
    virtual int is_sturdy(long long int value) = 0;
    virtual int swm(long long int value) = 0;
    virtual mp::mpz_int msw(long long int value) = 0;
    virtual mp::mpz_int mfw(long long int value) = 0;
};

long long int baby_step_giant_step(long long int mod);

int count_set_bits(long long int value);

std::vector<long long int> get_powers(long long int value);

#endif /* COMMON_H definition */
