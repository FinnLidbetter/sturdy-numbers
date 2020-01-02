#include <iostream>
#include "algorithms/dynamic_programming.h"
#include "algorithms/automaton.h"
#include "algorithms/bfs_01.h"
#include "algorithms/order_degree_bfs.h"

template <class AlgorithmClass>
int is_sturdy(long long int value) {
  return AlgorithmClass::is_sturdy(value);
}

template <class AlgorithmClass>
int swm(long long int value) {
  return AlgorithmClass::swm(value);
}

template <class Algorithm>
mp::mpz_int msw(long long int value) {
  return AlgorithmClass::msw(value);
}

template <class Algorithm>
mp::mpz_int mfw(long long int value) {
  return AlgorithmClass::mfw(value);
}


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
  Algorithm algo;

  long long int n;
  bool dp_is_sturdy_bool;
  int dp_swm_val;
  mp::mpz_int dp_msw_val;
  mp::mpz_int dp_mfw_val;
  std::cin >> n;
  std::cout << "DynamicProgramming:\n";
  dp_is_sturdy_bool = DynamicProgramming::is_sturdy(n) == 1;
  std::cout << (dp_is_sturdy_bool ? "\tsturdy\n" : "\tnot sturdy\n");
  dp_swm_val = DynamicProgramming::swm(n);
  std::cout << "\tswm(" << n << ") = " << dp_swm_val << "\n";
  dp_msw_val = DynamicProgramming::msw(n);
  std::cout << "\tmsw(" << n << ") = " << dp_msw_val << "\n";
  std::cout << "\tmsw(" << n << ") * " << n << " = " << dp_msw_val * n << "\n";
  dp_mfw_val = DynamicProgramming::mfw(n);
  std::cout << "\tmfw(" << n << ") = " << dp_mfw_val << "\n";

  bool aut_is_sturdy_bool;
  int aut_swm_val;
  mp::mpz_int aut_msw_val;
  mp::mpz_int aut_mfw_val;
  std::cout << "Automaton:\n";
  aut_is_sturdy_bool = Automaton::is_sturdy(n) == 1;
  std::cout << (aut_is_sturdy_bool ? "\tsturdy\n" : "\tnot sturdy\n");
  aut_swm_val = Automaton::swm(n);
  std::cout << "\tswm(" << n << ") = " << aut_swm_val << "\n";
  aut_msw_val = Automaton::msw(n);
  std::cout << "\tmsw(" << n << ") = " << aut_msw_val << "\n";
  std::cout << "\tmsw(" << n << ") * " << n << " = " << aut_msw_val * n << "\n";
  aut_mfw_val = Automaton::mfw(n);
  std::cout << "\tmfw(" << n << ") = " << aut_mfw_val << "\n"; 

  bool bfs_01_is_sturdy_bool;
  int bfs_01_swm_val;
  mp::mpz_int bfs_01_msw_val;
  mp::mpz_int bfs_01_mfw_val;
  std::cout << "Bfs01:\n";
  bfs_01_is_sturdy_bool = Bfs01::is_sturdy(n) == 1;
  std::cout << (bfs_01_is_sturdy_bool ? "\tsturdy\n" : "\tnot sturdy\n");
  bfs_01_swm_val = Bfs01::swm(n);
  std::cout << "\tswm(" << n << ") = " << bfs_01_swm_val << "\n";
  bfs_01_msw_val = Bfs01::msw(n);
  std::cout << "\tmsw(" << n << ") = " << bfs_01_msw_val << "\n";
  std::cout << "\tmsw(" << n << ") * " << n << " = " << bfs_01_msw_val * n << "\n";
  bfs_01_mfw_val = Bfs01::mfw(n);
  std::cout << "\tmfw(" << n << ") = " << bfs_01_mfw_val << "\n"; 

  bool order_degree_bfs_is_sturdy_bool;
  int order_degree_bfs_swm_val;
  mp::mpz_int order_degree_bfs_msw_val;
  mp::mpz_int order_degree_bfs_mfw_val;
  std::cout << "OrderDegreeBfs:\n";
  order_degree_bfs_is_sturdy_bool = OrderDegreeBfs::is_sturdy(n) == 1;
  std::cout << (order_degree_bfs_is_sturdy_bool ? "\tsturdy\n" : "\tnot sturdy\n");
  order_degree_bfs_swm_val = OrderDegreeBfs::swm(n);
  std::cout << "\tswm(" << n << ") = " << order_degree_bfs_swm_val << "\n";
  order_degree_bfs_msw_val = OrderDegreeBfs::msw(n);
  std::cout << "\tmsw(" << n << ") = " << order_degree_bfs_msw_val << "\n";
  std::cout << "\tmsw(" << n << ") * " << n << " = " << order_degree_bfs_msw_val * n << "\n";

  return 0;
}
