#ifndef S21_STACK_H_
#define S21_STACK_H_

namespace s21 {

class Stack {
 public:
  Stack();
  ~Stack();

  int size();
  void push(int value);
  int pop();
  int peek();

 private:
  struct node {
    int value;
    node* next;
  };

  node* _head;
  int _size;
};
}  //  namespace s21
#endif  // S21_STACK_H_