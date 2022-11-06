#pragma once
#include <Unified-Engine/Objects/objectComponent.h>

namespace UnifiedEngine
{   
    /**
     * @brief To Be inhertited from to allow to attach to a gameobject and be updated along with the game
     * 
     */
    class ScriptableObject : public ObjectComponent{
    protected:
        ScriptableObject(ObjectComponent* Parent) : ObjectComponent(Parent, OBJECT_SCRIPTABLE_OBJECT, true){}
    };
} // namespace UnifiedEngine
