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
    void clear();
    std::vector<TrackInfo>::iterator begin(); // Add this line
    std::vector<TrackInfo>::iterator end();   // Add this line

private:
    std::vector<TrackInfo> arr;
};

#endif // NPSTACK_H
