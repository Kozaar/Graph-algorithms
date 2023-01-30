#include "s21_graph_algorithms.h"

#include <cmath>
#include <map>

#include "antalgoritmh.h"
#include "geneticAlgorithm.h"
#include "s21_queue.h"
#include "s21_stack.h"

// #include <iostream>

namespace s21 {

std::vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph,
                                                   int startVertex) {
  short White = 0;
  short Gray = 1;
  short Black = 2;
  std::vector<int> result;
  s21::Stack vertexes;
  std::map<int, short> colorsVertexes;
  for (int i = 1; i <= graph.countElem(); i++) {
    colorsVertexes.insert(std::pair<int, short>{i, White});
  }
  vertexes.push(startVertex);
  result.push_back(startVertex);
  colorsVertexes[startVertex] = Gray;
  while (result.size() < graph.countElem()) {
    if (colorsVertexes[vertexes.peek()] == Black) {
      vertexes.pop();
    }
    for (int i = 0; i < graph.countElem(); ++i) {
      if (graph(vertexes.peek() - 1, i) && colorsVertexes[i + 1] == White) {
        colorsVertexes[i + 1] = Gray;
        vertexes.push(i + 1);
        result.push_back(i + 1);
        break;
      }
      if (colorsVertexes[vertexes.peek()] == Gray &&
          i == graph.countElem() - 1) {
        colorsVertexes[vertexes.peek()] = Black;
      }
    }
  }
  return result;
}

std::vector<int> GraphAlgorithms::breadthFirstSearch(Graph &graph,
                                                     int startVertex) {
  short White = 0;
  short Gray = 1;
  std::vector<int> result;
  s21::Queue vertexes;
  std::map<int, short> colorsVertexes;
  for (int i = 1; i <= graph.countElem(); i++) {
    colorsVertexes.insert(std::pair<int, short>{i, White});
  }
  vertexes.push(startVertex);
  result.push_back(startVertex);
  colorsVertexes[startVertex] = Gray;
  while (result.size() < graph.countElem()) {
    for (int i = 0; i < graph.countElem(); ++i) {
      if (graph(vertexes.peek() - 1, i) && colorsVertexes[i + 1] == White) {
        colorsVertexes[i + 1] = Gray;
        vertexes.push(i + 1);
        result.push_back(i + 1);
      }
    }
    vertexes.pop();
  }
  return result;
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  short White = 0;
  short Gray = 1;
  int distance = INT32_MAX;
  std::vector<int> distances;
  for (size_t i = 0; i < graph.countElem(); i++) {
    distances.push_back(INT32_MAX);
  }
  distances[vertex1 - 1] = 0;
  s21::Queue vertexes;
  std::vector<int> colorsVertexes;
  for (int i = 0; i < graph.countElem(); i++) {
    colorsVertexes.push_back(White);
  }
  vertexes.push(vertex1);
  colorsVertexes[vertex1] = Gray;
  while (vertexes.size()) {
    for (int i = 0; i < graph.countElem(); ++i) {
      if (graph(vertexes.peek() - 1, i) && colorsVertexes[i] == White) {
        colorsVertexes[i] = Gray;
        vertexes.push(i + 1);
      }
      if (graph(vertexes.peek() - 1, i) &&
          distances[i] >
              distances[vertexes.peek() - 1] + graph(vertexes.peek() - 1, i)) {
        distances[i] =
            distances[vertexes.peek() - 1] + graph(vertexes.peek() - 1, i);
        colorsVertexes[i] = White;
        vertexes.push(i + 1);
      }
    }
    vertexes.pop();
  }
  return distances[vertex2 - 1];
}

std::vector<std::vector<int>>
GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  int count = graph.countElem();
  std::vector<std::vector<int>> result(count);
  for (int i = 0; i < count; i++) {
    result[i].resize(count);
    for (int j = 0; j < count; j++) {
      if (graph(i, j) == 0 && i != j) {
        result[i][j] = 1e7;
      } else {
        result[i][j] = graph(i, j);
      }
    }
  }
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count; j++) {
      if (j == i) continue;
      for (int k = 0; k < count; k++) {
        if (k == i || k == j || result[j][i] == 1e7 || result[i][k] == 1e7)
          continue;
        result[j][k] = result[j][k] < result[j][i] + result[i][k]
                           ? result[j][k]
                           : result[j][i] + result[i][k];
      }
    }
  }
  return result;
}

std::vector<std::vector<int>> GraphAlgorithms::getLeastSpanningTree(
    Graph &graph) {
  int count = graph.countElem();
  std::vector<std::vector<int>> result(count);
  for (int i = 0; i < count; i++) {
    result[i].resize(count);
  }
  std::vector<int> finish(1, 1);
  std::vector<int> start(count - 1);
  for (int i = 2; i <= count; i++) start[i - 2] = i;
  for (int k = 0; k < count - 1; k++) {
    int newPathX = 1;
    int newPathY = 1;
    int minPath = 1e7;
    auto itPathY = start.begin();
    for (auto itFinish = finish.begin(); itFinish != finish.end(); itFinish++) {
      for (auto itStart = start.begin(); itStart != start.end(); itStart++) {
        if (!graph(*itFinish - 1, *itStart - 1)) continue;
        if (minPath > graph(*itFinish - 1, *itStart - 1)) {
          minPath = graph(*itFinish - 1, *itStart - 1);
          newPathX = *itFinish;
          newPathY = *itStart;
          itPathY = itStart;
        }
      }
    }
    finish.push_back(newPathY);
    start.erase(itPathY);
    result[newPathX - 1][newPathY - 1] = minPath;
    if (!graph.typeGraph()) result[newPathY - 1][newPathX - 1] = minPath;
  }
  return result;
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
  TsmResult result;
  AntAlgoritmh A(graph);
  result.vertices = A.findSolution(&(result.distance));
  return result;
}

TsmResult GraphAlgorithms::geneticAlgorithm(Graph &graph) {
  TsmResult res;
  GeneticAlgorithm ga;
  auto gRes = ga.exec(graph);
  res.distance = gRes.first;
  res.vertices = gRes.second;
  return res;
}

TsmResult GraphAlgorithms::greedyAlgorithm(Graph &graph) {
  TsmResult res;
  res.distance = 0;
  std::vector<std::vector<int>> copyMatrixAdjacency(graph.countElem());
  for (int i = 0; i < graph.countElem(); i++) {
    copyMatrixAdjacency[i].resize(graph.countElem());
    for (int j = 0; j < graph.countElem(); j++) {
      copyMatrixAdjacency[i][j] = graph(i, j);
    }
  }
  bool isCycle = false;
  res.vertices.push_back(1);
  while (!isCycle) {
    int localMin = INT32_MAX;
    int indexLocalMin = 0;
    for (int i = 0; i < graph.countElem() && !isCycle; i++) {
      if (graph(res.vertices.back() - 1, i) != 0 &&
          graph(res.vertices.back() - 1, i) < localMin &&
          !findIntInVector(res.vertices, i + 1)) {
        localMin = graph(res.vertices.back() - 1, i);
        indexLocalMin = i;
      }
    }
    if (indexLocalMin == 0) {
      isCycle = true;
      if (res.vertices.size() != graph.countElem()) {
        res.distance = -1;
        res.vertices.clear();
      }
    } else {
      res.distance += localMin;
      res.vertices.push_back(indexLocalMin + 1);
    }
  }
  if (res.distance != -1) {
    res.distance += (graph(res.vertices.back() - 1, 0) > 0)
                        ? graph(res.vertices.back() - 1, 0)
                        : INT16_MAX;
    res.vertices.push_back(1);
  }
  return res;
}

bool GraphAlgorithms::findIntInVector(const std::vector<int> &vec, int num) {
  bool contain = false;
  for (size_t i = 0; i < vec.size() && !contain; i++) {
    if (num == vec[i]) contain = true;
  }
  return contain;
}

}  //  namespace s21
