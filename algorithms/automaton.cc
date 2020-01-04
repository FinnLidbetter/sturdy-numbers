#include "automaton.h"

// Basic breadth first search on a graph
// given by a product automaton.

int Automaton::is_sturdy(long long int n) {
  // Complexity: O(n log(n))
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return STURDY;
  }
  int swm = Automaton::swm(n);
  if (num_set_bits == swm) {
    return STURDY;
  }
  return NOT_STURDY;
}

int Automaton::swm(long long int n) {
  // Complexity: O(n log(n))
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return num_set_bits;
  }
  if (baby_step_giant_step(n) > 0) {
    // If there exists x such that 
    // 2^x mod n = n - 1, then
    // 2^x + 1 is a multiple of n.
    return 2;
  }
  
  // Perform a breadth-first-search on the
  // corresponding product automaton.
  
  int curr_bits;
  long long int curr_res, next_res;
  bool vis[num_set_bits][n];
  std::queue<long long int> res_q;
  std::queue<long long int> dig_q;
  for (int i = 0; i < num_set_bits; i++) {
    for (int j = 0; j < n; j++) {
      vis[i][j] = false;
    }
  }
  vis[1][1] = true;
  res_q.push(1);
  dig_q.push(1);
  while (res_q.size() > 0) {
    curr_res = res_q.front();
    res_q.pop();
    curr_bits = dig_q.front();
    dig_q.pop();
    next_res = curr_res * 2;
    if (next_res >= n) {
      next_res -= n;
    }
    if (!vis[curr_bits][next_res]) {
      res_q.push(next_res);
      dig_q.push(curr_bits);
      vis[curr_bits][next_res] = true;
    }
    next_res++;
    if (next_res >= n) {
      next_res -= n;
    }
    if (curr_bits < num_set_bits - 1 && !vis[curr_bits + 1][next_res]) {
      res_q.push(next_res);
      dig_q.push(curr_bits + 1);
      vis[curr_bits + 1][next_res] = true;
    }
  }
  for (int i = 1; i < num_set_bits; i++) {
    if (vis[i][0]) {
      return i;
    }
  }
  return num_set_bits;
}

mp::mpz_int Automaton::msw(long long int n) {
  // Complexity: O(n log(n))
  int num_set_bits = count_set_bits(n);
  // Get the minimum number of powers of 2 needed.
  int swm = Automaton::swm(n);
  if (num_set_bits == swm) {
    return mp::mpz_int(1);
  }
  // Perform a breadth first search on the corresponding
  // product automaton, keeping track of the minimum
  // integer corresponding to each state.
  bool vis[swm + 1][n];
  long long int prev_res[swm + 1][n];
  int prev_dig[swm + 1][n];
  for (int i = 0; i <= swm; i++) {
    for (int j = 0; j < n; j++) {
      vis[i][j] = false;
      prev_res[i][j] = -1;
      prev_dig[i][j] = -1;
    }
  }
  std::queue<long long int> res_q;
  std::queue<int> dig_q;
  long long int curr_res, next_res;
  int curr_bits;
  res_q.push(1);
  dig_q.push(1);
  vis[1][1] = true;
  prev_res[1][1] = 0;
  prev_dig[1][1] = 1;
  while (res_q.size() > 0) {
    curr_res = res_q.front();
    res_q.pop();
    curr_bits = dig_q.front();
    dig_q.pop();
    if (curr_res == 0) {
      break;
    }
    next_res = curr_res * 2;
    if (next_res >= n) {
      next_res -= n;
    }
    if (!vis[curr_bits][next_res]) {
      res_q.push(next_res);
      dig_q.push(curr_bits);
      vis[curr_bits][next_res] = true;
      prev_dig[curr_bits][next_res] = 0;
      prev_res[curr_bits][next_res] = curr_res;
    }
    next_res++;
    if (next_res >= n) {
      next_res -= n;
    }
    if (curr_bits < swm && !vis[curr_bits + 1][next_res]) {
      res_q.push(next_res);
      dig_q.push(curr_bits + 1);
      vis[curr_bits + 1][next_res] = true;
      prev_dig[curr_bits + 1][next_res] = 1;
      prev_res[curr_bits + 1][next_res] = curr_res;
    }
  }
  // Re-construct the optimal integer using the
  // values stored during the breadth first search.
  curr_res = 0;
  curr_bits = swm;
  mp::mpz_int min_product = 0;
  const mp::mpz_int ONE = 1;
  int index = 0;
  do {
    int dig = prev_dig[curr_bits][curr_res];
    curr_res = prev_res[curr_bits][curr_res];
    min_product |= (ONE << index) * dig;
    if (dig > 0) 
      curr_bits--;
    index++;
  } while (curr_res != 0);
  return min_product / n;
}

mp::mpz_int Automaton::mfw(long long int n) {
  // Complexity: O(n log n)
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return mp::mpz_int(0);
  }
  // Perform a breadth-first-search on the appropriate
  // product automaton. (The direct product of the automaton
  // accepting strings with at most (num_set_bits - 1) 1's
  // and the automaton accepting strings corresponding to
  // multiples of n.
  bool vis[num_set_bits][n];
  long long int prev_res[num_set_bits][n];
  int prev_dig[num_set_bits][n];
  for (int i = 0; i < num_set_bits; i++) {
    for (int j = 0; j < n; j++) {
      vis[i][j] = false;
      prev_res[i][j] = -1;
      prev_dig[i][j] = -1;
    }
  }
  std::queue<long long int> res_q;
  std::queue<int> dig_q;
  long long int curr_res, next_res;
  int curr_bits;
  res_q.push(1);
  dig_q.push(1);
  vis[1][1] = true;
  prev_res[1][1] = 0;
  prev_dig[1][1] = 1;
  while (res_q.size() > 0) {
    curr_res = res_q.front();
    res_q.pop();
    curr_bits = dig_q.front();
    dig_q.pop();
    next_res = curr_res * 2;
    if (next_res >= n) {
      next_res -= n;
    }
    if (!vis[curr_bits][next_res]) {
      res_q.push(next_res);
      dig_q.push(curr_bits);
      vis[curr_bits][next_res] = true;
      prev_dig[curr_bits][next_res] = 0;
      prev_res[curr_bits][next_res] = curr_res;
    }
    next_res++;
    if (next_res >= n) {
      next_res -= n;
    }
    if (curr_bits < num_set_bits - 1 && !vis[curr_bits + 1][next_res]) {
      res_q.push(next_res);
      dig_q.push(curr_bits + 1);
      vis[curr_bits + 1][next_res] = true;
      prev_dig[curr_bits + 1][next_res] = 1;
      prev_res[curr_bits + 1][next_res] = curr_res;
    }
  }
  // Check if n is sturdy, based on the states reached.
  bool found = false;
  for (int i = 2; i < num_set_bits; i++) {
    if (vis[i][0]) {
      found = true;
    }
  }
  if (!found) {
    return mp::mpz_int(0);
  }
  // Re-construct the smallest multiple of n for each
  // number of 1's for which an accepting state is reached.
  const mp::mpz_int ONE = 1;
  const mp::mpz_int INF = ONE << n;
  mp::mpz_int mfw = INF;
  for (int i = 2; i < num_set_bits; i++) {
    if (vis[i][0]) {
      curr_res = 0;
      curr_bits = i;
      mp::mpz_int product = 0;
      int index = 0;
      do {
        int dig = prev_dig[curr_bits][curr_res];
        curr_res = prev_res[curr_bits][curr_res];
        product |= (ONE << index) * dig;
        if (dig > 0) 
          curr_bits--;
        index++;
      } while (curr_res != 0);
      if (product < mfw) {
        mfw = product;
      }
    }
  }
  return mfw;
}
