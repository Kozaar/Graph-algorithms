#include "s21_stack.h"

#include <stdexcept>

namespace s21 {
Stack::Stack() {
  _head = nullptr;
  _size = 0;
}

Stack::~Stack() {
  while (_head) {
    pop();
  }
}

int Stack::size() { return _size; }

void Stack::push(int value) {
  node* temp = _head;
  _head = new node;
  _head->value = value;
  _head->next = temp;
  _size++;
}

int Stack::pop() {
  if (!_head) {
    throw std::invalid_argument("You tried pop empty Stack");
  }
  int result = _head->value;
  node* temp = _head->next;
  delete _head;
  _head = temp;
  _size--;
  return result;
}

int Stack::peek() {
  if (!_size) {
    throw std::invalid_argument("You tried peek empty Stack");
  }
  return _head->value;
}
}  //  namespace s21