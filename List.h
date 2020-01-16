//
// Created by Abir on 16/01/2020.
//

#ifndef OOP_HW5_LIST_H
#define OOP_HW5_LIST_H
//TODO: check the List below (like viewed in tutorial 11) ITS NOT WORKING REMOVE COMMENTS TO SEE
/*
template<typename... TT>
struct TypeList {};

template<typename T, typename... TT>
struct TypeList {
typedef T type;
typedef TypeList<TT...> tail;
};
*/

template<typename...TT> struct List{};

template<>
struct List<> {
    constexpr static int size = 0;
};

template<typename T>
struct List<T> {
    typedef T head;
    typedef List<> next;
    constexpr static int size = 1;
};

template<typename T,typename... TT> struct List<T,TT...> {
    typedef T head;
    typedef List<TT...> next;
    constexpr static int  size = (sizeof...(TT)+1);
};

template<typename ... TT>struct PrependList{};

template<typename T, typename...TT>
struct PrependList<T,List<TT...>>{
   typedef List<T,TT...> list;
    constexpr static int  size = (sizeof...(TT)+1);
};



#endif //OOP_HW5_LIST_H
