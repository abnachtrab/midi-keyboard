#include "piano.h"

void Piano::queueSong(const Song &s) {
    songQueue.push(s);
}

void Piano::nextSong() {
    if (!songQueue.empty()) {
        songQueue.pop();
    }
}

void Piano::play() {
    isPlaying = true;
    player();
    isPlaying = false;
}

void Piano::stop() {
    isPlaying = false;
}


void Piano::player() {
    while (isPlaying && !songQueue.empty()) {
        currentSong = songQueue.front();
        songQueue.pop();
        while (isPlaying && !currentSong.measures.empty()) {
            auto [
                tempo, timeSignatureTop, timeSignatureBottom,
                noteStarts, noteEnds
            ] = currentSong.measures.front();
            currentSong.measures.erase(currentSong.measures.begin());
            for (int i = 0;isPlaying && i < timeSignatureTop * 24; i++) {
                // 24 note slots per beat
                // Start new notes
                while (isPlaying && !noteStarts[i].empty()) {
                    const Note note = noteStarts[i].front();
                    noteStarts[i].pop();
                    const int duration = static_cast<int>(note.duration * 24);
                    sendNote(note.pitch, note.velocity);
                    if (i + duration < timeSignatureTop * 24) {
                        noteEnds[i + duration].push(note);
                    } else {
                        const int endMeasure = duration / (timeSignatureTop * 24);
                        const int endBeat = duration % (timeSignatureTop * 24)-1;
                        // Add note to the endMeasure-th measure
                        currentSong.measures[endMeasure].noteEnds[endBeat].push(note);
                    }
                }
                // Stop notes
                while (isPlaying && !noteEnds[i].empty()) {
                    stopNote(noteEnds[i].front().pitch);
                    noteEnds[i].pop();
                }
                Sleep(60000 / tempo / 24);
            }
        }
        if (currentSong.measures.empty()) {
            nextSong();
        }
    }
}
