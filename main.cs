using Godot;
using System;

public class main : Node2D
{
    private MidiIO midi_io;

    public override void _Ready()
    {
        midi_io = (MidiIO) GetNode("/root/midi_io");
    }

    public void _on_CheckButton_toggled(bool button_pressed)
    {
        if (button_pressed)
        {
            midi_io.SendNoteOn(1, 60, 90);
        }
        else
        {
            midi_io.SendNoteOff(1, 60);
        }
    }

    public void _on_CheckButton2_toggled(bool button_pressed)
    {
        if (button_pressed)
        {
            midi_io.SendNoteOn(1, 64, 90);
        }
        else
        {
            midi_io.SendNoteOff(1, 64);
        }
    }

    public void _on_CheckButton3_toggled(bool button_pressed)
    {
        if (button_pressed)
        {
            midi_io.SendNoteOn(1, 67, 90);
        }
        else
        {
            midi_io.SendNoteOff(1, 67);
        }
    }

    public void _on_VSlider_value_changed(float value)
    {
        midi_io.SendControlChannel("cutoff", value);
    }

}
