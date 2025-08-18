#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include <stb_image.h>

#include "Utils/OpenGL/Texture/Texture.h"

class Renderbuffer
{
public:
	Renderbuffer(const TextureInternalFormat& InternalFormat, const GLuint& width, const GLuint& height);
	~Renderbuffer();

	GLuint GetID();

	GLuint GetWidth();
	GLuint GetHeight();

private:
	GLuint ID = 0;
	GLuint width = 0, height = 0;
};


#endif