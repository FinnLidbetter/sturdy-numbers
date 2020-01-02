#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "../common.h"

class Automaton : protected Algorithm {
  public:
    static int is_sturdy(long long int value);
    static int swm(long long int value);
    static mp::mpz_int msw(long long int value);
    static mp::mpz_int mfw(long long int value);
};

#endif /* AUTOMATON_H definition */
