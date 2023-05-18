#pragma once

#include "GraphDefinition.h"

namespace infc
{
GraphDefinition makeInfinityCubeD12(uint32_t ledsPerEdge)
{
  return std::vector<EdgeDefinition>{
        {0 * ledsPerEdge, 1 * ledsPerEdge, 0, 1},
        {1 * ledsPerEdge, 2 * ledsPerEdge, 1, 5},
        {2 * ledsPerEdge, 3 * ledsPerEdge, 5, 10},
        {3 * ledsPerEdge, 4 * ledsPerEdge, 10, 15},
        {4 * ledsPerEdge, 5 * ledsPerEdge, 15, 16},
        {5 * ledsPerEdge, 6 * ledsPerEdge, 11, 5},
        {6 * ledsPerEdge, 7 * ledsPerEdge, 1, 2},
        {7 * ledsPerEdge, 8 * ledsPerEdge, 2, 6},
        {8 * ledsPerEdge, 9 * ledsPerEdge, 6, 11},
        {9 * ledsPerEdge, 10 * ledsPerEdge, 11, 16},
        {10 * ledsPerEdge, 11 * ledsPerEdge, 16, 17},
        {11 * ledsPerEdge, 12 * ledsPerEdge, 12, 6},
        {12 * ledsPerEdge, 13 * ledsPerEdge, 2, 3},
        {13 * ledsPerEdge, 14 * ledsPerEdge, 3, 7},
        {14 * ledsPerEdge, 15 * ledsPerEdge, 7, 12},
        {15 * ledsPerEdge, 16 * ledsPerEdge, 12, 17},
        {16 * ledsPerEdge, 17 * ledsPerEdge, 17, 18},
        {17 * ledsPerEdge, 18 * ledsPerEdge, 13, 7},
        {18 * ledsPerEdge, 19 * ledsPerEdge, 3, 4},
        {19 * ledsPerEdge, 20 * ledsPerEdge, 4, 8},
        {20 * ledsPerEdge, 21 * ledsPerEdge, 8, 13},
        {21 * ledsPerEdge, 22 * ledsPerEdge, 13, 18},
        {22 * ledsPerEdge, 23 * ledsPerEdge, 18, 19},
        {23 * ledsPerEdge, 24 * ledsPerEdge, 14, 8},
        {24 * ledsPerEdge, 25 * ledsPerEdge, 4, 0},
        {25 * ledsPerEdge, 26 * ledsPerEdge, 0, 9},
        {26 * ledsPerEdge, 27 * ledsPerEdge, 9, 14},
        {27 * ledsPerEdge, 28 * ledsPerEdge, 14, 19},
        {28 * ledsPerEdge, 29 * ledsPerEdge, 19, 15},
        {29 * ledsPerEdge, 30 * ledsPerEdge, 10, 9},
    };
}

}
