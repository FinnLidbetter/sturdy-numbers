#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "../common.h"

class Automaton : public Algorithm {
  public:
    int is_sturdy(long long int value);
    int swm(long long int value);
    mp::mpz_int msw(long long int value);
    mp::mpz_int mfw(long long int value);
};

#endif /* AUTOMATON_H definition */
