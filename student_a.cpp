#include "shared_types.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>

namespace {

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

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data) {
    auto result = std::make_unique<Result>();
    result->algorithmName = "Dijkstra";

    const int n = data->vertexCount;
    const int src = data->source;
    const int dst = data->destination;

    std::vector<double> dist(n, INF);
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

    dist[src] = 0.0;

    using PQItem = std::pair<double, int>;
    std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> pq;
    pq.push({0.0, src});

    int iterations = 0;

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        ++iterations;

        if (u == dst) break;

        for (const auto& [v, weight] : data->adjacency[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
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