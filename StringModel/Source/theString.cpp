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
    Tr = 169;
    Tg = 131;
    Tb = 131;
}
theString::~theString(){};
void theString::paint(Graphics& g)
{
    g.fillAll(Colours::burlywood);
    g.setColour (Colour(Tr,Tg,Tb));
    float midX = getLocalBounds().getCentreX();
    float midY = getLocalBounds().getCentreY();

    Rectangle<float> myString2(Point<float>(midX-l/2,midY-diameter/2),
                                 Point<float> (midX+l/2,midY+diameter/2));
    
    //g.fillRect(myString2);
    g.fillCheckerBoard(myString2,Rho,Rho,Colours::black,Colour(Tr,Tg,Tb));

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
    
    if(T <= 38)
    {
        Tr = 131;Tb = 169;
        Tg = 169 - T;
    }
    else if (T > 38 and T <= 76)
    {
        Tg = 131;Tb = 169;
        Tr = 131 + (T - 38);
    }
    else if(T > 76 and T <= 114)
    {
        Tr = 169;Tg = 131;
        Tb = 169 - (T - 76);
    }
    Rho = 7+rho;
    
    
}

