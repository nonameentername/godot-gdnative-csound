using Godot;
using System.Collections.Generic;
using System;


public class MidiIO : Node
{
    private Node csound;

    public override void _Ready()
    {
        csound = GetNode("/root/csound");
    }

    public void SendNoteOn(int channel, int note, int velocity)
    {
        csound.Call("send_note_on", channel, note, velocity);
    }

    public void SendNoteOff(int channel, int note)
    {
        csound.Call("send_note_off", channel, note);
    }
}
