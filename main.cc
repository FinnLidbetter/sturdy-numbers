#include <iostream>
#include <chrono>
#include "algorithms/dynamic_programming.h"
#include "algorithms/automaton.h"
#include "algorithms/bfs_01.h"
#include "algorithms/order_degree_bfs.h"


int main(int argc, char** argv) {
  if (argc < 5 || argc > 6) {
    std::cout << "Usage: sturdy-tester [-t|--time] <algorithm> <test> <start> <end>\n";
    std::cout << "\tOptions for <algorithm> are: 'dp', 'aut', 'bfs01', 'order_deg_bfs'\n";
    std::cout << "\tOptions for <test> are: 'sturdy', 'swm', 'msw', 'mfw'\n";
    return 0;
  }
  int index = 1;
  bool print_timing = false;
  if (std::string(argv[index]).compare("-t") == 0 || std::string(argv[index]).compare("--time") == 0) {
    print_timing = true;
    index++;
  }
  std::string algorithm_choice = std::string(argv[index]);
  std::string test_choice = std::string(argv[index + 1]);
  long long int start = std::stoll(argv[index + 2]);
  long long int end = std::stoll(argv[index + 3]);
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
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
  if (test_choice.compare("sturdy") == 0) {
    for (long long int n = start; n <= end; n++) {
      std::cout << algo->is_sturdy(n) << "\n";
    }
  } else if (test_choice.compare("swm") == 0) {
    for (long long int n = start; n <= end; n++) {
      std::cout << algo->swm(n) << "\n";
    }
  } else if (test_choice.compare("msw") == 0) {
    for (long long int n = start; n <= end; n++) {
      std::cout << algo->msw(n) << "\n";
    }
  } else if (test_choice.compare("mfw") == 0) {
    for (long long int n = start; n <= end; n++) {
      std::cout << algo->mfw(n) << "\n";
    }
  } else {
    std::cout << "Unrecognized test. Choices are: 'sturdy', 'swm', 'msw', 'mfw'\n";
    return 0;
  }
  std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time);
  if (print_timing) {
    std::cout << duration.count() << " milliseconds\n";
  }
  return 0;
}
