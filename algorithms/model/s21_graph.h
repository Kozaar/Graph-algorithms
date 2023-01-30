#ifndef S21_GRAPH_H_
#define S21_GRAPH_H_

#include <string>
#include <vector>

namespace s21 {

class Graph {
 public:
  inline Graph() {
    countElem_ = 0;
    stateDi_ = false;
  }

  bool loadGraphFromFile(std::string filename);
  void exportGraphToDot(std::string filename);

  inline int countElem() { return countElem_; }
  inline bool typeGraph() { return stateDi_; }
  inline int operator()(int i, int j) {
    return i < countElem_ && j < countElem_ ? matrixAdjacency_[i][j] : 0;
  }
  inline std::vector<std::vector<int>> getGraph() { return matrixAdjacency_; }

 private:
  std::vector<std::vector<int>> matrixAdjacency_;
  int countElem_;
  bool stateDi_;

  std::vector<int> getFacet(std::string currentString);
  void transformIntoMatrix(std::vector<std::vector<int>>& allConnections);
};
}  //  namespace s21
#endif  // S21_GRAPH_H_