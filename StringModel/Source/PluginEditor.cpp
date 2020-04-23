/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StringModelAudioProcessorEditor::StringModelAudioProcessorEditor (StringModelAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p),cusGUI(p),cusGUI2(p),tabmode(TabbedButtonBar::Orientation::TabsAtTop)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 463);

    if(dynamic_cast<Component*>(&cusGUI)){
    tabmode.addTab("see your sound", Colour (188, 186, 167), &cusGUI, false);
    tabmode.addTab("excite the drum", Colour (188, 186, 167), &cusGUI2, false);
    }
    addAndMakeVisible(tabmode);
    if(tabmode.getCurrentTabIndex()==0){
        processor.dim = 0;
    }
    else{
        processor.dim = 1;
    }
}

StringModelAudioProcessorEditor::~StringModelAudioProcessorEditor()
{
}

//==============================================================================
void StringModelAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colour (188, 186, 167));
    g.setColour (Colours::darkkhaki);
    //auto centralArea = getLocalBounds().toFloat().reduced (10.0f);


    //cusGUI.changeGUI(dim);
 
    
    
}

void StringModelAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   
    //cusGUI.setBounds(50,100,500,200);
    tabmode.setBounds(0,0,600,463);

}
