#ifndef TRACKINFO_H
#define TRACKINFO_H

#include <QString>

class TrackInfo {
public:
    QString trackName;
    QString artistName;

    bool operator==(const TrackInfo& other) const {
        return trackName == other.trackName && artistName == other.artistName;
    }
};

#endif // TRACKINFO_H