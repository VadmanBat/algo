#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace algo {
class KahnTopologicalSort {
    using size      = std::size_t;
    using GraphType = std::unordered_map<size, std::vector<size>>;

    GraphType graph;
    std::vector<size> loop_breakers;

    std::vector<size> order;
    std::vector<size> broken_loop_breakers;
    std::unordered_map<size, int> indegree;

    size num_nodes = 0;

    void compute_indegrees() {
        indegree.clear();
        std::unordered_set<size> nodes;

        for (const auto& [u, adj] : graph) {
            nodes.insert(u);
            for (auto v : adj) {
                nodes.insert(v);
                ++indegree[v];
            }
        }

        for (auto node : nodes)
            indegree.try_emplace(node, 0);

        num_nodes = nodes.size();
    }

    void perform_sort() {
        compute_indegrees();

        std::queue<size> q;
        for (const auto& [node, deg] : indegree)
            if (deg == 0)
                q.push(node);

        order.clear();
        broken_loop_breakers.clear();
        order.reserve(num_nodes);

        while (true) {
            if (q.empty()) {
                size chosen = static_cast<size>(-1);
                for (size b : loop_breakers)
                    if (auto it = indegree.find(b); it != indegree.end() && it->second > 0) {
                        chosen = b;
                        break;
                    }

                if (chosen == static_cast<size>(-1))
                    break;

                broken_loop_breakers.push_back(chosen);
                q.push(chosen);
                indegree[chosen] = 0;
            }

            auto u = q.front();
            q.pop();
            order.push_back(u);

            if (auto it = graph.find(u); it != graph.end())
                for (auto v : it->second)
                    if (--indegree[v] == 0)
                        q.push(v);
        }
    }

public:
    explicit KahnTopologicalSort(GraphType g, const std::vector<size>& breakers = {})
        : graph(std::move(g)), loop_breakers(breakers) {
        perform_sort();
    }

    std::vector<size> result() const {
        return order;
    }

    std::vector<size> brokenLoopBreakers() const {
        return broken_loop_breakers;
    }

    bool hasUnbrokenCycle() const {
        return order.size() < num_nodes;
    }

    size nodeCount() const {
        return num_nodes;
    }
};
}