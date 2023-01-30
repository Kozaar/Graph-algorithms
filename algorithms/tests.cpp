#include <gtest/gtest.h>

#include <vector>

#include "model/s21_graph.h"
#include "model/s21_graph_algorithms.h"

TEST(graph, loadGoodFile) {
    s21::Graph graph;
    ASSERT_TRUE(graph.loadGraphFromFile("graphs/1.dot"));
    ASSERT_EQ(graph.countElem(), 6);
    ASSERT_FALSE(graph.typeGraph());
}

TEST(graph, loadBadFile_doubleVertices) {
    s21::Graph graph;
    ASSERT_TRUE(graph.loadGraphFromFile("graphs/bad1.dot"));
}

TEST(graph, loadBadFile_connectionVertices) {
    s21::Graph graph;
    ASSERT_TRUE(graph.loadGraphFromFile("graphs/bad2.dot"));
}

TEST(graph, loadBadFile_noVertices) {
    s21::Graph graph;
    ASSERT_TRUE(graph.loadGraphFromFile("graphs/bad3.dot"));
}

TEST(graph, exportGraph) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");
    graph.exportGraphToDot("graphs/export.dot");

    s21::Graph graph2;
    ASSERT_TRUE(graph2.loadGraphFromFile("graphs/export.dot"));

    ASSERT_EQ(graph.countElem(), graph2.countElem());
    ASSERT_EQ(graph.typeGraph(), graph2.typeGraph());
    for (int i = 0; i < graph2.countElem(); i++) {
        for (int j = 0; j < graph2.countElem(); j++) {
            ASSERT_EQ(graph(i, j), graph2(i, j));
        }
    }
}

TEST(graph_algorithms, breadthSearch) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");

    s21::GraphAlgorithms alg;
    auto res = alg.breadthFirstSearch(graph, 1);
    std::vector<int> correct = {1, 2, 3, 6, 4, 5};
    ASSERT_EQ(res.size(), correct.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(res[i], correct[i]);
    }
}

TEST(graph_algorithms, depthSearch) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");

    s21::GraphAlgorithms alg;
    auto res = alg.depthFirstSearch(graph, 1);
    std::vector<int> correct = {1, 2, 6, 5, 3, 4};
    ASSERT_EQ(res.size(), correct.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(res[i], correct[i]);
    }
}

TEST(graph_algorithms, shortestPathBetweenVertices) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");

    s21::GraphAlgorithms alg;
    auto res = alg.getShortestPathBetweenVertices(graph, 1, 4);
    ASSERT_EQ(res, 16);
}

TEST(graph_algorithms, shortestPathsBetweenAllVertices) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");

    s21::GraphAlgorithms alg;
    auto res = alg.getShortestPathsBetweenAllVertices(graph);
    std::vector<std::vector<int>> correct = {{0, 8, 13, 16, 23, 17},
                                             {8, 0, 21, 24, 21, 9},
                                             {13, 21, 0, 3, 10, 22},
                                             {16, 24, 3, 0, 11, 23},
                                             {23, 21, 10, 11, 0, 12},
                                             {17, 9, 22, 23, 12, 0}};
    ASSERT_EQ(res.size(), correct.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(res[i].size(), correct[i].size());
        for (int j = 0; j < res[i].size(); j++) {
            ASSERT_EQ(res[i][j], correct[i][j]);
        }
    }
}

TEST(graph_algorithms, leastSpanningTree) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");

    s21::GraphAlgorithms alg;
    auto res = alg.getLeastSpanningTree(graph);
    std::vector<std::vector<int>> correct = {{0, 8, 0, 0, 0, 0},
                                             {8, 0, 0, 0, 0, 9},
                                             {0, 0, 0, 3, 10, 0},
                                             {0, 0, 3, 0, 0, 0},
                                             {0, 0, 10, 0, 0, 12},
                                             {0, 9, 0, 0, 12, 0}};
    ASSERT_EQ(res.size(), correct.size());
    for (int i = 0; i < res.size(); i++) {
        ASSERT_EQ(res[i].size(), correct[i].size());
        for (int j = 0; j < res[i].size(); j++) {
            ASSERT_EQ(res[i][j], correct[i][j]);
        }
    }
}

TEST(graph_algorithms, antAlgorithm) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");

    s21::GraphAlgorithms alg;
    auto res = alg.solveTravelingSalesmanProblem(graph);
    s21::TsmResult correct;
    correct.distance = 56;
    correct.vertices = std::vector<int>({1, 2, 6 ,5, 4, 3, 1});
    ASSERT_EQ(res.distance, correct.distance);
    ASSERT_EQ(res.vertices.size(), correct.vertices.size());
}

TEST(graph_algorithms, geneticAlgorithm) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");

    s21::GraphAlgorithms alg;
    auto res = alg.geneticAlgorithm(graph);
    s21::TsmResult correct;
    correct.distance = 56;
    correct.vertices = std::vector<int>({1, 2, 6 ,5, 4, 3, 1});
    ASSERT_EQ(res.distance, correct.distance);
    ASSERT_EQ(res.vertices.size(), correct.vertices.size());
}

TEST(graph_algorithms, greedyAlgorithm) {
    s21::Graph graph;
    graph.loadGraphFromFile("graphs/1.dot");

    s21::GraphAlgorithms alg;
    auto res = alg.greedyAlgorithm(graph);
    s21::TsmResult correct;
    correct.distance = 56;
    correct.vertices = std::vector<int>({1, 2, 6 ,5, 4, 3, 1});
    ASSERT_TRUE(res.distance > correct.distance);
    ASSERT_EQ(res.vertices.size(), correct.vertices.size());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
