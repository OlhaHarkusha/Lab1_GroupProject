#include "shared_types.h"
#include <vector>
#include <algorithm>

namespace {

std::vector<Edge> collectEdges(const InputData& data) {
    std::vector<Edge> edges;
    for (int u = 0; u < data.vertexCount; ++u) {
        for (const auto& [v, w] : data.adjacency[u]) {
            edges.push_back({u, v, w});
        }
    }
    return edges;
}

std::vector<int> reconstructPath(const std::vector<int>& prev, int source, int destination) {
    std::vector<int> path;
    if (prev[destination] == -1 && source != destination) {
        return path;
    }
    for (int v = destination; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data) {
    auto result = std::make_unique<Result>();
    result->algorithmName = "Bellman-Ford";

    const int n = data->vertexCount;
    const int src = data->source;
    const int dst = data->destination;

    std::vector<double> dist(n, INF);
    std::vector<int> prev(n, -1);
    dist[src] = 0.0;

    const auto edges = collectEdges(*data);

    int iterations = 0;
    bool changed = true;

    for (int i = 0; i < n - 1 && changed; ++i) {
        changed = false;
        ++iterations;
        for (const auto& e : edges) {
            if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.weight;
                prev[e.to] = e.from;
                changed = true;
            }
        }
    }

    result->iterations = iterations;

    if (dist[dst] == INF) {
        result->pathFound = false;
        result->pathLength = INF;
        return result;
    }

    result->pathFound = true;
    result->pathLength = dist[dst];
    result->path = reconstructPath(prev, src, dst);
    return result;
}