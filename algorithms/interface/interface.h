#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <vector>

#include "../controller/controller.h"

namespace s21 {
class Interface {
 public:
  Interface();
  ~Interface();

  auto exec() -> void;

 private:
  Controller controller;

  auto showMainMenu() -> void;
  auto openGraph() -> void;
  auto viewGraph() -> void;
  auto checkFileExtension(const std::string& filename, std::string extension)
      -> bool;
  auto toLower(const std::string& str) -> std::string;
  auto breadthSearch() -> void;
  auto depthSearch() -> void;
  auto printVector(const std::vector<int>& v) -> void;
  auto getShortestPathBetweenVertices() -> void;
  auto getShortestPathsBetweenAllVertices() -> void;
  auto getLeastSpanningTree() -> void;
  auto solveTravelingSalesmanProblem() -> void;
  auto comparisonAlg() -> void;
  auto printResultAlg(int count, TsmResult (s21::Controller::*p)()) -> void;
};
}  //  namespace s21
#endif  // INTERFACE_H_