#pragma once

#include <stdint.h>

#define __GIO_WINDOW_OBJECT_ID__ 0x1

namespace UnifiedEngine
{
    class GameInteractionObject{
    protected:
        //Toggle
        bool loaded = false;

        //ID
        uint64_t ID = 0;
    protected:
        virtual int Load(){return -1;}
        virtual int Unload(){return -1;}

        inline GameInteractionObject(uint64_t id){
            //Save id
            this->ID = id;
        }
    };
} // namespace UnifiedEngine