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
    setSize (600, 463);
    addAndMakeVisible(&title);
    title.setText(".  See Your Sound  .",dontSendNotification);
    
    static Typeface::Ptr myType = Typeface::createSystemTypefaceFor(BinaryData::Amagro_bold_ttf,
                                                                BinaryData::Amagro_bold_ttfSize);
    Font* myFont = new Font(myType);
    myFont->setSizeAndStyle(30, 2, 1.0, 0.0);
    title.setFont(*myFont);
    
    title.setColour(Label::ColourIds::textColourId , Colours::black);
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
    g.fillAll(Colour (188, 186, 167));
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
    int dim = cusGUI.getsliderval(10);
    //std::cout<<"how many times\n";
    myString.changeParameter(tau,p,dispersion,alpha,alpha2,length,A,rho,T);
    myString.repaint();
    cusGUI.changeGUI(dim);
    
}

void StringModelAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    title.setBounds(187,0,619,112);
    cusGUI.setBounds(50,100,500,200);
    myString.setBounds(10, 253, 580, 200);
}
