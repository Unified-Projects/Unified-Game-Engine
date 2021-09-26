#pragma once

//Includes
#include "./Source.h"

namespace UnifiedEngine {
    class AudioMixer{
    private:
        //AL Context
        ALCdevice *dev = NULL;
        ALCcontext *ctx = NULL;

        //Device
        const char *defname;
    private:
        //Setup
        void init_al() {
            //Device
            this->defname = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

            //Context Creation
            this->dev = alcOpenDevice(this->defname);
            this->ctx = alcCreateContext(this->dev, NULL);
            alcMakeContextCurrent(this->ctx);
        }

    public:
        //Setup
        AudioMixer(){
            this->init_al();
        }

        //Prints the device
        void CoutDevice(){
            std::cout << "Default device: " << this->defname << std::endl;
        }

        //Destroys OpenAL
        ~AudioMixer(){
            alcMakeContextCurrent(NULL);
            alcDestroyContext(this->ctx);
            alcCloseDevice(this->dev);
        }
    };
}