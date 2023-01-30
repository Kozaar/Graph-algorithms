#include "s21_queue.h"

#include <stdexcept>

namespace s21 {

Queue::Queue() {
  _tail = nullptr;
  _head = nullptr;
  _size = 0;
}

Queue::~Queue() {
  while (_head) {
    pop();
  }
}

int Queue::size() { return _size; }

void Queue::push(int value) {
  node* temp = _tail;
  _tail = new node;
  _tail->next = nullptr;
  _tail->value = value;
  if (_size) {
    temp->next = _tail;
  } else {
    _head = _tail;
  }
  _size++;
}

int Queue::pop() {
  if (!_size) {
    throw std::invalid_argument("You tried pop empty Queue");
  }
  int result = _head->value;
  node* temp = _head->next;
  delete _head;
  _head = temp;
  _size--;
  return result;
}

int Queue::peek() {
  if (!_size) {
    throw std::invalid_argument("You tried peek empty Queue");
  }
  return _head->value;
}
}  //  namespace s21
