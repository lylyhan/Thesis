/*
  ==============================================================================

    theString.cpp
    Created: 23 Oct 2019 12:20:19pm
    Author:  Lily H

  ==============================================================================
*/

#include "theString.h"

theString::theString(StringModelAudioProcessor& p): processor(p)
{
    
    l = 580;
    diameter = 10;
    Rho = 1;
    //setSize(l,diameter);
    setSize(580,200);
}
theString::~theString(){};
void theString::paint(Graphics& g)
{
    g.fillAll(Colours::burlywood);
    g.setColour (Colours::darkkhaki);
    float midX = getLocalBounds().getCentreX();
    float midY = getLocalBounds().getCentreY();

    Rectangle<float> myString2(Point<float>(midX-l/2,midY-diameter/2),
                                 Point<float> (midX+l/2,midY+diameter/2));
    
    g.fillRect(myString2);

}
void theString::resized()
{
    
}

void theString::changeParameter(float tau, float p, float dispersion, float alpha, float alpha2,float length,float rho,float A, float T)
{
    // transform tau, p, dispersion, alpha, alpha2 to
    //l, diameter, rho
    //maybe airdrag parameters too, include background color here
    l = length;
    diameter = A;
    
}

