#include "shared_types.h"

#include <queue>
#include <limits>
#include <algorithm>
#include <memory>       // ← обов'язково для unique_ptr/shared_ptr

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data) {
    auto result = std::make_unique<Result>();
    result->algorithmName = "Алгоритм Дейкстри";
    result->iterations = 0;
    result->pathFound = false;

    const int n = data->numVertices;
    const int src = data->source;
    const int dst = data->destination;

    const double INF = std::numeric_limits<double>::infinity();

    std::vector<double> dist(n, INF);
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

    dist[src] = 0.0;

    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0.0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        ++result->iterations;

        if (u == dst) break;

        for (const auto& edge : data->adjacency[u]) {
            int v = edge.to;
            double w = edge.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    result->distance = dist[dst];

    if (dist[dst] == INF) {
        result->pathFound = false;
        return result;
    }

    std::vector<int> path;
    for (int v = dst; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    result->path = std::move(path);
    result->pathFound = true;

    return result;
}