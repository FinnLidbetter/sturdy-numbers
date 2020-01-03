#ifndef ORDER_DEGREE_BFS_01_H
#define ORDER_DEGREE_BFS_01_H

#include "../common.h"

class OrderDegreeBfs : public Algorithm {
  public:
    int is_sturdy(long long int n);
    int swm(long long int n);
    mp::mpz_int msw(long long int n);
    mp::mpz_int mfw(long long int n);
};

#endif /* ORDER_DEGREE_BFS_01_H definition */
