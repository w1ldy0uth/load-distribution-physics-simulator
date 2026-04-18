#include "solver/Solver.hpp"

#include <iostream>

int main() {
    solver::Model1D model;

    model.nodes.push_back({
        .id = 1,
        .x = 0.0,
        .fixed = true
    });
    model.nodes.push_back({
        .id = 2,
        .x = 1.0,
        .fixed = false
    });
    model.springs.push_back({
        .id = 1,
        .nodeA = 1,
        .nodeB = 2,
        .stiffness = 1000.0
    });
    model.loads.push_back({
        .node = 2,
        .force = 100.0
    });

    const solver::Solver1D solver;
    const auto result = solver.solve(model);

    std::cout << "Displacements:\n";

    for (const auto& displacement : result.displacements) {
        std::cout
            << " node=" << displacement.node
            << ", ux=" << displacement.ux
            << "\n";
    }

    std::cout << "Reactions:\n";

    for (const auto& reaction : result.reactions) {
        std::cout
            << "  node=" << reaction.node
            << ", fx=" << reaction.fx
            << "\n";
    }

    return 0;
}
