//
// Created by ארז on 15/01/2020.
//

#ifndef OOP_HW5_OBSERVER_H
#define OOP_HW5_OBSERVER_H

template<typename T> class Observer {
 public:
  virtual void handleEvent(const T& t) = 0;
};

#endif //OOP_HW5_OBSERVER_H
