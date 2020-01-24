#include <iostream>
#include "RushHour.h"
#include "Printer.h"

using namespace std;

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
    Printer<gameBoard>::print(cout);
 /*   constexpr static Direction D = LEFT;
    constexpr static int R=2,A=2,C=3;*/
    typedef GameBoard<gameBoard::board> B;
   // typedef MoveCarHorizontal<B,R,C,LEFT,A>::updatedBoard b;
   // Printer<b>::print(cout);
   // typedef MoveVehicle<gameBoard, 2, 3, LEFT, 2>::board b1; // Valid move
   // Printer<b1>::print(cout);
   // typedef MoveVehicle<gameBoard, 0, 4, DOWN, 0>::board b1; // Valid move
    //typedef MoveCarVertical<gameBoard,0 ,4, DOWN,1>::updatedBoard b1;
 /*   constexpr static int red_car_row = FindCar<B, X, B::length - 1, B::width - 1>::row;
    /// Gets the red car col using FindCar in utils.
    static_assert(red_car_row==2,"");
    constexpr static int red_car_col = FindCar<B, X, B::length - 1, B::width - 1>::col;
    static_assert(red_car_col==3,"");
    /// Check if all the cols to the right of the red car are empty or red.
    static constexpr bool res = ConditionalInteger<GetCellTypeInBoard<B, red_car_row, red_car_col>::T == X , true, // False if other than EMPTY/X
            /// Inner condition - if it's X or EMPTY check if next col is out of bounds, if so return True, else check next col.
            ConditionalInteger<GetCellTypeInBoard<B, red_car_row, red_car_col>::T == EMPTY,checkIfAllColsEmptyOrRed<B, red_car_row, red_car_col - 1>::result,false>::value>::value;
    static constexpr bool res_inner = ConditionalInteger<GetCellTypeInBoard<B, red_car_row, red_car_col>::T == EMPTY,checkIfAllColsEmptyOrRed<B, red_car_row, red_car_col - 1>::result,false>::value;
    static_assert(res_inner,"");
    static_assert(res,"");*/
    //static_assert(CheckWin<gameBoard>::result,"");

    static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solve
    return 0;
}

