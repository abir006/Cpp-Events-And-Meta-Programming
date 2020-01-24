#include <iostream>
#include <typeinfo>
#include "RushHour.h"
#include "Printer.h"


namespace classesForTesting {

template <int x>
struct Int {
	static constexpr int value = x;
};

template <typename T1, typename T2>
struct cmp {
	static constexpr bool value = false;
};
template <typename T>
struct cmp<T,T> {
	static constexpr bool value = true;
};

};
using namespace classesForTesting;


static void listTest_Basic() {
	typedef List<Int<1>, Int<2>, Int<3>> list123;
	static_assert(cmp<list123::head, Int<1>>::value, "List::head Fail");
	static_assert(cmp<list123::next::head, Int<2>>::value, "List::next Fail");
	static_assert(list123::size == 3, "List::size Fail");

	typedef typename PrependList<Int<4>, list123>::list list4123;
	static_assert(list4123::size == 4, "List::PrependList Fail");
	static_assert(cmp<list4123::head,       Int<4>>::value, "List::PrependList Fail");
	static_assert(cmp<list4123::next::head, Int<1>>::value, "List::PrependList Fail");

	static_assert(cmp<GetAtIndex<0, list123>::value, Int<1>>::value, "List::GetAtIndex Fail");
	static_assert(cmp<GetAtIndex<1, list123>::value, Int<2>>::value, "List::GetAtIndex Fail");
	static_assert(cmp<GetAtIndex<2, list123>::value, Int<3>>::value, "List::GetAtIndex Fail");

	typedef typename SetAtIndex<0, Int<5>, list123>::list list523;
	static_assert(cmp<list523::head,             Int<5>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<list523::next::head,       Int<2>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<list523::next::next::head, Int<3>>::value, "List::SetAtIndex Fail");

	typedef typename SetAtIndex<2, Int<7>, list123>::list list127;
	static_assert(cmp<list127::head,             Int<1>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<list127::next::head,       Int<2>>::value, "List::SetAtIndex Fail");
	static_assert(cmp<list127::next::next::head, Int<7>>::value, "List::SetAtIndex Fail");
}

static void listTest_Integration() {
	typedef List<> nil;
	typedef List<Int<5>> list5_expected;
	typedef List<Int<3>> list3_expected;
	typedef List<Int<5>, Int<3>> list53_expected;
	typedef List<Int<5>, Int<6>> list56_expected;
	typedef List<Int<7>, Int<5>, Int<3>> list753_expected;
	typedef List<Int<7>, Int<5>, Int<6>> list756_expected;
	typedef List<Int<7>, Int<7>, Int<6>> list776_expected;

	typedef PrependList<Int<5>, nil>::list list5;
	static_assert(cmp<list5, list5_expected>::value, "listTest_Integration Fail");
	static_assert(list5::size == 1, "listTest_Integration Fail");
	static_assert(cmp<list5::head, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<list5::next, nil>::value, "listTest_Integration Fail");

	typedef SetAtIndex<0, Int<3>, list5>::list list3;
	static_assert(cmp<list3, list3_expected>::value, "listTest_Integration Fail");
	static_assert(list3::size == 1, "listTest_Integration Fail");
	static_assert(cmp<list3::head, Int<3>>::value, "listTest_Integration Fail");
	static_assert(cmp<list3::next, nil>::value, "listTest_Integration Fail");

	typedef PrependList<Int<5>, list3>::list list53;
	static_assert(cmp<list53, list53_expected>::value, "listTest_Integration Fail");
	static_assert(list53::size == 2, "listTest_Integration Fail");
	static_assert(cmp<list53::head, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<list53::next, list3_expected>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<0, list53>::value, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<1, list53>::value, Int<3>>::value, "listTest_Integration Fail");

	typedef PrependList<Int<7>, list53>::list list753;
	static_assert(cmp<list753, list753_expected>::value, "listTest_Integration Fail");
	static_assert(list753::size == 3, "listTest_Integration Fail");
	static_assert(cmp<list753::head, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<list753::next, list53_expected>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<0, list753>::value, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<1, list753>::value, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<2, list753>::value, Int<3>>::value, "listTest_Integration Fail");

	typedef SetAtIndex<2, Int<6>, list753>::list list756;
	static_assert(cmp<list756, list756_expected>::value, "listTest_Integration Fail");
	static_assert(list756::size == 3, "listTest_Integration Fail");
	static_assert(cmp<list756::head, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<list756::next, list56_expected>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<0, list756>::value, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<1, list756>::value, Int<5>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<2, list756>::value, Int<6>>::value, "listTest_Integration Fail");

	typedef SetAtIndex<1, Int<7>, list756>::list list776;
	static_assert(cmp<list776, list776_expected>::value, "listTest_Integration Fail");
	static_assert(list776::size == 3, "listTest_Integration Fail");
	static_assert(cmp<list776::head, Int<7>>::value, "listTest_Integration Fail");
	static_assert(list776::next::size == 2, "listTest_Integration Fail");
	static_assert(cmp<list776::next::head, Int<7>>::value, "listTest_Integration Fail");
	static_assert(list776::next::next::size == 1, "listTest_Integration Fail");
	static_assert(cmp<list776::next::next::head, Int<6>>::value, "listTest_Integration Fail");
	static_assert(list776::next::next::next::size == 0, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<0, list776>::value, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<1, list776>::value, Int<7>>::value, "listTest_Integration Fail");
	static_assert(cmp<GetAtIndex<2, list776>::value, Int<6>>::value, "listTest_Integration Fail");
}

static void conditionalTest() {
	static_assert(ConditionalInteger<(0 != 1), 0, 1>::value == 0, "ConditionalInteger Fail");
	static_assert(ConditionalInteger<(0 == 1), 0, 1>::value == 1, "ConditionalInteger Fail");
	static_assert(cmp<Conditional<(0 != 1), Int<0>, Int<1>>::value, Int<0>>::value, "Conditional Fail");
	static_assert(cmp<Conditional<(0 == 1), Int<0>, Int<1>>::value, Int<1>>::value, "Conditional Fail");
}

static void boardCellFieldsTest() {
	static_assert(BoardCell<EMPTY, DOWN, 3>::type == EMPTY, "BoardCell Fail");
	static_assert(BoardCell<EMPTY, DOWN, 3>::direction == DOWN, "BoardCell Fail");
	static_assert(BoardCell<EMPTY, DOWN, 3>::length == 3, "BoardCell Fail");

	static_assert(BoardCell<X, LEFT, 50>::type == X, "BoardCell Fail");
	static_assert(BoardCell<X, LEFT, 50>::direction == LEFT, "BoardCell Fail");
	static_assert(BoardCell<X, LEFT, 50>::length == 50, "BoardCell Fail");

}

static void gameBoardFieldsTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0> >
		> list1x1;
	typedef GameBoard<list1x1> board1x1;
	static_assert(board1x1::width == 1, "GameBoard Fail");
	static_assert(board1x1::length == 1, "GameBoard Fail");
	static_assert(cmp<list1x1, board1x1::board>::value, "GameBoard Fail");

	typedef List<
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;
	typedef GameBoard<list2x3> board2x3;
	static_assert(board2x3::width == 2, "GameBoard Fail");
	static_assert(board2x3::length == 3, "GameBoard Fail");
	static_assert(cmp<list2x3, board2x3::board>::value, "GameBoard Fail");
}

static void moveFieldsTest() {
	static_assert(Move<A, DOWN, 3>::type == A, "Move Fail");
	static_assert(Move<A, DOWN, 3>::direction == DOWN, "Move Fail");
	static_assert(Move<A, DOWN, 3>::amount == 3, "Move Fail");

	static_assert(Move<X, RIGHT, 25>::type == X, "Move Fail");
	static_assert(Move<X, RIGHT, 25>::direction == RIGHT, "Move Fail");
	static_assert(Move<X, RIGHT, 25>::amount == 25, "Move Fail");
}

static void providedExample() {
	typedef GameBoard< List<
	        List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 2>,     BoardCell< A , LEFT , 2>,      BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell< O , UP , 3>,        BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , DOWN , 2>,      BoardCell< P , RIGHT , 3>,     BoardCell< P , RIGHT , 3>,     BoardCell< P , LEFT , 3> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , UP , 2>,        BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , RIGHT , 2>,     BoardCell< C , LEFT , 2> >
	> > gameBoard;

	typedef List<
	        Move < B, UP, 1 > , Move < C, LEFT, 4 > , Move < A, LEFT, 2 > , Move < X, LEFT, 2 > , Move < B, UP, 3 > , Move < P, LEFT, 3 > , Move < O, DOWN, 3 >
	> moves;

	static_assert(List<BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>,BoardCell< EMPTY , RIGHT , 0>>::size == 3, "Fail");
    static_assert(List<>::size == 0, "Fail");

    MoveVehicle<gameBoard, 2, 3, LEFT, 2>::board b1; (void)b1; // Valid move (cast to void to suppress 'unused' warnings)

    static_assert(CheckSolution<gameBoard, moves>::result, "Fail"); // Game should be solved
}

static void checkWin_board_1x1_Test() {
	typedef GameBoard< List<
	        List < BoardCell< X , RIGHT , 1> >
	> > gameBoard;
	static_assert(CheckWin<gameBoard>::result, "Fail");
}

static void checkWin_board_3x3_Test() {
	typedef GameBoard< List<
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< A , RIGHT , 2>,     BoardCell< A , LEFT , 2>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell< EMPTY , RIGHT , 0> >
	> > gameBoard;
	static_assert(CheckWin<gameBoard>::result, "Fail");
}

static void checkWin_noWin_board_3x3_Test() {
	typedef GameBoard< List<
	        List < BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell<  A , DOWN , 2> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell<  A , DOWN , 2> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >
	> > gameBoard;
	static_assert(not CheckWin<gameBoard>::result, "Fail");
}

static void checkWin_noWin_board_1x6_Test() {
	typedef GameBoard< List<
	        List < BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< EMPTY , UP , 1000>, BoardCell< EMPTY , DOWN , 42>, BoardCell< EMPTY , LEFT , 333>, BoardCell<A , DOWN , 1> >
	> > gameBoard;
	static_assert(not CheckWin<gameBoard>::result, "Fail");
}

static void moveVehicle_game_Test() {
	typedef GameBoard< List<
	        List < BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT , 0>, BoardCell<R ,    UP,     3>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< EMPTY, RIGHT , 0>>,
	        List < BoardCell<EMPTY, LEFT , 2>, BoardCell<EMPTY, LEFT , 2>, BoardCell<EMPTY, RIGHT , 0>, BoardCell<R ,    UP,     3>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< EMPTY, RIGHT , 0>>,
	        List < BoardCell<EMPTY, RIGHT, 0>, BoardCell<X,     RIGHT, 2>, BoardCell<X ,    RIGHT,  2>, BoardCell<R,     UP,     3>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< P ,    UP,     3>>,
	        List < BoardCell<EMPTY, RIGHT, 0>, BoardCell<C,     DOWN , 2>, BoardCell<D ,    LEFT  , 2>, BoardCell<D ,    LEFT  , 2>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< P,     UP ,    3>>,
	        List < BoardCell<EMPTY, RIGHT, 0>, BoardCell<C,     DOWN , 2>, BoardCell<EMPTY, RIGHT , 0>, BoardCell<EMPTY, RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< P ,    UP ,    3>>,
	        List < BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, UP    , 2>, BoardCell<EMPTY, RIGHT , 0>, BoardCell< F ,     RIGHT , 2>,  BoardCell< F,     RIGHT , 2>>
	> > gameBoard;

    static_assert(not CheckWin<gameBoard>::result, "Fail");

    std::cout << "Running: " << __FUNCTION__ << std::endl;
    Printer<gameBoard>::print(std::cout);
    /*
     * Every move here is valid and leads to win. Everything must compile.
     * But it's impossible to test board state (since it's OK to change EMPTY cells, as I understand)
     * So, here you have to rely on printer.
     */
    typedef MoveVehicle<gameBoard, 4, 1, DOWN,  1>::board b01; /* C */   Printer<b01>::print(std::cout);
	typedef MoveVehicle<b01,       3, 5, UP,    2>::board b02; /* P */   Printer<b02>::print(std::cout);
	typedef MoveVehicle<b02,       3, 2, RIGHT, 2>::board b03; /* D */   Printer<b03>::print(std::cout);
	typedef MoveVehicle<b03,       0, 3, DOWN,  3>::board b04; /* R */   Printer<b04>::print(std::cout);
	typedef MoveVehicle<b04,       2, 1, RIGHT, 1>::board b05; /* X */   Printer<b05>::print(std::cout);
	typedef MoveVehicle<b05,       5, 1, UP,    4>::board b06; /* C */   Printer<b06>::print(std::cout);
	typedef MoveVehicle<b06,       2, 2, LEFT,  1>::board b07; /* X */   Printer<b07>::print(std::cout);
	typedef MoveVehicle<b07,       3, 3, UP,    3>::board b08; /* R */   Printer<b08>::print(std::cout);
	typedef MoveVehicle<b08,       3, 5, LEFT,  4>::board b09; /* D */   Printer<b09>::print(std::cout);
	typedef MoveVehicle<b09,       5, 5, LEFT,  4>::board b10; /* F */   Printer<b10>::print(std::cout);
	typedef MoveVehicle<b10,       1, 5, DOWN,  3>::board b11; /* P */   Printer<b11>::print(std::cout);
	typedef MoveVehicle<b11,       1, 3, DOWN,  3>::board b12; /* R */   Printer<b12>::print(std::cout);

	static_assert(CheckWin<b12>::result, "Fail"); // Game should be solved

    std::cout << __FUNCTION__ << " end." <<  std::endl;
}

static void checkSolution_game_Test() {

	/* Same board and solution as moveVehicle_game_Test, but using Move list and CheckSolution */

	typedef GameBoard< List<
	        List < BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT, 1>, BoardCell<EMPTY, RIGHT , 0>, BoardCell<R ,    UP,     3>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< EMPTY, RIGHT , 0>>,
	        List < BoardCell<EMPTY, LEFT , 2>, BoardCell<EMPTY, LEFT , 2>, BoardCell<EMPTY, RIGHT , 0>, BoardCell<R ,    UP,     3>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< EMPTY, RIGHT , 0>>,
	        List < BoardCell<EMPTY, RIGHT, 0>, BoardCell<X,     RIGHT, 2>, BoardCell<X ,    RIGHT,  2>, BoardCell<R,     UP,     3>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< P ,    UP,     3>>,
	        List < BoardCell<EMPTY, RIGHT, 0>, BoardCell<C,     DOWN , 2>, BoardCell<D ,    LEFT  , 2>, BoardCell<D ,    LEFT  , 2>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< P,     UP ,    3>>,
	        List < BoardCell<EMPTY, RIGHT, 0>, BoardCell<C,     DOWN , 2>, BoardCell<EMPTY, RIGHT , 0>, BoardCell<EMPTY, RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>,  BoardCell< P ,    UP ,    3>>,
	        List < BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, RIGHT, 0>, BoardCell<EMPTY, UP    , 2>, BoardCell<EMPTY, RIGHT , 0>, BoardCell< F ,     RIGHT , 2>,  BoardCell< F,     RIGHT , 2>>
	> > gameBoard;

	typedef List<
	        Move < C, DOWN,  1 > , Move < P, UP,   2 > , Move < D, RIGHT, 2 > , Move < R, DOWN, 3 > ,
			Move < X, RIGHT, 1 > , Move < C, UP,   4 > , Move < X, LEFT,  1 > , Move < R, UP,   3 > ,
			Move < D, LEFT,  4 > , Move < F, LEFT, 4 > , Move < P, DOWN,  3 > , Move < R, DOWN, 3 >
	> moves;

	static_assert(CheckSolution<gameBoard, moves>::result, "Fail");
}




//#define TEST_COMPILATION_ERRORS // Uncomment to test error cases.
#ifdef TEST_COMPILATION_ERRORS

/* Expect to get "required from here" on every line, which creates some object.                    */
/* Note: casting variables to void suppresses unused variables warnings, that's the only purpose.  */

static void moveCannotBeEmptyTest() {
	Move<EMPTY, DOWN, 3> m; (void)m;
}

static void moveVehicleErrorsTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;
	typedef GameBoard<list2x3> board2x3;

	// index out of bounds:
	MoveVehicle<board2x3, -1,  1, LEFT, 1>m1; (void)m1;
	MoveVehicle<board2x3,  1, -1, LEFT, 1>m2; (void)m2;
	MoveVehicle<board2x3,  3,  1, LEFT, 1>m3; (void)m3;
	MoveVehicle<board2x3,  1,  2, LEFT, 1>m4; (void)m4;

	// move empty cell:
	MoveVehicle<board2x3, 0,  0, RIGHT, 1>m10; (void)m10;

	// move in bad direction (sideways)
	MoveVehicle<board2x3, 1, 0, UP,    1>m21; (void)m21;
	MoveVehicle<board2x3, 1, 0, DOWN,  1>m22; (void)m22;
	MoveVehicle<board2x3, 1, 1, LEFT,  1>m23; (void)m23;
	MoveVehicle<board2x3, 1, 1, RIGHT, 1>m24; (void)m24;


	typedef GameBoard< List<
	        List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 2>,     BoardCell< A , LEFT , 2>,      BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell< O , UP , 3>,        BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , DOWN , 2>,      BoardCell< P , RIGHT , 3>,     BoardCell< P , RIGHT , 3>,     BoardCell< P , LEFT , 3> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , UP , 2>,        BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , RIGHT , 2>,     BoardCell< C , LEFT , 2> >
	> > gameBoard;
	// move, when there's not enough empty cells in chosen direction
	MoveVehicle<board2x3, 2, 3, RIGHT, 1>m30; (void)m30; // X
	MoveVehicle<board2x3, 4, 3, LEFT,  1>m31; (void)m31; // P
	MoveVehicle<board2x3, 5, 2, UP,    4>m32; (void)m32; // B
	MoveVehicle<board2x3, 1, 4, DOWN,  2>m33; (void)m33; // O
}

#endif /* TEST_COMPILATION_ERRORS */



//#define COME_TO_THE_LEV_SIDE
/*
 * Those are tests for few simple functions (not required), which've served me as a good base, when implementing more complex functionality.
 * Maybe those will help you to find a simpler solution, or at least will serve as an additional example of template metaprogramming.
 * But if you choose to come to the Lev's side, I suggest you will use different names for your APIs (code reuse is the best, but not in Technion).
 */
#ifdef COME_TO_THE_LEV_SIDE

static void getCoordinatesTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;

	static_assert(GetCoordinates<X, list2x3>::row == 1, "Fail");
	static_assert(GetCoordinates<X, list2x3>::col == 0, "Fail");

	static_assert(GetCoordinates<A, list2x3>::row == 1, "Fail");
	static_assert(GetCoordinates<A, list2x3>::col == 1, "Fail");

	static_assert(GetCoordinates<A, list2x3>::row == 1, "Fail");
	static_assert(GetCoordinates<A, list2x3>::col == 1, "Fail");
}

static void gameBoardAtTest() {
	typedef List<
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>,
			List< BoardCell<X, RIGHT, 1>,  BoardCell<A, UP, 1>>,
			List< BoardCell<EMPTY, UP, 0>, BoardCell<EMPTY, UP, 0>>
		> list2x3;
	typedef GameBoard<list2x3> board2x3;

	static_assert(cmp<GameBoardAt<board2x3, 1, 1>::cell, BoardCell<A, UP, 1>>::value, "GameBoardAt Fail");
	static_assert(cmp<GameBoardAt<board2x3, 1, 0>::cell, BoardCell<X, RIGHT, 1>>::value, "GameBoardAt  Fail");
	static_assert(cmp<GameBoardAt<board2x3, 2, 1>::cell, BoardCell<EMPTY, UP, 0>>::value, "GameBoardAt Fail");
}

static void takeDropListTest() {
	typedef List<Int<1>, Int<2>, Int<3>, Int<4>, Int<5>> test_list;

	typedef typename Take<3, test_list>::list list123;
	static_assert(list123::size == 3, "List::Drop Fail");
	static_assert(cmp<GetAtIndex<0, list123>::value, Int<1>>::value, "List::Drop Fail");
	static_assert(cmp<GetAtIndex<1, list123>::value, Int<2>>::value, "List::Drop Fail");
	static_assert(cmp<GetAtIndex<2, list123>::value, Int<3>>::value, "List::Drop Fail");

	typedef typename Drop<2, test_list>::list list345;
	static_assert(list345::size == 3, "List::Take Fail");
	static_assert(cmp<GetAtIndex<0, list345>::value, Int<3>>::value, "List::Take Fail");
	static_assert(cmp<GetAtIndex<1, list345>::value, Int<4>>::value, "List::Take Fail");
	static_assert(cmp<GetAtIndex<2, list345>::value, Int<5>>::value, "List::Take Fail");

	typedef typename Drop<1,  test_list>::list list2345;
	typedef typename Take<2, list2345>::list list23;
	static_assert(list345::size == 3, "List::Take Fail");
	static_assert(cmp<GetAtIndex<0, list23>::value, Int<2>>::value, "List::DropTake Fail");
	static_assert(cmp<GetAtIndex<1, list23>::value, Int<3>>::value, "List::DropTake Fail");


	typedef typename Take<4, test_list>::list list1234;
	typedef typename Drop<1,  list1234>::list list234;
	static_assert(list345::size == 3, "List::Take Fail");
	static_assert(cmp<GetAtIndex<0, list234>::value, Int<2>>::value, "List::TakeDrop Fail");
	static_assert(cmp<GetAtIndex<1, list234>::value, Int<3>>::value, "List::TakeDrop Fail");
	static_assert(cmp<GetAtIndex<2, list234>::value, Int<4>>::value, "List::TakeDrop Fail");

	Take<1, List<Int<1>>>::list m1; (void)m1;
	Drop<1, List<Int<1>>>::list m2; (void)m2;
	Take<0, List<Int<1>>>::list m3; (void)m3;
	Drop<0, List<Int<1>>>::list m4; (void)m4;
	Take<0, List<>>::list       m5; (void)m5;
	Drop<0, List<>>::list       m6; (void)m6;
}

static void sublistTest() {
	typedef List<Int<1>, Int<2>, Int<3>, Int<4>, Int<5>, Int<6>> test_list;

	typedef typename SubList<test_list, 2, 4>::list list345;
	static_assert(list345::size == 2, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<0, list345>::value, Int<3>>::value, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<1, list345>::value, Int<4>>::value, "List::SubList Fail");

	typedef typename SubList<test_list, 0, 2>::list list123;
	static_assert(list123::size == 2, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<0, list123>::value, Int<1>>::value, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<1, list123>::value, Int<2>>::value, "List::SubList Fail");

	typedef typename SubList<test_list, 3, 6>::list list456;
	static_assert(list456::size == 3, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<0, list456>::value, Int<4>>::value, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<1, list456>::value, Int<5>>::value, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<2, list456>::value, Int<6>>::value, "List::SubList Fail");
}

static void concatTest() {
	typedef List<Int<1>, Int<2>, Int<3>, Int<4>, Int<5>, Int<6>> list123456;
	typedef List<Int<1>, Int<2>, Int<3>> list123;
	typedef List<Int<4>, Int<5>, Int<6>> list456;

	typedef Concat<list123, list456>::list result;
	static_assert(result::size == 6, "List::Concat Fail");
	static_assert(cmp<list123456, result>::value, "List::Concat Fail");

	typedef Concat<list456, list123>::list list456123;
	static_assert(result::size == 6, "List::SubList Fail");
	static_assert(cmp<GetAtIndex<0, list456123>::value, Int<4>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<1, list456123>::value, Int<5>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<2, list456123>::value, Int<6>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<3, list456123>::value, Int<1>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<4, list456123>::value, Int<2>>::value, "List::Concat Fail");
	static_assert(cmp<GetAtIndex<5, list456123>::value, Int<3>>::value, "List::Concat Fail");

	Concat<List<Int<1>>, List<>>::list m1; (void)m1;
	Concat<List<>, List<Int<1>>>::list m2; (void)m2;
	Concat<List<>, List<>>::list       m3; (void)m3;

	typedef List<Int<1>, Int<2>> list12;
	typedef List<Int<3>, Int<4>> list34;
	typedef List<Int<5>, Int<6>> list56;
	static_assert(cmp<ConcatAll<list12, list34, list56>::list, list123456>::value, "ConcatAll Fail");
}

static void reverseTest() {
	typedef List<Int<1>, Int<2>, Int<3>> list123;
	typedef List<Int<4>, Int<5>, Int<6>> list456;

	typedef List<Int<3>, Int<2>, Int<1>> list321;
	typedef List<Int<6>, Int<5>, Int<4>> list654;
	static_assert(cmp<Reverse<list123>::list, list321>::value, "Reverse Fail");
	static_assert(cmp<Reverse<list456>::list, list654>::value, "Reverse Fail");
}

static void moveForwardBackwardTest() {
	typedef List <
			BoardCell< EMPTY , RIGHT , 3>, BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0>
		> list;

	typedef typename MoveForward<X, list, 1>::result res_fw;
	typedef List <
			BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0>
		> expected_fw;
	static_assert(cmp<res_fw, expected_fw>::value, "MoveForward Fail");

	typedef typename MoveBackward<X, list, 1>::result res_back;
	typedef List <
			BoardCell< X , RIGHT , 2>, BoardCell< X , LEFT , 2>, BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , UP , 3>, BoardCell< EMPTY , RIGHT , 0>
		> expected_back;
	static_assert(cmp<res_back, expected_back>::value, "MoveBackward Fail");
}

static void providedExampleStepByStep() {
	typedef GameBoard< List<
	        List < BoardCell< EMPTY , RIGHT , 1>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 2>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< A , RIGHT , 2>,     BoardCell< A , LEFT , 2>,      BoardCell< O , DOWN , 3>,      BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 3>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< X , RIGHT , 2>,     BoardCell< X , LEFT , 2>,      BoardCell< O , UP , 3>,        BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , DOWN , 2>,      BoardCell< P , RIGHT , 3>,     BoardCell< P , RIGHT , 3>,     BoardCell< P , LEFT , 3> >,
	        List < BoardCell< EMPTY , RIGHT , 0>, BoardCell< EMPTY , RIGHT , 0>, BoardCell< B , UP , 2>,        BoardCell< EMPTY , RIGHT , 0>, BoardCell< C , RIGHT , 2>,     BoardCell< C , LEFT , 2> >
	> > gameBoard;

    Printer<gameBoard>::print(std::cout);
    typedef DoMove<gameBoard, Move < B, UP,   1 >>::result b01;    Printer<b01>::print(std::cout);
    typedef DoMove<b01,       Move < C, LEFT, 4 >>::result b02;    Printer<b02>::print(std::cout);
    typedef DoMove<b02,       Move < A, LEFT, 2 >>::result b03;    Printer<b03>::print(std::cout);
    typedef DoMove<b03,       Move < X, LEFT, 2 >>::result b04;    Printer<b04>::print(std::cout);
    typedef DoMove<b04,       Move < B, UP,   3 >>::result b05;    Printer<b05>::print(std::cout);
    typedef DoMove<b05,       Move < P, LEFT, 3 >>::result b06;    Printer<b06>::print(std::cout);
    typedef DoMove<b06,       Move < O, DOWN, 3 >>::result b07;    Printer<b07>::print(std::cout);
    static_assert(CheckWin<b07>::result, "Fail"); // Game should be solved

}

#endif /* COME_TO_THE_LEV_SIDE */


int main(){
	providedExample();
	listTest_Basic();
	listTest_Integration();
	conditionalTest();
	boardCellFieldsTest();
	gameBoardFieldsTest();
	moveFieldsTest();
	checkWin_board_1x1_Test();
	checkWin_board_3x3_Test();
	checkWin_noWin_board_3x3_Test();
	checkWin_noWin_board_1x6_Test();
	moveVehicle_game_Test();
	checkSolution_game_Test();

#ifdef TEST_COMPILATION_ERRORS
	moveCannotBeEmptyTest();
	moveVehicleErrorsTest();
#endif

#ifdef COME_TO_THE_LEV_SIDE
	getCoordinatesTest();
	gameBoardAtTest();
	takeDropListTest();
	sublistTest();
	concatTest();
	reverseTest();
	moveForwardBackwardTest();
	providedExampleStepByStep();
#endif

    return 0;
}

