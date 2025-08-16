#ifndef TEXTURE_H
#define TEXTURE_H


#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <string>
#include <stdexcept>

#ifdef _DEBUG
#include <iostream>
#endif

#include "Utils/File/File.h"

enum TextureWrap {
	REPEAT = GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
};
enum TextureFilter {
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
};

struct TextureSetting {
	TextureWrap WrapX = TextureWrap::CLAMP_TO_EDGE;
	TextureWrap WrapY = TextureWrap::CLAMP_TO_EDGE;
	TextureFilter Min = TextureFilter::LINEAR;
	TextureFilter Max = TextureFilter::LINEAR;
};

enum TextureType {
	_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	_BYTE = GL_BYTE,
	_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	_SHORT = GL_SHORT,
	_UNSIGNED_INT = GL_UNSIGNED_INT,
	_INT = GL_INT,
	_FLOAT = GL_FLOAT
};

enum TextureFormat {
	RED = GL_RED,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	DEPTH = GL_DEPTH_COMPONENT,
};

enum TextureInternalFormat {
	RGBA32F		= GL_RGBA32F,
	RGBA32I		= GL_RGBA32I,
	RGBA32UI	= GL_RGBA32UI,
	RGBA16		= GL_RGBA16,
	RGBA16F		= GL_RGBA16F,
	RGBA16I		= GL_RGBA16I,
	RGBA16UI	= GL_RGBA16UI,
	RGBA8		= GL_RGBA8,
	RGBA8UI		= GL_RGBA8UI,

	RGB8		= GL_RGB8,
	RGB8I		= GL_RGB8I,
	RGB8UI		= GL_RGB8UI,
	RGB16		= GL_RGB16,
	RGB16F		= GL_RGB16F,
	RGB16I		= GL_RGB16I,
	RGB16UI		= GL_RGB16UI,
	RGB32F		= GL_RGB32F,
	RGB32I		= GL_RGB32I,
	RGB32UI		= GL_RGB32UI,

	RG8			= GL_RG8,
	RG8I		= GL_RG8I,
	RG8UI		= GL_RG8UI,
	RG16		= GL_RG16,
	RG16F		= GL_RG16F,
	RG32F		= GL_RG32F,
	RG32I		= GL_RG32I,
	RG32UI		= GL_RG32UI,

	R8			= GL_R8,
	R8I			= GL_R8I,
	R8UI		= GL_R8UI,
	R16			= GL_R16,
	R16F		= GL_R16F,
	R16I		= GL_R16I,
	R16UI		= GL_R16UI,
	R32F		= GL_R32F,
	R32I		= GL_R32I,
	R32UI		= GL_R32UI,

	DEPTH_COMPONENT		= GL_DEPTH_COMPONENT,
	DEPTH_COMPONENT32F	= GL_DEPTH_COMPONENT32F,
	DEPTH_COMPONENT24	= GL_DEPTH_COMPONENT24,
	DEPTH_COMPONENT16	= GL_DEPTH_COMPONENT16,
	DEPTH_STENCIL		= GL_DEPTH_STENCIL,
	DEPTH32F_STENCIL8	= GL_DEPTH32F_STENCIL8,
	DEPTH24_STENCIL8	= GL_DEPTH24_STENCIL8,
};


struct TextureInfo {
	int width = 0;
	int height = 0;
	int channels = 0; 
};


class Texture {
public:
	Texture();
	Texture(TextureSetting setting,
		const int& MipMapLevel,
		TextureInternalFormat internalFormat,
		int width,
		int height,
		TextureFormat format,
		TextureType type,
		const void* data);
	Texture(const TextureSetting& setting, const std::string& Path2Image, const int& desiredCount_channels = 0);
	~Texture();

	void SetSetting(const TextureSetting& setting);
	void LoadTexture(const std::string& Path2Image, const int& desiredCount_channels = 0);
	void LoadTexture(const uint8_t* data, const int& len);

	void Init();

	int GetWidth();
	int GetHeight();

	int GetID();
private:
	GLuint ID;
	TextureSetting setting;
	TextureInfo info;

	uint8_t* dataImage = nullptr;

	int GetTypeImageData(const int& channels);
};







#endif