#pragma once

//Includes
#include "../OpenGL/OpenGLInc.h"
#include "../Input/Input.h"
#include "../../Maths/Maths.h"

#include <iostream>
#include <string>

namespace UnifiedEngine {
	class Window {
	private:
		//Created
		bool Created;

		//Sizing
		bool IsFullscreen;

		//Backups for fullscreen
		ivec2 BackupSize;
		ivec2 BackupPos;

		//Comparitives
		ivec2 CompareSize;
		bool CompareVsync;
		const char* CompareTitle;
		bool CompareResizable;
		
	public:
		//Window
		GLFWwindow* WindowObject;

		//Resolution
		ivec2 Resolution;
		bool UseResoltuition;

		//Window Sepcifics
		ivec2 Size;
		int FPS;
		bool UsingVsync;
		bool Resizable;

		const char* Title;

		//Sizing
		ivec2 FrameBufferSize;

		//OpenGL
		ivec2 GLVersion;

		//Enable Fullscreen
		void ToggleFullscreen() {
			if (this->IsFullscreen) {
				//Backup
				glfwGetWindowPos(this->WindowObject, &this->BackupPos.x, &this->BackupPos.y);
				glfwGetWindowSize(this->WindowObject, &this->BackupSize.x, &this->BackupSize.y);

				//Make Fullscreen
				const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				glfwSetWindowMonitor(this->WindowObject, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
			}
			else {
				//Set back to backups
				glfwSetWindowMonitor(this->WindowObject, nullptr, this->BackupPos.x, this->BackupSize.y, this->BackupSize.x, this->BackupSize.y, GLFW_DONT_CARE);
			}
			//Toggle for next run
			this->IsFullscreen = !this->IsFullscreen;
		}

		//Generation
		void MakeWindow(const char* title, int width, int height, bool vsync, int glMajor, int glMinor, bool resizable) {
			//OpenGL
			this->GLVersion = ivec2(glMajor, glMinor);
			
			//Window Settings
			glfwWindowHint(GLFW_DOUBLEBUFFER, vsync);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
			glfwWindowHint(GLFW_RESIZABLE, resizable);
		
			#ifdef __APPLE__
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			#endif

			//Create Window
			this->WindowObject = glfwCreateWindow(width, height, title, NULL, NULL);

			//Errors
			if (!this->WindowObject) {
				throw("ERR::WINDOW:WINDOW_FAILED_TO_INITIALISE");
				glfwTerminate();
			}

			//Framebuffer size and callback
			glfwGetFramebufferSize(this->WindowObject, &this->FrameBufferSize.x, &this->FrameBufferSize.y);
			glfwSetFramebufferSizeCallback(this->WindowObject, this->framebuffer_resize_callback);
			//glViewport(0, 0, framebufferWidth, framebufferHeight);

			//Context
			glfwMakeContextCurrent(this->WindowObject);
			if (!this->Created) {
				this->Created = true;
			}

			//Variable Initialise
			this->Size = ivec2(width, height);
			this->UsingVsync = vsync;
			this->Title = title;
			this->Resizable = resizable;
			this->CompareSize = this->Size;
			this->CompareVsync = vsync;
			this->CompareTitle = title;
			this->CompareResizable = resizable;
			this->UseResoltuition = false;
			this->Resolution = this->Size;
		}

		//For Extra windwos
		void MakeSingleWindow(const char* title, int width, int height, bool vsync, bool resizable, GLFWwindow* share = NULL){
			
			//Hints
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
			glfwWindowHint(GLFW_RESIZABLE, resizable);
			glfwWindowHint(GLFW_DOUBLEBUFFER, vsync);

			//Window
			this->WindowObject = glfwCreateWindow(width, height, title, NULL, share);

			//Errors
			if (!this->WindowObject) {
				throw("ERR::WINDOW:WINDOW_FAILED_TO_INITIALISE");
				glfwTerminate();
			}

			//Framebuffer
			glfwGetFramebufferSize(this->WindowObject, &this->FrameBufferSize.x, &this->FrameBufferSize.y);
			glfwSetFramebufferSizeCallback(this->WindowObject, this->framebuffer_resize_callback);
			//glViewport(0, 0, framebufferWidth, framebufferHeight);

			//glfwMakeContextCurrent(this->WindowObject);
			if (!this->Created) {
				this->Created = true;
			}

			//Init Varaibles
			this->Size = ivec2(width, height);
			this->UsingVsync = vsync;
			this->Title = title;
			this->Resizable = resizable;
			this->CompareSize = this->Size;
			this->CompareVsync = vsync;
			this->CompareTitle = title;
			this->CompareResizable = resizable;
			this->UseResoltuition = false;
			this->Resolution = this->Size;
		}

		//Updating
		void Update() {
			//Get Size
			glfwGetFramebufferSize(this->WindowObject, &this->FrameBufferSize.x, &this->FrameBufferSize.y);
			
			//Compare Size
			if (this->Size != this->CompareSize) {
				//Resize
				glViewport(0, 0, this->Size.x, this->Size.y);
				glfwSetWindowSize(this->WindowObject, this->Size.x, this->Size.y);
				this->FrameBufferSize = this->Size;
				this->CompareSize = this->Size;
			}
			else if (this->Size != this->FrameBufferSize) {
				//Resize
				glViewport(0, 0, this->FrameBufferSize.x, this->FrameBufferSize.y);
				this->Size = this->FrameBufferSize;
				this->CompareSize = this->Size;
			}
			
			//Vsync Change
			if (this->UsingVsync != this->CompareVsync) {
				//Window Change
				glfwWindowHint(GLFW_DOUBLEBUFFER, this->UsingVsync);
				this->CompareVsync = this->UsingVsync;
			}

			//Title Change
			if (this->Title != this->CompareTitle) {
				//Change Title
				glfwSetWindowTitle(this->WindowObject, this->Title);
				string s = this->Title;
				this->CompareTitle = s.c_str();
			}

			//Resize Change
			if (this->Resizable != this->Resizable) {
				//Change Resizable
				glfwWindowHint(GLFW_RESIZABLE, this->Resizable);
				this->CompareResizable = this->Resizable;
			}

			//Resolution Change
			if (this->Resolution.x <= 0 || this->Resolution.y <= 0) {
				this->Resolution = this->Size;
			}
		}

		//Chaneg Size
		void UpdateViewPort(ivec2 size) {
			glViewport(0, 0, size.x, size.y);
		}

		//Use Context
		void MakeContext(){
			glfwMakeContextCurrent(this->WindowObject);
		}

		//Callbacks
		static void framebuffer_resize_callback(GLFWwindow* windows, int fbw, int fbh)
		{
			glViewport(0, 0, fbw, fbh);
		}
	};
}