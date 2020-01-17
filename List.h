//
// Created by Abir on 16/01/2020.
//

#ifndef OOP_HW5_LIST_H
#define OOP_HW5_LIST_H

/// declaring List
template<typename...TT> struct List{};

/// empty List should contain only size 0.
template<> struct List<> {
    constexpr static int size = 0;
};

/// List of 1 element, contain the element, next is empty List , and size 1.
template<typename T> struct List<T> {
    typedef T head;
    typedef List<> next;
    constexpr static int size = 1;
};

/// List , contains head, next List , and Size.
template<typename T,typename... TT> struct List<T,TT...> {
    typedef T head;
    typedef List<TT...> next;
    constexpr static int  size = (sizeof...(TT)+1);
};

/// declaring PrependList.
template<typename ... TT>struct PrependList{};

/// putting the element in the head of List , and rest in Next of List.
template<typename T, typename...TT> struct PrependList<T,List<TT...>>{
   typedef List<T,TT...> list;
    constexpr static int  size = (sizeof...(TT)+1);
};

/// declaring GetAtIndex.
template<int N, typename T> struct GetAtIndex {};

/// GetAtIndex 0 for a List with 1 type.
template<typename T> struct GetAtIndex<0,List<T>>{
    typedef T value;
};

/// GetAtIndex 0 for a List with more than 1 type.
template<typename T,typename...TT> struct GetAtIndex<0,List<T,TT...>>{
    typedef T value;
};

/// GetAtIndex for a List, only if N>=0 , recursive untill N=0, value will be the type.
template<int N, typename T, typename ...TT> struct GetAtIndex<N, List<T,TT...>>{
    static_assert(N<0,"INDEX IS ILLEGAL (smaller than 0)");
    typedef typename GetAtIndex<N-1,List<TT...>>::value value;
};

/// declaring SetAtIndex.
template<int N,typename U, typename T> struct SetAtIndex{};

/// SetAtIndex 0 for List with 1 type.
template <typename U, typename T> struct SetAtIndex<0,U,List<T>>{
    typedef List<U> list;
};

/// SetAtIndex 0 for List with more than 1 type.
template <typename U,typename T,typename...TT> struct SetAtIndex<0,U,List<T,TT...>>{
    typedef List<U,TT...> list;
};

/// SetAtIndex for other index's.
/// if we are here than N!=0, so make Recursive definition till index is 0
/// where everytime we take first type, and join it to the rest where we try to put a type at index N-1
/// which will be put when N=0.
template <int N,typename U, typename T,typename...TT> struct SetAtIndex<N,U,List<T,TT...>>{
    static_assert(N<0, "Index  is smaller than 0");
    typedef typename PrependList<T,SetAtIndex<N-1,U,List<TT...>>>::list list;
};





#endif //OOP_HW5_LIST_H
