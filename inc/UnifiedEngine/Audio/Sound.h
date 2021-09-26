#pragma once
//Includes
#include <AL/al.h>
#include <AL/alc.h>

#include <string>

namespace UnifiedEngine {
    class Sound{
    private:
        //Buffers
        ALuint buf;

        //Timing
        float Length;
    public:
        //Initiate with a constant frequency
        Sound(float freq = 440.0f, float seconds = 1.0f, unsigned sample_rate = 22050){
            //Check Time
            if(seconds <= 0.0f)
                seconds = 1.0f;
            
            //Remember
            this->Length = seconds;
            
            //Buffer
            alGenBuffers(1, &this->buf);

            //Sizing
            size_t buf_size = seconds * sample_rate;
            short *samples;
            samples = new short[buf_size];

            //Generate Samples
            for(int i=0; i<buf_size; ++i) {
                samples[i] = 32760 * sin( (2.f*float(3.14159f)*freq)/sample_rate * i );
            }

            //Pass Data
            alBufferData(buf, AL_FORMAT_MONO16, samples, buf_size, sample_rate);
        }

        //Read Wav Files To Play
        Sound(string wavFile){
            
        }

        
        void Freq(float freq = 440.0f, float seconds = 1.0f, unsigned sample_rate = 22050){
            //Delete old data
            alDeleteBuffers(1, &buf);

            //Check Time
            if(seconds <= 0.0f)
                seconds = 1.0f;
            
            //Remember
            this->Length = seconds;
            
            //Buffer
            alGenBuffers(1, &this->buf);

            //Sizing
            size_t buf_size = seconds * sample_rate;
            short *samples;
            samples = new short[buf_size];

            //Generate Samples
            for(int i=0; i<buf_size; ++i) {
                samples[i] = 32760 * sin( (2.f*float(3.14159f)*freq)/sample_rate * i );
            }

            //Pass Data
            alBufferData(buf, AL_FORMAT_MONO16, samples, buf_size, sample_rate);
        }

        //Get Buffer
        ALuint GetBuffer(){
            return this->buf;
        }

        //Returns Lenght
        float GetLength(){
            return this->Length;
        }
        
        //Delete Buffer
        ~Sound(){
            alDeleteBuffers(1, &this->buf);
        }
    };
}