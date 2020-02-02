# sturdy-numbers
Command line interface for timing algorithms related to sums of digits of multiples of natural numbers.

## Dependencies
This project requires you to install the C++ boost library: https://www.boost.org/ and the GMP library: https://gmplib.org/

## Usage
Once you have installed the dependencies run (from this directory):
```
make

# Use the 'aut' automaton-based approach to evaluate the
# sturdiness of each integer between 5 and 15.
./sturdy_tester aut sturdy 5 15

# Use the 'dp' dynamic programing approach to compute the
# msw function for values between 1 and 100, and output the
# running time in mircoseconds.
./sturdy_tester -t dp msw 1 100

# Print usage information for the available algorithms and
# functions.
./sturdy_tester

```
