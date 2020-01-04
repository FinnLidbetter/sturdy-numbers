#ifndef COMMON_H
#define COMMON_H

#include <queue>
#include <map>
#include <unordered_set>
#include <vector>
#include <boost/multiprecision/gmp.hpp>

namespace mp = boost::multiprecision;

class Algorithm {
  public:
    virtual int is_sturdy(long long int n) = 0;
    virtual int swm(long long int n) = 0;
    virtual mp::mpz_int msw(long long int n) = 0;
    virtual mp::mpz_int mfw(long long int n) = 0;
};

const int STURDY = 1;
const int NOT_STURDY = 0;

long long int baby_step_giant_step(long long int n);

int count_set_bits(long long int n);

std::vector<long long int> get_powers(long long int n);

#endif /* COMMON_H definition */
