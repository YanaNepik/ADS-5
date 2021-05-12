// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
 private:
  struct ITEM {
    T data;
    ITEM* prior;
    ITEM* next;
  };
  ITEM* start;
  ITEM* end;
  TPQueue::ITEM* create(const T& data, ITEM* prior) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->prior = prior;
    return item;
  }

 public:
  TPQueue() : start(nullptr), end(nullptr) {}
  ~TPQueue() {
    while (start) pop();
  }
  void push(const T& data) {
    if (end && start) {
      ITEM* this = end;
      while (this && data.prior > (this->data).prior) {
        this = this->prior;
      }
      if (this) {
        ITEM* tmp = this->next;
        this->next = create(data, this);
        this = this->next;
        this->next = tmp;
        if (tmp) {
          tmp->prior = this;
        } else {
          end = this;
        }
      } else {
        this = create(data, nullptr);
        this->next = start;
        start->prior = this;
        start = this;
      }
    } else {
      start = create(data, nullptr);
      end = start;
    }
  }
  T pop() {
    assert(start);
    ITEM* tmp = start->next;
    T data = start->data;
    if (tmp) tmp->prior = nullptr;
    delete start;
    start = tmp;
    return data;
  }
};

struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
