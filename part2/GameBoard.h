//
// Created by Shahak on 18/01/2020.
//

#ifndef OOP_HW5_GAMEBOARD_H
#define OOP_HW5_GAMEBOARD_H

#include "BoardCell.h"
#include "List.h"
#include "CellType.h"

/// The c'tor receives the board as a list of lists and holds it's dimensions.
    template<typename B> /// The board type doesn't need to be specified as we are assured to have a correct input
    struct GameBoard {
        typedef B board; /// Using typedef as we only have the type B and not a concrete value
        constexpr static int width = B::head::size; /// The width is the number of columns, which is the number of elements in each list.
        constexpr static int length = B::size; /// The length is the number of rows, which is the number of lists.
};

#endif //OOP_HW5_GAMEBOARD_H
