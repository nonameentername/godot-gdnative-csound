#include "gdcsoundplayer.h"
#include <iostream>

using namespace godot;
using namespace std;


static int MidiDataWrite(CSOUND *csound, void *userData,
                         const unsigned char *mbuf, int nbytes) {
    //cout << "WERNER: I'm writing some midi" << endl;
    return nbytes;
}

static int MidiDataRead(CSOUND *csound, void *userData,
                         unsigned char *mbuf, int nbytes) {
    //cout << "WERNER: I'm reading some midi" << endl;
    return nbytes;
    return 0;
}


GDCSoundAudioStreamPlayer::GDCSoundAudioStreamPlayer() {
    for(int i=0;i<24000;i++)
    {
        if (i <= 24000)
        {
            simpleRamp[i] = (float)i/48000.f;
            simpleRamp[48000-i-1] = (float)i/48000.f;
        }
    }
}

GDCSoundAudioStreamPlayer::~GDCSoundAudioStreamPlayer() {
    delete csound;
}

void GDCSoundAudioStreamPlayer::_init() {
    csound = new Csound();
    //csound->SetDebug(true);
    csound->Compile("test.csd");
    //csound->Reset();
    //csound->CreateMessageBuffer(0);


    csound->SetHostImplementedAudioIO(1,0);
    //csound->SetHostImplementedMIDIIO(true);
    //csound->SetExternalMidiWriteCallback(MidiDataWrite);
    //csound->SetExternalMidiReadCallback(MidiDataRead);

    csound->Start();

    spout = csound->GetSpout();
    spin  = csound->GetSpin();
    scale = csound->Get0dBFS();

    stream_playback = get_stream_playback();
    sampleCount = 0;
}

void GDCSoundAudioStreamPlayer::_process(float delta) {
    fill_buffer();
}

void GDCSoundAudioStreamPlayer::fill_buffer() {

    if (stream_playback == NULL) {
        return;
    }

    int64_t to_fill = stream_playback->get_frames_available();

    if (to_fill > 48000) {
        to_fill = 48000;
    }

    int64_t filled = 0;

    while (csound->PerformKsmps() == 0) {
        /*
        while (csound->GetMessageCnt() > 0)
        {
            cout << "CSOUND_MESSAGE:" << csound->GetFirstMessage();
            csound->PopFirstMessage();
        }
        */

        for (int i = 0; i < csound->GetKsmps() * 2; i = i + 2) {
            stream_playback->push_frame(
                    Vector2(spout[i] / scale, spout[i + 1] / scale));
            filled = filled + 1;

            if (filled >= to_fill) {
                return;
            }
        }
    }
}

void GDCSoundAudioStreamPlayer::_register_methods() {
    register_method("_process", &GDCSoundAudioStreamPlayer::_process);
}
