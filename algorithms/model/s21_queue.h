#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

namespace s21 {

class Queue {
 public:
  Queue();
  ~Queue();

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
  node* _tail;
  int _size;
};
}  //  namespace s21
#endif  // S21_QUEUE_H_