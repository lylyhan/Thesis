/*
  ==============================================================================

    Togglebutton.h
    Created: 7 Mar 2020 11:43:03am
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class Togglebutton    : public Component
{
public:
    Togglebutton(StringModelAudioProcessor&);
    ~Togglebutton();
    
    void updateToggleState();
    
private:
    
    StringModelAudioProcessor& processor;
       
    DrawableButton stringButton;
    DrawableButton drumButton;
    DrawableButton boxButton;
    
    
    
};


    
    
