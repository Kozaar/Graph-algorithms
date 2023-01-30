#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/s21_graph.h"
#include "../model/s21_graph_algorithms.h"
#include "controller.h"

namespace s21 {
class Controller {
 public:
  Controller();
  ~Controller();

  auto openGraph(std::string filename) -> bool;
  auto breadthSearch(int start) -> std::vector<int>;
  auto depthSearch(int start) -> std::vector<int>;
  auto viewGraph() -> std::vector<std::vector<int>>;
  auto isGraphOpened() -> int;
  auto getShortestPathBetweenVertices(int vertex1, int vertex2) -> int;
  auto getShortestPathsBetweenAllVertices() -> std::vector<std::vector<int>>;
  auto getLeastSpanningTree() -> std::vector<std::vector<int>>;
  auto solveTravelingSalesmanProblem() -> TsmResult;
  auto GreedyAlgorithm() -> TsmResult;
  auto geneticAlgorithm() -> TsmResult;

 private:
  Graph graph;
  GraphAlgorithms alg;
};
}  //  namespace s21
#endif  // CONTROLLER_H_