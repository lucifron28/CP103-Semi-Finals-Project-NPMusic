#include "npqueue.h"
#include "trackinfo.h"
#include <stdexcept>
#include <algorithm>

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

void npqueue::remove(const TrackInfo& value) {
    auto it = std::find(arr.begin(), arr.end(), value);
    if (it != arr.end()) {
        arr.erase(it);
    }
}

void npqueue::clear()
{
    arr.clear();
}
