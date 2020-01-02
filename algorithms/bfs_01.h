#ifndef BFS_01_H
#define BFS_01_H

#include "../common.h"

class Bfs01 : protected Algorithm {
  public:
    static int is_sturdy(long long int value);
    static int swm(long long int value);
    static mp::mpz_int msw(long long int value);
    static mp::mpz_int mfw(long long int value);
};

#endif /* BFS_01_H definition */
