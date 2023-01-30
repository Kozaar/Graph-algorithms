#include "controller.h"

#include "../model/geneticAlgorithm.h"

namespace s21 {

Controller::Controller() {}

Controller::~Controller() {}

auto Controller::openGraph(std::string filename) -> bool {
  return graph.loadGraphFromFile(filename);
}

auto Controller::breadthSearch(int start) -> std::vector<int> {
  return alg.breadthFirstSearch(graph, start);
}

auto Controller::depthSearch(int start) -> std::vector<int> {
  return alg.depthFirstSearch(graph, start);
}

std::vector<std::vector<int>> Controller::viewGraph() {
  return graph.getGraph();
}

int Controller::isGraphOpened() { return graph.countElem(); }

int Controller::getShortestPathBetweenVertices(int vertex1, int vertex2) {
  return alg.getShortestPathBetweenVertices(graph, vertex1, vertex2);
}

std::vector<std::vector<int>> Controller::getShortestPathsBetweenAllVertices() {
  return alg.getShortestPathsBetweenAllVertices(graph);
}

std::vector<std::vector<int>> Controller::getLeastSpanningTree() {
  return alg.getLeastSpanningTree(graph);
}

TsmResult Controller::solveTravelingSalesmanProblem() {
  return alg.solveTravelingSalesmanProblem(graph);
}

TsmResult Controller::GreedyAlgorithm() { return alg.greedyAlgorithm(graph); }

TsmResult Controller::geneticAlgorithm() { return alg.geneticAlgorithm(graph); }

}  //  namespace s21
