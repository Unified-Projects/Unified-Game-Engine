#pragma once

//Include
//Main
#include "../OpenGL/Initiate.h"
#include "../OpenGL/Configure.h"
#include "../Window/Window.h"
#include "../Debuging/Debugger.h"
#include "./Timing/Time.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Shader.h"
#include "../Renderer/RenderInfo.h"
#include "../../Scenes/Scene.h"
#include "../../UI/Canvas.h"
#include "../Input/InputInfo.h"
#include "../Renderer/PixelRender.h"

//Audio
#ifdef OPENAL_AUDIO
#include "../../Audio/Mixer.h"
#endif

//Debug
#include "../Window/Console.h"

namespace UnifiedEngine {

	//Main Input
	static InputClass* InputP;

	//Main Input Scrollback
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		InputP->Mouse.setScroll(xoffset, yoffset);
	}

	//Game
	class Game {
	private:
		//For FPS Limiting
		float LastTime;

		//If Rendering Through a pixel renderer
		Texture2D Screen;

		//Debug
		bool DebugMade = false;

	public:
		//Main Objects
		Window window;
		InputClass Input;
		Renderer* Rendering;
		Scene ActiveScene;

		//Debug
		Debugger* Debug;
		bool DebuggerMode = false;

		//Initialiser
		Game(const char* WindowTitle, int WindowWidth, int WindowHeight, bool Vsync, int FPS, int OpenGLMajor, int OpenGLMinor, bool Resizable)
			: Input(nullptr, nullptr)
		{
			//OpenGL
			GLMajor = OpenGLMajor;
			GLMinor = OpenGLMinor;

			//Initiation
			InititateOpenGL();
			this->window.MakeWindow(WindowTitle, WindowWidth, WindowHeight, Vsync, OpenGLMajor, OpenGLMinor, Resizable);
			InititateOpenGLAddons();

			//Configure
			OpenGLEnable(GL_DEPTH_TEST);
			OpenGLEnable(GL_CULL_FACE);
			OpenGLRendering(GL_BACK, GL_CCW);
			OpenGLEnable(GL_BLEND);
			OpenGLBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			OpenGLPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//Input
			glfwSetScrollCallback(this->window.WindowObject, scroll_callback);
			glfwSetKeyCallback(this->window.WindowObject, key_callback);
			glfwSetCharCallback(this->window.WindowObject, character_callback);

			//Variable Initialiser
			this->window.FPS = FPS;
			Input = InputClass(this->window.WindowObject, &this->window.FrameBufferSize);
			InputP = &Input;
			this->LastTime = 0.f;

			//Render and debug
			this->Rendering = new Renderer(&this->window);
			if(this->DebuggerMode){
				this->Debug = new Debugger(ivec2(WindowWidth, WindowHeight), Vsync, ivec2(OpenGLMajor, OpenGLMinor), FPS);
				this->DebugMade = true;
			}
		}

		//Uninitialise
		~Game(){
			if(this->DebugMade)
				delete Rendering;
			delete Debug;
		}

		//For main loop
		bool getApplicationShouldClose() {
			return glfwWindowShouldClose(this->window.WindowObject);
		}

		//Quits
		void quitApplication() {
			glfwSetWindowShouldClose(this->window.WindowObject, GL_TRUE);
		}

		//Game Update
		void Update() {

			//Input
			glfwPollEvents();

			//Tick Time
			Time.Update();

			//Size and scaling updateing
			this->window.Update();

			//Render Items
			ProjectionMatrix = mat4(1.f);
			ProjectionMatrix = perspective(radians(this->ActiveScene.MainCamera.FOV), static_cast<float>(this->window.FrameBufferSize.x) / this->window.FrameBufferSize.y, this->ActiveScene.MainCamera.NearPlane, this->ActiveScene.MainCamera.FarPlane);
			UIProjection = ortho(0.0f, static_cast<float>(this->window.Size.x), 0.0f, static_cast<float>(this->window.Size.y));
			
			//Camera and ui
			this->ActiveScene.MainCamera.Update();
			this->ActiveScene.UI.Update(this->window.Size);
			
			//Debug Creation
			if(DebuggerMode && !this->DebugMade){
				this->Debug = new Debugger(ivec2(this->window.Size.x, this->window.Size.y), this->window.UsingVsync, ivec2(this->window.GLVersion.x, this->window.GLVersion.y), this->window.FPS);
				this->DebugMade = true;
			}

			//Debug Update
			if(DebuggerMode)
				this->Debug->Update();
		}

		void Render() {

			//Use Main Window
			this->window.MakeContext();

			//Two Types of rendering
			if (this->window.UseResoltuition) {
				//Scale To Resoltion
				this->window.UpdateViewPort(this->window.Resolution);
				//Sort out fake framebuffer
				this->Rendering->GenerateFrameBuffer();
				this->Rendering->BindFrameBuffer(GL_FRAMEBUFFER, this->Rendering->FB.Framebuffer);
			}
			else {
				//Ensure Corrent Sizing
				this->window.UpdateViewPort(this->window.Size);
				this->Rendering->BindFrameBuffer(GL_FRAMEBUFFER, 0);
			}

			//Depth
			OpenGLEnable(GL_DEPTH_TEST);

			//Resoltuion Texture and depth
			if (this->window.UseResoltuition) {
				//Texture
				this->Rendering->GenerateTexture(GL_TEXTURE_2D, GL_RGB, this->window.Resolution);
				//Depth
				this->Rendering->UseDepthBufferOnFB(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->window.Resolution);
				//Attach
				this->Rendering->AttachTextureToFramebuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D);
				this->Rendering->AtttachDepthBufferToFrameBuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER);
			}

			//Clear For renderign
			this->Rendering->Clear(true, true, true);

			//Objects (Change resoltion)
			for (GameObject* OBJ : this->ActiveScene.gameObjects) {
				OBJ->Render();
			}

			//Render if Using Resolution
			if (this->window.UseResoltuition) {
				//Bind To Main Draw
				this->Rendering->BindFrameBuffer(GL_DRAW_FRAMEBUFFER, 0);

				//No Depth
				OpenGLDisable(GL_DEPTH_TEST);

				//If Any Issues Occour With Depth
				//this->Rendering->Clear(true, false, false);
				//Clear
				this->Rendering->Clear(true, true, false);

				//Attach Texture for reading
				this->Rendering->AttachTextureToFramebuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D);

				//Scale window to normal
				this->window.UpdateViewPort(this->window.Size);

				//Scale texture onto screen
				this->Rendering->BlitBuffer(this->window.Resolution, this->window.Size);

				//Unbind
				this->Rendering->BindFrameBuffer(GL_FRAMEBUFFER, 0);
			}

			//Render UI
			this->ActiveScene.UI.Render();

			//Buffers
			if (this->window.UsingVsync) {
				glfwSwapBuffers(this->window.WindowObject);
			}

			//Debug Creation
			if(DebuggerMode && !this->DebugMade){
				this->Debug = new Debugger(ivec2(this->window.Size.x, this->window.Size.y), this->window.UsingVsync, ivec2(this->window.GLVersion.x, this->window.GLVersion.y), this->window.FPS);
				this->DebugMade = true;
			}

			//Debug
			if(DebuggerMode)
				this->Debug->Render();

			//Clean
			glFlush();

			//Delay next frame
			if (!this->window.UsingVsync && this->window.FPS > 0 && this->LastTime > 0.f) {
				while (Time.Time() < this->LastTime + 1.0 / this->window.FPS) {
					//Do Nothing
				}
			}

			//Update for FPS
			this->LastTime = Time.Time();
		}

		//Image Rendering
		void Render(PixelImage* PI, int Scale = 1) {
			//Use Window
			this->window.MakeContext();

			//Sizing
			this->window.Size = PI->Size * ivec2(Scale, Scale);

			//Apply Data to texture
			Screen.UpdateTexture(PI->ReturnData(), PI->Size.x, PI->Size.y);

			//Use FB Method
			this->Rendering->GenerateFrameBuffer();
			this->Rendering->BindFrameBuffer(GL_FRAMEBUFFER, this->Rendering->FB.Framebuffer);

			//Use Special Texture
			this->Rendering->RenderTexture = Screen.GetID();

			//Render Buffer
			this->Rendering->BindFrameBuffer(GL_DRAW_FRAMEBUFFER, 0);

			//No Depth
			OpenGLDisable(GL_DEPTH_TEST);

			//If Any Issues Occour With Depth
			//this->Rendering->Clear(true, false, false);
			//Clear
			this->Rendering->Clear(true, true, false);

			//FB use texture
			this->Rendering->AttachTextureToFramebuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D);

			//Size to screen
			this->Rendering->BlitBuffer(PI->Size, this->window.Size);

			//Unbinf
			this->Rendering->BindFrameBuffer(GL_FRAMEBUFFER, 0);

			//Buffer
			if (this->window.UsingVsync) {
				glfwSwapBuffers(this->window.WindowObject);
			}

			//Debug Creation
			if(DebuggerMode && !this->DebugMade){
				this->Debug = new Debugger(ivec2(this->window.Size.x, this->window.Size.y), this->window.UsingVsync, ivec2(this->window.GLVersion.x, this->window.GLVersion.y), this->window.FPS);
				this->DebugMade = true;
			}

			//Debug
			if(DebuggerMode)
				this->Debug->Render();

			//Clean
			glFlush();

			//Delay next frame
			if (!this->window.UsingVsync && this->window.FPS > 0 && this->LastTime > 0.f) {
				while (Time.Time() < this->LastTime + 1.0 / this->window.FPS) {
					//Do Nothing
				}
			}

			//Update for FPS
			this->LastTime = Time.Time();
		}
	};
}