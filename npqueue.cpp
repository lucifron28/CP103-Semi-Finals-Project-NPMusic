#include "npqueue.h"
#include <stdexcept>

void npqueue::enqueue(const TrackInfo& value) {
    arr.push_back(value);
}

TrackInfo npqueue::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    TrackInfo frontElement = arr.front();
    arr.erase(arr.begin());
    return frontElement;
}

TrackInfo npqueue::front() const {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    return arr.front();
}

bool npqueue::isEmpty() const {
    return arr.empty();
}
