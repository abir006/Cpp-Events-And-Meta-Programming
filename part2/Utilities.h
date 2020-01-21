//
// Created by Shahak on 17/01/2020.
//

#ifndef OOP_HW5_UTILITIES_H
#define OOP_HW5_UTILITIES_H

#include "GameBoard.h"

/// Declaring Conditional.
/// This declaration defines an expression that is evaluated to True, therefore value is of type T.
template<bool B, typename T, typename F>
struct Conditional {
    typedef T value;
};

/// This declaration deals with a False expression through specialization, therefore value is of type F.
template<typename T, typename F>
struct Conditional<false, T, F> {
    typedef F value;
};

/// Declaring ConditionalInteger
/// This declaration defines an expression that is evaluated to True, therefore value is the integer T.
template<bool B, int T, int F>
struct ConditionalInteger {
    constexpr static int value = T;
};

/// This declaration deals with a False expression through specialization, therefore value is the integer F.
template<int T, int F>
struct ConditionalInteger<false, T, F> {
    constexpr static int value = F;
};

/// Receives a board and indexes and returns the cell type
template<typename B, int R, int C>
struct GetCellTypeInBoard {
    constexpr static CellType T =
            GetAtIndex<C, typename /// Outer GetAtIndex - receives the result of the inner GetAtIndex, which will be a list (row)
            GetAtIndex<R, typename B::board> /// Inner GetAtIndex - gets the list at row R and returns it's elements (value)
            ::value> /// Outer GetAtIndex - takes the element in column C after getting row R
            ::value::type; /// Extracts the type of the cell
};

/// Receives a board and indexes and returns the direction of the vehicle
template<typename B, int R, int C>
struct GetCellDirectionInBoard {
    constexpr static Direction D =
            GetAtIndex<C, typename /// Outer GetAtIndex - receives the result of the inner GetAtIndex, which will be a list (row)
            GetAtIndex<R, typename B::board> /// Inner GetAtIndex - gets the list at row R and returns it's elements (value)
            ::value> /// Outer GetAtIndex - takes the element in column C after getting row R
            ::value::direction; /// Extracts the direction of the cell
};

#endif //OOP_HW5_UTILITIES_H
