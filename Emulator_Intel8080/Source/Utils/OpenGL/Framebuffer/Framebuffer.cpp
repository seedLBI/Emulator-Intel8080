#include "Framebuffer.h"

Framebuffer::Framebuffer() {
	Init();
}

Framebuffer::~Framebuffer() {
	glDeleteFramebuffers(1, &ID);
}


void Framebuffer::SetCountDrawBuffers(const int& count) {
	Bind();

	std::vector<GLenum> attachments;

	for (int i = 0; i < count; i++) {
		attachments.push_back(Buffer_Attachment::COLOR_ATTACHMENT0 + i);
	}

	glDrawBuffers(count, attachments.data());
	
	UnBind();
}

void Framebuffer::AttachTexture(Texture& texture, const Buffer_Attachment& attachment) {
	Bind();
	
	glViewport(0, 0, texture.GetWidth(), texture.GetHeight());

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture.GetID(), 0);

	UnBind();
}
void Framebuffer::AttachRenderBuffer(Renderbuffer& buffer, const Buffer_Attachment& attachment) {
	Bind();

	glViewport(0, 0, buffer.GetWidth(), buffer.GetHeight());

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, buffer.GetID());

	UnBind();
}


void Framebuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}
void Framebuffer::UnBind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Framebuffer::Init() {
	glGenFramebuffers(1, &ID);
}