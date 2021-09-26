#pragma once

//Includes
#include "./Text/Label.h"
#include "./Images/Image.h"
#include "../Core/Window/Window.h"

#include <iostream>

namespace UnifiedEngine {
    //Canvas class for UI
    class Canvas{
    private:
        //Comparisons for Updating
        ivec2 OldSize;
        bool OldGened = false;
        ivec2 CurrentSize;

        //Sizing
        vec2 Scale = vec2(1);
    public:
        //Optional Auto Adjustment of Scales and positions
        bool ScaleWithWindowSize = false;

        //Items in UI
        vector<Label*> Labels;
        vector<Image*> Images;
        
        //Init Label to UI
        void NewLabel(Label* L){
            this->Labels.push_back(new Label(*L));
        }

        //Init Image to UI
        void NewImage(Image* I){
            this->Images.push_back(new Image(*I));
        }

        //Main Update For Scaling
        void Update(ivec2 Size){
            //If Auto Scale Toggled
            if (this->ScaleWithWindowSize){
                //Stop Errors with pre assigning
                if(!this->OldGened){
                    this->OldSize = Size;
                    this->OldGened = true;
                }

                //Load size
                this->CurrentSize = Size;

                //Get Difference
                this->Scale.x = static_cast<float>(CurrentSize.x)/static_cast<float>(OldSize.x);
                this->Scale.y = static_cast<float>(CurrentSize.y)/static_cast<float>(OldSize.y);

                //for (Label* l : this->Labels){
                    //l->Position *= this->Scale;
                    //l->Scale *= this->Scale;
                //}

                //for (Image* i : this->Images){
                    //i->Position *= this->Scale;
                    //i->scale *= this->Scale;
                //}

                //Remember this size
                this->OldSize = Size;

                //Apply scale if different
                if(this->Scale.x != 1 || this->Scale.y != 1){
                    for (Image* i : this->Images){
                        i->Update(this->Scale);
                    }

                    for (Label* l : this->Labels){
                        l->Update(this->Scale);
                    }
                }
                
            }
        }

        //Render All items
        void Render(){
            //Label
            for (Label* l : this->Labels){
                l->Render();
            }

            //Image
            for (Image* i : this->Images){
                i->Render();
            }
        }
    };
}