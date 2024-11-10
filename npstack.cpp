#include "npstack.h"
#include <stdexcept>

void npstack::push(const TrackInfo& value) {
    arr.push_back(value);
}

TrackInfo npstack::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    TrackInfo value = arr.back();
    arr.pop_back();
    return value;
}

TrackInfo npstack::peek() const {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    return arr.back();
}

bool npstack::isEmpty() const {
    return arr.empty();
}

void npstack::clear()
{
    arr.clear();
}

std::vector<TrackInfo>::iterator npstack::begin() {
    return arr.begin();
}

std::vector<TrackInfo>::iterator npstack::end() {
    return arr.end();
}
