#ifndef __PRIORITY_QUEUE_HPP__
#define __PRIORITY_QUEUE_HPP__

#include <vector>

template <typename T> class PriorityQueue {
  public:
    PriorityQueue(bool (*compare)(T i, T j)) {
        container = std::vector<T>(1);
        this->compare = compare;
    }

    PriorityQueue(bool (*compare)(T i, T j), int capacity) {
        container = std::vector<T>(1);
        container.reserve(capacity);
        this->compare = compare;
    }

    bool empty() { return container.size() == 1; }

    void push(T t) {
        container.push_back(t);
        heapify_bottomup();
    }

    T top() { return container[1]; }

    void pop() {
        if (empty()) {
            return;
        }
        container[1] = container[container.size() - 1];
        container.pop_back();
        heapify_topdown(1);
    }

    int size() { return container.size() - 1; }

  private:
    void heapify_bottomup() {
        int n = container.size() - 1;
        while (n != 1 && compare(container[n], container[n / 2])) {
            T temp;
            temp = container[n];
            container[n] = container[n / 2];
            container[n / 2] = temp;
            n /= 2;
        }
    }

    void heapify_topdown(int n) {
        int left = 2 * n, right = left + 1;
        int size = container.size();

        while (true) {
            int smaller = n;
            if (left < size && compare(container[left], container[n])) {
                smaller = left;
            }
            if (right < size && compare(container[right], container[smaller])) {
                smaller = right;
            }

            if (smaller == n) {
                break;
            }

            T temp;
            temp = container[smaller];
            container[smaller] = container[n];
            container[n] = temp;

            n = smaller;
            left = 2 * n;
            right = left + 1;
        }
    }

    std::vector<T> container;
    bool (*compare)(T i, T j);
};

#endif