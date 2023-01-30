#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include <map>
#include <random>
#include <vector>

#include "s21_graph.h"

namespace s21 {
class GeneticAlgorithm {
 public:
  GeneticAlgorithm() = default;
  auto exec(Graph &graph) -> std::pair<int, std::vector<int>>;

 private:
  std::multimap<int, std::vector<int>> population_;
  int mutationRate_;

  auto makeFirtsGeneration(Graph &graph, std::random_device &rd,
                           std::mt19937 &g) -> std::vector<std::vector<int>>;
  auto makeChildren(std::vector<int> &parent1, std::vector<int> &parent2,
                    std::mt19937 &g)
      -> std::pair<std::vector<int>, std::vector<int>>;
  auto mutation(std::vector<int> *pass, std::mt19937 &g) -> void;

  auto findIntInVector(const std::vector<int> &vec, int num) -> bool;
  auto calculateDistance(Graph &graph, const std::vector<int> &pass) -> int;
};
}  //  namespace s21

#endif  //  GENETICALGORITHM_H_