#ifndef STRUCTS_H
#define STRUCTS_H

#include <map>
#include <queue>
#include <vector>

struct Note {
    int pitch;
    int velocity;
    double duration;
};

struct Measure {
    unsigned int tempo{};
    int timeSignatureTop{};
    int timeSignatureBottom{};
    std::map<int, std::queue<Note>> noteStarts;
    std::map<int, std::queue<Note>> noteEnds;
};

struct Song {
    std::vector<Measure> measures;
};

#endif //STRUCTS_H
