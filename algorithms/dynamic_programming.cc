#include "dynamic_programming.h"

int DynamicProgramming::is_sturdy(long long int value) {
  int num_set_bits = count_set_bits(value);
  if (num_set_bits <= 2) {
    return 1;
  }
  std::vector<long long int> pow_list = get_powers(value);
  long long int ord = pow_list.size();
  
  long long int pows[ord];
  for (int i = 0; i < ord; i++) {
    pows[i] = pow_list.at(i);
  }
  
  bool reachable[num_set_bits][value][ord + 1];

  for (long long int r = 0; r <= ord; r++) {
    for (int i = 0; i < num_set_bits; i++) {
      for (long long int j = 0; j < value; j++) {
        reachable[i][j][r] = false;
      }
    }
    reachable[0][0][r] = true;
  }
  for (long long int r = 1; r <= ord; r++) {
    for (long long int j = 0; j < value; j++) {
      long long int prev_res = j - pows[r-1];
      if (prev_res < 0) {
        prev_res += value;
      }
      for (int i = 1; i < num_set_bits; i++) {
        reachable[i][j][r] = reachable[i][j][r-1];
        if (reachable[i-1][prev_res][r-1]) {
          reachable[i][j][r] = true;
        }
      }
    }
  }
  for (int i = 2; i < num_set_bits; i++) {
    if (reachable[i][0][ord]) {
      return 0;
    }
  }

  return 1;
}

int DynamicProgramming::swm(long long int value) {
  int num_set_bits = count_set_bits(value);
  if (num_set_bits <= 2) {
    return num_set_bits;
  }
  std::vector<long long int> pow_list = get_powers(value);
  long long int ord = pow_list.size();
  
  long long int pows[ord];
  for (int i = 0; i < ord; i++) {
    pows[i] = pow_list.at(i);
  }
  const mp::mpz_int ONE = 1;
  const mp::mpz_int INF = ONE << ord;
  bool ***reachable;
  mp::mpz_int ***min_valid;
  reachable = new bool**[num_set_bits];
  min_valid = new mp::mpz_int**[num_set_bits];
  for (size_t i = 0; i < num_set_bits; i++) {
    reachable[i] = new bool*[value];
    min_valid[i] = new mp::mpz_int*[value];
    for (size_t j = 0; j < value; j++) {
      reachable[i][j] = new bool[ord + 1];
      min_valid[i][j] = new mp::mpz_int[ord + 1];
      for (size_t k = 0; k < ord + 1; k++) {
        reachable[i][j][k] = false;
        min_valid[i][j][k] = INF;
      }
    }
  }
  DynamicProgramming::fill_tables(reachable, min_valid, pows, num_set_bits, value, ord);
  for (int i = 2; i < num_set_bits; i++) {
    if (reachable[i][0][ord]) {
      return i;
    }
  }
  return num_set_bits;
}

mp::mpz_int DynamicProgramming::msw(long long int value) {
  int num_set_bits = count_set_bits(value);
  if (num_set_bits <= 2) {
    return 1;
  }
  std::vector<long long int> pow_list = get_powers(value);
  int ord = pow_list.size();
  
  long long int pows[ord];
  for (int i = 0; i < ord; i++) {
    pows[i] = pow_list.at(i);
  }
  const mp::mpz_int ONE = 1;
  const mp::mpz_int INF = ONE << ord;
  bool ***reachable;
  mp::mpz_int ***min_valid;
  reachable = new bool**[num_set_bits];
  min_valid = new mp::mpz_int**[num_set_bits];
  for (size_t i = 0; i < num_set_bits; i++) {
    reachable[i] = new bool*[value];
    min_valid[i] = new mp::mpz_int*[value];
    for (size_t j = 0; j < value; j++) {
      reachable[i][j] = new bool[ord + 1];
      min_valid[i][j] = new mp::mpz_int[ord + 1];
      for (size_t k = 0; k < ord + 1; k++) {
        reachable[i][j][k] = false;
        min_valid[i][j][k] = INF;
      }
    }
  }
  DynamicProgramming::fill_tables(reachable, min_valid, pows, num_set_bits, value, ord);
  for (int i = 2; i < num_set_bits; i++) {
    if (reachable[i][0][ord]) {
      return min_valid[i][0][ord] / value;
    }
  }
  return mp::mpz_int(1);
}

mp::mpz_int DynamicProgramming::mfw(long long int value) {
  int num_set_bits = count_set_bits(value);
  if (num_set_bits <= 2) {
    return mp::mpz_int(0);
  }
  std::vector<long long int> pow_list = get_powers(value);
  int ord = pow_list.size();
  
  long long int pows[ord];
  for (int i = 0; i < ord; i++) {
    pows[i] = pow_list.at(i);
  }
  const mp::mpz_int ONE = 1;
  const mp::mpz_int INF = ONE << ord;
  bool ***reachable;
  mp::mpz_int ***min_valid;
  reachable = new bool**[num_set_bits];
  min_valid = new mp::mpz_int**[num_set_bits];
  for (size_t i = 0; i < num_set_bits; i++) {
    reachable[i] = new bool*[value];
    min_valid[i] = new mp::mpz_int*[value];
    for (size_t j = 0; j < value; j++) {
      reachable[i][j] = new bool[ord + 1];
      min_valid[i][j] = new mp::mpz_int[ord + 1];
      for (size_t k = 0; k < ord + 1; k++) {
        reachable[i][j][k] = false;
        min_valid[i][j][k] = INF;
      }
    }
  }
  DynamicProgramming::fill_tables(reachable, min_valid, pows, num_set_bits, value, ord);
  mp::mpz_int mfw = INF;
  for (int i = num_set_bits - 1; i >= 1; i--) {
    if (reachable[i][0][ord]) {
      if (min_valid[i][0][ord] < mfw) {
        mfw = min_valid[i][0][ord];
      }
    }
  }
  if (mfw == INF) {
    return mp::mpz_int(0);
  }
  return mfw;
}

void DynamicProgramming::fill_tables(bool ***reachable, 
                                     mp::mpz_int ***min_valid, 
                                     long long int *pows,
                                     int num_set_bits,
                                     long long int value,
                                     long long int ord) {
  const mp::mpz_int ONE = 1;
  for (int r = 0; r <= ord; r++) {
    for (int i = 0; i < num_set_bits; i++) {
      for (int j = 0; j < value; j++) {
        reachable[i][j][r] = false;
        min_valid[i][j][r] = ONE << ord;
      }
    }
    reachable[0][0][r] = true;
    min_valid[0][0][r] = mp::mpz_int(0);
  }
  for (int r = 1; r <= ord; r++) {
    for (int j = 0; j < value; j++) {
      long long int prev_res = j - pows[r-1];
      if (prev_res < 0) {
        prev_res += value;
      }
      for (int i = 1; i < num_set_bits; i++) {
        reachable[i][j][r] = reachable[i][j][r-1];
        min_valid[i][j][r] = mp::mpz_int(min_valid[i][j][r-1]);
        if (reachable[i-1][prev_res][r-1]) {
          reachable[i][j][r] = true;
          mp::mpz_int sum = min_valid[i-1][prev_res][r-1] | (ONE << (r-1));
          if (sum < min_valid[i][j][r]) {
            min_valid[i][j][r] = sum;
          }
        }
      }
    }
  }
}
