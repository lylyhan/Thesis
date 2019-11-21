/*
 ==============================================================================
 
 SynthesiserVoice.h
 Created: 10 Oct 2018 3:46:36pm
 Author:  Lily H
 
 ==============================================================================
 */

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "./SynthSound.h"
//#include "maximilian.h"
#include <math.h>       /* pow */
#include <algorithm>
#include<array>
#include <complex>
using namespace std;

#define MAX_M1  5
#define MAX_M2  5

class SynthVoice: public SynthesiserVoice
{
public:
    bool canPlaySound(SynthesiserSound* sound )
    {
        //if succesfully cast sound into my own class, return true
        return dynamic_cast<SynthSound*>(sound)!=nullptr;
    };
    
    //==================================
    //some function that grabs value from the slider, and then either returns or set the signal of my synethesized drum sound
    void getcusParam(float* tau,float* omega,float* p,float* dispersion,float* alpha1,float* alpha2,float* dimtype)
    {
        //this function fetch parameters from the customized GUI and calculate the corresponding parameters in order to synthesize the sound
        //for each dimension, different algorithms are called
        
        ftau=float(*tau);
        fomega=float(frequency/2/M_PI+1000);
        fp=float(*p);
        fd=float(*dispersion);
        fa=float(*alpha1);
        fa2=float(*alpha2);
        dim=float(*dimtype);
        //2-D drum
        if(dim==1){
            //set the three vectors - sigma, omega, K to use later
            deff(1);
            deff(2);
            getf(1);
            getf(2);
            
            getsigma();
            getw();
            getK();
            findmax();
        }
        //1-D string
        if(dim==0){
            //need sigma, omega
            /*
            deff(1);
            getf(1);
            
            getsigma1d();
            getw1d();
            getK1d();
            findmax1d();
            */
            ///////////////////the difference eq implementation///////////////
            getsigma1d();
            getw1d();

            
        }
        //3-D drum
        if(dim==2){
            deff(1);
            deff(2);
            deff(3);
            getf(1);
            getf(2);
            getf(3);
            getsigma3d();
            getw3d();
            getK3d();
            findmax3d();
        }
    }
    
    //findmax functions find value of first sample and scale everything else based on this value
    void findmax()
    {
        float h=0;
        float t1=M_PI/2/omega[0];
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                h+=k[i*m1+j]*exp(sigma[i*m1+j]*t1)*sin(omega[i*m1+j]*t1);
            }
            
        }
        maxh=h;
    }
    void findmax1d()
    {
        float h=0;
        float t1=M_PI/2/omega1d[0];
        for(int i=0;i<m1;i++)
        {
            
            h+=k1d[i]*exp(sigma1d[i]*t1)*sin(omega1d[i]*t1);
            
        }
        maxh=h;
    }
    void findmax3d()
    {
        float h=0;
        float t1=M_PI/2/omega3d[0];
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                for(int m=0;m<m3;m++)
                {
                    h+=k3d[i*m1+j*m2+m]*exp(sigma3d[i*m1+j*m2+m]*t1)*sin(omega3d[i*m1+j*m2+m]*t1);
                }
            }
        }
        maxh=h;
    }
    
  
   
    
    //intermediate variables
    //sigma
    void getsigma()
    {
        float sigma1=-1/ftau;
        float beta=fa+1/fa;
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                sigma[i*m1+j]=sigma1*(1+fp*(pow(i+1,2)*fa+pow(j+1,2)/fa-beta));
                decayamp[i*m1+j]=exp(sigma[i*m1+j]/sr);
            }
        }
    }
    
    void getsigma1d()
    {
        float sigma1=-1/ftau;
        for(int i=0;i<m1;i++)
        {
            sigma1d[i]=sigma1*(1+fp*(pow(i+1,2)-1));
            expsigma1d[i]=exp(sigma1d[i]/sr);
            decayamp1[i]=exp(sigma1d[i]/sr);
        }
    }
    
    void getsigma3d()
    {
        float sigma1=-1/ftau;
        float beta=fa*fa2+fa/fa2+fa2/fa;
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                for(int m=0;m<m3;m++)
                {
                    sigma3d[i*m1+j*m2+m]=(sigma1*(1+fp*(pow(i+1,2)*fa*fa2+pow(j+1,2)*fa2/fa+pow(m+1,2)*fa/fa2-beta)));
                    decayamp3[i*m1+j*m2+m]=exp(sigma3d[i*m1+j*m2+m]/sr);
                }
            }
        }
    }
    
    //get coefficients of the integral f1m1 using trapezoid rule
    void getf(int which)
    {
        //integrate f(x)sin(mpix/l)dx from 0 to l using trapezoid rule
        float l;
        int m;
        float integral;
        float l1=M_PI;
        float l2=fa*M_PI;
        float l3=fa2*M_PI;
        if(which==1) {l=l1;m=m1;}
        else if(which==2) {l=l2;m=m2;}
        else{l=l3;m=m3;}
        float h=l/tau;
        if(which==1)
        {
            for(int j=0;j<m;j++)
            {
                integral=0;
                for(int i=0;i<tau;i++)
                {
                    integral+=(fx1[i+1]*sin((i+1)*h*M_PI*(j+1)/l)+fx1[i]*sin(i*h*M_PI*(j+1)/l))*h/2.0;//(f(b)+f(a))*(b-a)/2
                }
                f1[j]=2*integral/l;
            }
            
        }
        else if(which==2)
        {
            for(int j=0;j<m;j++)
            {
                integral=0;
                for(int i=0;i<tau;i++)
                {
                    integral+=(fx2[i+1]*sin((i+1)*h*M_PI*(j+1)/l)+fx2[i]*sin(i*h*M_PI*(j+1)/l))*h/2.0;//(f(b)+f(a))*(b-a)/2
                }
                f2[j]=2*integral/l;
            }
        }
        else
        {
            for(int j=0;j<m;j++)
            {
                integral=0;
                for(int i=0;i<tau;i++)
                {
                    integral+=(fx3[i+1]*sin((i+1)*h*M_PI*(j+1)/l)+fx2[i]*sin(i*h*M_PI*(j+1)/l))*h/2.0;//(f(b)+f(a))*(b-a)/2
                }
                f3[j]=2*integral/l;
            }
        }
    }
    
    //define f(x) as a gaussian distribution with mean at the middle point l/2
    void deff(int which)
    {
        float s=0.4;//standard deviation
        if(which==1)
        {
            float h=M_PI/tau;
            for(int i=0;i<tau+1;i++)
            {
                fx1[i]=( 1 / ( s * sqrt(2*M_PI) ) ) * exp( -0.5 * pow( (i*h-M_PI/2.0)/s, 2.0 ) );
            }
        }
        else if(which==2)
        {
            float h=fa*M_PI/tau;
            for(int i=0;i<tau+1;i++)
            {
                fx2[i]=( 1 / ( s * sqrt(2*M_PI) ) ) * exp( -0.5 * pow( (i*h-fa*M_PI/2.0)/s, 2.0 ) );
            }
        }
        else
        {
            float h=fa*M_PI/tau;
            for(int i=0;i<tau+1;i++)
            {
                fx3[i]=( 1 / ( s * sqrt(2*M_PI) ) ) * exp( -0.5 * pow( (i*h-fa*M_PI/2.0)/s, 2.0 ) );
            }
        }
    }
    
    //get coefficient k for the impulse response
    void getK()
    {
        float l1=M_PI;
        float l2=fa*M_PI;
        float x1=l1/2;
        float x2=l2/2;
        
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                k[i*m1+j]=f1[i]*f2[j]*sin((i+1)*x1*M_PI/l1)*sin((j+1)*x2*M_PI/l2)/omega[i*m1+j];
            }
        }
        
    }
    void getK1d()
    {
        float l1=M_PI;
        float x1=l1/2;
        
        
        for(int i=0;i<m1;i++)
        {
            
            k1d[i]=f1[i]*sin((i+1)*x1*M_PI/l1)/omega1d[i];
            
        }
        
    }
    void getK3d()
    {
        float l1=M_PI;
        float l2=fa*M_PI;
        float l3=fa2*M_PI;
        float x1=l1/2;
        float x2=l2/2;
        float x3=l3/2;
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                for(int m=0;m<m3;m++)
                {
                    k3d[i*m1+j*m2+m]=f1[i]*f2[j]*f3[m]*sin((i+1)*x1*M_PI/l1)*sin((j+1)*x2*M_PI/l2)*sin((m+1)*x3*M_PI/l3)/omega3d[i*m1+j*m2+m];
                }
            }
        }
        
    }
    
    //get coefficient omega for the impulse response
    void getw()
    {
        float beta=fa+1/fa;
        float sigma=-1/ftau;
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                float interm=pow(i+1,2)*fa+pow(j+1,2)/fa;
                
                omega[i*m1+j]= sqrt(pow(fd*fomega*interm,2)+interm*(pow(sigma*(1-fp*beta),2)/beta+pow(fomega,2)*(1-pow(fd*beta,2))/beta)-pow(sigma*(1-fp*beta),2));
                
            }
        }
    }
    void getw1d()
    {
        float sigma=-1/ftau;
        for(int i=0;i<m1;i++)
        {
            
            float interm=pow(i+1,2);//M^2
            omega1d[i]= sqrt(pow(fd*fomega*interm,2)+interm*(pow(sigma*(1-fp),2)+pow(fomega,2)*(1-pow(fd,2)))-pow(sigma*(1-fp),2));
            cosomega1d[i] = cos(omega1d[i]/sr);
            
            
        }
    }
    void getw3d()
    {
        float beta=fa*fa2+fa/fa2+fa2/fa;
        float sigma=-1/ftau;
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                for(int m=0;m<m3;m++)
                {
                    float interm=pow(i+1,2)*fa*fa2+pow(j+1,2)*fa2/fa+pow(m+1,2)*fa/fa2;
                    
                    omega3d[i*m1+j*m2+m]= sqrt(pow(fd*fomega*interm,2)+interm*(pow(sigma*(1-fp*beta),2)/beta+pow(fomega,2)*(1-pow(fd*beta,2))/beta)-pow(sigma*(1-fp*beta),2));
                }
                
            }
        }
    }
    
    //==================================
    //==================================
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int
                    currentPitchWheelPosition)
    {
        //the keyboard-voice activation interface, should write different excitation signals here.
        trig = 1;
        t=0;
        nsamp=0;
        level=velocity;
        //map keyboard to frequency
        frequency= MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        //xbuffer[0]=1.0;
        xbuf0 = 1.0;
        //std::cout<<"i hit "<<xbuffer[0]<<"\n";
        
    };
    
    //==================================
    void stopNote (float velocity, bool allowTailOff)
    {
        allowTailOff=true;
        
        if(velocity ==0)//allow next note to come in
            t=0;
        clearCurrentNote();
        
    };
    //==================================
    bool isVoiceActive()
    {
        
    };
    
    //this function synthesize signalvalue at each sample
    double finaloutput(int sample)
    {
        float h=0;
        //2-D
        if(dim==1)
        {
            //sum up to mode m1 and mode m2
            for(int i=0;i<m1;i++)
            {
                for(int j=0;j<m2;j++)
                {
                    //designate the exponential envelope
                    if(nsamp==0){
                        decayampn[i*m1+j]=decayamp[i*m1+j];
                    }
                    else{
                        decayampn[i*m1+j]*=decayamp[i*m1+j];
                    }
                    //synthesize the sound at time t
                    h+=k[i*m1+j]*decayampn[i*m1+j]*sin(omega[i*m1+j]*t);
                }
            }
            //std::cout<<"output 2d "<<h/maxh<<"\n";
        }
        //1-D
        else if(dim==0)
        {
            //maxh = 1.0;
            //std::complex<float> imaginary(0,1);
            /*
             for(int i=0;i<m1;i++)
             {
             if(nsamp==0){
             decayampn1[i]=decayamp1[i];
             }
             else{
             decayampn1[i]*=decayamp1[i];
             }
             
             h+=k1d[i]*decayampn1[i]*sin(omega1d[i]*t);
             }
             */
            //this is the difference eq version of implementation
            for(int i=0;i<m1;i++)
            {
                ybuffer[i] = 2*expsigma1d[i]*cosomega1d[i]*ybuffer1[i]-expsigma1d[i]*ybuffer2[i]-xbuf0/omega1d[i]+expsigma1d[i]*xbuf1*cosomega1d[i]/omega1d[i];
                h+=ybuffer[i];
                
            }
            if(xbuf0 !=0) {maxh = h;}
            //if(xbuf0 != 0) {std::cout<<"h "<<h<<" "<<xbuf0<<"\n";}
            //update buffers
            ybuffer2 = ybuffer1;
            ybuffer1 = ybuffer;
            xbuf1 = xbuf0;
            xbuf0 = 0.0;
            //std::cout<<"h "<<h<<" "<<xbuffer[2]<<" "<<xbuffer[0]<<"  "<<ybuffer[2]<<" "<<ybuffer[1]<<" "<<ybuffer[0]<<"\n";
            //std::cout<<"ybuffer1"<<" "<<ybuffer1[0]<<" "<<ybuffer1[1]<<" "<<ybuffer[2]<<"\n";
            //std::cout<<"omega "<<omega1d[0]<<" "<<omega1d[1]<<" "<<omega1d[2]<<" "<<omega[3]<<"\n";
            //std::cout<<"output 1d "<<h/maxh<<" "<<maxh<<"\n";
        }
        //3-D
        else
        {
            for(int i=0;i<m1;i++)
            {
                for(int j=0;j<m2;j++)
                {
                    for(int m=0;m<m3;m++)
                    {
                        if(nsamp==0){
                            decayampn3[i*m1+j*m2+m]=decayamp3[i*m1+j*m2+m];
                        }
                        else{
                            decayampn3[i*m1+j*m2+m]*=decayamp3[i*m1+j*m2+m];
                        }
                        h+=k3d[i*m1+j*m2+m]*decayampn3[i*m2+j*m2+m]*sin(omega3d[i*m1+j*m2+m]*t);
                    }
                }
                
            }
        }
        //scale the output
        output=h/maxh;
        //output = h/1.0;
        if(trig!=0)//if note is pressed, start counting time samples
        {
            t+=1/sr;//t advancing one sample
            nsamp+=1;
        }
       // std::cout<<"output "<<h<<" "<<output<<"\n";
        return double(output);
      
    }
    //==================================
    void pitchWheelMoved (int newPitchWheelValue)
    {
        
    };
    //==================================
    void controllerMoved (int controllerNumber, int newControllerValue)
    {
        
    };
    //==================================
    void aftertouchChanged (int newAftertouchValue)
    {
        
    };
    //==================================
    void channelPressureChanged (int newChannelPressureValue)
    {
        
    };
    //==================================
    void renderNextBlock (AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
    {
        //callback function

        for(int sample=0;sample<numSamples;++sample)
        {
            
            //put the synthesized drum sound here
            double drumSound=finaloutput(sample);
            //if(drumSound!=0){std::cout<<"drumSound "<<drumSound<<"\n";}
            for(int channel=0;channel<outputBuffer.getNumChannels();++channel)
            {
                outputBuffer.addSample(channel,  startSample, drumSound );//put whatever sound synthesized here.
            }
            ++startSample;
        }
        
        
        
    };
    //==================================
    void renderNextBlock (AudioBuffer< double > &outputBuffer, int startSample, int numSamples)
    {
        
        
    };
    //==================================
    void setCurrentPlaybackSampleRate (double newRate)
    {
        
    };
    //==================================
    bool isPlayingChannel (int midiChannel)
    {
        
    };
    //==================================
    double getSampleRate()
    {
        
    };
    //==================================
    bool isKeyDown()
    {
        
    };
    //==================================
    void setKeyDown(bool isNowDown)
    {
        
    };
    //==================================
    bool isPlayingButReleased()
    {
        
    };
    //==================================
    bool wasStartedBefore(const SynthesiserVoice& other)
    {
        
    };
    //==================================
    //==================================
    //==================================
    //==================================
    
    
private:
    double level;
    double frequency;
    int trig;
    double output;
    double t;
    int nsamp;
    double sr=44100;
    double sinlookup[62832];
    float ftau;
    float fa;
    float fa2;
    float fp;
    float fomega;
    float fd;
    float dim;
    int tau=300;
    int m1=5;   //can't be bigger than MAX_M1
    int m2=5;
    int m3=5;
    float k[MAX_M1*MAX_M2];//m1*m2
    float omega[25];
    float sigma[25];
   
    float decayamp1[MAX_M1];
    float decayampn1[MAX_M1];
    float decayamp[25];
    float decayampn[25];
    float decayamp3[125];
    float decayampn3[125];
    float k3d[125];//m1*m2
    float k1d[MAX_M1];
    float omega3d[125];
    float omega1d[MAX_M1];
   
    float sigma3d[125];
    float sigma1d[MAX_M1];
    float expsigma1d[MAX_M1];
    float cosomega1d[MAX_M1];
    float f1[5];//m1
    float f2[5];//m2
    float f3[5];//m3
    float maxh;//the max of h for each set of parameters
    // float test[25];
    float fx1[301];//tau
    float fx2[301];
    float fx3[301];
    //double drumSound[512];
    double gain;
    
    
    
    //circular buffers! [t,t-1,t-2]
    //std::array<float,MAX_M1> A = {10,20,30,40};
    //std::array<int,4> B = A; //copy array A into array B
    
    std::array<float,MAX_M1> ybuffer;
    std::array<float,MAX_M1> ybuffer1;
    std::array<float,MAX_M1> ybuffer2;
    //float ybuffer1[MAX_M1];
    //float ybuffer2[MAX_M1];
    //float xbuffer[3] = {1.0, 0.0, 0.0};
    float xbuf0,xbuf1;
    //pointers for buffers!
    //int yread,ywrite;
    //int xread,xwrite;
    
    
    
};
