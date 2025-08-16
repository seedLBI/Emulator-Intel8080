#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture() {
	glGenTextures(1, &ID);
}

Texture::~Texture() {
	if (dataImage)
		stbi_image_free(dataImage);
	glDeleteTextures(1, &ID);
}

Texture::Texture(const TextureSetting& setting, const std::string& Path2Image, const int& desiredCount_channels) {
	glGenTextures(1, &ID);
	SetSetting(setting);
	LoadTexture(Path2Image, desiredCount_channels);
	Init();
}

Texture::Texture(
	TextureSetting setting,
	const int& MipMapLevel,
	TextureInternalFormat internalFormat,
	int width,
	int height,
	TextureFormat format,
	TextureType type,
	const void* data)
{
	SetSetting(setting);
	info.width = width;
	info.height = height;

	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, setting.WrapX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, setting.WrapY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, setting.Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, setting.Max);

	glTexImage2D(GL_TEXTURE_2D, MipMapLevel, internalFormat, info.width, info.height, 0, format, type, data);
}


int Texture::GetWidth() {
	return info.width;
}
int Texture::GetHeight() {
	return info.height;
}

int Texture::GetID() {
	return ID;
}

void Texture::SetSetting(const TextureSetting& setting) {
	this->setting = setting;
}

int Texture::GetTypeImageData(const int& channels) {
	switch (channels) {
	case 4:
		return GL_RGBA;
		break;
	case 3:
		return GL_RGB;
		break;
	case 2:
		return GL_RG;
		break;
	case 1:
		return GL_R;
		break;
	case 0:
		exit(100);
		break;
	default:
		break;
	}
}

void Texture::LoadTexture(const std::string& Path2Image, const int& desiredCount_channels) {
	if (!isFileExist(Path2Image)) {
		throw std::runtime_error("Incorrect path to image: [" + Path2Image + "]");
	}

	stbi_set_flip_vertically_on_load(true);
	dataImage = stbi_load(Path2Image.c_str(), &info.width, &info.height, &info.channels, desiredCount_channels);

#ifdef _DEBUG

	std::cout << "[Info Texture] [" << Path2Image << "]\n";
	std::cout << "\t\tWidth:   [" << info.width << "]\n";
	std::cout << "\t\tHeight:  [" << info.height << "]\n";
	std::cout << "\t\tChannels:[" << info.channels << "]\n";

#endif // _DEBUG

}

void Texture::LoadTexture(const uint8_t* data, const int& len) {
	stbi_set_flip_vertically_on_load(true);
	dataImage = stbi_load_from_memory(data, len, &info.width, &info.height, &info.channels, 0);
#ifdef _DEBUG
	std::cout << "[Info Texture]\n";
	std::cout << "\t\tWidth:   [" << info.width << "]\n";
	std::cout << "\t\tHeight:  [" << info.height << "]\n";
	std::cout << "\t\tChannels:[" << info.channels << "]\n";
#endif // _DEBUG

}


void Texture::Init() {
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, setting.WrapX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, setting.WrapY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, setting.Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, setting.Max);



	const int mipmapFilters[4] = {
		GL_NEAREST_MIPMAP_NEAREST,
		GL_NEAREST_MIPMAP_LINEAR,
		GL_LINEAR_MIPMAP_NEAREST,
		GL_LINEAR_MIPMAP_LINEAR };
	bool haveMipmapFilter = false;
	for (int i = 0; i < 4; i++)
	{
		if (setting.Min == mipmapFilters[i]
			|| setting.Max == mipmapFilters[i])
		{
			haveMipmapFilter = true;
			break;
		}
	}

	if (dataImage) {
		int TypeData = GetTypeImageData(info.channels);

		glTexImage2D(GL_TEXTURE_2D, 0, TypeData, info.width, info.height, 0, TypeData, GL_UNSIGNED_BYTE, dataImage);

		if (haveMipmapFilter) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		stbi_image_free(dataImage);
		dataImage = nullptr;
	}
	else
		throw std::runtime_error("Load image before initialization!!!");






}