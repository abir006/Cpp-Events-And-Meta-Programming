#include <iostream>
#include "RushHour.h"
#include "Printer.h"

typedef GameBoard< List<
        List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 3>, BoardCell< EMPTY , RIGHT , 0> >,
        List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 2>, BoardCell< A , LEFT , 2>, BoardCell< O , DOWN , 3>, BoardCell< EMPTY , RIGHT , 0> >,
        List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0> >,
        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , DOWN , 2>, BoardCell< P , RIGHT , 3>, BoardCell< P , RIGHT , 3>, BoardCell< P , LEFT , 3> >,
        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , UP , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , RIGHT , 2>, BoardCell< C , LEFT , 2> >
> > gameBoard;

typedef List<
        Move < B, UP, 1 > , Move < C, LEFT, 4 > , Move < A, LEFT, 2 > , Move < X, LEFT, 2 > , Move < B, UP, 3 > , Move < P, LEFT, 3 > , Move < O, DOWN, 3 >
> moves;

int main(){

    static_assert(List<BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>>::size == 3, "Fail");
    static_assert(List<>::size == 0, "Fail");
    typedef MoveVehicle<gameBoard, 2, 3, LEFT, 2>::board b1; // Valid move
    static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solved

    return 0;
}

