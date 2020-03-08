/*
  ==============================================================================

    Customize.h
    Created: 10 Oct 2019 10:02:42am
    Author:  Lily H

  ==============================================================================
*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "cusSlider.h"
//==============================================================================
/*
 */
class Customize    : public Component
{
public:
    Customize(StringModelAudioProcessor&,int mode);
    ~Customize();
    
    void paint (Graphics&) override;
    void resized() override;
    float getsliderval(int seq);

private:
    Slider tauSlider;
    Slider pSlider;
    Slider dispersionSlider;
    Slider alphaSlider;
    Slider alpha2Slider;
   
    
    //ComboBox dimMenu;
    Label taulabel;
    Label plabel;
    Label dispersionlabel;
    Label alphalabel;
    Label alpha2label;
    Label dimlabel;
    Label title;

    
    
    StringModelAudioProcessor& processor;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> tauTree;
    //ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> omegaTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> pTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> dispersionTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> alphaTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> alpha2Tree;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> dimSelection;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Customize)
};


