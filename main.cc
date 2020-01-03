#include <iostream>
#include "algorithms/dynamic_programming.h"
#include "algorithms/automaton.h"
#include "algorithms/bfs_01.h"
#include "algorithms/order_degree_bfs.h"


int main(int argc, char** argv) {
  if (argc != 5) {
    std::cout << "Usage: sturdy-tester <algorithm> <test> <start> <end>\n";
    std::cout << "\tOptions for <algorithm> are: 'dp', 'aut', 'bfs01', 'order_deg_bfs'\n";
    std::cout << "\tOptions for <test> are: 'sturdy', 'swm', 'msw', 'mfw'\n";
    return 0;
  }
  std::string algorithm_choice = std::string(argv[1]);
  std::string test_choice = std::string(argv[2]);
  long long int start = std::stoll(argv[3]);
  long long int end = std::stoll(argv[4]);
  Algorithm * algo;
  DynamicProgramming dp;
  Automaton aut;
  Bfs01 bfs01;
  OrderDegreeBfs order_deg_bfs;
  if (algorithm_choice.compare("dp") == 0) {
    algo = &dp;
  } else if (algorithm_choice.compare("aut") == 0) {
    algo = &aut;
  } else if (algorithm_choice.compare("bfs01") == 0) {
    algo = &bfs01;
  } else if (algorithm_choice.compare("order_deg_bfs") == 0) {
    algo = &order_deg_bfs;
  } else {
    std::cout << "Unrecognized algorithm. Choices are: 'dp', 'aut', 'bfs01', 'order_deg_bfs'\n";
    return 0;
  }
  if (test_choice.compare("sturdy") == 0) {
    for (long long int i = start; i <= end; i++) {
      std::cout << algo->is_sturdy(i) << "\n";
    }
  } else if (test_choice.compare("swm") == 0) {
    for (long long int i = start; i <= end; i++) {
      std::cout << algo->swm(i) << "\n";
    }
  } else if (test_choice.compare("msw") == 0) {
    for (long long int i = start; i <= end; i++) {
      std::cout << algo->msw(i) << "\n";
    }
  } else if (test_choice.compare("mfw") == 0) {
    for (long long int i = start; i <= end; i++) {
      std::cout << algo->mfw(i) << "\n";
    }
  } else {
    std::cout << "Unrecognized test. Choices are: 'sturdy', 'swm', 'msw', 'mfw'\n";
    return 0;
  }
  return 0;
}
