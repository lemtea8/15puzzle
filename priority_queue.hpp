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
        heapify_bottomup(container.size() - 1);
    }

    void clear() {
        container.clear();
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
    void heapify_bottomup(int curr) {
        T bottom = container[curr];
        while (curr != 1 && compare(bottom, container[curr / 2])) {
            container[curr] = container[curr / 2];
            curr /= 2;
        }
        container[curr] = bottom;
    }

    void heapify_topdown(int curr) {
        int size = container.size();
        T root = container[curr];
        int child;

        while (curr * 2 < size) {
            // left
            child = curr * 2;
            // right
            if (child < size && compare(container[child + 1], container[child])) {
                child += 1;
            }
            if (compare(container[child], root)) {
                container[curr] = container[child];
            } else {
                break;
            }
            curr = child;
        }
        container[curr] = root;
    }

    std::vector<T> container;
    bool (*compare)(T i, T j);
};

#endif