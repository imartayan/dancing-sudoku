#ifndef HEAP_HPP
#define HEAP_HPP

#include <unordered_map>
#include <vector>

template <typename U, typename T> class Heap {
private:
  int size = 0;
  std::vector<T> data;
  std::vector<U> id;                // maps an index to its id
  std::unordered_map<U, int> index; // maps an id to its index

  void swap(int i, int j) {
    T x = data[i];
    data[i] = data[j];
    data[j] = x;
    U u = id[i];
    id[i] = id[j];
    id[j] = u;
    index[id[i]] = i;
    index[id[j]] = j;
  }

  void sift_up(int i) {
    int j = (i - 1) / 2;
    if (j >= 0 && data[i] < data[j]) {
      swap(i, j);
      sift_up(j);
    }
  }

  void sift_down(int i) {
    int j = 2 * i + 1;
    if (j + 1 < size && data[j + 1] < data[j])
      j++;
    if (j < size && data[j] < data[i]) {
      swap(i, j);
      sift_down(j);
    }
  }

public:
  Heap() {}

  Heap(std::vector<U> keys, std::vector<T> values) {
    size = values.size();
    data = values;
    id = keys;
    for (int i = 0; i < size; i++)
      index[keys[i]] = i;
    heapify();
  }

  void append(U u, T x) {
    int i = data.size();
    data.push_back(x);
    id.push_back(u);
    index[u] = i;
    swap(i, size);
    size++;
  }

  void heapify() {
    for (int i = (size - 1) / 2; i >= 0; i--)
      sift_down(i);
  }

  bool is_empty() { return size == 0; }

  U take_min() {
    size--;
    swap(0, size);
    sift_down(0);
    return id[size];
  }

  void increase(U u, T x) {
    int i = index[u];
    if (i < size) {
      data[i] = x;
      sift_down(i);
    }
  }

  void decrease(U u, T x) {
    int i = index[u];
    if (i < size) {
      data[i] = x;
      sift_up(i);
    }
  }

  void remove(U u) {
    int i = index[u];
    if (i < size) {
      size--;
      swap(i, size);
      sift_down(i);
    }
  }

  void restore(U u) {
    int i = index[u];
    if (i >= size) {
      swap(i, size);
      sift_up(size);
      size++;
    }
  }
};

#endif // HEAP_HPP
