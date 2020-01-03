#ifndef DP_H
#define DP_H

#include "../common.h"

class DynamicProgramming : public Algorithm {
  public:
    int is_sturdy(long long int n);
    int swm(long long int n);
    mp::mpz_int msw(long long int n);
    mp::mpz_int mfw(long long int n);
  private:
    static void fill_tables(bool ***reachable,
                            mp::mpz_int ***min_valid,
                            long long int *pows,
                            int num_set_bits,
                            long long int n,
                            long long int ord);
};

#endif /* DP_H definition */
