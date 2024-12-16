# midi-keyboard
This project was created as a stepping-stone for some other projects I plan to work on surrounding my Yamaha CK88. I didn't quite want to interact with a full DAW, so I wrote this instead.

# File Structure
I have split the "Piano" class into two separate files so that later on, if I or someone else wanted to, they could change all the Windows calls to work with Linux or MacOS.
The commands I send to the piano are in the [bindings](Yamaha-CK88-Bindings.h) file so more can be added easily as needed.
[structs.h](structs.h) holds Note, Measure, Song struct definitions. See the implementation section for a description of those.

# Implementation
This project is a bit more than just a barebones API, but is not anything as full-fledged as a DAW. The `Piano` class is what handles the connection to the MIDI device that data will be sent to. `Piano` objects also have a "queue" of sorts that holds `Songs` in them. These `Song` structs contains `Measures` which contain `Notes`. The `Piano::player()` function goes through the queue of `Songs` and, using the `Measures`' tempo and time signature, plays the `Notes` accordingly.
