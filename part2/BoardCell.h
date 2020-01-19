//
// Created by Shahak on 18/01/2020.
//

#ifndef OOP_HW5_BOARDCELL_H
#define OOP_HW5_BOARDCELL_H

#include "CellType.h"
#include "Direction.h"
#include <iostream>

/// The c'tor receives the actual values representing the cell, therefore using constexpr to set the values the struct fields will hold.
template<CellType T, Direction D, int L>
struct BoardCell {
    static_assert(L >= 0, "BoardCell: LENGTH IS ILLEGAL (must be non-negative)");
    constexpr static CellType type = T;
    constexpr static Direction direction = D;
    constexpr static int length = L;
};

#endif //OOP_HW5_BOARDCELL_H