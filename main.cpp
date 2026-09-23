#include <iostream>
#include <memory>
#include <chrono>
#include <iomanip>
#include <cmath>

#include "shared_types.h"

// Оголошення функцій студентів
std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data);
std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data);

// Допоміжна функція для створення тестового графа
std::shared_ptr<const InputData> createTestGraph() {
    auto data = std::make_shared<InputData>();
    data->numVertices = 6;
    data->source = 0;
    data->destination = 5;
    data->adjacency.resize(6);

    auto addEdge = [&](int u, int v, double w) {
        data->adjacency[u].push_back({v, w});
        data->adjacency[v].push_back({u, w}); // неорієнтований граф
    };

    // Тестовий граф:
    //   0 --4-- 1 --8-- 2
    //   |       |       |
    //   8       11      7
    //   |       |       |
    //   3 --7-- 4 --2-- 5
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
	SetConsoleOutputCP(CP_UTF8);   
    SetConsoleCP(CP_UTF8);
    std::cout << "=== Лабораторна робота №1. Варіант 11 ===\n";
    std::cout << "Порівняння алгоритмів Дейкстри та Беллмана-Форда\n\n";

    // Єдиний екземпляр вхідних даних для обох алгоритмів
    auto data = createTestGraph();

    std::cout << "Граф: " << data->numVertices << " вершин\n";
    std::cout << "Джерело: " << data->source
              << ", Призначення: " << data->destination << "\n\n";

    // --- Алгоритм Студента А (Дейкстра) ---
    auto startA = std::chrono::high_resolution_clock::now();
    auto resultA = calculateA(data);
    auto endA = std::chrono::high_resolution_clock::now();
    auto timeA = std::chrono::duration_cast<std::chrono::microseconds>(endA - startA).count();

    // --- Алгоритм Студента Б (Беллман-Форд) ---
    auto startB = std::chrono::high_resolution_clock::now();
    auto resultB = calculateB(data);
    auto endB = std::chrono::high_resolution_clock::now();
    auto timeB = std::chrono::duration_cast<std::chrono::microseconds>(endB - startB).count();

    // --- Structured bindings ---
    auto [distanceA, pathA, iterationsA, nameA] = *resultA;
    auto [distanceB, pathB, iterationsB, nameB] = *resultB;

    std::cout << "--- Результат " << nameA << " ---\n";
    std::cout << "Довжина шляху: " << distanceA << "\n";
    std::cout << "Шлях: ";
    for (size_t i = 0; i < pathA.size(); ++i) {
        std::cout << pathA[i];
        if (i + 1 < pathA.size()) std::cout << " -> ";
    }
    std::cout << "\nКількість ітерацій: " << iterationsA << "\n";
    std::cout << "Час виконання: " << timeA << " мкс\n\n";

    std::cout << "--- Результат " << nameB << " ---\n";
    std::cout << "Довжина шляху: " << distanceB << "\n";
    std::cout << "Шлях: ";
    for (size_t i = 0; i < pathB.size(); ++i) {
        std::cout << pathB[i];
        if (i + 1 < pathB.size()) std::cout << " -> ";
    }
    std::cout << "\nКількість ітерацій: " << iterationsB << "\n";
    std::cout << "Час виконання: " << timeB << " мкс\n\n";

    std::cout << "=== Порівняння ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Різниця в довжині шляху: "
              << std::fabs(distanceA - distanceB) << "\n";
    std::cout << "Шляхи " << (pathA == pathB ? "збігаються" : "відрізняються") << "\n";
    std::cout << "Співвідношення ітерацій (A/B): "
              << static_cast<double>(iterationsA) / iterationsB << "\n";
    std::cout << "Співвідношення часу (A/B): "
              << static_cast<double>(timeA) / timeB << "\n";

    return 0;
}