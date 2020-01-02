#include "common.h"

long long int baby_step_giant_step(long long int mod) {
  long long int target = mod - 1;
  if (mod % 2 == 0) {
    return -1;
  }
  long long int sqrt_ceil = static_cast<long long int>(std::ceil(std::sqrt(mod)));
  long long int pow = 1;
  std::unordered_map<long long int, long long int> lookup_table = std::unordered_map<long long int, long long int>();
  for (long long int exp = 0; exp < sqrt_ceil; exp++) {
    lookup_table[pow] = exp;
    pow *= 2;
    if (pow >= mod) {
      pow %= mod;
    }
  }
  long long int giant_step_neg_pow = 1;
  for (long long int neg_exp = 1; neg_exp <= sqrt_ceil; neg_exp++) {
    if (giant_step_neg_pow % 2 == 0) {
      giant_step_neg_pow /= 2;
    } else {
      giant_step_neg_pow = (giant_step_neg_pow + mod) / 2;
    }
  }
  long long int curr_giant_step_pow = 1;
  for (long long int giant_step_exp = 0; giant_step_exp < sqrt_ceil; giant_step_exp++) {
    long long int required_baby_step = (curr_giant_step_pow * target) % mod;
    if (lookup_table.find(required_baby_step) != lookup_table.end()) {
      return giant_step_exp * sqrt_ceil + lookup_table[required_baby_step];
    }
  }
  return -1;
}

int count_set_bits(long long int value) {
  // Return the number of set bits in `value`.
  long long int copy = value;
  int num_set_bits = 0;
  while (copy > 0) {
    if ((copy & 1) > 0) {
      num_set_bits++;
    }
    copy >>= 1;
  }
  return num_set_bits;
}

std::vector<long long int> get_powers(long long int value) {
  // Get a list of the powers of 2 modulo `value`.
  std::unordered_set<long long int> pow_set;
  std::vector<long long int> pow_list;
  long long int pow = 1;
  while (pow_set.find(pow) == pow_set.end()) {
    pow_set.insert(pow);
    pow_list.push_back(pow);
    pow <<= 1;
    if (pow >= value)
      pow -= value;
  }
  return pow_list;
}


