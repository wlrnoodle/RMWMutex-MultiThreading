
#include <shared_mutex>
using namespace std;

class Llist_node {
 public:
  Llist_node(int d) {
    data = d;
    next = NULL;
  }

  int data;
  Llist_node *next;
};

class CSE113_Stack {
 public:
  CSE113_Stack() {
    start = NULL;
  }

  void swaptop(int p) {
    m_shared.lock_shared();

    if (start == NULL) {
      m_shared.unlock_shared();
      return;
    }

    Llist_node *current = start;

    while (current->next != NULL) {
      current = current->next;
    }

    if (current->data == p) {
      m_shared.unlock_shared();
      return;
    }

    m_shared.unlock_shared();
    m_shared.lock();

    if (start != NULL) {
      current = start;

      while (current->next != NULL) {
        current = current->next;
      }
      current->data = p;
    }

    m_shared.unlock();
  }

  int pop() {
    m_shared.lock();

    if (start == NULL) {
      m_shared.unlock();
      return -1;
    }

    if (start->next == NULL) {
      int ret = start->data;
      delete start;
      start = NULL;
      m_shared.unlock();
      return ret;
    }

    Llist_node *current = start->next;
    Llist_node *previous = start;

    while (current->next != NULL) {
      previous = current;
      current = current->next;
    }

    int ret = current->data;
    previous->next = NULL;
    delete current;

    m_shared.unlock();
    return ret;
  }

  int peek() {
    m_shared.lock_shared();

    if (start == NULL) {
      m_shared.unlock_shared();
      return -1;
    }

    Llist_node *current = start;

    while (current->next != NULL) {
      current = current->next;
    }

    int ret = current->data;

    m_shared.unlock_shared();
    return ret;
  }

  void push(int p) {
    m_shared.lock();

    if (start == NULL) {
      start = new Llist_node(p);
      m_shared.unlock();
      return;
    }

    Llist_node *current = start;

    while (current->next != NULL) {
      current = current->next;
    }

    current->next = new Llist_node(p);

    m_shared.unlock();
  }

 private:
  Llist_node *start;
  shared_mutex m_shared;
};