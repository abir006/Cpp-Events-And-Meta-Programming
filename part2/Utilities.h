//
// Created by Shahak on 17/01/2020.
//

#ifndef OOP_HW5_UTILITIES_H
#define OOP_HW5_UTILITIES_H

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

#endif //OOP_HW5_UTILITIES_H
