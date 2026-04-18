#pragma once

#include "Model.hpp"
#include "Result.hpp"

namespace solver {

    class Solver1D {
        public:
            SolveResult1D solve(const Model1D& model) const;
    };
}