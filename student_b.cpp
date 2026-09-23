#include "shared_types.h"

#include <memory>       // ← обов'язково
#include <vector>
#include <algorithm>
#include <limits>

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data) {
    auto result = std::make_unique<Result>();
    result->algorithmName = "Алгоритм Беллмана-Форда";
    result->iterations = 0;
    result->pathFound = false;

    const int n = data->numVertices;
    const int src = data->source;
    const int dst = data->destination;

    const double INF = std::numeric_limits<double>::infinity();

    std::vector<double> dist(n, INF);
    std::vector<int> prev(n, -1);
    dist[src] = 0.0;

    struct RawEdge { int from; int to; double weight; };
    std::vector<RawEdge> edges;
    for (int u = 0; u < n; ++u) {
        for (const auto& e : data->adjacency[u]) {
            edges.push_back({u, e.to, e.weight});
        }
    }

    bool changed = true;
    for (int i = 0; i < n - 1 && changed; ++i) {
        changed = false;
        ++result->iterations;

        for (const auto& e : edges) {
            if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.weight;
                prev[e.to] = e.from;
                changed = true;
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