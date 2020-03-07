/*
  ==============================================================================

    Togglebutton.cpp
    Created: 7 Mar 2020 11:43:03am
    Author:  Lily H

  ==============================================================================
*/

#include "Togglebutton.h"
#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;


Togglebutton::Togglebutton(StringModelAudioProcessor& p):processor(p),
stringButton("string", DrawableButton::ButtonStyle::ImageFitted),
drumButton("drum", DrawableButton::ButtonStyle::ImageFitted),
boxButton("box", DrawableButton::ButtonStyle::ImageFitted)
{
    
  std::unique_ptr<Drawable> buttonOff;
  std::unique_ptr<Drawable> buttonOn;
  
 
  buttonOff = Drawable::createFromImageData(BinaryData::stringOff_png, BinaryData::stringOff_pngSize);
  buttonOn = Drawable::createFromImageData(BinaryData::stringOn_png, BinaryData::stringOn_pngSize);


  stringButton.setImages(buttonOff.get(), buttonOn.get(), buttonOn.get());
  //stringButton.onStateChange = [this] { drumButtonClicked(MidiNotes::kick, Tabs::kickTab, kickButton.isDown()); };


  addAndMakeVisible (stringButton);
    
    
  addAndMakeVisible (drumButton);
  addAndMakeVisible (boxButton);
  //stringButton  .onClick = [this] { updateToggleState (&stringButton,   "String");   };
 // drumButton.onClick = [this] { updateToggleState (&drumButton, "Drum"); };
  //boxButton  .onClick = [this] { updateToggleState (&boxButton,   "Box");   };

}

void Togglebutton::updateToggleState(){
    
};
