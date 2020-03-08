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
    : AudioProcessorEditor (&p), processor (p),mode(TabbedButtonBar::Orientation::TabsAtRight),
stringButton("string", DrawableButton::ButtonStyle::ImageStretched ),
drumButton("drum", DrawableButton::ButtonStyle::ImageStretched ),
boxButton("box", DrawableButton::ButtonStyle::ImageStretched ),
stringCUS(p,1),drumCUS(p,2),boxCUS(p,3)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
   
    //addAndMakeVisible(&title);
    //title.setText("Acoustic Drum Synthesizer",dontSendNotification);
    //title.setColour(1, Colours::brown);
    setSize (400,500);
    background = ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);
    std::unique_ptr<Drawable> buttonOff;
    std::unique_ptr<Drawable> buttonOn;
     
     buttonOff = Drawable::createFromImageData(BinaryData::stringOff_png, BinaryData::stringOff_pngSize);
     buttonOn = Drawable::createFromImageData(BinaryData::stringOn_png, BinaryData::stringOn_pngSize);
    stringButton.setClickingTogglesState(true);
    stringButton.setImages(buttonOff.get(), nullptr,nullptr,nullptr,buttonOn.get());
    stringButton.onStateChange = [this] {buttonClicked(1);};
    stringButton.setRadioGroupId(1);

    stringTree= new AudioProcessorValueTreeState::ButtonAttachment(processor.tree,"dim1",stringButton);

     addAndMakeVisible (stringButton);
       
    buttonOff = Drawable::createFromImageData(BinaryData::drumOff_png, BinaryData::drumOff_pngSize);
    buttonOn = Drawable::createFromImageData(BinaryData::drumOn_png, BinaryData::drumOn_pngSize);
    drumButton.setClickingTogglesState(true);
    drumButton.setImages(buttonOff.get(), nullptr,nullptr,nullptr,buttonOn.get());
    drumButton.setRadioGroupId(1);
    drumButton.onStateChange = [this] {buttonClicked(2);};
    drumTree= new AudioProcessorValueTreeState::ButtonAttachment(processor.tree,"dim2",drumButton);

    addAndMakeVisible (drumButton);
    
    buttonOff = Drawable::createFromImageData(BinaryData::boxOff_png, BinaryData::boxOff_pngSize);
    buttonOn = Drawable::createFromImageData(BinaryData::boxOn_png, BinaryData::boxOn_pngSize);
    boxButton.setClickingTogglesState(true);
       boxButton.setImages(buttonOff.get(), nullptr,nullptr,nullptr,buttonOn.get());
    boxButton.onStateChange = [this] {buttonClicked(3);};
    boxButton.setRadioGroupId(1);
    boxTree= new AudioProcessorValueTreeState::ButtonAttachment(processor.tree,"dim3",boxButton);

    addAndMakeVisible (boxButton);
    
    
    
    //stringCUS = new Customize(p,1);
    //drumCUS = new Customize(p,2);
    //boxCUS = new Customize(p,3);
   // addAndMakeVisible(stringCUS);
    
    if(stringButton.getToggleState()==1){
        addAndMakeVisible(stringCUS);
    }
    else if(drumButton.getToggleState()==1){
        addAndMakeVisible(drumCUS);
    }
    else if(boxButton.getToggleState()==1){
        addAndMakeVisible(boxCUS);
    }
    //mode = new TabbedComponent(TabbedButtonBar::Orientation::TabsAtRight);
    /*
    mode.addTab("String", Colours::red, stringCUS, false);
    mode.addTab("Drum", Colours::red, drumCUS, false);
    mode.addTab("Box", Colours::red, boxCUS, false);
    mode.setVisible(true);
    int currentTab = mode.getTabbedButtonBar().getCurrentTabIndex();
    //currentTab.referTo (processor.tree.getParameterAsValue ("dimtype"));
    //std::cout<<"current Tab "<<currentTab<<"\n";
    if ((but = dynamic_cast<Button*>(mode.getTabbedButtonBar().getTabButton(currentTab)))){
        if(currentTab==0){
        //but->getToggleStateValue().referTo (processor.tree.getParameterAsValue ("dimtype"));
           // processor.tree.addParameterListener("dimtype", *but);
            dimSelection = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree,"dimtype",*but);
      //  std::cout<<"dimtype "<<float(*processor.tree.getRawParameterValue("dimtype"))<<"\n";
        }
    }
    //addAndMakeVisible(cusGUI);
    //addAndMakeVisible(myString);
     */
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
    //this->repaint();
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
     RectanglePlacement backgroundRectanglePlacement(64);
     g.drawImageWithin(background, 0, 0,getWidth(),getHeight(),backgroundRectanglePlacement,false);
    if(stringButton.getToggleState()==1){
        stringCUS.setBounds(-61,-2,338,479);
        addAndMakeVisible(stringCUS);
        
         }
         else if(drumButton.getToggleState()==1){
             drumCUS.setBounds(-61,-2,338,479);
             addAndMakeVisible(drumCUS);
         }
         else if(boxButton.getToggleState()==1){
             boxCUS.setBounds(-61,-2,338,479);
             addAndMakeVisible(boxCUS);
         }
    
    
    //std::cout<<"dimension?? "<<float(*processor.tree.getRawParameterValue("dim1"))<<"\n";
}

void StringModelAudioProcessorEditor::buttonClicked(int seq)
{
    if(seq==1){
        stringCUS.repaint();
        drumCUS.setVisible(false);
        boxCUS.setVisible(false);
    }
    else if(seq==2){
        drumCUS.repaint();
        stringCUS.setVisible(false);
        boxCUS.setVisible(false);
    }
    else if(seq==3){
        boxCUS.repaint();
        drumCUS.setVisible(false);
        stringCUS.setVisible(false);
    }
    //std::cout<<"did tree change "<<float(*processor.tree.getRawParameterValue("dim1"))<<"\n";
}

void StringModelAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    setSize (372,470);
   // title.setBounds(200,0,200,100);
     //mode.setBounds(-61,-2,338,479);
     stringButton.setBounds(249,10,122,122);
     drumButton.setBounds(249,169,122,122);
     boxButton.setBounds(249,326,122,122);
     //stringCUS.setBounds(-61,-2,338,479);
   
    
    
    /*
    //std::cout<<"toggle state "<<stringButton.getToggleState()<<"\n";
       for (int i=0;i < mode.getNumTabs(); i++)
       {
           mode.getTabbedButtonBar().getTabButton(i)->setBounds(200,
                                                                500/3*i,
                                                                30,
                                                                25);
       }
       //addAndMakeVisible(mode);
    //cusGUI.setBounds(-66,-36,370,500);
   // myString.setBounds(10, 300, 580, 200);
     */
}
