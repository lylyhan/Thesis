/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Customize.h"
#include "Customize2.h"
//==============================================================================
/**
*/
class StringModelAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    StringModelAudioProcessorEditor (StringModelAudioProcessor&);
    ~StringModelAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    TabbedComponent tabmode;
    SharedResourcePointer <TooltipWindow> help;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    StringModelAudioProcessor& processor;
    
    Customize cusGUI;
    Customize2 cusGUI2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StringModelAudioProcessorEditor)
};
