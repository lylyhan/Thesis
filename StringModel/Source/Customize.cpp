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
    setSize(400,140);
    
    tauSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    tauSlider.setRange(0.1f,5000.0f);
    tauSlider.setValue(0.1f);
    tauSlider.setTextValueSuffix (" s");
    addAndMakeVisible(&tauSlider);
    addAndMakeVisible (&taulabel);
    taulabel.setText ("Tau", dontSendNotification);//(fundamental time constant)
    taulabel.attachToComponent (&tauSlider, true);
    
 
    
    pSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pSlider.setRange(0.1f,5000.0f);
    pSlider.setValue(0.1f);
    addAndMakeVisible(&pSlider);
    addAndMakeVisible (&plabel);
    plabel.setText ("p", dontSendNotification);//(frequency dependent damping)
    plabel.attachToComponent (&pSlider, true);
    
    lSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    lSlider.setRange(0.0f,500.0f);
    lSlider.setValue(300.0f);
    addAndMakeVisible(&lSlider);
    addAndMakeVisible (&llabel);
    llabel.setText ("l", dontSendNotification);//(frequency dependent damping)
    llabel.attachToComponent (&lSlider, true);
    
    rhoSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    rhoSlider.setRange(0.1f,10.0f);
    rhoSlider.setValue(0.5f);
    addAndMakeVisible(&rhoSlider);
    addAndMakeVisible (&rholabel);
    rholabel.setText ("rho", dontSendNotification);//(frequency dependent damping)
    rholabel.attachToComponent (&rhoSlider, true);
    
    ASlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    ASlider.setRange(10.0f,100.0f);
    ASlider.setValue(10.0f);
    addAndMakeVisible(&ASlider);
    addAndMakeVisible (&Alabel);
    Alabel.setText ("A", dontSendNotification);//(frequency dependent damping)
    Alabel.attachToComponent (&ASlider, true);
    
    TSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    TSlider.setRange(0.0f,580.0f);
    TSlider.setValue(300.0f);
    addAndMakeVisible(&ASlider);
    addAndMakeVisible (&Alabel);
    Tlabel.setText ("T", dontSendNotification);//(frequency dependent damping)
    Tlabel.attachToComponent (&TSlider, true);
    
    dispersionSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    dispersionSlider.setRange(0.1f,5000.0f);
    dispersionSlider.setValue(0.1f);
    addAndMakeVisible(&dispersionSlider);
    addAndMakeVisible (&dispersionlabel);
    dispersionlabel.setText ("dispersion", dontSendNotification);//(inharmonicity)
    dispersionlabel.attachToComponent (&dispersionSlider, true);
    
    
    alphaSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    alphaSlider.setRange(0.1f,5000.0f);
    alphaSlider.setValue(0.1f);
    addAndMakeVisible(&alphaSlider);
    addAndMakeVisible (&alphalabel);
    alphalabel.setText ("alpha1", dontSendNotification);//(shape of drum)
    alphalabel.attachToComponent (&alphaSlider, true);
    
    alpha2Slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    alpha2Slider.setRange(0.1f,5000.0f);
    alpha2Slider.setValue(0.1f);
    addAndMakeVisible(&alpha2Slider);
    addAndMakeVisible (&alpha2label);
    alpha2label.setText ("alpha2", dontSendNotification);//(shape of drum)
    alpha2label.attachToComponent (&alpha2Slider, true);
    
    dimMenu.addItem("1-D", 1);
    dimMenu.addItem("2-D", 2);
    dimMenu.addItem("3-D", 3);
    dimMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&dimMenu);
    addAndMakeVisible(&dimlabel);
    dimlabel.setText ("dimension", dontSendNotification);//(shape of drum)
    dimlabel.attachToComponent (&dimMenu, true);
    
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
    
    g.fillAll (Colours::darkslateblue);
}

void Customize::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //Rectangle<int> area=getLocalBounds();
    
    tauSlider.setBounds(100,0,300,20);
    //omegaSlider.setBounds(100,20,300,20);
    
    pSlider.setBounds(100,20,300,20);
    dispersionSlider.setBounds(100,40,300,20);
    alphaSlider.setBounds(100,60,300,20);
    alpha2Slider.setBounds(100,80,300,20);
    dimMenu.setBounds(100,100,300,20);
    lSlider.setBounds(100,120,300,20);
    rhoSlider.setBounds(100,140,300,20);
    ASlider.setBounds(100,160,300,20);
    TSlider.setBounds(100,180,300,20);
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
    return 0;
}

