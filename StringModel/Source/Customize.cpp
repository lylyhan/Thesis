/*
  ==============================================================================

    Customize.cpp
    Created: 10 Oct 2019 10:02:42am
    Author:  Lily H

  ==============================================================================
*/

#include "Customize.h"

#include "../JuceLibraryCode/JuceHeader.h"
#include "Customize.h"

//==============================================================================
Customize::Customize(StringModelAudioProcessor& p,int mode):
processor(p),helpComp("help")
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

   
    
   Image helpImg = ImageCache::getFromMemory(BinaryData::question3_png, BinaryData::question3_pngSize);
         
     helpComp.setImage(helpImg);
    helpComp.setTooltip("Information\n This is a drum synth implemented with physical modeling. You may switch between the three available physical models - string, rectangular drum and cuboid box. Each of the knobs controls a combination of the underlying physical parameters, examined based on qualities of the sound produced.\n Sustain - short to long\n Roundness - harsh to round\n Inharmonicity - harmonic to inharmonic\n Drum squareness - elongated to square drum\n Box shape - flat to cubic box");
     addAndMakeVisible(&helpComp);
    

    
    
    
    
    Font myFont = Font(Typeface::createSystemTypefaceFor(BinaryData::AmaticSCRegular_ttf,
                                                  BinaryData::AmaticSCRegular_ttfSize));
    Font myFont2 = Font(Typeface::createSystemTypefaceFor(BinaryData::ColabThi_otf,
    BinaryData::ColabThi_otfSize));
    myFont2.setBold(true);
    Font myFont3 = Font(Typeface::createSystemTypefaceFor(BinaryData::ExistenceLight_otf,
       BinaryData::ExistenceLight_otfSize));
    
    
    
    tauSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    tauSlider.setRange(0.1f,5000.0f);
    tauSlider.setValue(0.1f);
    //tauSlider.setTextValueSuffix (" s");
    tauSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox,true,0,0);
    tauSlider.setColour(Slider::ColourIds::backgroundColourId,Colours::red);
    addAndMakeVisible(&tauSlider);
    addAndMakeVisible (&taulabel);
    taulabel.setText ("Sustain", dontSendNotification);//(fundamental time constant)
    // taulabel.setFont(myFont2);
    
    //taulabel.attachToComponent (&tauSlider, false);
    
 
    
    pSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pSlider.setRange(0.1f,5000.0f);
    pSlider.setValue(0.1f);
    pSlider.setColour(Slider::ColourIds::backgroundColourId,Colours::red);
    
    addAndMakeVisible(&pSlider);
    addAndMakeVisible (&plabel);
    pSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox,true,0,0);
    plabel.setText ("Roundness", dontSendNotification);//(frequency dependent damping)
    //plabel.setFont(myFont3);
    //plabel.attachToComponent (&pSlider, false);
    

    
    dispersionSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dispersionSlider.setRange(0.1f,5000.0f);
    dispersionSlider.setValue(0.1f);
    dispersionSlider.setColour(Slider::ColourIds::backgroundColourId,Colours::red);
    addAndMakeVisible(&dispersionSlider);
    addAndMakeVisible (&dispersionlabel);
    dispersionSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox,true,0,0);
    dispersionlabel.setText ("Inharmonicity", dontSendNotification);//(inharmonicity)
    //dispersionlabel.attachToComponent (&dispersionSlider, false);
    
    if(mode >= 2 ){
        alphaSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        alphaSlider.setRange(0.1f,5000.0f);
        alphaSlider.setValue(0.1f);
        alphaSlider.setColour(Slider::ColourIds::backgroundColourId,Colours::red);
        addAndMakeVisible(&alphaSlider);
        addAndMakeVisible (&alphalabel);
        alphaSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox,true,0,0);
        alphalabel.setText ("Drum Squareness", dontSendNotification);//(shape of drum)
        //std::cout<<"fonts "<<juce::Font::findAllTypefaceNames()[0]<<"\n";
        //alphalabel.setFont(myFont);
        //alphalabel.attachToComponent (&alphaSlider, false);
        alphaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha",alphaSlider);
        if(mode == 3){
            alpha2Slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
            alpha2Slider.setRange(0.1f,5000.0f);
            alpha2Slider.setValue(0.1f);
            alpha2Slider.setColour(Slider::ColourIds::backgroundColourId,Colours::red);
            addAndMakeVisible(&alpha2Slider);
            addAndMakeVisible (&alpha2label);
            alpha2Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox,true,0,0);
            alpha2label.setText ("Box Shape", dontSendNotification);//(shape of drum)
            //alpha2label.attachToComponent (&alpha2Slider, false);
            alpha2Tree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha2",alpha2Slider);
               
        }
    }
    tauTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"tau",tauSlider);//this class maintains a connection between slider and parameter in apvts
   // omegaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"omega",omegaSlider);
    pTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"p",pSlider);
    dispersionTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"dispersion",dispersionSlider);
    //alphaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha",alphaSlider);
    //alpha2Tree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha2",alpha2Slider);
    
    
}

Customize::~Customize()
{
}

void Customize::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
   // g.fillAll (Colours::white);
    cusSlider* cusRotarySliderlook = new cusSlider();
    if(auto* newl = dynamic_cast<juce::LookAndFeel*> (cusRotarySliderlook))
    {
        tauSlider.setLookAndFeel(newl);
        pSlider.setLookAndFeel(newl);
        dispersionSlider.setLookAndFeel(newl);
        alphaSlider.setLookAndFeel(newl);
        alpha2Slider.setLookAndFeel(newl);
    }
    
   
}

void Customize::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //Rectangle<int> area=getLocalBounds();
    
    tauSlider.setBounds(74,32,100,100);
    taulabel.setBounds(98,133,133,11);
    pSlider.setBounds(186,105,100,100);
    plabel.setBounds(197,207,133,11);
    dispersionSlider.setBounds(74,179,100,100);
    dispersionlabel.setBounds(79,281,133,11);
    alphaSlider.setBounds(186,249,100,100);
    alphalabel.setBounds(180,353,131,13);
    alpha2Slider.setBounds(74,323,100,100);
    alpha2label.setBounds(90,428,133,13);
    helpComp.setBounds(3,449,143,23);
    //dimMenu.setBounds(0,1500,100,100);

  
}
//seq: 1. tau, 2. p, 3. dispersino, 4. alpha, 5. alpha2, 6. l,
float Customize::getsliderval(int seq)
{
    if (seq == 1)
    {
        return tauSlider.getValue();
    }
    else if(seq == 2)
    {
        return pSlider.getValue();
    }
    else if(seq == 3)
    {
        return dispersionSlider.getValue();
    }
    else if(seq == 4)
    {
        return alphaSlider.getValue();
    }
    else if(seq == 5)
    {
        return alpha2Slider.getValue();
    }

    return 0;
}
