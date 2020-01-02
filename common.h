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
    static int is_sturdy(long long int value);
    static int swm(long long int value);
    static int msw(long long int value);
    static int mfw(long long int value);

    static int * is_sturdy_range(long long int value_min, long long int value_max);
    static int * swm_range(long long int value_min, long long int value_max);
    static int * msw_range(long long int value_min, long long int value_max);
    static int * mfw_range(long long int value_min, long long int value_max);


  private:
    static int * test_range(long long int value_min, long long int value_max, int (*func)(long long int));

};

long long int baby_step_giant_step(long long int mod);

int count_set_bits(long long int value);

std::vector<long long int> get_powers(long long int value);

#endif /* COMMON_H definition */
