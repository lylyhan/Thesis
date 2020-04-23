/*
  ==============================================================================

    Drumface.h
    Created: 10 Apr 2020 12:28:06pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class Drumface : public Component
{
public:
    Drumface(StringModelAudioProcessor& p);
    ~Drumface();
    void paint(Graphics& g) override;
    void resized() override;
    void changeParameter(float length,float alpha);
    void mouseDown (const MouseEvent& e) override;
    void clicked(int midiNote);
private:
    ImageComponent helpButton;
    float l1,l2;
    StringModelAudioProcessor& processor;
    Rectangle<float> Drum;
};
