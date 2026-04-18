#pragma once

#include <vector>
#include <cstddef>

namespace solver {

    using NodeId = std::size_t;
    using ElementId =  std::size_t;

    struct Node1D {
        NodeId id;
        double x;
        bool fixed = false;
    };

    struct Spring1D {
        ElementId id;
        NodeId nodeA;
        NodeId nodeB;
        double stiffness;
    };

    struct PointLoad1D {
        NodeId node;
        double force;
    };

    struct Model1D {
        std::vector<Node1D> nodes;
        std::vector<Spring1D> springs;
        std::vector<PointLoad1D> loads;
    };
}