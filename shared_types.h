#pragma once

#include <vector>
#include <string>
#include <utility>

// Ребро зваженого графа: (суміжна вершина, вага)
struct Edge {
    int to;
    double weight;
};

// Спільні вхідні дані для обох алгоритмів
struct InputData {
    int numVertices;                          // кількість вершин
    int source;                               // вершина-джерело
    int destination;                          // вершина призначення
    std::vector<std::vector<Edge>> adjacency; // список суміжності
};

// Результат роботи алгоритму
struct Result {
    double distance;                // довжина найкоротшого шляху
    std::vector<int> path;          // послідовність вершин шляху
    int iterations;                 // кількість виконаних ітерацій
    std::string algorithmName;      // назва алгоритму
};