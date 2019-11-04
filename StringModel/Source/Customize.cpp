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
Customize::Customize(StringModelAudioProcessor& p):
processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(500,250);
    
    static Typeface::Ptr myType = Typeface::createSystemTypefaceFor(BinaryData::Ubuntu_L_ttf,
                                                                    BinaryData::Ubuntu_L_ttfSize);
    Font* myFont = new Font(myType);
    //myFont->setSizeAndStyle(30, 2, 1.0, 0.0);
    
    
    tauSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    tauSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&tauSlider);
    addAndMakeVisible (&taulabel);
    taulabel.setText ("Duration", dontSendNotification);//(fundamental time constant)
    taulabel.attachToComponent (&tauSlider, true);
    taulabel.setFont(*myFont);
    taulabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    pSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&pSlider);
    addAndMakeVisible (&plabel);
    plabel.setText ("Damping", dontSendNotification);//(frequency dependent damping)
    plabel.attachToComponent (&pSlider, true);
    plabel.setFont(*myFont);
    plabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    lSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    lSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    lSlider.setRange(0.0f,500.0f);
    lSlider.setValue(300.0f);
    addAndMakeVisible(&lSlider);
    addAndMakeVisible (&llabel);
    llabel.setText ("Length", dontSendNotification);//(frequency dependent damping)
    llabel.attachToComponent (&lSlider, true);
    llabel.setFont(*myFont);
    llabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    
    rhoSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    rhoSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    rhoSlider.setRange(0.1f,10.0f);
    rhoSlider.setValue(0.5f);
    addAndMakeVisible(&rhoSlider);
    addAndMakeVisible (&rholabel);
    rholabel.setText ("Density", dontSendNotification);//(frequency dependent damping)
    rholabel.attachToComponent (&rhoSlider, true);
    rholabel.setFont(*myFont);
    rholabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    ASlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    ASlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    ASlider.setRange(10.0f,100.0f);
    ASlider.setValue(10.0f);
    addAndMakeVisible(&ASlider);
    addAndMakeVisible (&Alabel);
    Alabel.setText ("Thickness", dontSendNotification);//(frequency dependent damping)
    Alabel.attachToComponent (&ASlider, true);
    Alabel.setFont(*myFont);
    Alabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    TSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    TSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    TSlider.setRange(0.0f,114.0f);
    TSlider.setValue(57.0f);
    addAndMakeVisible(&TSlider);
    addAndMakeVisible (&Tlabel);
    Tlabel.setText ("Tension", dontSendNotification);//(frequency dependent damping)
    Tlabel.attachToComponent (&TSlider, true);
    Tlabel.setFont(*myFont);
    Tlabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    dispersionSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    dispersionSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&dispersionSlider);
    addAndMakeVisible (&dispersionlabel);
    dispersionlabel.setText ("Dispersion", dontSendNotification);//(inharmonicity)
    dispersionlabel.attachToComponent (&dispersionSlider, true);
    dispersionlabel.setFont(*myFont);
    dispersionlabel.setColour(Label::ColourIds::textColourId , Colours::black);
   
    dimMenu.addItem("1-D", 1);
    dimMenu.addItem("2-D", 2);
    dimMenu.addItem("3-D", 3);
    dimMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&dimMenu);
    addAndMakeVisible(&dimlabel);
    dimlabel.setText ("Dimension", dontSendNotification);//(shape of drum)
    dimlabel.attachToComponent (&dimMenu, true);
    dimlabel.setFont(*myFont);
    dimlabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    
    alphaSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    alphaSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    alphalabel.setText ("Alpha1", dontSendNotification);//(shape of drum)
    alphalabel.attachToComponent (&alphaSlider, true);
    alphalabel.setFont(*myFont);
    alphalabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    alpha2Slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    alpha2Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    alpha2label.setText ("Alpha2", dontSendNotification);//(shape of drum)
    alpha2label.attachToComponent (&alpha2Slider, true);
    alpha2label.setFont(*myFont);
    alpha2label.setColour(Label::ColourIds::textColourId , Colours::black);

    
    //addAndMakeVisible(&alphaSlider);
    //addAndMakeVisible (&alphalabel);
    //addAndMakeVisible(&alpha2Slider);
    //addAndMakeVisible (&alpha2label);
  
    dimSelection = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree,"dimtype",dimMenu);
    tauTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"tau",tauSlider);//this class maintains a connection between slider and parameter in apvts
   // omegaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"omega",omegaSlider);
    pTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"p",pSlider);
    dispersionTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"dispersion",dispersionSlider);
    alphaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha",alphaSlider);
    alpha2Tree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha2",alpha2Slider);
    
    
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
    
    //g.fillAll (Colours::darkslateblue);
}
void Customize::changeGUI(int dim)
{
    if(dim == 1)
    {
        //std::cout<<"dimension? "<<dim<<"\n";
        addAndMakeVisible(&alphaSlider);
        addAndMakeVisible (&alphalabel);
        alpha2Slider.setVisible(false);
        alpha2label.setVisible(false);
    }
    else if (dim == 2)
    {
        addAndMakeVisible(&alpha2Slider);
        addAndMakeVisible (&alpha2label);
        alphaSlider.setVisible(false);
        alphalabel.setVisible(false);
    }
    else if (dim == 0)
    {
        alphaSlider.setVisible(false);
        alphalabel.setVisible(false);
        alpha2Slider.setVisible(false);
        alpha2label.setVisible(false);
    }
    
    
}

void Customize::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //Rectangle<int> area=getLocalBounds();
    
    tauSlider.setBounds(79,0,150,20);
    //omegaSlider.setBounds(100,20,300,20);
    
    pSlider.setBounds(79,20,150,20);
    dispersionSlider.setBounds(79,40,150,20);
    //alphaSlider.setBounds(100,60,300,20);
    //alpha2Slider.setBounds(100,80,300,20);
    dimMenu.setBounds(358,0,150,20);
    lSlider.setBounds(358,20,150,20);
    rhoSlider.setBounds(358,40,150,20);
    ASlider.setBounds(358,60,150,20);
    TSlider.setBounds(358,80,150,20);
    alphaSlider.setBounds(358,100,150,20);
    alpha2Slider.setBounds(358,100,150,20);

        
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
    else if(seq == 6)
    {
        return lSlider.getValue();
    }
    else if(seq == 7)
    {
        return rhoSlider.getValue();
    }
    else if(seq == 8)
    {
        return ASlider.getValue();
    }
    else if(seq == 9)
    {
        return TSlider.getValue();
    }
    else if(seq == 10)
    {
        return dimMenu.getSelectedItemIndex();
        
    }
    return 0;
    
}

