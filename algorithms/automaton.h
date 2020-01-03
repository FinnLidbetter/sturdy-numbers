#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "../common.h"

class Automaton : public Algorithm {
  public:
    int is_sturdy(long long int n);
    int swm(long long int n);
    mp::mpz_int msw(long long int n);
    mp::mpz_int mfw(long long int n);
};

#endif /* AUTOMATON_H definition */
