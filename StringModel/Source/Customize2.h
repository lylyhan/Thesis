/*
  ==============================================================================

    Customize2.h
    Created: 10 Apr 2020 1:05:36pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Drumface.h"
//==============================================================================
/*
 */
class Customize2    : public Component
{
public:
    Customize2(StringModelAudioProcessor&);
    ~Customize2();
    
    void paint (Graphics&) override;
    void resized() override;
    void playButtonClicked(int midiNote, bool isDown);
private:
    //Label title;
    
    Slider tauSlider;
    Slider omegaSlider;
    Slider lSlider;
    Slider pSlider;
    Slider dispersionSlider;
    Slider alphaSlider;


    //DrawableButton playButton;
    Label taulabel;
    
    Label omegalabel;
    Label llabel;
    Label plabel;
    Label dispersionlabel;
    Label alphalabel;

 
    Label title,sonic,physics,instruction;

    
    Drumface myDrum;
    
    StringModelAudioProcessor& processor;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> tauTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> omegaTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> pTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> dispersionTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> alphaTree;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> dimSelection;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lengthTree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Customize2)
};


