#pragma once

//Includes
#include "../OpenGL/OpenGLInc.h"
#include "../../Maths/Maths.h"

namespace UnifiedEngine {
	class RenderBuffer {
	public:
		//Buffer
		GLuint Renderbuffer;
		
		//Delete
		~RenderBuffer() {
			if(this->Renderbuffer)
				glDeleteRenderbuffers(1, &this->Renderbuffer);
		}

		//Generation
		void Generate(GLenum Target, GLenum Stencil, ivec2 Resolution) {
			if (this->Renderbuffer)
				glDeleteRenderbuffers(1, &this->Renderbuffer);
			glGenRenderbuffers(1, &this->Renderbuffer);
			glBindRenderbuffer(Target, this->Renderbuffer);
			glRenderbufferStorage(Target, Stencil, Resolution.x, Resolution.y);
		}
		
		//Unbinding
		void Unbind() {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
	};
}