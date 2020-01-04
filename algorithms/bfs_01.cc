#include "bfs_01.h"

int Bfs01::is_sturdy(long long int n) {
  // Complexity: O(n)
  int num_set_bits = count_set_bits(n);
  int swm = Bfs01::swm(n);
  if (num_set_bits == swm) {
    return STURDY;
  }
  return NOT_STURDY;
}

int Bfs01::swm(long long int n) {
  // Complexity: O(n)
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return num_set_bits;
  }
  if (baby_step_giant_step(n) > 0) {
    return 2;
  }
  bool vis[n];
  for (long long int i = 0; i < n; i++) {
    vis[i] = false;
  }
  std::deque<long long int> q;
  q.push_back(1);
  // Use -1 as a delimiter to track the depth.
  q.push_back(-1);
  int depth = 1;
  long long int curr_res, next_res;
  while (q.size() > 1) {
    curr_res = q.front();
    q.pop_front();
    if (curr_res == -1) {
      q.push_back(-1);
      depth++;
      continue;
    }
    if (vis[curr_res]) {
      continue;
    }
    vis[curr_res] = true;
    if (curr_res == 0) {
      return depth;
    }
    next_res = curr_res * 2;
    if (next_res >= n) {
      next_res -= n;
    }
    q.push_front(next_res);
    next_res++;
    if (next_res >= n) {
      next_res -= n;
    }
    q.push_back(next_res);
  }
  return num_set_bits;
}

mp::mpz_int Bfs01::msw(long long int n) {
  // Complexity: O(n log(n))
  // With the exception of the function used to calculate
  // swm, this function is identical to that of Automaton::msw
  int num_set_bits = count_set_bits(n);
  int swm = Bfs01::swm(n);
  if (num_set_bits == swm) {
    return mp::mpz_int(1);
  }
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

mp::mpz_int Bfs01::mfw(long long int n) {
  // Complexity: O(n log n)
  // This implementation is identical to that of
  // Automaton::mfw.
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return mp::mpz_int(0);
  }
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
  bool found = false;
  for (int i = 2; i < num_set_bits; i++) {
    if (vis[i][0]) {
      found = true;
    }
  }
  if (!found) {
    return mp::mpz_int(0);
  }
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

