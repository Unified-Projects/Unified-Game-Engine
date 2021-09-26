#pragma once

//Includes
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "Sound.h"

namespace UnifiedEngine {
    class Source2D{
    private:
        //Source
        ALuint src;
    public:
        //Creation of source
        Source2D(){
            alGenSources(1, &this->src);
        }

        //Delete source
        ~Source2D(){
            alDeleteSources(1, &this->src);
        }

        //Play a sound
        void PlaySound(Sound sound){
            alSourcei(this->src, AL_BUFFER, sound.GetBuffer());
            alSourcePlay(this->src);
        }
    };
}