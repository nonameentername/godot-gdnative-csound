#ifndef GDCSOUNDPLAYER_H
#define GDCSOUNDPLAYER_H

#include <Godot.hpp>
#include <AudioStream.hpp>
#include <AudioStreamPlayer.hpp>
#include <AudioStreamGenerator.hpp>
#include <AudioStreamGeneratorPlayback.hpp>
#include <ProjectSettings.hpp>
#include <ResourceLoader.hpp>
#include <Resource.hpp>
#include <File.hpp>
#include "csound.hpp"
#include "MidiMessage.h"
#include <queue>
#include <memory>
#include <thread>


namespace godot {

class GDCSoundAudioStreamPlayer : public AudioStreamPlayer {
    GODOT_CLASS(GDCSoundAudioStreamPlayer, AudioStreamPlayer)

private:
    bool stop_thread = false;
    std::thread my_thread;
    int sampleCount;
    MYFLT *spin, *spout;
    MYFLT scale;
    Csound* csound;
    Ref<AudioStreamGeneratorPlayback> stream_playback;
    Ref<AudioStreamGenerator> stream_generator;

    void fill_buffer();

public:
    static std::queue<std::unique_ptr<smf::MidiMessage>> midi_queue;

    static void _register_methods();

    GDCSoundAudioStreamPlayer();
    ~GDCSoundAudioStreamPlayer();

    static int ReadMidiData(CSOUND *csound, void *userData, unsigned char *mbuf, int nbytes);
    static int WriteMidiData(CSOUND *csound, void *userData, const unsigned char *mbuf, int nbytes);

    void _init();
    void _process(float delta);
    void sendNoteOn(int channel, int key, int velocity);
    void sendNoteOff(int channel, int key);
    void sendControlChange(int channel, int number, float value);
    void sendControlChannel(String channel, float value);
    void threadMain();
};

}

#endif
