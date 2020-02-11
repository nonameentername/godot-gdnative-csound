#ifndef GDCSOUNDPLAYER_H
#define GDCSOUNDPLAYER_H

#include <Godot.hpp>
#include <AudioStream.hpp>
#include <AudioStreamPlayer.hpp>
#include <AudioStreamGeneratorPlayback.hpp>
#include <ProjectSettings.hpp>
#include <ResourceLoader.hpp>
#include <Resource.hpp>
#include <File.hpp>
#include "csound.hpp"


namespace godot {

class GDCSoundAudioStreamPlayer : public AudioStreamPlayer {
    GODOT_CLASS(GDCSoundAudioStreamPlayer, AudioStreamPlayer)

private:
    int sampleCount;
    MYFLT simpleRamp[48000];
    MYFLT *spin, *spout;
    MYFLT scale;
    Csound* csound;
    Ref<AudioStreamGeneratorPlayback> stream_playback;

    void fill_buffer();

public:
    static void _register_methods();

    GDCSoundAudioStreamPlayer();
    ~GDCSoundAudioStreamPlayer();

    void _init();
    void _process(float delta);
};

}

#endif
