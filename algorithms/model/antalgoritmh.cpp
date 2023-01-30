#include "antalgoritmh.h"

#include <cmath>
#include <random>

namespace s21 {

AntAlgoritmh::AntAlgoritmh(Graph& graph) {
  vertexesCount_ = graph.countElem();
  matrixAdjacency_.resize(vertexesCount_);
  for (int i = 0; i < vertexesCount_; i++) {
    matrixAdjacency_[i].resize(vertexesCount_);
    for (int j = 0; j < vertexesCount_; j++) {
      if (!graph(i, j) && i != j) {
        matrixAdjacency_[i][j] = 1e7;
      } else {
        matrixAdjacency_[i][j] = graph(i, j);
      }
    }
  }
  matrixPheromone_.resize(vertexesCount_);
  for (int i = 0; i < vertexesCount_; i++) {
    matrixPheromone_[i].resize(vertexesCount_);
    for (int j = 0; j < vertexesCount_; j++) {
      matrixPheromone_[i][j] = 1.0;
    }
  }
}

int AntAlgoritmh::findNextVertex(std::vector<int> possibleWays,
                                 int currentVertex) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<int> myProb(findProbability(possibleWays, currentVertex));
  for (int i = 1; i < possibleWays.size(); i++) {
    myProb[i] += myProb[i - 1];
  }
  std::uniform_int_distribution<> dist(0, 10000);
  int randomRes = dist(gen);
  int i = 0;
  while (myProb[i] < randomRes && i < myProb.size() - 1) i++;
  return possibleWays[i];
}

std::vector<int> AntAlgoritmh::findProbability(std::vector<int> possibleWays,
                                               int currentVertex) {
  std::vector<double> buf(possibleWays.size(), 0.0);
  std::vector<int> result(possibleWays.size());
  double allOptions = 0.0;
  for (int i = 0; i < possibleWays.size(); i++) {
    buf[i] =
        pow(matrixPheromone_[currentVertex - 1][possibleWays[i] - 1], alfa_) *
        pow(1.0 / matrixAdjacency_[currentVertex - 1][possibleWays[i] - 1],
            beta_);
    allOptions += buf[i];
  }
  for (int i = 0; i < possibleWays.size(); i++) {
    result[i] = buf[i] / allOptions * 10000;
  }
  return result;
}

std::vector<int> AntAlgoritmh::findSolution(int* lenghtSolution) {
  std::vector<std::vector<double>> pheromoneFromAnts(vertexesCount_);
  for (int i = 0; i < vertexesCount_; i++) {
    pheromoneFromAnts[i].resize(vertexesCount_);
  }
  std::vector<int> possibleWays(vertexesCount_ - 1);
  for (int i = 0; i < vertexesCount_ - 1; i++) {
    possibleWays[i] = i + 2;
  }
  std::vector<int> bestPath(vertexesCount_ + 1);
  int bestLenghtWay = 1e7;
  for (int g = 0; g < repeatCount_; g++) {
    for (int ant = 0; ant < antsCount_; ant++) {
      int lenghtWay = 0;
      std::vector<int> path(vertexesCount_ + 1);
      path[0] = 1;
      path.back() = 1;
      std::vector<int> currentPossibleWays(possibleWays);
      for (int i = 1; i < vertexesCount_; i++) {
        path[i] = findNextVertex(currentPossibleWays, path[i - 1]);
        delete_from_vector(&currentPossibleWays, path[i]);
        lenghtWay += matrixAdjacency_[path[i - 1] - 1][path[i] - 1];
      }
      lenghtWay +=
          matrixAdjacency_[path[vertexesCount_ - 1] - 1][path.back() - 1];
      for (int i = 0; i < vertexesCount_; i++) {
        pheromoneFromAnts[path[i] - 1][path[i + 1] - 1] = Q / lenghtWay;
      }
      if (lenghtWay < bestLenghtWay) {
        bestLenghtWay = lenghtWay;
        bestPath.swap(path);
      }
    }
    updatePheromone(pheromoneFromAnts);
  }
  *lenghtSolution = bestLenghtWay;
  return bestPath;
}

void AntAlgoritmh::delete_from_vector(std::vector<int>* x, int xN) {
  auto it = x->begin();
  for (; *it != xN && it != x->end(); it++)
    ;
  if (it != x->end()) x->erase(it);
}

void AntAlgoritmh::updatePheromone(
    std::vector<std::vector<double>> pheromoneFromAnt) {
  for (int i = 0; i < vertexesCount_; i++) {
    for (int j = 0; j < vertexesCount_; j++) {
      matrixPheromone_[i][j] =
          (1.0 - evaporationRate_) * matrixPheromone_[i][j] +
          pheromoneFromAnt[i][j];
    }
  }
}

}  // namespace s21