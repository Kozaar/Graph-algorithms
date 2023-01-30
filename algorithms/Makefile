SHELL=/bin/sh
CC=g++
CFLAGS=-std=c++17
LDFLAGS=-L. -ls21_graph_algorithms -ls21_graph
SOURCE_GRAPH=model/s21_graph.cpp
SOURCE_GRAPH_ALG=model/s21_graph_algorithms.cpp model/s21_queue.cpp model/s21_stack.cpp model/antalgoritmh.cpp model/geneticAlgorithm.cpp
OS=$(shell uname)
ifeq ($(OS), Linux)
    CHECK_FLAGS=-lgtest -pthread -lrt -lm
else
    CHECK_FLAGS=-lgtest
endif
GCOVFLAGS=--coverage
HTML_CREATE=lcov --no-external -t a.out -o rep.info -c -d .; genhtml -o report rep.info
TEST_COMPILE= $(CC) $(CFLAGS) tests.cpp $(CHECK_FLAGS) $(LDFLAGS)

all: tests app

s21_graph.a:
	$(CC) $(CFLAGS) -c $(SOURCE_GRAPH)
	ar rcs libs21_graph.a s21_graph.o
	ranlib libs21_graph.a

s21_graph_algorithms.a:
	$(CC) $(CFLAGS) -c $(SOURCE_GRAPH_ALG)
	ar rcs libs21_graph_algorithms.a s21_graph_algorithms.o s21_queue.o s21_stack.o antalgoritmh.o geneticAlgorithm.o
	ranlib libs21_graph_algorithms.a

app:
	$(CC) main.cpp interface/*.cpp controller/*.cpp $(SOURCE_GRAPH) $(SOURCE_GRAPH_ALG)
	./a.out

test: tests

tests: s21_graph.a s21_graph_algorithms.a
	$(TEST_COMPILE)
	./a.out
	make clean

clean:
	rm -rf *.g* *.out *.clang-format *.a *.o graphs/export.dot
