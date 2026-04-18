#include "solver/Solver.hpp"

#include <stdexcept>
#include <unordered_map>
#include <cmath>

namespace solver {

    namespace {

        const Node1D& findNode(const Model1D& model, NodeId id) {
            for (const auto& node : model.nodes) {
                if (node.id == id) {
                    return node;
                }
            }

            throw std::runtime_error("Node not found");
        }

        double totalLoadAtNode(const Model1D& model, NodeId id) {
            double total = 0.0;

            for (const auto& load : model.loads) {
                if (load.node == id) {
                    total += load.force;
                }
            }

            return total;
        }
    }

    SolveResult1D Solver1D::solve(const Model1D& model) const {
        if (model.nodes.size() != 2) {
            throw std::runtime_error("Initial Solver1D supports exactly 2 nodes");
        }

        if (model.springs.size() != 1) {
            throw std::runtime_error("Initial Solver1D supports exactly 1 spring");
        }

        const auto& spring = model.springs[0];

        if (spring.stiffness <= 0.0) {
            throw std::runtime_error("Spring stiffness must be positive");
        }

        const auto& nodeA = findNode(model, spring.nodeA);
        const auto& nodeB = findNode(model, spring.nodeB);

        if (!nodeA.fixed && !nodeB.fixed) {
            throw std::runtime_error("At least one node must be fixed");
        }

        if (nodeA.fixed && nodeB.fixed) {
            throw std::runtime_error("Initial Solver1D does not support both nodes fixed");
        }

        const Node1D& fixedNode = nodeA.fixed ? nodeA : nodeB;
        const Node1D& freeNode = nodeA.fixed ? nodeB : nodeA;

        const double force = totalLoadAtNode(model, freeNode.id);
        const double displacement = force / spring.stiffness;

        const double reaction = -force;

        SolveResult1D result;

        result.displacements.push_back({
            .node = fixedNode.id,
            .ux = 0.0
        });
        result.displacements.push_back({
            .node = freeNode.id,
            .ux = displacement
        });

        result.reactions.push_back({
            .node = fixedNode.id,
            .fx = reaction
        });

        return result;
    }
}