#ifndef PART2_PRINTER_H
#define PART2_PRINTER_H

#include "RushHour.h"
#include <iostream>

/**
 * The Printer struct recieves TYPES related to the game and prints out their data
 * Usage: let T be a game type, in order to print its data, use Printer<T>::print().
 * Pass in std::cout in order to print to the console.
 */

template<typename>
struct Printer;

template<typename List>
struct Printer<GameBoard<List>>{
    static void print(std::ostream& output){
        output << "Game Board: " << std::endl << " ";
        Printer<List>::print(output);
    }
};

template<typename Head, typename... Tail>
struct Printer<List<Head, Tail...>>{
    static void print(std::ostream& output){
        Printer<Head>::print(output);
        output << " ";
        Printer<List<Tail...>>::print(output);
    }
};

template<>
struct Printer<List<>>{
    static void print(std::ostream& output){
        output << std::endl;
    }
};

template<CellType Type, Direction Dir, int Length>
struct Printer<BoardCell<Type, Dir, Length>>{
    static void print(std::ostream& output){
        char printed = '_';
        switch(Type){
            case EMPTY: printed = '_'; break;
            case X: printed = 'X'; break;
            case A: printed = 'A'; break;
            case B: printed = 'B'; break;
            case C: printed = 'C'; break;
            case D: printed = 'D'; break;
            case E: printed = 'E'; break;
            case F: printed = 'F'; break;
            case G: printed = 'G'; break;
            case H: printed = 'H'; break;
            case I: printed = 'I'; break;
            case J: printed = 'J'; break;
            case K: printed = 'K'; break;
            case O: printed = 'O'; break;
            case P: printed = 'P'; break;
            case Q: printed = 'Q'; break;
            case R: printed = 'R'; break;
        }
        output << printed;
    }
};

#endif //PART2_PRINTER_H
