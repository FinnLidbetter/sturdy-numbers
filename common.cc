#include "common.h"

long long int baby_step_giant_step(long long int n) {
  long long int target = n - 1;
  if (n % 2 == 0) {
    return -1;
  }
  long long int sqrt_ceil = static_cast<long long int>(std::ceil(std::sqrt(n)));
  long long int pow = 1;
  std::unordered_map<long long int, long long int> lookup_table = std::unordered_map<long long int, long long int>();
  for (long long int exp = 0; exp < sqrt_ceil; exp++) {
    lookup_table[pow] = exp;
    pow *= 2;
    if (pow >= n) {
      pow %= n;
    }
  }
  long long int giant_step_neg_pow = 1;
  for (long long int neg_exp = 1; neg_exp <= sqrt_ceil; neg_exp++) {
    if (giant_step_neg_pow % 2 == 0) {
      giant_step_neg_pow /= 2;
    } else {
      giant_step_neg_pow = (giant_step_neg_pow + n) / 2;
    }
  }
  long long int curr_giant_step_pow = 1;
  for (long long int giant_step_exp = 0; giant_step_exp < sqrt_ceil; giant_step_exp++) {
    long long int required_baby_step = (curr_giant_step_pow * target) % n;
    if (lookup_table.find(required_baby_step) != lookup_table.end()) {
      return giant_step_exp * sqrt_ceil + lookup_table[required_baby_step];
    }
    curr_giant_step_pow *= giant_step_neg_pow;
    if (curr_giant_step_pow >= n) {
      curr_giant_step_pow %= n;
    }
  }
  return -1;
}

int count_set_bits(long long int n) {
  // Return the number of set bits in n.
  long long int copy = n;
  int num_set_bits = 0;
  while (copy > 0) {
    if ((copy & 1) > 0) {
      num_set_bits++;
    }
    copy >>= 1;
  }
  return num_set_bits;
}

std::vector<long long int> get_powers(long long int n) {
  // Get a list of the powers of 2 nulo n.
  std::unordered_set<long long int> pow_set;
  std::vector<long long int> pow_list;
  long long int pow = 1;
  while (pow_set.find(pow) == pow_set.end()) {
    pow_set.insert(pow);
    pow_list.push_back(pow);
    pow <<= 1;
    if (pow >= n)
      pow -= n;
  }
  return pow_list;
}


