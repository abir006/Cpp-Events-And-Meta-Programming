//
// Created by Abir on 16/01/2020.
//

#ifndef OOP_HW5_LIST_H
#define OOP_HW5_LIST_H

/// Declaring List.
template<typename ...TT>
struct List {};

/// Assert that an empty List contains only size=0.
template<>
struct List<> {
    constexpr static int size = 0;
};

/// In a singleton list, the list contains the single element, next is an empty List, and size is 1.
template<typename T>
struct List<T> {
    typedef T head;
    typedef List<> next;
    constexpr static int size = 1;
};

/// Non singleton list contains head, next List, and size.
template<typename T, typename ...TT>
struct List<T, TT...> {
    typedef T head;
    typedef List<TT...> next;
    constexpr static int size = (sizeof ...(TT) + 1);
};

/// Declaring PrependList.
template<typename ...TT>
struct PrependList {};

/// Puts the element in the head of List, and the rest in Next of List.
template<typename T, typename ...TT>
struct PrependList<T, List<TT...> > {
    typedef List<T, TT...> list;
    constexpr static int  size = (sizeof ...(TT)+1);
};

/// Declaring GetAtIndex.
template<int N, typename T>
struct GetAtIndex {};

/// GetAtIndex(0) for a List with a single type.
template<typename T>
struct GetAtIndex<0, List<T> > {
    typedef T value;
};

/// GetAtIndex(0) for a List with several types.
template<typename T, typename ...TT>
struct GetAtIndex<0, List<T, TT...> >{
    typedef T value;
};

/// GetAtIndex for a List, only if N>=0, continues recursively until N=0, value will be the type.
template<int N, typename T, typename ...TT>
struct GetAtIndex<N, List<T, TT...> > {
    static_assert(N >= 0, "GetAtIndex: INDEX IS ILLEGAL (must be non-negative)");
    typedef typename GetAtIndex<N - 1, List<TT...> >::value value;
};

/// Declaring SetAtIndex.
template<int N,typename U, typename T>
struct SetAtIndex {};

/// SetAtIndex(0) for List with a single type.
template <typename U, typename T>
struct SetAtIndex<0, U, List<T> > {
    typedef List<U> list;
};

/// SetAtIndex(0) for List with several types.
template <typename U, typename T, typename...TT>
struct SetAtIndex<0, U, List<T, TT...> > {
    typedef List<U, TT...> list;
};

/// SetAtIndex for other indexes.
/// If we are here then N!=0, so make a recursive definition till index is 0.
/// Every iteration we take the first type, and join it to the rest where we try to put the original type at index N-1.
/// The value will be set in the end of the recursion when N=0.
template <int N, typename U, typename T, typename ...TT>
struct SetAtIndex<N, U, List<T, TT...> > {
    static_assert(N >= 0, "SetAtIndex: INDEX IS ILLEGAL (must be non-negative)");
    typedef typename PrependList<T,typename SetAtIndex<N - 1, U, List<TT...> >::list>::list list;
};

#endif //OOP_HW5_LIST_H