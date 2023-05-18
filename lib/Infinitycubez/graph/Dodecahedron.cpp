#include "Dodecahedron.h"

namespace infc
{
  GraphDefinition makeInfinityCubeD12(int ledsPerEdge)
  {
    return {{0 * ledsPerEdge, 1 * ledsPerEdge - 1, 0, 1},
            {1 * ledsPerEdge, 2 * ledsPerEdge - 1, 1, 5},
            {2 * ledsPerEdge, 3 * ledsPerEdge - 1, 5, 10},
            {3 * ledsPerEdge, 4 * ledsPerEdge - 1, 10, 15},
            {4 * ledsPerEdge, 5 * ledsPerEdge - 1, 15, 16},
            {5 * ledsPerEdge, 6 * ledsPerEdge - 1, 11, 5},
            {6 * ledsPerEdge, 7 * ledsPerEdge - 1, 1, 2},
            {7 * ledsPerEdge, 8 * ledsPerEdge - 1, 2, 6},
            {8 * ledsPerEdge, 9 * ledsPerEdge - 1, 6, 11},
            {9 * ledsPerEdge, 10 * ledsPerEdge - 1, 11, 16},
            {10 * ledsPerEdge, 11 * ledsPerEdge - 1, 16, 17},
            {11 * ledsPerEdge, 12 * ledsPerEdge - 1, 12, 6},
            {12 * ledsPerEdge, 13 * ledsPerEdge - 1, 2, 3},
            {13 * ledsPerEdge, 14 * ledsPerEdge - 1, 3, 7},
            {14 * ledsPerEdge, 15 * ledsPerEdge - 1, 7, 12},
            {15 * ledsPerEdge, 16 * ledsPerEdge - 1, 12, 17},
            {16 * ledsPerEdge, 17 * ledsPerEdge - 1, 17, 18},
            {17 * ledsPerEdge, 18 * ledsPerEdge - 1, 13, 7},
            {18 * ledsPerEdge, 19 * ledsPerEdge - 1, 3, 4},
            {19 * ledsPerEdge, 20 * ledsPerEdge - 1, 4, 8},
            {20 * ledsPerEdge, 21 * ledsPerEdge - 1, 8, 13},
            {21 * ledsPerEdge, 22 * ledsPerEdge - 1, 13, 18},
            {22 * ledsPerEdge, 23 * ledsPerEdge - 1, 18, 19},
            {23 * ledsPerEdge, 24 * ledsPerEdge - 1, 14, 8},
            {24 * ledsPerEdge, 25 * ledsPerEdge - 1, 4, 0},
            {25 * ledsPerEdge, 26 * ledsPerEdge - 1, 0, 9},
            {26 * ledsPerEdge, 27 * ledsPerEdge - 1, 9, 14},
            {27 * ledsPerEdge, 28 * ledsPerEdge - 1, 14, 19},
            {28 * ledsPerEdge, 29 * ledsPerEdge - 1, 19, 15},
            {29 * ledsPerEdge, 30 * ledsPerEdge - 1, 10, 9}};
  }

}
