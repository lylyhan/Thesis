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

//==============================================================================
/*
 */
class Customize    : public Component
{
public:
    Customize(StringModelAudioProcessor&);
    ~Customize();
    
    void paint (Graphics&) override;
    void resized() override;
    float getsliderval(int seq);

private:
    Slider tauSlider;
    //Slider omegaSlider;
    Slider lSlider;
    Slider pSlider;
    Slider dispersionSlider;
    Slider alphaSlider;
    Slider alpha2Slider;
    Slider rhoSlider;
    Slider ASlider;
    Slider TSlider;
    
    ComboBox dimMenu;
    Label taulabel;
    
    //Label omegalabel;
    Label llabel;
    Label plabel;
    Label dispersionlabel;
    Label alphalabel;
    Label alpha2label;
    Label dimlabel;
    Label title;
    Label rholabel,Alabel,Tlabel;
    
    
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


