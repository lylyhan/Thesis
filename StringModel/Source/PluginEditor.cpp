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
    : AudioProcessorEditor (&p), processor (p),cusGUI(p),myString(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 500);
    addAndMakeVisible(&title);
    title.setText("Acoustic Drum Synthesizer",dontSendNotification);
    title.setColour(1, Colours::brown);
    addAndMakeVisible(cusGUI);
    addAndMakeVisible(myString);
}

StringModelAudioProcessorEditor::~StringModelAudioProcessorEditor()
{
}

//==============================================================================
void StringModelAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::midnightblue);
    g.setColour (Colours::darkkhaki);
    //auto centralArea = getLocalBounds().toFloat().reduced (10.0f);
    //g.drawRoundedRectangle (centralArea, 5.0f, 3.0f);
    float tau = cusGUI.getsliderval(1);
    float p = cusGUI.getsliderval(2);
    float dispersion = cusGUI.getsliderval(3);
    float alpha = cusGUI.getsliderval(4);
    float alpha2 = cusGUI.getsliderval(5);
    float length = cusGUI.getsliderval(6);
    float A = cusGUI.getsliderval(7);
    float rho = cusGUI.getsliderval(8);
    float T = cusGUI.getsliderval(9);
    //std::cout<<"how many times\n";
    myString.changeParameter(tau,p,dispersion,alpha,alpha2,length,A,rho,T);
    myString.repaint();
    
}

void StringModelAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    title.setBounds(200,0,200,100);
    cusGUI.setBounds(100,100,400,200);
    myString.setBounds(10, 300, 580, 200);
}
