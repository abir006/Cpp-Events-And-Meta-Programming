//
// Created by Shahak on 19/01/2020.
//

#ifndef OOP_HW5_MOVEVEHICLE_H
#define OOP_HW5_MOVEVEHICLE_H

#include "GameBoard.h"
#include "CellType.h"
#include "Direction.h"
#include "Utilities.h"

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
    static_assert(R >= 0 && R < B::length, "MoveVehicle: ROW NUMBER IS ILLEGAL (must be between 0 and the length of the board)");
    static_assert(C >= 0 && C < B::width, "MoveVehicle: COLUMN NUMBER IS ILLEGAL (must be between 0 and the length of the board)");
    static_assert(GetCellTypeInBoard<B, R, C>::T != EMPTY, "MoveVehicle: CANNOT MOVE AN EMPTY CELL"); /// If it's EMPTY, fail the compilation
    static_assert(
            ((GetCellDirectionInBoard<B, R, C>::D == UP || GetCellDirectionInBoard<B, R, C>::D == DOWN) && (D == UP || D == DOWN)) ||
            ((GetCellDirectionInBoard<B, R, C>::D == LEFT || GetCellDirectionInBoard<B, R, C>::D == RIGHT) && (D == LEFT || D == RIGHT)),
            "MoveVehicle: MOVE DIRECTION DOES NOT MATCH CAR ORIENTATION (must be parallel)"); /// Make sure the car moves in a legal direction
    typedef B board; //TODO to be completed
};

// TODO deal with the case where A = 0
template<typename B, int R, int C, Direction D>
struct MoveVehicle<B, R, C, D, 0> {
    typedef B board; //TODO to be completed
};

/// Receives the board, a horizontal car and current index and finds the rear of the car (left side).
/// IMPORTANT - this method assumes that (Board[R, C] == T) for the initial R, C
template<typename B, CellType T, int R, int C>
struct FindCarRear {
    constexpr static int rear =
            ConditionalInteger<GetCellTypeInBoard<B, R, 0>::T == T, /// Apply a condition by the vehicle in the current index, as in true if it's T
            FindCarRear<B, T, R, C - 1>::rear, /// If it equals to T, call recursively for the previous column
            (C + 1)>::value; /// If it does not equal to T, the result will be the previous column
};

/// Stopping criteria for FindCarRear - if we reached column 0, it's 0 if the current cell is T or 1 if it's different than T
template<typename B, CellType T, int R>
struct FindCarRear<B, T, R, 0> {
    constexpr static int rear = ConditionalInteger<GetCellTypeInBoard<B, R, 0>::T == T, 0, 1>::value; /// If we got to column 0, stop and set the rear index
};

/// Moves the entire vehicle one cell to the left
template<typename B, int R, int C>
struct MoveCarLeftOnce {
    /// Get car details
    constexpr static CellType T = GetCellTypeInBoard<B, R, C>::T;
    constexpr static Direction D = GetCellDirectionInBoard<B, R, C>::D;
    constexpr static int L = GetCellLengthInBoard<B, R, C>::length;
    constexpr static int rear = FindCarRear<B, T, R, C>::rear;
    constexpr static int front = rear + GetCellLengthInBoard<B, R, C>::length - 1;

    static_assert((GetCellTypeInBoard<B, R, (rear - 1)>::T == EMPTY),
                  "MoveVehicle: BOARD CELL ALREADY OCCUPIED"); /// Check that there's no car in the cell the car is moving to

    typedef typename SetBoardCell<B, R, (rear - 1), T, LEFT, L>::updatedBoard B_; /// Move the rear one cell to the left
    typedef typename SetBoardCell<B_ , R, front, EMPTY, D, 0>::updatedBoard updatedBoard; /// Erase the front cell
};

/// Moves the entire vehicle A cells to the left
template<typename B, int R, int C, int A>
struct MoveCarLeft {
    /// Get car details
    constexpr static CellType T = GetCellTypeInBoard<B, R, C>::T;
    constexpr static int rear = FindCarRear<B, T, R, C>::rear;

    typedef typename MoveCarLeftOnce<B, R, C>::updatedBoard B_; /// Move the car once to the left
    typedef typename Conditional<(A - 1) >= 1, /// Check if we should move the car again
            typename MoveCarLeft<B_, R, (rear - 1), (A - 1)>::updatedBoard, /// Call recursively with updated rear and amount
            B_>::value updatedBoard; /// Otherwise, set the updated board as the current one
};

/// Moves the entire vehicle one cell to the right
template<typename B, int R, int C>
struct MoveCarRightOnce {
    /// Get car details
    constexpr static CellType T = GetCellTypeInBoard<B, R, C>::T;
    constexpr static Direction D = GetCellDirectionInBoard<B, R, C>::D;
    constexpr static int L = GetCellLengthInBoard<B, R, C>::length;
    constexpr static int rear = FindCarRear<B, T, R, C>::rear;
    constexpr static int front = rear + GetCellLengthInBoard<B, R, C>::length - 1;

    static_assert((GetCellTypeInBoard<B, R, (front + 1)>::T == EMPTY),
                  "MoveVehicle: BOARD CELL ALREADY OCCUPIED"); /// Check that there's no car in the cell the car is moving to

    typedef typename SetBoardCell<B, R, (front + 1), T, RIGHT, L>::updatedBoard B_; /// Move the front one cell to the right
    typedef typename SetBoardCell<B_ , R, rear, EMPTY, D, 0>::updatedBoard updatedBoard; /// Erase the rear cell
};

/// Moves the entire vehicle A cells to the right
template<typename B, int R, int C, int A>
struct MoveCarRight {
    /// Get car details
    constexpr static CellType T = GetCellTypeInBoard<B, R, C>::T;
    constexpr static int rear = FindCarRear<B, T, R, C>::rear;
    constexpr static int front = rear + GetCellLengthInBoard<B, R, C>::length - 1;

    typedef typename MoveCarRightOnce<B, R, C>::updatedBoard B_; /// Move the car once to the right
    typedef typename Conditional<(A - 1) >= 1, /// Check if we should move the car again
            typename MoveCarRight<B_, R, (front + 1), (A - 1)>::updatedBoard, /// Call recursively with updated front and amount
            B_>::value updatedBoard; /// Otherwise, set the updated board as the current one
};

/// Moves the entire car once
/// IMPORTANT - This function assumes that the car is horizontal.
template<typename B, int R, int C, Direction D, int A>
struct MoveCarHorizontal {
    typedef typename Conditional<D == LEFT, typename MoveCarLeft<B, R, C, A>::updatedBoard, /// If D == LEFT call MoveCarLeft
            typename MoveCarRight<B, R, C, A>::updatedBoard>::value updatedBoard; /// Otherwise, call MoveCarRight
};

#endif //OOP_HW5_MOVEVEHICLE_H