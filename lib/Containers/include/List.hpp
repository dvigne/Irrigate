#pragma once

template <typename Value>
class List {
private:

  struct Node {
    Value value;
    Node * prev;
    Node * next;

    Node(Value value, Node * previousNode) : value(value), prev(previousNode) { };
  };

  Node * root = NULL;

  void _push(Value value, Node * node) {
    if (root == NULL) {
      root = new Node(value, NULL);
      return;
    }
    if (node->next == NULL) {
      node->next = new Node(value, node);
      return;
    }
    return _push(value, node->next);
  }

  void _pop(Value value, Node * node) {
    if (node->value == value) {
      Node * nextNode = node->next;
      node->prev->next = nextNode;
      return free(node);
    }
    if(node->next == NULL) {
      return;
    }
    return _pop(value, node->next);
  }

  Node * _find(Value value Node * node) {
    if (node->value == value) {
      return node;
    }
    if (node->next == NULL) {
      return NULL;
    }
    return _find(value, node->next);
  }

public:
  List() = default;

  List(uint8_t size, Value initializerList[]) {
    for (size_t i = 0; i < size; i++) {
      _push(initializerList[i].value, root);
    }
  }

  uint8_t size() {
    uint8_t count = 0;
    Node * node = root;
    while((node = node->next) != NULL) {
      count++;
    }
    return count;
  }

  void pop(Value value) {
    return _pop(value, root);
  }

  void push(Value value) {
    return _push(value, root);
  }

  Value &operator[](Value value) {
    return _find(value, root)->pair.value;
  }

};
