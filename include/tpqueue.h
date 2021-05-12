// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template <typename T>
class TPQueue {
 private:
  struct ITEM {
    T data;
    ITEM* prev;
    ITEM* next;
  };
  ITEM* start;
  ITEM* end;
  TPQueue::ITEM* create(const T& data, ITEM* prev) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->prev = prev;
    return item;
  }

 public:
  TPQueue() : start(nullptr), end(nullptr) {}
  ~TPQueue() {
    while (start) pop();
  }
  void push(const T& data) {
    if (end && start) {
      ITEM* curr = end;
      while (curr && data.prior > (curr->data).prior) {
        curr = curr->prev;
      }
      if (curr) {
        ITEM* tmp = curr->next;
        curr->next = create(data, curr);
        curr = curr->next;
        curr->next = tmp;
        if (tmp) {
          tmp->prev = curr;
        } else {
          end = curr;
        }
      } else {
        curr = create(data, nullptr);
        curr->next = start;
        start->prev = curr;
        start = curr;
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
    if (tmp) tmp->prev = nullptr;
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
