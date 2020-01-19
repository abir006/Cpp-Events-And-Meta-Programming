//
// Created by Shahak on 19/01/2020.
//

#ifndef OOP_HW5_MOVEVEHICLE_H
#define OOP_HW5_MOVEVEHICLE_H

#include "GameBoard.h"
#include "CellType.h"
#include "Direction.h"

/// The c'tor receives the parameters and defines the struct describing the action to be made on the board.
template<CellType T, Direction D, int A>
struct Move {
    static_assert(A >= 0, "MoveVehicle: AMOUNT IS ILLEGAL (must be non-negative)");
    static_assert(T != EMPTY, "MoveVehicle: CELLTYPE IS ILLEGAL (must be different than EMPTY)");
    constexpr static CellType type = T;
    constexpr static Direction direction = D;
    constexpr static int amount = A;
};

/// Receives the current board, row & column, direction and length to move and updates the board.
template<typename B, int R, int C, Direction D, int A>
struct MoveVehicle {
    typedef B board; //TODO to be completed
};

#endif //OOP_HW5_MOVEVEHICLE_H