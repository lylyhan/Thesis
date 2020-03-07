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
    : AudioProcessorEditor (&p), processor (p),mode(TabbedButtonBar::Orientation::TabsAtRight)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
   
    //addAndMakeVisible(&title);
    //title.setText("Acoustic Drum Synthesizer",dontSendNotification);
    //title.setColour(1, Colours::brown);
    setSize (400,500);
    stringCUS = new Customize(p,1);
    drumCUS = new Customize(p,2);
    boxCUS = new Customize(p,3);
    
    //mode = new TabbedComponent(TabbedButtonBar::Orientation::TabsAtRight);
    mode.addTab("String", Colours::red, stringCUS, false);
    mode.addTab("Drum", Colours::red, drumCUS, false);
    mode.addTab("Box", Colours::red, boxCUS, false);
    mode.setVisible(true);
    int currentTab = mode.getTabbedButtonBar().getCurrentTabIndex();
    //currentTab.referTo (processor.tree.getParameterAsValue ("dimtype"));
    std::cout<<"current Tab "<<currentTab<<"\n";
    if ((but = dynamic_cast<Button*>(mode.getTabbedButtonBar().getTabButton(currentTab)))){
        if(currentTab==0){
        //but->getToggleStateValue().referTo (processor.tree.getParameterAsValue ("dimtype"));
        dimSelection = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree,"dimtype",*but);
        std::cout<<"dimtype "<<processor.tree.getRawParameterValue("dimtype")<<"\n";
        }
    }
    //addAndMakeVisible(cusGUI);
    //addAndMakeVisible(myString);
}

StringModelAudioProcessorEditor::~StringModelAudioProcessorEditor()
{
}

//==============================================================================
void StringModelAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll(Colours::white);
    //g.setColour (Colours::darkkhaki);
    //auto centralArea = getLocalBounds().toFloat().reduced (10.0f);
    //g.drawRoundedRectangle (centralArea, 5.0f, 3.0f);
    //float tau = cusGUI.getsliderval(1);
    //float p = cusGUI.getsliderval(2);
    //float dispersion = cusGUI.getsliderval(3);
    //float alpha = cusGUI.getsliderval(4);
    //float alpha2 = cusGUI.getsliderval(5);
    //std::cout<<"how many times\n";
    //myString.changeParameter(tau,p,dispersion,alpha,alpha2);
    //myString.repaint();
    
}

void StringModelAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    setSize (372,470);
    title.setBounds(200,0,200,100);
     mode.setBounds(-61,
                      -2,
                      338,
                      479);
       

       for (int i=0;i < mode.getNumTabs(); i++)
       {
           mode.getTabbedButtonBar().getTabButton(i)->setBounds(200,
                                                                500/3*i,
                                                                30,
                                                                25);
       }
       addAndMakeVisible(mode);
    //cusGUI.setBounds(-66,-36,370,500);
   // myString.setBounds(10, 300, 580, 200);
}
