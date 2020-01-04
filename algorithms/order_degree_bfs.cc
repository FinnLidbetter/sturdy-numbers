#include "order_degree_bfs.h"

int OrderDegreeBfs::is_sturdy(long long int n) {
  // Complexity O(n log(n))
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return STURDY;
  }
  if (baby_step_giant_step(n) > 0) {
    return NOT_STURDY;
  }
  std::vector<long long int> pows_vector = get_powers(n);
  long long int n_pows = pows_vector.size();
  long long int pows[n_pows];
  for (long long int i = 0; i < n_pows; i++) {
    pows[i] = pows_vector.at(i);
  }
  
  int depth = 0;
  std::queue<long long int> q;
  int dist[n];
  for (int i = 0; i < n; i++) {
    dist[i] = -1;
  }
  // Use -1 as a special n that will be treated like 0,
  // but will not trigger the break condition immediately.
  const long long int INITIAL_ZERO = -1;
  q.push(INITIAL_ZERO);
  // Use -2 as a delimiter to track the depth.
  const long long int DELIMITER = -2;
  q.push(DELIMITER);
  long long int curr_res, next_res;
  while (q.size() > 1 && depth < num_set_bits) {
    curr_res = q.front();
    q.pop();
    if (curr_res == DELIMITER) {
      depth++;
      q.push(DELIMITER);
      continue;
    }
    if (curr_res == 0) {
      return dist[curr_res];
    }
    if (curr_res == INITIAL_ZERO) {
      curr_res = 0;
    }
    for (long long int index = 0; index < n_pows; index++) {
      next_res = curr_res + pows[index];
      if (next_res >= n) {
        next_res -= n;
      }
      if (dist[next_res] == -1) {
        dist[next_res] = depth + 1;
        if (next_res != 0 && dist[n - next_res] != -1 && dist[n - next_res] + dist[next_res] < num_set_bits) {
          return NOT_STURDY;
        }
        if (curr_res == 0 || next_res == 0 || dist[n - next_res] == -1 || dist[n - next_res] + dist[next_res] < num_set_bits) {
          // Only keep searching this path if it is not known
          // to be impossible to reach 0 residue at a depth
          // less than num_set_bits.
          q.push(next_res);
        }
      }
    }
  }
  return STURDY;
}

int OrderDegreeBfs::swm(long long int n) {
  // Complexity: O(n log(n)) 
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return num_set_bits;
  }
  if (baby_step_giant_step(n) > 0) {
    return 2;
  }
  std::vector<long long int> pows_vector = get_powers(n);
  long long int n_pows = pows_vector.size();
  long long int pows[n_pows];
  for (long long int i = 0; i < n_pows; i++) {
    pows[i] = pows_vector.at(i);
  }
  
  int depth = 0;
  std::queue<long long int> q;
  int dist[n];
  for (int i = 0; i < n; i++) {
    dist[i] = -1;
  }
  // Use -1 as a special n that will be treated like 0,
  // but will not trigger the break condition immediately.
  const long long int INITIAL_ZERO = -1;
  q.push(INITIAL_ZERO);
  // Use -2 as a delimiter to track the depth.
  const long long int DELIMITER = -2;
  q.push(DELIMITER);
  long long int curr_res, next_res;
  while (q.size() > 1 && depth < num_set_bits) {
    curr_res = q.front();
    q.pop();
    if (curr_res == DELIMITER) {
      depth++;
      q.push(DELIMITER);
      continue;
    }
    if (curr_res == 0) {
      return dist[curr_res];
    }
    if (curr_res == INITIAL_ZERO) {
      curr_res = 0;
    }
    for (long long int index = 0; index < n_pows; index++) {
      next_res = curr_res + pows[index];
      if (next_res >= n) {
        next_res -= n;
      }
      if (dist[next_res] == -1) {
        dist[next_res] = depth + 1;
        if (curr_res == 0 || next_res == 0 || dist[n - next_res] == -1 || dist[n - next_res] + dist[next_res] < num_set_bits) {
          // Only keep searching this path if it is not known
          // to be impossible to reach 0 residue at a depth
          // less than num_set_bits.
          q.push(next_res);
        }
      }
    }
  }
  return num_set_bits;
 }

mp::mpz_int OrderDegreeBfs::msw(long long int n) {
  // Complexity O(n log(n))
  int num_set_bits = count_set_bits(n);
  if (num_set_bits <= 2) {
    return mp::mpz_int(1);
  }
  std::vector<long long int> pows_vector = get_powers(n);
  long long int n_pows = pows_vector.size();
  long long int pows[n_pows];
  for (long long int i = 0; i < n_pows; i++) {
    pows[i] = pows_vector.at(i);
  }
  
  int depth = 0;
  std::queue<long long int> q;
  int dist[n];
  long long int max_bit[n];
  long long int add_index[n];
  for (int i = 0; i < n; i++) {
    dist[i] = -1;
    max_bit[i] = -1;
    add_index[i] = -1;
  }
  // Use -1 as a special n that will be treated like 0,
  // but will not trigger the break condition immediately.
  const long long int INITIAL_ZERO = -1;
  q.push(INITIAL_ZERO);
  // Use -2 as a delimiter to track the depth.
  const long long int DELIMITER = -2;
  q.push(DELIMITER);
  long long int curr_res, next_res;
  while (q.size() > 1 && depth < num_set_bits) {
    curr_res = q.front();
    q.pop();
    if (curr_res == DELIMITER) {
      depth++;
      q.push(DELIMITER);
      continue;
    }
    if (curr_res == 0) {
      break;
    }
    if (curr_res == INITIAL_ZERO) {
      curr_res = 0;
    }
    for (long long int index = 0; index < n_pows; index++) {
      next_res = curr_res + pows[index];
      if (next_res >= n) {
        next_res -= n;
      }
      if (dist[next_res] == -1) {
        // First time visiting next_res at this depth.
        // Set initial values for dist, add_index, and max_bit.
        dist[next_res] = depth + 1;
        add_index[next_res] = index;
        if (max_bit[curr_res] > index) {
          // Case where curr_res is 0 from initial special case is
          // handled correctly here without additional logic.
          max_bit[next_res] = max_bit[curr_res];
        } else {
          max_bit[next_res] = index;
        }
        q.push(next_res);
      } else if (dist[next_res] == depth + 1) {
        long long int other_res = next_res - pows[add_index[next_res]];
        if (other_res < 0) {
          other_res += n;
        }
        if ((index < max_bit[next_res] && max_bit[curr_res] < max_bit[next_res]) || (index == max_bit[next_res] && max_bit[curr_res] <= max_bit[next_res] && max_bit[curr_res] < max_bit[other_res])) {
          add_index[next_res] = index;
          if (max_bit[curr_res] > index) {
            max_bit[next_res] = max_bit[curr_res];
          } else {
            max_bit[next_res] = index;
          }
        }
      }
    }
  }
  if (dist[0] == -1) {
    // n is sturdy.
    return mp::mpz_int(1);
  }

  curr_res = 0;
  const mp::mpz_int ONE = 1;
  mp::mpz_int product = 0;
  do {
    product |= ONE << add_index[curr_res];
    next_res = curr_res - pows[add_index[curr_res]];
    if (next_res < 0) {
      next_res += n;
    }
    curr_res = next_res;
  } while (curr_res != 0);
  return product / n;
}

mp::mpz_int OrderDegreeBfs::mfw(long long int n) {
  // Not implemented!
  return mp::mpz_int(-1);
}

