#pragma once

//Includes
#include "./OpenGLInc.h"

//Namespace
namespace UnifiedEngine {
	//Enable
	void OpenGLEnable(GLenum ToEnable) {
		glEnable(ToEnable);
	}

	//Disable
	void OpenGLDisable(GLenum ToDisable) {
		glEnable(ToDisable);
	}

	//PolygonMode
	void OpenGLPolygonMode(GLenum Face, GLenum Mode) {
		glPolygonMode(Face, Mode);
	}

	//Blending
	void OpenGLBlend(GLenum SFactor, GLenum DFactor) {
		glBlendFunc(SFactor, DFactor);
	}

	//GLRendering
	void OpenGLRendering(GLenum Cull, GLenum Front) {
		glCullFace(Cull);
		glFrontFace(Front);
	}
}