#include <iostream>
#include <memory>
#include <chrono>
#include <cmath>
#include "shared_types.h"

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);

std::shared_ptr<const InputData> buildTestGraph() {
    auto data = std::make_shared<InputData>();
    data->vertexCount = 6;
    data->adjacency.resize(6);

    auto addEdge = [&](int u, int v, double w) {
        data->adjacency[u].push_back({v, w});
        data->adjacency[v].push_back({u, w});
    };

    addEdge(0, 1, 7.0);
    addEdge(0, 2, 9.0);
    addEdge(0, 5, 14.0);
    addEdge(1, 2, 10.0);
    addEdge(1, 3, 15.0);
    addEdge(2, 3, 11.0);
    addEdge(2, 5, 2.0);
    addEdge(3, 4, 6.0);
    addEdge(4, 5, 9.0);

    data->source = 0;
    data->destination = 4;
    return data;
}

int main() {
    std::cout << "=== Laboratory work #1. Variant 11 ===\n";
    std::cout << "Graph shortest path comparison\n\n";

    auto data = buildTestGraph();

    // --- Студент А: алгоритм Дейкстри ---
    auto startA = std::chrono::high_resolution_clock::now();
    auto resultA = calculateA(data);
    auto endA = std::chrono::high_resolution_clock::now();

    auto [lengthA, pathA, itersA, foundA, nameA] = *resultA;

    std::cout << "Algorithm A (" << nameA << "):\n";
    if (foundA) {
        std::cout << "  Path length: " << lengthA << "\n";
        std::cout << "  Path: ";
        for (size_t i = 0; i < pathA.size(); ++i)
            std::cout << pathA[i] << (i + 1 < pathA.size() ? " -> " : "");
        std::cout << "\n";
    } else {
        std::cout << "  Path not found\n";
    }
    std::cout << "  Iterations: " << itersA << "\n";
    std::cout << "  Time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endA - startA).count()
              << " us\n\n";

    // --- Студент Б: алгоритм Беллмана–Форда ---
    auto startB = std::chrono::high_resolution_clock::now();
    auto resultB = calculateB(data);
    auto endB = std::chrono::high_resolution_clock::now();

    auto [lengthB, pathB, itersB, foundB, nameB] = *resultB;

    std::cout << "Algorithm B (" << nameB << "):\n";
    if (foundB) {
        std::cout << "  Path length: " << lengthB << "\n";
        std::cout << "  Path: ";
        for (size_t i = 0; i < pathB.size(); ++i)
            std::cout << pathB[i] << (i + 1 < pathB.size() ? " -> " : "");
        std::cout << "\n";
    } else {
        std::cout << "  Path not found\n";
    }
    std::cout << "  Iterations: " << itersB << "\n";
    std::cout << "  Time: "
              << std::chrono::duration_cast<std::chrono::microseconds>(endB - startB).count()
              << " us\n\n";

    // --- Порівняння ---
    std::cout << "=== Comparison ===\n";
    if (foundA && foundB) {
        std::cout << "Path lengths match: "
                  << (std::abs(lengthA - lengthB) < 1e-9 ? "YES" : "NO") << "\n";
        std::cout << "Paths match: "
                  << (pathA == pathB ? "YES" : "NO") << "\n";
        std::cout << "Iterations: A=" << itersA << ", B=" << itersB << "\n";
    }

    return 0;
}