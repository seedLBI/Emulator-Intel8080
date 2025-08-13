#include "Renderbuffer.h"


Renderbuffer::Renderbuffer(const TextureInternalFormat& InternalFormat, const GLuint& width, const GLuint& height) {
	this->width = width;
	this->height = height;
	glGenRenderbuffers(1, &ID);
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
	glRenderbufferStorage(GL_RENDERBUFFER, InternalFormat, width, height);
}

Renderbuffer::~Renderbuffer() {

}

GLuint Renderbuffer::GetWidth() {
	return width;
}
GLuint Renderbuffer::GetHeight() {
	return height;
}
GLuint Renderbuffer::GetID() {
	return ID;
}