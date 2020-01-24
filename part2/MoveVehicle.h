//
// Created by Shahak on 19/01/2020.
//

#ifndef OOP_HW5_MOVEVEHICLE_H
#define OOP_HW5_MOVEVEHICLE_H

#include "GameBoard.h"
#include "CellType.h"
#include "Direction.h"
#include "Utilities.h"
#include "TransposeList.h"

/// The c'tor receives the parameters and defines the struct describing the action to be made on the board.
template<CellType T, Direction D, int A>
struct Move {
    static_assert(A >= 0, "MoveVehicle: AMOUNT IS ILLEGAL (must be non-negative)");
    static_assert(T != EMPTY, "MoveVehicle: CELLTYPE IS ILLEGAL (must be different than EMPTY)");
    constexpr static CellType type = T;
    constexpr static Direction direction = D;
    constexpr static int amount = A;
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

    typedef typename SetBoardCell<B, R, (rear - 1), T, D, L>::updatedBoard B_; /// Move the rear one cell to the left
    typedef typename SetBoardCell<B_ , R, front, EMPTY, D, 0>::updatedBoard updatedBoard; /// Erase the front cell
};

/// Moves the entire vehicle A cells to the left
template<typename B, int R, int C, int A>
struct MoveCarLeft {
    /// Get car details
    constexpr static CellType T = GetCellTypeInBoard<B, R, C>::T;
    constexpr static int rear = FindCarRear<B, T, R, C>::rear;
    static_assert(rear - A >= 0, "MoveCarLeft: INDEX OUT OF BOUND");

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

    typedef typename SetBoardCell<B, R, (front + 1), T, D, L>::updatedBoard B_; /// Move the front one cell to the right
    typedef typename SetBoardCell<B_ , R, rear, EMPTY, D, 0>::updatedBoard updatedBoard; /// Erase the rear cell
};

/// Moves the entire vehicle A cells to the right
template<typename B, int R, int C, int A>
struct MoveCarRight {
    /// Get car details
    constexpr static CellType T = GetCellTypeInBoard<B, R, C>::T;
    constexpr static int rear = FindCarRear<B, T, R, C>::rear;
    constexpr static int front = rear + GetCellLengthInBoard<B, R, C>::length - 1;
    static_assert(front + A < B::width, "MoveCarRight: INDEX OUT OF BOUND");

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

/// IMPORTANT - this function assumes that the car is vertical.
template<typename B, int R, int C, Direction D, int A>
struct MoveCarVertical {
    ///TODO make sure that up = left (what i assume) or up = right.
    constexpr static Direction new_direction = ConditionalInteger<D == UP, LEFT, RIGHT>::value;
    typedef typename Transpose<typename B::board>::matrix transposed_board; ///Transpose the board.
    typedef GameBoard<transposed_board> B_;
    typedef typename Conditional<new_direction == LEFT, typename MoveCarLeft<B_, R, C, A>::updatedBoard, /// If D == LEFT call MoveCarLeft
            typename MoveCarRight<B_, R, C, A>::updatedBoard>::value temp_updatedBoard; /// Otherwise, call MoveCarRight
    typedef GameBoard<typename Transpose<typename temp_updatedBoard::board>::matrix> updatedBoard;   ///After moving, transpose the board again.
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
    typedef typename Conditional<A == 0, B, /// Outer condition - if we want to move amount of 0 , then we return the board without changes
             typename Conditional<D == LEFT || D == RIGHT, /// Otherwise, go to inner condition - check if the move is horizontal
                      typename MoveCarHorizontal<B, R, C, D, A>::updatedBoard, /// If its horizontal sends to horizontal move
                      typename MoveCarVertical<B, R, C, D, A>::updatedBoard>::value>::value board; /// If its vertical sends to vertical move
};

#endif //OOP_HW5_MOVEVEHICLE_H