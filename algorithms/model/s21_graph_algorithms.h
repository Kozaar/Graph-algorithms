#ifndef S21_GRAPH_ALGORITHMS_H_
#define S21_GRAPH_ALGORITHMS_H_

#include <vector>

#include "s21_graph.h"

namespace s21 {
struct TsmResult {
  std::vector<int> vertices;
  int distance;
};

class GraphAlgorithms {
 public:
  inline GraphAlgorithms(){};

  auto depthFirstSearch(Graph &graph, int startVertex) -> std::vector<int>;
  auto breadthFirstSearch(Graph &graph, int startVertex) -> std::vector<int>;

  auto getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2)
      -> int;
  auto getShortestPathsBetweenAllVertices(Graph &graph)
      -> std::vector<std::vector<int>>;

  auto getLeastSpanningTree(Graph &graph) -> std::vector<std::vector<int>>;

  auto solveTravelingSalesmanProblem(Graph &graph) -> TsmResult;
  auto geneticAlgorithm(Graph &graph) -> TsmResult;
  auto greedyAlgorithm(Graph &graph) -> TsmResult;

 private:
  auto findIntInVector(const std::vector<int> &vec, int num) -> bool;
};
}  //  namespace s21
#endif  // S21_GRAPH_ALGORITHMS_H_