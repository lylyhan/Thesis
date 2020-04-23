/*
  ==============================================================================

    Drumface.cpp
    Created: 10 Apr 2020 12:28:06pm
    Author:  Lily H

  ==============================================================================
*/

#include "Drumface.h"
#include <math.h>
Drumface::Drumface(StringModelAudioProcessor& p): processor(p),helpButton("help")
{
    l1 = 200;
    l2 = 200;
    
    Image helpImg = ImageCache::getFromMemory(BinaryData::question2_png, BinaryData::question2_pngSize);
         
    helpButton.setImage(helpImg);
   
     
    helpButton.setTooltip("Information:\n This is a drum model illustration. You may adjust its shape via the side length ratio sliders on the right and alter the sound parameters on the left.\n To excite the drum you may click on any part on the drum illustration. Try hitting on different positions to hear the change.\n Friendly Reminder: turner down your volume, as some sounds may come out unexpectedly loud.");
    addAndMakeVisible(helpButton);

    //setSize(l,diameter);
    setSize(580,200);
  
    
}
Drumface::~Drumface(){};
void Drumface::paint(Graphics& g)
{
    //g.fillAll(Colours::burlywood);
    
    float midX = getLocalBounds().getCentreX();
    float midY = getLocalBounds().getCentreY();
    
 
    Drum = Rectangle<float> (juce::Point<float>(midX-l1/2,midY-l2/2),
                                juce::Point<float> (midX+l1/2,midY+l2/2));
    
    Image drumImg = ImageCache::getFromMemory(BinaryData::drumface_png, BinaryData::drumface_pngSize);
            
    //g.setColour(Colour(104,69,24));
    //g.setTiledImageFill(drumImg, JUCE_LIVE_CONSTANT(0),JUCE_LIVE_CONSTANT(0),1);
    g.drawImage(drumImg, Drum);
    //g.fillRect(Drum);
    //g.setOpacity(0.4);
    
    g.setColour(Colour(0,0,0));
    g.drawRect(Drum,2.0f);

    helpButton.setBounds(0,156,40,40);
    
    
}
void Drumface::resized()
{
    float midX = getLocalBounds().getCentreX();
    float midY = getLocalBounds().getCentreY();
       
    Drum = Rectangle<float> (juce::Point<float>(midX-l1/2,midY-l2/2),
                             juce::Point<float> (midX+l1/2,midY+l2/2));
    
}

void Drumface::changeParameter(float length,float alpha)
{
   
    //l1 = length/M_PI*580/3;
    
    l2 = l1 * alpha;
    //std::cout<<"alpha "<<alpha<<"\n";
}

void Drumface::mouseDown (const MouseEvent& e)
{
    if (! e.mods.isPopupMenu() || ! Drum.contains (e.x, e.y))
        if(e.x-Drum.getX()>0 and e.x-Drum.getX()<Drum.getWidth())
        {
            if(e.y-Drum.getY()>0 and e.y-Drum.getY()<Drum.getHeight())
            {
                //in the drum
                float x1 = (e.x-Drum.getX())/Drum.getWidth();
                float x2 = (e.y-Drum.getY())/Drum.getHeight();
                //let the synth know about this position
                if(auto myVoice = dynamic_cast<SynthVoice*>(processor.mySynth.getVoice(0)))
                {
                    myVoice->setPosition(x1,x2);
                    
                   // std::cout<<"did you set"<<x1<<" "<<x2<<"\n";
                }
                //activate synth
                clicked(87);
                //std::cout<<"did you click "<<e.y-Drum.getY()<<" "<<Drum.getHeight()<<" "<<x1<<" "<<x2<<"\n";
            }
        }
      
    
}
void Drumface::clicked(int midiNote)
{
    processor.mySynth.noteOn(1,midiNote,120);
        if (processor.getMidiOutput() != nullptr)
            processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOn(1, midiNote, 1.f));
               
    
        else{
               //processor.mySynth.noteOff(1, midiNote, 0, true);
               if (processor.getMidiOutput() != nullptr)
                   processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOff(1, midiNote, 0.f));
           }
}
