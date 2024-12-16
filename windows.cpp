#include <iostream>

#include "piano.h"
#include "Yamaha-CK88-Bindings.h"

Piano::Piano(const unsigned int deviceIndex): currentSong() {
    if (midiOutOpen(&device, deviceIndex, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
        std::cout << "Connected to MIDI device!" << std::endl;
    } else {
        std::cerr << "Failed to connect to MIDI device." << std::endl;
    }
}

void Piano::sendNote(const unsigned char note, const unsigned char velocity) const {
    const DWORD message = NOTE_PLAY | note << 8 | velocity << 16;
    midiOutShortMsg(device, message);
}

void Piano::stopNote(const unsigned char note) const {
    const DWORD message = NOTE_PLAY | note << 8;
    midiOutShortMsg(device, message);
}

void Piano::stopAll() const {
    constexpr DWORD message = 0xB0 | 0x7B << 8;
    midiOutShortMsg(device, message);
}


