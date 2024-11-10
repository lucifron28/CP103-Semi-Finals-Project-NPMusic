#ifndef NPQUEUE_H
#define NPQUEUE_H

#include "trackinfo.h"
#include <vector>

class npqueue
{
public:
    void enqueue(const TrackInfo& value);
    TrackInfo dequeue();
    TrackInfo front() const;
    bool isEmpty() const;

    // Iterator support
    std::vector<TrackInfo>::iterator begin() { return arr.begin(); }
    std::vector<TrackInfo>::iterator end() { return arr.end(); }
    std::vector<TrackInfo>::const_iterator begin() const { return arr.begin(); }
    std::vector<TrackInfo>::const_iterator end() const { return arr.end(); }

private:
    std::vector<TrackInfo> arr;
};

#endif // NPQUEUE_H
