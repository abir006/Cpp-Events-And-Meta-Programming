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

/// Receives a board and indexes and returns the length of the vehicle
template<typename B, int R, int C>
struct GetCellLengthInBoard {
    constexpr static int length =
            GetAtIndex<C, typename /// Outer GetAtIndex - receives the result of the inner GetAtIndex, which will be a list (row)
            GetAtIndex<R, typename B::board> /// Inner GetAtIndex - gets the list at row R and returns it's elements (value)
            ::value> /// Outer GetAtIndex - takes the element in column C after getting row R
            ::value::length; /// Extracts the length of the vehicle
};

/// Receives the board, a horizontal car and current index and finds the rear of the car (left side).
/// IMPORTANT - this method assumes that (Board[R, C] == T) for the initial R, C
template<typename B, CellType T, int R, int C>
struct FindCarRear {
    constexpr static int rear =
            ConditionalInteger<GetCellTypeInBoard<B, R, C>::T == T, /// Apply a condition by the vehicle in the current index, as in true if it's T
                    FindCarRear<B, T, R, C - 1>::rear, /// If it equals to T, call recursively for the previous column
                    (C + 1)>::value; /// If it does not equal to T, the result will be the previous column
};

/// Stopping criteria for FindCarRear - if we reached column 0, it's 0 if the current cell is T or 1 if it's different than T
template<typename B, CellType T, int R>
struct FindCarRear<B, T, R, 0> {
    constexpr static int rear = ConditionalInteger<GetCellTypeInBoard<B, R, 0>::T == T, 0, 1>::value; /// If we got to column 0, stop and set the rear index
};

/// Sets a given BoardCell in given indexes of the board
template<typename B, int R, int C_, CellType T, Direction D, int L>
struct SetBoardCell {
    typedef typename GetAtIndex<R, typename B::board>::value Row; /// Get the row of the cell to be updated
    typedef typename SetAtIndex<C_, BoardCell<T, D, L>, Row>::list updatedRow; /// Updated the vehicle in the relevant index
    typedef typename SetAtIndex<R, updatedRow, typename B::board>::list B_; /// Update the board with the updated row
    typedef GameBoard<B_> updatedBoard;

    /// Equivalent to:
/*    typedef typename
            SetAtIndex<R, typename /// Update the entire row in the board
            SetAtIndex<C_, BoardCell<T, D, L>, typename GetAtIndex<R, typename B::board>::value>::list, /// Get the row from the board and set the new value
            B>::list updatedBoard; /// Get the board (list of lists) and assign to updatedBoard*/
};

/// Checking if the car is in this row (except for col 0 which will be in next struct).
/// If the car is not in this row, return -1.
template<typename B, CellType T ,int R, int C>
struct isCarInRow { /// Checking if this cell has the car T, if not - recursively check if any col in this row has it.
    constexpr static int col = ConditionalInteger<GetCellTypeInBoard<B, R, C>::T == T, C, isCarInRow<B, T, R, C - 1>::col>::value;
};

/// Stopping condition - checking if the car is in this row at col 0, if its not then return -1.
template<typename B, CellType T, int R>
struct isCarInRow<B, T, R, 0> {
    constexpr static int col = ConditionalInteger<GetCellTypeInBoard<B, R, 0>::T == T, 0, -1>::value;
};

/// Stopping condition - checking if the car is in this row at col 0, if its not then return -1.
template<typename B, CellType T, int C>
struct isCarInRow<B, T, 0, C> {
    constexpr static int col = ConditionalInteger<GetCellTypeInBoard<B, 0, C>::T == T, C, isCarInRow<B, T, 0, C - 1>::col>::value;
};

/// Getting a car row and col.
template<typename B, CellType T, int R, int C>
struct FindCar {
    /// Checking if the car is in the row (will start from last row), if it is, will return the row, else will check if its in previous row.
    constexpr static int row = ConditionalInteger<isCarInRow<B, T, R, C>::col != -1, R, FindCar<B, T, R - 1, C>::row>::value;
    /// Same checks, except returning the col instead of row.
    constexpr static int col = ConditionalInteger<isCarInRow<B, T, R, C>::col != -1, isCarInRow<B, T, R, C>::col, FindCar<B,T, R - 1,C>::col>::value;
    static_assert(col != -1, "FindCar: Car not found");
    static_assert(row != -1, "FindCar: Car not found");
};

template<typename B, int R, int C>
struct checkIfAllColsEmptyOrRed{
    constexpr static bool result =
            /// Outer condition - checks if type is NOT x or empty
            ConditionalInteger<GetCellTypeInBoard<B, R, C>::T != X && GetCellTypeInBoard<B, R, C>::T != EMPTY, false, // False if other than EMPTY/X
                    /// Inner condition - if it's X or EMPTY check if next col is out of bounds, if so return True, else check next col.
                    ConditionalInteger<B::width <= C + 1, true, checkIfAllColsEmptyOrRed<B, R, C + 1>::result>::value>::value;
};

#endif //OOP_HW5_UTILITIES_H