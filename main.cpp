#include <iostream>
#include <memory>
#include <chrono>
#include <iomanip>
#include <cmath>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "shared_types.h"

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);

std::shared_ptr<const InputData> createTestGraph() {
    auto data = std::make_shared<InputData>();
    data->numVertices = 6;                  // ← numVertices, не vertexCount
    data->source = 0;
    data->destination = 5;
    data->adjacency.resize(6);

    auto addEdge = [&](int u, int v, double w) {
        data->adjacency[u].push_back({v, w});
        data->adjacency[v].push_back({u, w});
    };

    addEdge(0, 1, 4.0);
    addEdge(0, 3, 8.0);
    addEdge(1, 2, 8.0);
    addEdge(1, 4, 11.0);
    addEdge(2, 5, 7.0);
    addEdge(3, 4, 7.0);
    addEdge(4, 5, 2.0);

    return data;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "=== Лабораторна робота №1. Варіант 11 ===\n";
    std::cout << "Порівняння алгоритмів Дейкстри та Беллмана-Форда\n\n";

    auto data = createTestGraph();

    std::cout << "Граф: " << data->numVertices << " вершин\n";
    std::cout << "Джерело: " << data->source
              << ", Призначення: " << data->destination << "\n\n";

    auto startA = std::chrono::high_resolution_clock::now();
    auto resultA = calculateA(data);
    auto endA = std::chrono::high_resolution_clock::now();
    auto timeA = std::chrono::duration_cast<std::chrono::microseconds>(endA - startA).count();

    auto startB = std::chrono::high_resolution_clock::now();
    auto resultB = calculateB(data);
    auto endB = std::chrono::high_resolution_clock::now();
    auto timeB = std::chrono::duration_cast<std::chrono::microseconds>(endB - startB).count();

    // Structured bindings — 5 імен, бо Result має 5 полів
    auto [distanceA, pathA, iterationsA, nameA, foundA] = *resultA;
    auto [distanceB, pathB, iterationsB, nameB, foundB] = *resultB;

    std::cout << "--- Результат " << nameA << " ---\n";
    if (foundA) {
        std::cout << "Довжина шляху: " << distanceA << "\n";
        std::cout << "Шлях: ";
        for (size_t i = 0; i < pathA.size(); ++i) {
            std::cout << pathA[i];
            if (i + 1 < pathA.size()) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "Шлях не знайдено\n";
    }
    std::cout << "Кількість ітерацій: " << iterationsA << "\n";
    std::cout << "Час виконання: " << timeA << " мкс\n\n";

    std::cout << "--- Результат " << nameB << " ---\n";
    if (foundB) {
        std::cout << "Довжина шляху: " << distanceB << "\n";
        std::cout << "Шлях: ";
        for (size_t i = 0; i < pathB.size(); ++i) {
            std::cout << pathB[i];
            if (i + 1 < pathB.size()) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "Шлях не знайдено\n";
    }
    std::cout << "Кількість ітерацій: " << iterationsB << "\n";
    std::cout << "Час виконання: " << timeB << " мкс\n\n";

    std::cout << "=== Порівняння ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Різниця в довжині шляху: "
              << std::fabs(distanceA - distanceB) << "\n";
    std::cout << "Шляхи " << (pathA == pathB ? "збігаються" : "відрізняються") << "\n";

    if (iterationsB > 0) {
        std::cout << "Співвідношення ітерацій (A/B): "
                  << static_cast<double>(iterationsA) / iterationsB << "\n";
    }
    if (timeB > 0) {
        std::cout << "Співвідношення часу (A/B): "
                  << static_cast<double>(timeA) / timeB << "\n";
    }

    return 0;
}