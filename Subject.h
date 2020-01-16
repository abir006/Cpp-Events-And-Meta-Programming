//
// Created by ארז on 15/01/2020.
//

#ifndef OOP_HW5_SUBJECT_H
#define OOP_HW5_SUBJECT_H

#include "OOP5EventException.h"
#include <vector>
using std::vector;
template<typename T> class Subject {
  vector<Observer<T>*> observers_vec;
 public:
  Subject() = default;
  void notify(const T& t){
    for(Observer<T>* observer : observers_vec){
      observer->handleEvent(t);
    }
  }

  void addObserver(Observer<T>& observer_to_add){
    for(Observer<T>* observer : observers_vec){
      if(observer == &observer_to_add){
        throw ObserverAlreadyKnownToSubject();
      }
    }
    observers_vec.push_back(&observer_to_add);
  }

  void removeObserver(Observer<T>& observer_to_remove){
   for(typename vector<Observer<T>*>::const_iterator it = observers_vec.cbegin() ; it != observers_vec.cend() ; ++it){
     if(*it == &observer_to_remove){
       observers_vec.erase(it);
       return;
     }
   }
   throw ObserverUnknownToSubject();
  }

  Subject<T>& operator+=(Observer<T>& observer_to_add){
    addObserver(observer_to_add);
    return *this;
  }

  Subject<T>& operator-=(Observer<T>& observer_to_remove){
    removeObserver(observer_to_remove);
    return *this;
  }

  Subject<T>& operator()(const T& t){
    notify(t);
    return *this;
  }

};

#endif //OOP_HW5_SUBJECT_H
