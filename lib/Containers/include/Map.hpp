#pragma once

template <typename Key, typename Value>
struct Pair {
  Key key;
  Value value;
};

template <typename Key, typename Value>
class List {
private:

  struct Node {
    Pair<Key, Value> pair;
    Node * prev;
    Node * next;

    Node(Key key, Value value, Node * previousNode) : pair( { key, value} ), prev(previousNode) { };
    Node(Key key, Node * previousNode) : pair( { key, NULL } ), prev(previousNode) { };
  };

  Node * root = NULL;

  void _push(Key key, Value value, Node * node) {
    if (root == NULL) {
      root = new Node(key, value, NULL);
      return;
    }
    if (node->next == NULL) {
      node->next = new Node(key, value, node);
      return;
    }
    return _push(key, value, node->next);
  }

  void _pop(Key key, Node * node) {
    if (node->pair.key == key) {
      Node * nextNode = node->next;
      node->prev->next = nextNode;
      return free(node);
    }
    if(node->next == NULL) {
      return;
    }
    return _pop(key, node->next);
  }

  Node * _find(Key key, Node * node) {
    if (node->pair.key == key) {
      return node;
    }
    if (node->next == NULL) {
      return NULL;
    }
    return _find(key, node->next);
  }

public:
  List() = default;

  List(uint8_t size, Pair<Key, Value> initializerList[]) {
    for (size_t i = 0; i < size; i++) {
      _push(initializerList[i].key, initializerList[i].value, root);
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

  void pop(Key key) {
    return _pop(key, root);
  }

  void push(Key key, Value value) {
    return _push(key, value, root);
  }

  Value &operator[](Key key) {
    return _find(key, root)->pair.value;
  }

};
