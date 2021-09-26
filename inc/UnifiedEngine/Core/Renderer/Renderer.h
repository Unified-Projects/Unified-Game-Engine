#pragma once

//Includes
#include "./Framebuffer.h"
#include "../Window/Window.h"

namespace UnifiedEngine {
	class Renderer {
	private:
		//Window
		Window* window;

		//Resolution
		ivec2 oldRes;

	public:
		//Texture
		GLuint RenderTexture;

		//FrameBuffer
		FrameBuffer FB;

		//Initiate
		Renderer(Window* window) {
			this->window = window;
		}

		//Uninitailise
		~Renderer() {
			glDeleteTextures(1, &this->RenderTexture);
		}
		
		//Generate FB
		void GenerateFrameBuffer() {
			this->FB.Generate();
		}
		
		//Binding FB
		void BindFrameBuffer(GLenum Target, GLuint Framebuffer) {
			glBindFramebuffer(Target, Framebuffer);
		}

		//Create texture
		void GenerateTexture(GLenum Type, GLenum Color, ivec2 Resolution) {
			if (this->RenderTexture)
				glDeleteTextures(1, &this->RenderTexture);
			glGenTextures(1, &this->RenderTexture);
			glBindTexture(Type, this->RenderTexture);
			glTexImage2D(Type, 0, Color, Resolution.x, Resolution.y, 0, Color, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(Type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(Type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}

		//Use Assing Depth Buffer
		void UseDepthBufferOnFB(GLenum Target, GLenum Stencil, ivec2 Resolution) {
			this->FB.LoadDepthBuffer(Target, Stencil, Resolution);
		}

		//Attach texture
		void AttachTextureToFramebuffer(GLenum Target, GLenum Attachment, GLenum Texture) {
			glFramebufferTexture2D(Target, Attachment, Texture, this->RenderTexture, 0);
		}

		//Attach RenderBuffer
		void AtttachDepthBufferToFrameBuffer(GLenum Target, GLenum Attachment, GLenum Renderbuffer) {
			glFramebufferRenderbuffer(Target, Attachment, Renderbuffer, this->FB.DepthRB.Renderbuffer);
		}

		//Clear Specific
		void Clear(bool ColorBit, bool DepthBit, bool StencilBit, vec4 Color = vec4(0, 0, 0 ,1)) {
			//Color
			glClearColor(Color.x, Color.y, Color.z, Color.w);
			//Bits
			if (ColorBit)
				glClear(GL_COLOR_BUFFER_BIT);
			if (DepthBit)
				glClear(GL_DEPTH_BUFFER_BIT);
			if (StencilBit)
				glClear(GL_STENCIL_BUFFER_BIT);
		}

		//BlitImage
		void BlitBuffer(ivec2 Resolution, ivec2 Size) {
			glBlitFramebuffer(0, 0, Resolution.x, Resolution.y, 0, 0, Size.x, Size.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		}
	};
}