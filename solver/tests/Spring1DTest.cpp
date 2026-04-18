#include "solver/Solver.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {

    void assertNear(double actual, double expected, double tolerance, const char* message) {
        if (std::abs(actual - expected) > tolerance) {
            std::cerr
                << "Assertion failed: " << message
                << "\nExpected: " << expected
                << "\nActual: " << actual
                << "\n";

            throw std::runtime_error(message);
        }
    }

    const solver::NodeDisplacement1D& findDisplacement(
        const solver::SolveResult1D& result,
        solver::NodeId node
    ) {
        for (const auto& displacement : result.displacements) {
            if (displacement.node == node) {
                return displacement;
            }
        }

        throw std::runtime_error("Displacement not found");
    }

    const solver::ReactionForce1D& findReaction(
        const solver::SolveResult1D& result,
        solver::NodeId node
    ) {
        for (const auto& reaction : result.reactions) {
            if (reaction.node == node) {
                return reaction;
            }
        }

        throw std::runtime_error("Reaction not found");
    }

    void springDisplacementEqualsForceDividedByStiffness() {
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
        const auto& result = solver.solve(model);

        const auto& freeNodeDisplacement = findDisplacement(result, 2);
        const auto& fixedNodeReaction = findReaction(result, 1);

        assertNear(
            freeNodeDisplacement.ux,
            0.1,
            1e-9,
            "Free node displacement should equal F / k"
        );

        assertNear(
            fixedNodeReaction.fx,
            -100.0,
            1e-9,
            "Fixed node reaction should balance external force"
        );
    }
}

int main() {
    springDisplacementEqualsForceDividedByStiffness();

    std::cout << "All tests passed\n";

    return 0;
}