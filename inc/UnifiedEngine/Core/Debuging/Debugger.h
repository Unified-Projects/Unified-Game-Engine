#pragma once

//Includes
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/PixelRender.h"
#include "../../UI/Text/Label.h"

#include <string>

namespace UnifiedEngine{
    
    //Object Constructor
    struct DebugObject{
        //Name
        string Header;
        
        //Content
        vector<string> Items;
        vector<Label> Labels;

        //Not Used
        int type = 0;
    };

    //Selector Constructor
    struct DebugSelectorObject : DebugObject{
        //Name
        string Header;
        
        //Content
        vector<string> Items;
        map<string, DebugObject> Objects;

        vector<Label> Labels;

        PixelImage Selector = PixelImage(ivec2(1, 1), vec3(1));

        //Selector
        string Selected;
        int SelectedIndex = -1;

        //Unused
        int type = 1;
    };

    //Console Constructor
    struct DebugConsole : DebugObject{
        //Name
        string Header;

        //Content
        vector<string> Items;
        vector<Label> Labels;

        //Unused
        int type = 2;
    };

    //Colum
    struct DebugColum{
        vector<DebugObject> Objects;
    };

    //Layout
    struct DebugLayout{
        DebugColum C1;
        DebugColum C2;
        DebugColum C3;
    };

    class Debugger{
    private:
        //Window
        Window window;
        Renderer* render;

        //Fonts
        Font font;

        //Layout
        DebugLayout Layout;

    public:

        //Creation
        Debugger(ivec2 Size, bool vsync, ivec2 OpenGL, int fps, GLFWwindow* share = NULL)
            : font("./rsc/Fonts/Debug/Debug.ttf", 8)
        {   
            //Window (Inherits Main Window)
            this->window.MakeSingleWindow("Debugger", Size.x, Size.y, vsync, false, share);

            //Renderer
            this->render = new Renderer(&this->window);
        }

        //Delete Pointers
        ~Debugger(){
            delete this->render;
        }

    private:
        void SelectorUpdate(){

        }

        void SelectorReder(){

        }

    private:
        void ObjectUpdate(){

        }

        void ObjectRender(){

        }

    public:
        void Update(){
            
        }
        
        void Render(){
            //Make Context
            this->window.MakeContext();

            //Clear
            render->Clear(true, true, true, vec4(0, 0, 0, 0));

            //Buffers
            if (this->window.UsingVsync) {
				glfwSwapBuffers(this->window.WindowObject);
			}
        }
    };
}