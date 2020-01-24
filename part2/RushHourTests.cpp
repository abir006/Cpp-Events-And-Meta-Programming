// Author: Oranichu.

#include <iostream>
#include "List.h"
#include "Utilities.h"
#include "Printer.h"
#include "TransposeList.h"
#include "RushHour.h"

using namespace std;

template<int i>
struct Int {
    constexpr static int value = i;
};

void TestList() {
    typedef List<Int<1>, Int<2>, Int<3>> list;
    static_assert(list::head::value == 1, "List head for non-empty list is invalid"); // = Int <1>
    typedef typename list::next listTail; // = List< Int <2>, Int <3>>
    static_assert(list::size == 3, "List size for non-empty list is invalid"); // = 3

    typedef typename PrependList<Int<4>, list>::list newList;
    static_assert(newList::size == 4, "List size for non-empty list is invalid"); // = 4

    static_assert(GetAtIndex<0, list>::value::value == 1, "1"); // = Int<1>
    static_assert(GetAtIndex<2, list>::value::value == 3, "2"); // = Int<3>

    // Test SetAtIndex
    typedef List<Int<1>, Int<2>, Int<3>> list2;
    typedef typename SetAtIndex<0, Int<-1>, list2>::list list20;
    static_assert(GetAtIndex<0, list20>::value::value == -1, "SetAtIndex failed for first element of list");
    static_assert(GetAtIndex<2, list20>::value::value == 3, "SetAtIndex failed for last element of list");
    typedef typename SetAtIndex<1, Int<0>, SetAtIndex<2, Int<-3>, list20>::list>::list list21;
    static_assert(GetAtIndex<0, list21>::value::value == -1, "SetAtIndex failed for double SetAtIndex");
    static_assert(GetAtIndex<1, list21>::value::value == 0, "SetAtIndex failed for double SetAtIndex");
    static_assert(GetAtIndex<2, list21>::value::value == -3, "SetAtIndex failed for double SetAtIndex");

    // Test list::size attribute
    static_assert(list::size == 3, "List size is invalid");
    static_assert(list21::size == 3, "List size is invalid after SetAtIndex");

    typedef List<> emptyList;
    static_assert(emptyList::size == 0, "Empty list size is invalid");

    // Combined Get + Set test
    typedef List<Int<1>, Int<2>, Int<3>> sg_list;
    typedef typename SetAtIndex<0, Int<5>, sg_list>::list sg_listA; // = List<Int<5>, Int<2>, Int<3>>
    static_assert(GetAtIndex<0, sg_listA>::value::value == 5, "error 3.1"); // = Int<5>
    static_assert(GetAtIndex<1, sg_listA>::value::value == 2, "error 3.2"); // = Int<2>
    static_assert(GetAtIndex<2, sg_listA>::value::value == 3, "error 3.3"); // = Int<3>
    typedef typename SetAtIndex<2, Int<7>, sg_list>::list sg_listB; // = List<Int<1>, Int<2>, Int<7>>
    static_assert(GetAtIndex<0, sg_listB>::value::value == 1, "error 4.1"); // = Int<1>
    static_assert(GetAtIndex<1, sg_listB>::value::value == 2, "error 4.2"); // = Int<2>
    static_assert(GetAtIndex<2, sg_listB>::value::value == 7, "error 4.3"); // = Int<7>
}

void TestConditional() {
    static_assert(ConditionalInteger<(0 != 1), 0, 1>::value == 0, "error Conditonal 1"); // = 0
    static_assert(ConditionalInteger<(0 == 1), 0, 1>::value == 1, "error Conditonal 2"); // = 1

    static_assert(Conditional<(0 != 1), Int<0>, Int<1>>::value::value == 0, "error Conditonal 3");
    static_assert(Conditional<(0 == 1), Int<0>, Int<1>>::value::value == 1, "error Conditonal 4");
};

void TestGameBoard() {
    typedef GameBoard<List<
            List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 3>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<X, RIGHT, 2>, BoardCell<X, LEFT, 2>, BoardCell<O, UP, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
    >> gameBoard1;

    typedef GameBoard<List<
            List<BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
            List<BoardCell<X, RIGHT, 1>, BoardCell<A, UP, 1>>,
            List<BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
    >> gameBoard2;
    typedef Move<X, UP, 3> m;
    static_assert(m::type == X, "Move type wrong");
    static_assert(m::direction == UP, "Move direction wrong");
    static_assert(m::amount == 3, "Move amount wrong");


    static_assert(gameBoard1::width == 6, "GameBoard 1 width error");
    static_assert(gameBoard2::width == 2, "GameBoard 2 width error");
    static_assert(gameBoard1::length == 6, "GameBoard 1 length error");
    static_assert(gameBoard2::length == 3, "GameBoard 2 length error");

}

void testMoveVehicle() { //Cheers Akiva.
    typedef List<
            List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 3>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<X, RIGHT, 2>, BoardCell<X, LEFT, 2>, BoardCell<O, UP, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
    > gameBoardLists;
    typedef GameBoard<gameBoardLists> gameBoard;


    typedef typename MoveVehicle<gameBoard, 2, 2, LEFT, 2>::board x_2_left_1;
    typedef typename MoveVehicle<gameBoard, 2, 3, LEFT, 2>::board x_2_left_2;
    Printer<x_2_left_1 >::print(cout);
    cout << endl << "this is x_2_left_1" << endl;
    Printer<x_2_left_2 >::print(cout);
    cout  << "this is x_2_left_2" << endl;

    typedef typename GetAtIndex<2, typename GetAtIndex<5, gameBoard::board>::value>::value B;

    typedef typename MoveVehicle<gameBoard, 5, 2, UP, 1>::board b_1_up;
    static_assert(std::is_same<x_2_left_1, b_1_up>::value == false, "Both coordinates are'nt point on the same car,"
                                                                    " so it not suppose to be equal");

    typedef typename GetAtIndex<2, typename GetAtIndex<5, b_1_up::board>::value>::value oldB;
    typedef typename GetAtIndex<2, typename GetAtIndex<3, b_1_up::board>::value>::value newB;
    static_assert(oldB::type == EMPTY, "old position of B suppose to be empty");
    static_assert((B::type == newB::type) && (B::length == newB::length), "B suppose to move one up");

    typedef typename MoveVehicle<b_1_up, 5, 4, LEFT, 4>::board b1up_c4left;
    typedef typename GetAtIndex<1, typename GetAtIndex<5, b1up_c4left::board>::value>::value newC;
    typedef typename GetAtIndex<4, typename GetAtIndex<5, b1up_c4left::board>::value>::value oldC;
    static_assert(oldC::type == EMPTY, "old position of C suppose to be empty");
    static_assert(newC::type == C, "c suppose to move to the left side of the board");
};

void testMoveVehicleErrors() {
    typedef List<
            List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 3>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<X, RIGHT, 2>, BoardCell<X, LEFT, 2>, BoardCell<O, UP, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
    > gameBoardLists;
    typedef GameBoard<gameBoardLists> gameBoard;

    // ##### do this function after 'testMoveVehicle' function is compiled successfully #####
    // ##### remove one comment each time to check if the compilation failed #######

//    typedef typename MoveVehicle<gameBoard,-1, 2, RIGHT, 1>::board b; // error: out of board bounds. left
//    typedef typename MoveVehicle<gameBoard,6, 2, RIGHT, 1>::board b; // error: out of board bounds. down
//    typedef typename MoveVehicle<gameBoard,2, -1, RIGHT, 1>::board b2; // error: out of board bounds. up
//    typedef typename MoveVehicle<gameBoard,2, 6, RIGHT, 1>::board b2; // error: out of board bounds. right

//    typedef typename MoveVehicle<gameBoard,0, 0, RIGHT, 1>::board b; // error: empty cell

//    typedef typename MoveVehicle<gameBoard,2, 2, DOWN, 1>::board b; // error: wrong direction
//    typedef typename MoveVehicle<gameBoard,5, 2, LEFT, 1>::board b; // error: wrong direction

//    typedef typename MoveVehicle<gameBoard,2, 2, RIGHT, 1>::board b; // O block X
//    typedef typename MoveVehicle<gameBoard,5, 2, UP, 2>::board b; // X block B
//    typedef typename MoveVehicle<gameBoard,5, 5, LEFT, 4>::board b; // B block C

}

void TestCheckWin() {
    typedef List<
            List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 3>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<X, RIGHT, 2>, BoardCell<X, LEFT, 2>, BoardCell<O, UP, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
    > gameBoardLists;
    typedef GameBoard<gameBoardLists> gameBoard;

    typedef GameBoard<List<
            List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<B, RIGHT, 2>, BoardCell<B, RIGHT, 2>, BoardCell<X, RIGHT, 3>, BoardCell<X, LEFT, 3>, BoardCell<X, UP, 3>, BoardCell<E, RIGHT, 1> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
    >> gameBoardLose;

    typedef GameBoard<List<
            List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<B, RIGHT, 2>, BoardCell<B, RIGHT, 2>, BoardCell<X, RIGHT, 3>, BoardCell<X, LEFT, 3>, BoardCell<X, UP, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
    >> gameBoardWin;

    typedef GameBoard<List<
            List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 3>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<X, RIGHT, 2>, BoardCell<X, LEFT, 2>, BoardCell<EMPTY, UP, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
    >> gameBoard1;

    static_assert(CheckWin<gameBoard>::result == false, "CheckWin Error");
    static_assert(CheckWin<gameBoardLose>::result == false, "CheckWin Error");
    static_assert(CheckWin<gameBoard1>::result == true, "CheckWin Error");
    static_assert(CheckWin<gameBoardWin>::result == true, "CheckWin Error");
}

void TestRushHourSegel() {

    typedef GameBoard<List<
            List<BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<A, RIGHT, 2>, BoardCell<A, LEFT, 2>, BoardCell<O, DOWN, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 3>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<X, RIGHT, 2>, BoardCell<X, LEFT, 2>, BoardCell<O, UP, 3>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, DOWN, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<B, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<C, RIGHT, 2>, BoardCell<C, LEFT, 2> >
    > > gameBoard;

    typedef List<
            Move<B, UP, 1>, Move<C, LEFT, 4>, Move<A, LEFT, 2>, Move<X, LEFT, 2>, Move<B, UP, 3>, Move<P, LEFT, 3>, Move<O, DOWN, 3>
    > moves;

    static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solved

}

void TestCheckSoloution() {

    typedef GameBoard<List<
            List<BoardCell<A, DOWN, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, RIGHT, 3>, BoardCell<O, LEFT, 3>, BoardCell<O, RIGHT, 3> >,
            List<BoardCell<A, DOWN, 2>, BoardCell<B, RIGHT, 2>, BoardCell<B, RIGHT, 2>, BoardCell<C, DOWN, 2>, BoardCell<EMPTY, DOWN, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<X, RIGHT, 2>, BoardCell<X, RIGHT, 2>, BoardCell<D, UP, 2>, BoardCell<C, UP, 2>, BoardCell<EMPTY, UP, 0>, BoardCell<R, DOWN, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<D, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<R, UP, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<E, DOWN, 2>, BoardCell<F, RIGHT, 2>, BoardCell<F, RIGHT, 2>, BoardCell<R, UP, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<E, UP, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >
    > > gameBoard;

    Printer<gameBoard>::print(cout);
    typedef List<
            Move<C, DOWN, 1>, Move<B, RIGHT, 3>, Move<D, UP, 2>, Move<X, RIGHT, 1>, Move<A, DOWN, 4>, Move<X, LEFT, 1>,
            Move<D, DOWN, 2>, Move<O, LEFT, 1>, Move<B, LEFT, 1>, Move<D, UP, 1>, Move<E, UP, 1>, Move<A, UP, 1>,
            Move<P, LEFT, 3>, Move<R, DOWN, 1>, Move<O, RIGHT, 1>, Move<B, RIGHT, 1>, Move<D, UP, 1>, Move<X, RIGHT, 1>,
            Move<A, UP, 3>, Move<X, LEFT, 1>, Move<E, UP, 1>, Move<F, LEFT, 3>, Move<E, DOWN, 1>, Move<C, DOWN, 1>
    > moves;
    static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solved

    typedef List<
            Move<C, DOWN, 1>, Move<B, RIGHT, 3>, Move<D, UP, 2>, Move<X, RIGHT, 1>, Move<A, DOWN, 4>, Move<X, LEFT, 1>,
            Move<D, DOWN, 2>, Move<O, LEFT, 1>, Move<B, LEFT, 1>, Move<D, UP, 1>, Move<E, UP, 1>, Move<A, UP, 1>,
            Move<P, LEFT, 3>, Move<R, DOWN, 1>, Move<O, RIGHT, 1>, Move<B, RIGHT, 1>, Move<D, UP, 1>, Move<X, RIGHT, 1>,
            Move<A, UP, 3>, Move<X, LEFT, 1>, Move<E, UP, 1>, Move<F, LEFT, 3>, Move<E, DOWN, 1>
    > movesWrong;
    static_assert(CheckSolution<gameBoard, movesWrong>::result == false, "Fail"); // Game should be solved
}

void TestCheckSoloutionErrs() {

    // ##### do this function after 'TestCheckSoloution' function is compiled successfully #####
    // ##### remove one comment each time to check if the compilation failed #######

    typedef GameBoard<List<
            List<BoardCell<A, DOWN, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<O, RIGHT, 3>, BoardCell<O, LEFT, 3>, BoardCell<O, RIGHT, 3> >,
            List<BoardCell<A, DOWN, 2>, BoardCell<B, RIGHT, 2>, BoardCell<B, RIGHT, 2>, BoardCell<C, DOWN, 2>, BoardCell<EMPTY, DOWN, 0>, BoardCell<EMPTY, RIGHT, 0> >,
            List<BoardCell<X, RIGHT, 2>, BoardCell<X, RIGHT, 2>, BoardCell<D, UP, 2>, BoardCell<C, UP, 2>, BoardCell<EMPTY, UP, 0>, BoardCell<R, DOWN, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<D, UP, 2>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<R, UP, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<E, DOWN, 2>, BoardCell<F, RIGHT, 2>, BoardCell<F, RIGHT, 2>, BoardCell<R, UP, 3> >,
            List<BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<E, UP, 2>, BoardCell<P, RIGHT, 3>, BoardCell<P, RIGHT, 3>, BoardCell<P, LEFT, 3> >
    > > gameBoard;

//
//    typedef List<
//            Move<C, DOWN, 1>, Move<B, RIGHT, 3>, Move<D, DOWN, 2>, Move<X, RIGHT, 1>, Move<A, DOWN, 4>, Move<X, LEFT, 1>,
//            Move<D, DOWN, 2>, Move<O, LEFT, 1>, Move<B, LEFT, 1>, Move<D, UP, 1>, Move<E, UP, 1>, Move<A, UP, 1>,
//            Move<P, LEFT, 3>, Move<R, DOWN, 1>, Move<O, RIGHT, 1>, Move<B, RIGHT, 1>, Move<D, UP, 1>, Move<X, RIGHT, 1>,
//            Move<A, UP, 3>, Move<X, LEFT, 1>, Move<E, UP, 1>, Move<F, LEFT, 3>, Move<E, DOWN, 1>
//    > movesCarInWay;
//    static_assert(CheckSolution<gameBoard, movesCarInWay>::result == false, "Fail"); // Game should assert fail car in the way
//
//    typedef List<
//            Move<C, DOWN, 1>, Move<B, RIGHT, 3>, Move<D, UP, 2>, Move<X, RIGHT, 1>, Move<A, DOWN, 4>, Move<X, LEFT, 1>,
//            Move<D, DOWN, 2>, Move<O, LEFT, 1>, Move<B, LEFT, 1>, Move<D, UP, 1>, Move<E, UP, 1>, Move<A, UP, 1>,
//            Move<P, LEFT, 3>, Move<R, DOWN, 1>, Move<O, UP, 1>, Move<B, RIGHT, 1>, Move<D, UP, 1>, Move<X, RIGHT, 1>,
//            Move<A, UP, 3>, Move<X, LEFT, 1>, Move<E, UP, 1>, Move<F, LEFT, 3>, Move<E, DOWN, 1>
//    > movesCarInWrongDir;
//    static_assert(CheckSolution<gameBoard, movesCarInWrongDir>::result == false, "Fail"); // Game should be assert fail wrong direction move for vehicle


}


int main() {
    TestList();
    TestConditional();
    TestGameBoard();
    testMoveVehicle();
    testMoveVehicleErrors();
    TestCheckWin();
    TestRushHourSegel();
    TestCheckSoloution();
    TestCheckSoloutionErrs();
    return 0;
}
