#ifndef ORDER_DEGREE_BFS_01_H
#define ORDER_DEGREE_BFS_01_H

#include "../common.h"

class OrderDegreeBfs : public Algorithm {
  public:
    int is_sturdy(long long int value);
    int swm(long long int value);
    mp::mpz_int msw(long long int value);
    mp::mpz_int mfw(long long int value);
};

#endif /* ORDER_DEGREE_BFS_01_H definition */
