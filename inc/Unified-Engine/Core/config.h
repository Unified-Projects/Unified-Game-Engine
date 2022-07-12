#pragma once

namespace UnifiedEngine
{
    struct GlobalConfig{
        //OpenGL
        unsigned char VersionMajor = 3;
        unsigned char VersionMinor = 3;
    };

    //Modifiable Config (Refain from modifying after init)
    extern GlobalConfig __GLOBAL_CONFIG__;
} // namespace UnifiedEngine
