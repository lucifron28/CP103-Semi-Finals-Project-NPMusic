#ifndef NPSTACK_H
#define NPSTACK_H

#include "trackinfo.h"
#include <vector>

class npstack
{
public:
    void push(const TrackInfo& value);
    TrackInfo pop();
    TrackInfo peek() const;
    bool isEmpty() const;

private:
    std::vector<TrackInfo> arr;
};

#endif // NPSTACK_H
