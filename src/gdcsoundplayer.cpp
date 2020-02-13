#include "gdcsoundplayer.h"
#include <iostream>

using namespace godot;
using namespace std;
using namespace smf;

std::queue<std::unique_ptr<smf::MidiMessage>> GDCSoundAudioStreamPlayer::midi_queue;


GDCSoundAudioStreamPlayer::GDCSoundAudioStreamPlayer() {
}

GDCSoundAudioStreamPlayer::~GDCSoundAudioStreamPlayer() {
    delete csound;
}

void GDCSoundAudioStreamPlayer::_init() {
    csound = new Csound();
    csound->Compile("test.csd");
    //csound->Reset();

    //csound->CreateMessageBuffer(0);
    //csound->SetDebug(true);

    csound->SetHostImplementedAudioIO(1,0);
    csound->SetHostImplementedMIDIIO(true);
    csound->SetExternalMidiWriteCallback(WriteMidiData);
    csound->SetExternalMidiReadCallback(ReadMidiData);

    //csound->ReadScore("i 1 0 5 440 .5");
    csound->Start();

    spout = csound->GetSpout();
    spin  = csound->GetSpin();
    scale = csound->Get0dBFS();

    stream_playback = get_stream_playback();
    stream_generator = get_stream();

    sampleCount = 0;
}

void GDCSoundAudioStreamPlayer::_process(float delta) {
    fill_buffer();
}

void GDCSoundAudioStreamPlayer::fill_buffer() {
    if (stream_playback == NULL || stream_generator == NULL) {
        return;
    }

    int64_t to_fill = stream_playback->get_frames_available();

    int mix_rate = stream_generator->get_mix_rate();

    if (to_fill > mix_rate) {
        to_fill = mix_rate;
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

        for (int i = 0; i < csound->GetKsmps() * csound->GetNchnls(); i = i + csound->GetNchnls()) {
            stream_playback->push_frame(
                    Vector2(spout[i] / scale, spout[i + 1] / scale));
            filled = filled + 1;

            if (filled >= to_fill) {
                return;
            }
        }
    }
}

void GDCSoundAudioStreamPlayer::sendNoteOn(int channel, int note, int velocity) {
    unique_ptr<MidiMessage> midi_message (new MidiMessage());
    midi_message->makeNoteOn(channel, note, velocity);
    midi_queue.push(move(midi_message));
}

void GDCSoundAudioStreamPlayer::sendNoteOff(int channel, int note) {
    unique_ptr<MidiMessage> midi_message (new MidiMessage());
    midi_message->makeNoteOff(channel, note);
    midi_queue.push(move(midi_message));
}

int GDCSoundAudioStreamPlayer::WriteMidiData(CSOUND *csound, void *userData,
                         const unsigned char *mbuf, int nbytes) {
    return 0;
}

int GDCSoundAudioStreamPlayer::ReadMidiData(CSOUND *csound, void *userData,
                         unsigned char *mbuf, int nbytes) {
    int count = 0;

    while (!midi_queue.empty() && count <= (nbytes - 3)) {
        unique_ptr<MidiMessage> midi_message = move(midi_queue.front());
        midi_queue.pop();

        for (auto it = midi_message->begin(); it != midi_message->end(); ++it) {
            *mbuf++ = *it;;
        }
        count += midi_message->getSize();
    }

    return count;
}

void GDCSoundAudioStreamPlayer::_register_methods() {
    register_method("_process", &GDCSoundAudioStreamPlayer::_process);
    register_method("send_note_on", &GDCSoundAudioStreamPlayer::sendNoteOn);
    register_method("send_note_off", &GDCSoundAudioStreamPlayer::sendNoteOff);
}
