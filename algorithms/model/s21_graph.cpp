#include "s21_graph.h"

#include <fstream>

namespace s21 {

bool Graph::loadGraphFromFile(std::string filename) {
  std::ifstream fin(filename);
  if (fin.is_open()) {
    stateDi_ = false;
    countElem_ = 0;
    std::string currentString;
    std::vector<std::vector<int>> allConnections;
    std::getline(fin, currentString);
    while (currentString.find("graph") == std::string::npos)
      std::getline(fin, currentString);
    if (currentString.find("digraph") != std::string::npos) stateDi_ = true;
    std::getline(fin, currentString);
    while (currentString.find("}") == std::string::npos) {
      if ((currentString.find("--") != std::string::npos && !stateDi_ ||
           currentString.find("->") != std::string::npos && stateDi_) &&
          currentString.find("//") == std::string::npos) {
        try {
          allConnections.push_back(getFacet(currentString));
        } catch (std::exception) {
          return false;
        }
      }
      std::getline(fin, currentString);
    }
    transformIntoMatrix(allConnections);
    fin.close();
    return true;
  }
  return false;
}

std::vector<int> Graph::getFacet(std::string str) {
  std::vector<int> result;
  size_t buf;
  // take first vertex
  int number = std::stoi(str, &buf);
  str.erase(0, buf);
  result.push_back(number);
  if (countElem_ < number) countElem_ = number;

  // find and take second vertex
  buf = str.find_first_of("1234567890");
  str.erase(0, buf);
  number = std::stoi(str, &buf);
  str.erase(0, buf);
  result.push_back(number);
  if (countElem_ < number) countElem_ = number;

  // find weight of facet
  buf = str.find_first_of("1234567890");
  if (buf != std::string::npos) {
    str.erase(0, buf);
    number = std::stoi(str, &buf);
    str.erase(0, buf);
    result.push_back(number);
  } else {
    result.push_back(1);
  }
  return result;
}

void Graph::transformIntoMatrix(std::vector<std::vector<int>>& allConnections) {
  matrixAdjacency_.clear();
  matrixAdjacency_.resize(countElem_);
  for (int i = 0; i < countElem_; ++i) {
    matrixAdjacency_[i].resize(countElem_);
  }
  for (size_t i = 0; i < allConnections.size(); i++) {
    matrixAdjacency_[allConnections[i][0] - 1][allConnections[i][1] - 1] =
        allConnections[i][2];
    if (!stateDi_) {
      matrixAdjacency_[allConnections[i][1] - 1][allConnections[i][0] - 1] =
          allConnections[i][2];
    }
  }
}

void Graph::exportGraphToDot(std::string filename) {
  std::ofstream fout(filename);
  if (fout.is_open()) {
    if (stateDi_) {
      fout << "di";
    }
    fout << "graph graphname {\n";
    if (stateDi_) {
      for (int i = 0; i < countElem_; i++) {
        for (int j = 0; j < countElem_; j++) {
          if (matrixAdjacency_[i][j]) {
            fout << '\t' << i + 1 << " -> " << j + 1
                 << " [label=" << matrixAdjacency_[i][j] << "];\n";
          }
        }
      }
    } else {
      for (int i = 0; i < countElem_; i++) {
        for (int j = 0; j < i + 1; j++) {
          if (matrixAdjacency_[i][j]) {
            fout << '\t' << i + 1 << " -- " << j + 1
                 << " [label=" << matrixAdjacency_[i][j] << "];\n";
          }
        }
      }
    }
    fout << "}";
    fout.close();
  }
}
}  //  namespace s21
