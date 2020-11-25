/*
  ==============================================================================

    theString.cpp
    Created: 23 Oct 2019 12:20:19pm
    Author:  Lily H

  ==============================================================================
*/

#include "theString.h"
#include <math.h>
theString::theString(StringModelAudioProcessor& p): processor(p),helpButton("help")
{
    
    Image helpImg = ImageCache::getFromMemory(BinaryData::question2_png, BinaryData::question2_pngSize);
         
    helpButton.setImage(helpImg);
   
     
    helpButton.setTooltip("Information:\n This is a string model illustration. You may adjust its length and thickness via the two sliders on the right. Meanwhile you can see qualities of the string (tension and stiffness) changes as you alter the sound parameters on the upper right.\n Tension of the string is color coded: blue as loose and red as tight.\n Stiffness of the string is represented by density of the checkerboard pattern on the string. The stiffer the string the denser the pattern.\n If you don't have a midi keyboard, activate the sound by clicking the button in the middle.");
    addAndMakeVisible(helpButton);
    l = 580;
    diameter = 10;
    S = 1;
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

    Rectangle<float> myString2(juce::Point<float>(midX-l/2,midY-diameter/2),
                                 juce::Point<float> (midX+l/2,midY+diameter/2));
    
    //g.fillRect(myString2);
    float gridSize;
    if(S > 18){gridSize = 2;}
    else{gridSize = 20-S;}
    g.fillCheckerBoard(myString2,gridSize,gridSize,Colours::black,Colour(Tr,Tg,Tb));
    helpButton.setBounds(0,156,40,40);
}
void theString::resized()
{
    
}

void theString::changeParameter(float tau, float p, float dispersion, float alpha, float alpha2,float omega, float length,float A)
{
    //obtain the true S and Ts by recover d1,d3,c,S first + denormalize
    float d1, d3, c,a;
    d1 = 2*(1-p)/tau;
    d3 = -2*p/tau;
    c = sqrt((1-p*p)/pow(tau,2)+pow(omega,2)*(1-dispersion*dispersion));
    S = pow(pow(dispersion*omega,2)+pow(p/tau,2),0.25);
    a = length/M_PI;
    //denormalize
    S = a * S / pow(A,1/4)/8;//this need to be below 10
    T = pow(a*c,2)*1e-6/227*114; //this need to be between 0 and 114
    
    //std::cout<<"T "<<T<<" "<<S<<" "<<dispersion<<" "<<tau<<" "<<p<<"\n";

    // transform tau, p, dispersion, alpha, alpha2 to
    //l, diameter, rho
    //maybe airdrag parameters too, include background color here
    l = length/M_PI*580/3;
    diameter = A*30;
    //Rho = (pow(pow(dispersion*omega,2)+pow(p/tau,2),0.25)+1)/87*8+2; //actually stiffness
    //scale between 2 and 10
 
    
    //T = (A*((1-p*p)/tau/tau+omega*omega*(1-dispersion*dispersion))*1e-7+1)/18*114;//scale between 0 and 114
    
    //processor.
    processor.tension = T;
    //processor.stiffness = Rho;
    //float uplim = sqrt((1-p*p)/pow(tau*omega,2)+1);
    //std::cout<<"T "<<T<<" "<<Rho<<" "<<dispersion<<" "<<uplim<<" "<<tau<<" "<<p<<"\n";
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
    //Rho = 7+rho;
    
    
}

