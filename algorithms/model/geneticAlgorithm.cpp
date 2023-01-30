#include "geneticAlgorithm.h"

#include <algorithm>

namespace s21 {

std::pair<int, std::vector<int>> s21::GeneticAlgorithm::exec(Graph &graph) {
  mutationRate_ = graph.countElem() / 4;
  std::random_device rd;
  std::mt19937 g(rd());
  int countGenerations = 1000;
  std::vector<std::vector<int>> first = makeFirtsGeneration(graph, rd, g);
  for (int i = 0; i < first.size(); i++) {
    population_.insert(std::pair<int, std::vector<int>>(
        calculateDistance(graph, first[i]), first[i]));
  }
  for (int i = 0; i < countGenerations; i++) {
    auto it = population_.begin();
    ++it;
    std::pair<std::vector<int>, std::vector<int>> children =
        makeChildren((*(population_.begin())).second, (*it).second, g);
    mutation(&children.first, g);
    mutation(&children.second, g);
    population_.insert(std::pair<int, std::vector<int>>(
        calculateDistance(graph, children.first), children.first));
    population_.insert(std::pair<int, std::vector<int>>(
        calculateDistance(graph, children.second), children.second));
    population_.erase(--(population_.end()));
    population_.erase(--(population_.end()));
  }
  std::vector<int> res;
  res.push_back(1);
  for (int i = 0; i < (*(population_.begin())).second.size(); i++) {
    res.push_back((*(population_.begin())).second[i]);
  }
  res.push_back(1);
  return std::pair<int, std::vector<int>>((*(population_.begin())).first, res);
}

std::vector<std::vector<int>> GeneticAlgorithm::makeFirtsGeneration(
    Graph &graph, std::random_device &rd, std::mt19937 &g) {
  int sizeGeneration = 5;
  std::vector<std::vector<int>> generation(sizeGeneration);
  std::vector<int> curent;
  for (int i = 1; i < graph.countElem(); i++) {
    curent.push_back(i + 1);
  }
  for (int i = 0; i < sizeGeneration; i++) {
    std::shuffle(curent.begin(), curent.end(), g);
    for (int j = 0; j < curent.size(); j++) {
      generation[i].push_back(curent[j]);
    }
  }
  return generation;
}

std::pair<std::vector<int>, std::vector<int>> GeneticAlgorithm::makeChildren(
    std::vector<int> &parent1, std::vector<int> &parent2, std::mt19937 &g) {
  std::vector<int> child1;
  std::vector<int> child2;
  std::uniform_int_distribution<int> uni(1, parent1.size());
  int cross = uni(g);
  for (int i = 0; i < cross; i++) {
    child1.push_back(parent1[i]);
    child2.push_back(parent2[i]);
  }
  for (int i = 0; i < parent1.size(); i++) {
    if (!findIntInVector(child1, parent2[i])) {
      child1.push_back(parent2[i]);
    }
    if (!findIntInVector(child2, parent1[i])) {
      child2.push_back(parent1[i]);
    }
  }
  return std::pair<std::vector<int>, std::vector<int>>(child1, child2);
}

void GeneticAlgorithm::mutation(std::vector<int> *pass, std::mt19937 &g) {
  std::uniform_int_distribution<int> uni(0, pass->size() - 1);
  for (int i = 0; i < mutationRate_; i++) {
    std::swap(pass->at(uni(g)), pass->at(uni(g)));
  }
}

bool GeneticAlgorithm::findIntInVector(const std::vector<int> &vec, int num) {
  bool contain = false;
  for (size_t i = 0; i < vec.size() && !contain; i++) {
    if (num == vec[i]) contain = true;
  }
  return contain;
}

int GeneticAlgorithm::calculateDistance(Graph &graph,
                                        const std::vector<int> &pass) {
  if (pass.size() == 0) return -1;
  int distance =
      (graph(0, pass[0] - 1) > 0) ? graph(0, pass[0] - 1) : INT16_MAX;
  for (int i = 0; i < pass.size() - 1; i++) {
    distance += (graph(pass[i] - 1, pass[i + 1] - 1) > 0)
                    ? graph(pass[i] - 1, pass[i + 1] - 1)
                    : INT16_MAX;
  }
  distance +=
      (graph(pass.back() - 1, 0) > 0) ? graph(pass.back() - 1, 0) : INT16_MAX;
  return distance;
}

}  //  namespace s21