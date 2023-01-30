#ifndef ANTALGORITMH_H_
#define ANTALGORITMH_H_

#include <vector>

#include "s21_graph.h"

namespace s21 {

class AntAlgoritmh {
 public:
  AntAlgoritmh(Graph& graph);

  std::vector<int> findSolution(int* lenghtSolution);
  
 private:

  int findNextVertex(std::vector<int> possibleWays, int currentVertex);
  void updatePheromone(std::vector<std::vector<double>> pheromoneFromAnt);
  std::vector<int> findProbability(std::vector<int> possibleWays,
                                   int currentVertex);
  void delete_from_vector(std::vector<int>*, int);
 
  static constexpr double evaporationRate_ = 0.2;
  static constexpr double Q = 10;
  static constexpr double alfa_ = 1.0;
  static constexpr double beta_ = 2.0;
  static constexpr int antsCount_ = 10;
  static constexpr int repeatCount_ = 3;

  int vertexesCount_;
  std::vector<std::vector<int>> matrixAdjacency_;
  std::vector<std::vector<double>> matrixPheromone_;
};

}  // namespace s21
#endif  // ANTALGORITMH_H_