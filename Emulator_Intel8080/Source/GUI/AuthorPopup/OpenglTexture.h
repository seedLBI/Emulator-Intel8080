#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H


#include "OpenglWindow/OpenglWindow.h"

#include <string>
#include <vector>

struct OpenglTexturee {
	OpenglTexturee() {

	}
	OpenglTexturee(std::string filePath) {
		Init();
		SetData(filePath);
	}
	OpenglTexturee(unsigned char* data, int width, int height, int channels) {
		Init();
		SetData(data, width, height, channels);
	}
	~OpenglTexturee() {
		glDeleteTextures(1, &ID);
	}

	void ReadFromFile(std::string filePath) {
		Init();
		SetData(filePath);
	}

	void ReadFromMemory(std::vector<uint8_t> file_data) {
		Init();
		SetData(file_data);
	}

	void ReadFromMemoryWithAlpha(std::vector<uint8_t> file_data) {
		Init();
		SetDataWithAlpha(file_data);
	}

	GLuint GetTextureID() {
		return ID;
	}
	glm::vec2 GetSize() {
		return glm::vec2(width, height);
	}


private:

	int width = 0, height = 0, channels = 0;
	unsigned char* data;
	GLuint ID;


	void Init() {
		glGenTextures(1, &ID);
	}


	void SetDataWithAlpha(std::vector<uint8_t> file_data) {

		data = SOIL_load_image_from_memory(file_data.data(), file_data.size(), &width, &height, &channels, 4);


		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void SetData(std::vector<uint8_t> file_data) {

		data = SOIL_load_image_from_memory(file_data.data(), file_data.size(), &width, &height, &channels, SOIL_LOAD_AUTO);


		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}


	void SetData(unsigned char* data, int width, int height, int channels) {
		this->data = data;
		this->width = width;
		this->height = height;
		this->channels = channels;


		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

	void SetData(std::string filePath) {

		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



		if (data = SOIL_load_image(filePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO))
		{
#ifdef WITH_DEBUG_OUTPUT
			std::cout << "nice " << channels << "  " << filePath << std::endl;
#endif
			if (channels == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}

		}
		else {
#ifdef WITH_DEBUG_OUTPUT
			std::cout << "failed " << filePath << std::endl;
#endif
			exit(0);
		}


	}

};

#endif // !OPENGL_TEXTURE_H
