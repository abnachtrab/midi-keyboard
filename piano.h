#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <queue>

#include "structs.h"

class Piano {
public:
    explicit Piano(unsigned int deviceIndex);
    void sendNote(unsigned char note, unsigned char velocity) const;
    void stopNote(unsigned char note) const;
    void skipSong();
    void queueSong(const Song& s);
    void nextSong();
    void play();
    void stop();
    void stopAll() const;
private:
    std::queue<Song> songQueue;
    Song currentSong;
    bool isPlaying = false;
    void player();
#ifdef _WIN32
    HMIDIOUT device{};
#endif
};

#endif //KEYBOARD_H
