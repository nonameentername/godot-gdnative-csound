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

    public void SendNoteOn(int channel, int key, int velocity)
    {
        csound.Call("send_note_on", channel, key, velocity);
    }

    public void SendNoteOff(int channel, int key)
    {
        csound.Call("send_note_off", channel, key);
    }

    public void SendControlChange(int channel, int number, float value)
    {
        csound.Call("send_control_change", channel, number, value);
    }

    public void SendControlChannel(string channel, float value)
    {
        csound.Call("send_control_channel", channel, value);
    }
}
