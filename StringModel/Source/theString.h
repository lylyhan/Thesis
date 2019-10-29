/*
  ==============================================================================

    theString.h
    Created: 23 Oct 2019 12:20:19pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class theString : public Component
{
public:
    theString(StringModelAudioProcessor& p);
    ~theString();
    void paint(Graphics& g) override;
    void resized() override;
    void changeParameter(float tau, float p, float dispersion, float alpha, float alpha2,float length,float A, float rho, float T);
    
private:
    Path myString;
    //Rectangle<float> Mystring2;
    StringModelAudioProcessor& processor;
    float l,diameter,Rho;
   
};
