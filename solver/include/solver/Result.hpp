#pragma once

#include <vector>
#include <cstddef>

namespace solver {

    using NodeId =  std::size_t;

    struct NodeDisplacement1D {
        NodeId node;
        double ux;
    };

    struct ReactionForce1D {
        NodeId node;
        double fx;
    };

    struct SolveResult1D {
        std::vector<NodeDisplacement1D> displacements;
        std::vector<ReactionForce1D> reactions;
    };
}