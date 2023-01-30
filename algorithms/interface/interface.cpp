#include "interface.h"

#include <time.h>

#include <iostream>

namespace s21 {

Interface::Interface() {}

Interface::~Interface() {}

void Interface::exec() {
  char input = ' ';
  while (input != 'q') {
    showMainMenu();
    std::cin >> input;
    if (input == '1') {
      openGraph();
    } else if (controller.isGraphOpened()) {
      if (input == '2') {
        breadthSearch();
      } else if (input == '3') {
        depthSearch();
      } else if (input == '4') {
        getShortestPathBetweenVertices();
      } else if (input == '5') {
        getShortestPathsBetweenAllVertices();
      } else if (input == '6') {
        getLeastSpanningTree();
      } else if (input == '7') {
        solveTravelingSalesmanProblem();
      } else if (input == '8') {
        comparisonAlg();
      } else if (input == '9') {
        viewGraph();
      }
    } else if (input != 'q') {
      std::cout << "Error input\n";
    }
    if (input != 'q') {
      std::cout << "Нажмите enter чтобы продолжить\n";
      std::string str;
      if (input == '5' || input == '6' || input == '7' || input == '9')
        std::getline(std::cin, str);
      std::getline(std::cin, str);
    }
  }
}

void Interface::showMainMenu() {
  system("clear");
  std::cout << "Главное меню:\n"
            << "1. Загрузка графа из файла\n";
  if (controller.isGraphOpened()) {
    std::cout << "2. Обход графа в ширину\n"
              << "3. Обход графа в глубину\n"
              << "4. Поиск кратчайшего пути между двумя вершинами\n"
              << "5. Поиск кратчайших путей между всеми парами вершин в графе\n"
              << "6. Поиск минимального остовного дерева в графе\n"
              << "7. Решение задачи комивояжера\n"
              << "8. Сравнительное исследование работы трех алгоритмов\n"
              << "9. Показать текущий граф\n";
  }
  std::cout << "q. Выход\n";
}

void Interface::openGraph() {
  bool isCorrect = false;
  std::cout << "Введите имя файла. Для отмены введите 'Cancel'\n";
  std::string filename;
  std::getline(std::cin, filename);
  while (!isCorrect) {
    std::getline(std::cin, filename);
    if (toLower(filename) == "cancel" || toLower(filename) == "cansel" ||
        filename == "сфтсуд" || filename == "q") {
      break;
    }
    if (checkFileExtension(filename, ".dot")) {
      isCorrect = true;
    } else {
      std::cout << "Incorrect filename\nВведите другое имя файла или 'Cancel' "
                   "для отмены\n";
    }
  }
  if (isCorrect) {
    if (controller.openGraph(filename)) {
      viewGraph();
    } else {
      std::cout << "Incorrect file\nНажмите enter чтобы продолжить\n";
      std::getline(std::cin, filename);
    }
  }
}

void Interface::viewGraph() {
  std::vector<std::vector<int>> graph = controller.viewGraph();
  std::cout << "--------------------------------\n";
  for (int i = 0; i < graph.size(); i++) {
    for (int j = 0; j < graph[i].size(); j++) {
      std::cout << " " << graph[i][j];
    }
    std::cout << '\n';
  }
  std::cout << "--------------------------------\n";
}

bool Interface::checkFileExtension(const std::string& filename,
                                   std::string extension) {
  bool equal = false;
  if (filename.size() > extension.size()) {
    size_t pos = filename.find(extension);
    if (pos == filename.size() - extension.size()) {
      equal = true;
    }
  }
  return equal;
}

std::string Interface::toLower(const std::string& str) {
  std::string res;
  for (size_t i = 0; i < str.size(); i++) {
    res += (str[i] >= 'A' && str[i] <= 'Z') ? (str[i] + 32) : (str[i]);
  }
  return res;
}

void Interface::breadthSearch() {
  int start = 0;
  std::cout << "Введите начальную вершину (1-" << controller.isGraphOpened()
            << ")\n";
  std::string str;
  std::getline(std::cin, str);
  std::getline(std::cin, str);
  try {
    start = std::stoi(str);
  } catch (const std::exception& e) {
  }
  if (start > 0 && start <= controller.isGraphOpened()) {
    std::vector<int> res = controller.breadthSearch(start);
    printVector(res);
  } else {
    std::cout << "Incorrect start\n";
  }
}

auto Interface::depthSearch() -> void {
  int start = 0;
  std::cout << "Введите начальную вершину (1-" << controller.isGraphOpened()
            << ")\n";
  std::string str;
  std::getline(std::cin, str);
  std::getline(std::cin, str);
  try {
    start = std::stoi(str);
  } catch (const std::exception& e) {
  }
  if (start > 0 && start <= controller.isGraphOpened()) {
    std::vector<int> res = controller.depthSearch(start);
    printVector(res);
  } else {
    std::cout << "Incorrect start\n";
  }
}

void Interface::printVector(const std::vector<int>& v) {
  std::cout << '[';
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i];
    if (i != v.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]\n";
}

void Interface::getShortestPathBetweenVertices() {
  int start = 0;
  std::cout << "Введите начальную вершину (1-" << controller.isGraphOpened()
            << ")\n";
  std::string str;
  std::getline(std::cin, str);
  std::getline(std::cin, str);
  try {
    start = std::stoi(str);
  } catch (const std::exception& e) {
  }
  int finish = 0;
  std::cout << "Введите конечную вершину (1-" << controller.isGraphOpened()
            << ")\n";
  std::getline(std::cin, str);
  try {
    finish = std::stoi(str);
  } catch (const std::exception& e) {
  }
  if (start != 0 && finish != 0 && start <= controller.isGraphOpened() &&
      finish <= controller.isGraphOpened()) {
    int distance = controller.getShortestPathBetweenVertices(start, finish);
    std::cout << distance << '\n';
  } else {
    std::cout << "Incorrect vertex\n";
  }
}

void Interface::getShortestPathsBetweenAllVertices() {
  std::vector<std::vector<int>> res =
      controller.getShortestPathsBetweenAllVertices();
  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      std::cout << "\t" << i << "--" << j << "\t" << res[i][j];
    }
    std::cout << '\n';
  }
}

void Interface::getLeastSpanningTree() {
  std::vector<std::vector<int>> res = controller.getLeastSpanningTree();
  for (size_t i = 0; i < res.size(); i++) {
    for (size_t j = 0; j < res[i].size(); j++) {
      std::cout << res[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

void Interface::solveTravelingSalesmanProblem() {
  TsmResult res = controller.solveTravelingSalesmanProblem();
  std::cout << "Длина маршрута: ";
  if (res.distance > INT16_MAX) {
    std::cout << "inf\n";
  } else {
    std::cout << res.distance << '\n';
  }
  printVector(res.vertices);
}

void Interface::comparisonAlg() {
  std::cout << "Введите число повторений N\nN = ";
  int countRepeat = 5;
  std::string str;
  std::getline(std::cin, str);
  std::getline(std::cin, str);
  try {
    countRepeat = std::stoi(str);
  } catch (const std::exception& e) {
    countRepeat = 5;
  }
  std::cout << "Муравьиный алгоритм:\n";
  TsmResult (s21::Controller::*p)() =
      &s21::Controller::solveTravelingSalesmanProblem;
  printResultAlg(countRepeat, p);

  std::cout << "\nЖадный алгоритм:\n";
  TsmResult (s21::Controller::*g)() = &s21::Controller::GreedyAlgorithm;
  printResultAlg(countRepeat, g);

  std::cout << "\nГенетический алгоритм:\n";
  TsmResult (s21::Controller::*ga)() = &s21::Controller::geneticAlgorithm;
  printResultAlg(countRepeat, ga);
}

void Interface::printResultAlg(int count, TsmResult (s21::Controller::*p)()) {
  clock_t start = clock();
  TsmResult alg;
  alg.distance = 1e7;
  for (int i = 0; i < count; i++) {
    TsmResult alg1 = (controller.*p)();
    if (alg1.distance < alg.distance) alg = alg1;
  }
  clock_t end = clock();
  std::cout << "Расстояние: ";
  if (alg.distance > INT16_MAX) {
    std::cout << "inf\n[]\n";
  } else {
    std::cout << alg.distance << '\n';
    printVector(alg.vertices);
  }
  std::cout << "Время: " << ((double)(end - start) / CLOCKS_PER_SEC) << '\n';
}

}  //  namespace s21
