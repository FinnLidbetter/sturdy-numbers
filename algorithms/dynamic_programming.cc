#include "dynamic_programming.h"

// Dynamic programming implementation for the 4 functions
// of interest.

int DynamicProgramming::is_sturdy(long long int n) {
  // Complexity: O(n^2 log n)
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return STURDY;
  }
  if (baby_step_giant_step(n) > 0) {
    // If 2^x mod n = n - 1 for some x, then
    // 2^x + 1 is a multiple of n using only 2 bits.
    return NOT_STURDY;
  }
  std::vector<long long int> pow_list = get_powers(n);
  long long int ord = pow_list.size();
  
  long long int pows[ord];
  for (int i = 0; i < ord; i++) {
    pows[i] = pow_list.at(i);
  }
  // reachable[i][j][r] is true iff we can represent
  // j mod n as the sum of i powers of 2 (without 
  // repetition), considering only the first r powers 
  // of 2.
  bool ***reachable;
  reachable = new bool**[num_set_bits];
  for (size_t i = 0; i < num_set_bits; i++) {
    reachable[i] = new bool*[n];
    for (size_t j = 0; j < n; j++) {
      reachable[i][j] = new bool[ord + 1];
      for (size_t k = 0; k < ord + 1; k++) {
        if (i > 0 || j > 0) {
          reachable[i][j][k] = false;
        } else {
          reachable[i][j][k] = true;
        }
      }
    }
  }
  
  for (long long int r = 1; r <= ord; r++) {
    for (long long int j = 0; j < n; j++) {
      long long int prev_res = j - pows[r-1];
      if (prev_res < 0) {
        prev_res += n;
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
      clean_up_reachable(reachable, num_set_bits, n);
      return NOT_STURDY;
    }
  }
  clean_up_reachable(reachable, num_set_bits, n);
  return STURDY;
}

int DynamicProgramming::swm(long long int n) {
  // Complexity: O(n^2 log n)
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return num_set_bits;
  }
  if (baby_step_giant_step(n) > 0) {
    // If 2^x mod n = n - 1 for some x, then
    // 2^x + 1 is a multiple of n using only 2 bits.
    return 2;
  }
  std::vector<long long int> pow_list = get_powers(n);
  long long int ord = pow_list.size();
  
  long long int pows[ord];
  for (int i = 0; i < ord; i++) {
    pows[i] = pow_list.at(i);
  }
  const mp::mpz_int ONE = 1;
  const mp::mpz_int INF = ONE << ord;
  
  // min_valid[i][j][r] is the smallest integer congruent to
  // j mod n that is the sum of exactly i powers of 2 
  // (modulo n), considering only the first r powers of 2,
  // without repetitions.
  bool ***reachable;
  mp::mpz_int ***min_valid;
  reachable = new bool**[num_set_bits];
  min_valid = new mp::mpz_int**[num_set_bits];
  for (size_t i = 0; i < num_set_bits; i++) {
    reachable[i] = new bool*[n];
    min_valid[i] = new mp::mpz_int*[n];
    for (size_t j = 0; j < n; j++) {
      reachable[i][j] = new bool[ord + 1];
      min_valid[i][j] = new mp::mpz_int[ord + 1];
      for (size_t k = 0; k < ord + 1; k++) {
        reachable[i][j][k] = false;
        min_valid[i][j][k] = INF;
      }
    }
  }
  DynamicProgramming::fill_tables(reachable, min_valid, pows, num_set_bits, n, ord);
  for (int i = 2; i < num_set_bits; i++) {
    if (reachable[i][0][ord]) {
      clean_up_reachable(reachable, num_set_bits, n);
      clean_up_min_valid(min_valid, num_set_bits, n);
      return i;
    }
  }
  clean_up_reachable(reachable, num_set_bits, n);
  clean_up_min_valid(min_valid, num_set_bits, n);
  return num_set_bits;
}

mp::mpz_int DynamicProgramming::msw(long long int n) {
  // Complexity: O(n^2 log n)
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return 1;
  }
  std::vector<long long int> pow_list = get_powers(n);
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
    reachable[i] = new bool*[n];
    min_valid[i] = new mp::mpz_int*[n];
    for (size_t j = 0; j < n; j++) {
      reachable[i][j] = new bool[ord + 1];
      min_valid[i][j] = new mp::mpz_int[ord + 1];
      for (size_t k = 0; k < ord + 1; k++) {
        reachable[i][j][k] = false;
        min_valid[i][j][k] = INF;
      }
    }
  }
  DynamicProgramming::fill_tables(reachable, min_valid, pows, num_set_bits, n, ord);
  for (int i = 2; i < num_set_bits; i++) {
    if (reachable[i][0][ord]) {
      clean_up_reachable(reachable, num_set_bits, n);
      clean_up_min_valid(min_valid, num_set_bits, n);
      return min_valid[i][0][ord] / n;
    }
  }
  clean_up_reachable(reachable, num_set_bits, n);
  clean_up_min_valid(min_valid, num_set_bits, n);
  return mp::mpz_int(1);
}

mp::mpz_int DynamicProgramming::mfw(long long int n) {
  // Complexity: O(n^2 log n)
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return mp::mpz_int(0);
  }
  std::vector<long long int> pow_list = get_powers(n);
  int ord = pow_list.size();
  
  long long int pows[ord];
  for (int i = 0; i < ord; i++) {
    pows[i] = pow_list.at(i);
  }
  const mp::mpz_int ONE = 1;
  // The minimum flimsy witness, if it exists, is guaranteed 
  // to be less than 2^ord. So use this as a 'n for infinity'.
  const mp::mpz_int INF = ONE << ord;
  bool ***reachable;
  mp::mpz_int ***min_valid;
  reachable = new bool**[num_set_bits];
  min_valid = new mp::mpz_int**[num_set_bits];
  for (size_t i = 0; i < num_set_bits; i++) {
    reachable[i] = new bool*[n];
    min_valid[i] = new mp::mpz_int*[n];
    for (size_t j = 0; j < n; j++) {
      reachable[i][j] = new bool[ord + 1];
      min_valid[i][j] = new mp::mpz_int[ord + 1];
      for (size_t k = 0; k < ord + 1; k++) {
        reachable[i][j][k] = false;
        min_valid[i][j][k] = INF;
      }
    }
  }
  DynamicProgramming::fill_tables(reachable, min_valid, pows, num_set_bits, n, ord);
  mp::mpz_int mfw = INF;
  for (int i = num_set_bits - 1; i >= 1; i--) {
    if (reachable[i][0][ord]) {
      if (min_valid[i][0][ord] < mfw) {
        mfw = min_valid[i][0][ord];
      }
    }
  }

  clean_up_reachable(reachable, num_set_bits, n);
  clean_up_min_valid(min_valid, num_set_bits, n);
  if (mfw == INF) {
    return mp::mpz_int(0);
  }
  return mfw / n;
}

void DynamicProgramming::clean_up_reachable(bool ***reachable, int num_set_bits, long long int n) {
  for (size_t i = 0; i < num_set_bits; i++) {
    for (size_t j=0; j < n; j++) {
      delete [] reachable[i][j];
    }
    delete [] reachable[i];
  }
  delete [] reachable;
}

void DynamicProgramming::clean_up_min_valid(mp::mpz_int ***min_valid, int num_set_bits, long long int n) {
  for (size_t i = 0; i < num_set_bits; i++) {
    for (size_t j=0; j < n; j++) {
      delete [] min_valid[i][j];
    }
    delete [] min_valid[i];
  }
  delete [] min_valid;
}

void DynamicProgramming::fill_tables(bool ***reachable, 
                                     mp::mpz_int ***min_valid, 
                                     long long int *pows,
                                     int num_set_bits,
                                     long long int n,
                                     long long int ord) {
  // The dynamic programming part of the algorithm to populate
  // min_valid and reachable.
  const mp::mpz_int ONE = 1;
  // Initialize the arrays.
  for (int r = 0; r <= ord; r++) {
    for (int i = 0; i < num_set_bits; i++) {
      for (int j = 0; j < n; j++) {
        reachable[i][j][r] = false;
        // If there is a smallest representation for j mod n,
        // it is guaranteed to be less than 2^ord. So this serves
        // as a 'n for infinity'.
        min_valid[i][j][r] = ONE << ord;
      }
    }
    reachable[0][0][r] = true;
    min_valid[0][0][r] = mp::mpz_int(0);
  }
  for (int r = 1; r <= ord; r++) {
    for (int j = 0; j < n; j++) {
      long long int prev_res = j - pows[r-1];
      if (prev_res < 0) {
        prev_res += n;
      }
      for (int i = 1; i < num_set_bits; i++) {
        reachable[i][j][r] = reachable[i][j][r-1];
        min_valid[i][j][r] = mp::mpz_int(min_valid[i][j][r-1]);
        if (reachable[i-1][prev_res][r-1]) {
          reachable[i][j][r] = true;
          // Try using the current power of 2.
          mp::mpz_int sum = min_valid[i-1][prev_res][r-1] | (ONE << (r-1));
          if (sum < min_valid[i][j][r]) {
            min_valid[i][j][r] = sum;
          }
        }
      }
    }
  }
}
