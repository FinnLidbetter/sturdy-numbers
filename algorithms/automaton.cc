#include "automaton.h"

int Automaton::is_sturdy(long long int value) {
  int num_set_bits = count_set_bits(value);
  int swm = Automaton::swm(value);
  if (num_set_bits == swm) {
    return 1;
  }
  return 0;
}

int Automaton::swm(long long int value) {
  int num_set_bits = count_set_bits(value);
  if (num_set_bits <= 2) {
    return num_set_bits;
  }
  int lo = 2;
  int hi = num_set_bits - 1;
  int mid, curr_bits;
  long long int curr_res, next_res;
  int best = num_set_bits;
  while (lo <= hi) {
    mid = lo + (hi - lo) / 2;
    bool vis[mid + 1][value];
    std::queue<long long int> res_q;
    std::queue<long long int> dig_q;
    for (int i = 0; i <= mid; i++) {
      for (int j = 0; j < value; j++) {
        vis[i][j] = false;
      }
    }
    vis[1][1] = true;
    res_q.push(1);
    dig_q.push(1);
    bool found = false;
    while (res_q.size() > 0) {
      curr_res = res_q.front();
      res_q.pop();
      curr_bits = dig_q.front();
      dig_q.pop();
      if (curr_res == 0) {
        found = true;
        break;
      }
      next_res = curr_res * 2;
      if (next_res >= value) {
        next_res -= value;
      }
      if (!vis[curr_bits][next_res]) {
        res_q.push(next_res);
        dig_q.push(curr_bits);
        vis[curr_bits][next_res] = true;
      }
      next_res++;
      if (next_res >= value) {
        next_res -= value;
      }
      if (curr_bits < mid && !vis[curr_bits + 1][next_res]) {
        res_q.push(next_res);
        dig_q.push(curr_bits + 1);
        vis[curr_bits + 1][next_res] = true;
      }
    }
    if (found) {
      best = mid;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return best;
}

mp::mpz_int Automaton::msw(long long int value) {
  int num_set_bits = count_set_bits(value);
  int swm = Automaton::swm(value);
  if (num_set_bits == swm) {
    return mp::mpz_int(1);
  }
  bool vis[swm + 1][value];
  long long int prev_res[swm + 1][value];
  int prev_dig[swm + 1][value];
  for (int i = 0; i <= swm; i++) {
    for (int j = 0; j < value; j++) {
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
    if (next_res >= value) {
      next_res -= value;
    }
    if (!vis[curr_bits][next_res]) {
      res_q.push(next_res);
      dig_q.push(curr_bits);
      vis[curr_bits][next_res] = true;
      prev_dig[curr_bits][next_res] = 0;
      prev_res[curr_bits][next_res] = curr_res;
    }
    next_res++;
    if (next_res >= value) {
      next_res -= value;
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
  return min_product / value;
}

mp::mpz_int Automaton::mfw(long long int value) {
  int num_set_bits = count_set_bits(value);
  if (num_set_bits <= 2) {
    return mp::mpz_int(0);
  }
  bool vis[num_set_bits][value];
  long long int prev_res[num_set_bits][value];
  int prev_dig[num_set_bits][value];
  for (int i = 0; i < num_set_bits; i++) {
    for (int j = 0; j < value; j++) {
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
    if (next_res >= value) {
      next_res -= value;
    }
    if (!vis[curr_bits][next_res]) {
      res_q.push(next_res);
      dig_q.push(curr_bits);
      vis[curr_bits][next_res] = true;
      prev_dig[curr_bits][next_res] = 0;
      prev_res[curr_bits][next_res] = curr_res;
    }
    next_res++;
    if (next_res >= value) {
      next_res -= value;
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
  const mp::mpz_int INF = ONE << value;
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
