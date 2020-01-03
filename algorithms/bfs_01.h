#ifndef BFS_01_H
#define BFS_01_H

#include "../common.h"

class Bfs01 : public Algorithm {
  public:
    int is_sturdy(long long int n);
    int swm(long long int n);
    mp::mpz_int msw(long long int n);
    mp::mpz_int mfw(long long int n);
};

#endif /* BFS_01_H definition */
