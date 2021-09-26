#pragma once

//Includes
#include "./RenderBuffer.h"

namespace UnifiedEngine {
	class FrameBuffer {
	public:
		//RenderB
		RenderBuffer DepthRB;

		//Buffer
		GLuint Framebuffer;

		//Delete Buffer
		~FrameBuffer() {
			if(this->Framebuffer)
				glDeleteFramebuffers(1, &this->Framebuffer);
		}

		//Create Buffer
		void Generate() {
			if (this->Framebuffer)
				glDeleteFramebuffers(1, &this->Framebuffer);
			glGenFramebuffers(1, &this->Framebuffer);
		}

		//Load DepthBuffer
		void LoadDepthBuffer(GLenum Target, GLenum Stencil, ivec2 Resolution) {
			this->DepthRB.Generate(Target, Stencil, Resolution);
		}
	};
}