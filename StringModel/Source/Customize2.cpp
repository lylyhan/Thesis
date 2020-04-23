/*
  ==============================================================================

    Customize2.cpp
    Created: 10 Apr 2020 1:05:36pm
    Author:  Lily H

  ==============================================================================
*/

#include "Customize2.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <math.h>
//==============================================================================
Customize2::Customize2(StringModelAudioProcessor& p):
processor(p),myDrum(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(500,250);
    addAndMakeVisible(myDrum);
    addAndMakeVisible(&title);
       title.setText("This is a drum",dontSendNotification);
       
       static Typeface::Ptr myType2 = Typeface::createSystemTypefaceFor(BinaryData::Amagro_bold_ttf,
                                                                   BinaryData::Amagro_bold_ttfSize);
       Font* myFont2 = new Font(myType2);
       myFont2->setSizeAndStyle(30, 2, 1.0, 0.0);
       title.setFont(*myFont2);
       
       title.setColour(Label::ColourIds::textColourId , Colours::black);
    
    addAndMakeVisible(&sonic);
      sonic.setText("Sonic Attributes",dontSendNotification);
      addAndMakeVisible(&physics);
      physics.setText("Physical Appearance Attributes",dontSendNotification);
      addAndMakeVisible(&instruction);
          instruction.setText("Click anywhere on the drumface below!",dontSendNotification);
          
        
    
    

    //playButton.setShape(butoutline, true, true, false);

    static Typeface::Ptr myType = Typeface::createSystemTypefaceFor(BinaryData::Ubuntu_L_ttf,
                                                                    BinaryData::Ubuntu_L_ttfSize);
    Font* myFont = new Font(myType);
    //myFont->setSizeAndStyle(30, 2, 1.0, 0.0);
    
    
    tauSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    tauSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&tauSlider);
    addAndMakeVisible (&taulabel);
    taulabel.setText ("Sustain", dontSendNotification);//(fundamental time constant)
    taulabel.attachToComponent (&tauSlider, true);
    taulabel.setFont(*myFont);
    taulabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    
    
    omegaSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    omegaSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&omegaSlider);
    addAndMakeVisible (&omegalabel);
    omegalabel.setText ("Pitch", dontSendNotification);//(frequency dependent damping)
    omegalabel.attachToComponent (&omegaSlider, true);
    omegalabel.setFont(*myFont);
    omegalabel.setColour(Label::ColourIds::textColourId , Colours::black);
  


    pSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    //pSlider.onValueChange = [this] {sanitycheck(1);};
    addAndMakeVisible(&pSlider);
    addAndMakeVisible (&plabel);
    plabel.setText ("Roundness", dontSendNotification);//(frequency dependent damping)
    plabel.attachToComponent (&pSlider, true);
    plabel.setFont(*myFont);
    plabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    lSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    lSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    lSlider.setRange(0.0f,500.0f);
    lSlider.setValue(300.0f);
    //lSlider.onValueChange = [this] {sanitycheck(0);};
   // addAndMakeVisible(&lSlider);
    //addAndMakeVisible (&llabel);
    llabel.setText ("Length", dontSendNotification);//(frequency dependent damping)
    llabel.attachToComponent (&lSlider, true);
    llabel.setFont(*myFont);
    llabel.setColour(Label::ColourIds::textColourId , Colours::black);
   

  
    dispersionSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    dispersionSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&dispersionSlider);
    addAndMakeVisible (&dispersionlabel);
    dispersionlabel.setText ("Dispersion", dontSendNotification);//(inharmonicity)
    dispersionlabel.attachToComponent (&dispersionSlider, true);
    dispersionlabel.setFont(*myFont);
    dispersionlabel.setColour(Label::ColourIds::textColourId , Colours::black);
   

    alphaSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    alphaSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    alphalabel.setText ("Side length Ratio", dontSendNotification);//(shape of drum)
    alphalabel.attachToComponent (&alphaSlider, true);
    alphalabel.setFont(*myFont);
    alphalabel.setColour(Label::ColourIds::textColourId , Colours::black);
    

    
    addAndMakeVisible(&alphaSlider);
    addAndMakeVisible (&alphalabel);

  
    
    tauTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"tau",tauSlider);//this class maintains a connection between slider and parameter in apvts
    omegaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"omega",omegaSlider);
    pTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"p",pSlider);
    dispersionTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"dispersion",dispersionSlider);
    alphaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha1",alphaSlider);
    lengthTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"length",lSlider);

}

Customize2::~Customize2()
{
}

void Customize2::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */

  
    myDrum.changeParameter(lSlider.getValue(),
                           alphaSlider.getValue());
    myDrum.repaint();
    processor.dim = 1;
    
}


void Customize2::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //Rectangle<int> area=getLocalBounds();
    int top = 80;
    tauSlider.setBounds(79,top,150,20);
    omegaSlider.setBounds(79,top+20,150,20);
    pSlider.setBounds(79,top+40,150,20);
    dispersionSlider.setBounds(79,top+60,150,20);
   
    //lSlider.setBounds(358,top,150,20);
    alphaSlider.setBounds(358,top+20,150,20);
    
    sonic.setBounds(79,42,170,40);
    physics.setBounds(361,42,226,42);
    instruction.setBounds(178,163,253,34);
    title.setBounds(178,16,242,32);
    
    myDrum.setBounds(10,206,573,200);
    
   
        
}



void Customize2::playButtonClicked(int midiNote,bool isDown)
{
    if(isDown){
        processor.mySynth.noteOn(1,midiNote,120);
        if (processor.getMidiOutput() != nullptr)
                   processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOn(1, midiNote, 1.f));
        
    }
    else{
        //processor.mySynth.noteOff(1, midiNote, 0, true);
        if (processor.getMidiOutput() != nullptr)
            processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOff(1, midiNote, 0.f));
    }
}



