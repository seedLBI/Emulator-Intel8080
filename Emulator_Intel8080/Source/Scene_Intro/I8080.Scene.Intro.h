#pragma once
#ifndef I8080_SCENE_INTRO_H
#define I8080_SCENE_INTRO_H

#include "Config_Compilier.h"

#include "OpenglWindow\OpenglWindow.h"

#include "Shader\Shader.h"

#include "Scene_Intro\Shaders\Intro.Shaders.h"

#include "ImagesData\Image_MSDF_ATLAS.h"
#include "ImagesData\Image_MSDF_DESIGN_8080.h"
#include "ImagesData\Image_MSDF_DESIGN_seedLBI_production.h"

#include "Utils\TextUtils.h"

#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <cmath>
#include <thread>
#include <algorithm>
#include <iostream>
using namespace std;



bool isAnyKeyDown(GLFWwindow* window) {

	for (int KeyMouse = GLFW_MOUSE_BUTTON_LEFT; KeyMouse < GLFW_MOUSE_BUTTON_MIDDLE; KeyMouse++)
	{
		if (glfwGetMouseButton(window, KeyMouse) == GLFW_PRESS)
		{
			return true;
		}
	}

	for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
		if (glfwGetKey(window, key) == GLFW_PRESS) {
			return true;
		}
	}

	return false;
}


std::vector<uint16_t> utf8_to_utf16(const std::string& utf8) {
	std::vector<uint16_t> utf16;
	size_t i = 0;
	while (i < utf8.size()) {
		uint32_t codepoint = 0;
		unsigned char c = utf8[i];
		if ((c & 0x80) == 0) {
			codepoint = c;
			i += 1;
		}
		else if ((c & 0xE0) == 0xC0) {
			if (i + 1 >= utf8.size()) throw std::runtime_error("Invalid UTF-8 sequence");
			codepoint = ((c & 0x1F) << 6) | (utf8[i + 1] & 0x3F);
			i += 2;
		}
		else if ((c & 0xF0) == 0xE0) {
			if (i + 2 >= utf8.size()) throw std::runtime_error("Invalid UTF-8 sequence");
			codepoint = ((c & 0x0F) << 12) | ((utf8[i + 1] & 0x3F) << 6) | (utf8[i + 2] & 0x3F);
			i += 3;
		}
		else if ((c & 0xF8) == 0xF0) {
			if (i + 3 >= utf8.size()) throw std::runtime_error("Invalid UTF-8 sequence");
			codepoint = ((c & 0x07) << 18) | ((utf8[i + 1] & 0x3F) << 12) | ((utf8[i + 2] & 0x3F) << 6) | (utf8[i + 3] & 0x3F);
			i += 4;
		}
		else {
			throw std::runtime_error("Invalid UTF-8 sequence");
		}

		if (codepoint >= 0x10000) {
			codepoint -= 0x10000;
			utf16.push_back(0xD800 | (codepoint >> 10));
			utf16.push_back(0xDC00 | (codepoint & 0x3FF));
		}
		else {
			utf16.push_back(static_cast<uint16_t>(codepoint));
		}
	}
	return utf16;
}

struct Rectanglee {
	float X = 0.f, Y = 0.f;
	float Width = 0.f, Height = 0.f;
};
struct Glyph {
	float advance = 0.f;

	Rectanglee Atlas;

	Rectanglee Plane;

	void Print() {
#ifdef WITH_DEBUG_OUTPUT
		cout << "--------GLYPH_INFO---------\n";
		cout << "advance = " << advance << endl;
		cout << "Atlas.X = " << Atlas.X << endl;
		cout << "Atlas.Y = " << Atlas.Y << endl;
		cout << "Atlas.Width = " << Atlas.Width << endl;
		cout << "Atlas.Height = " << Atlas.Height << endl;
		cout << "Plane.X = " << Plane.X << endl;
		cout << "Plane.Y = " << Plane.Y << endl;
		cout << "Plane.Width = " << Plane.Width << endl;
		cout << "Plane.Height = " << Plane.Height << endl;
#endif // WITH_DEBUG_OUTPUT
	}

};
struct OpenglTexture {
	OpenglTexture() {

	}
	OpenglTexture(string filePath) {
		Init();
		SetData(filePath);
	}
	OpenglTexture(unsigned char* data, int width, int height, int channels) {
		Init();
		SetData(data, width, height, channels);
	}
	~OpenglTexture() {
		glDeleteTextures(1, &ID);
	}

	void ReadFromFile(string filePath) {
		Init();
		SetData(filePath);
	}

	void ReadFromMemory(std::vector<uint8_t> file_data) {
		Init();
		SetData(file_data);
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

	void SetData(string filePath) {

		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



		if (data = SOIL_load_image(filePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO))
		{
#ifdef WITH_DEBUG_OUTPUT
			cout << "nice " << channels << "  " << filePath << endl;
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
			cout << "failed " << filePath << endl;
#endif
			exit(0);
		}


	}

};

template <typename T>
class UBO {
public:

	UBO(const string& name) {
		Constructor(name);
	}

	UBO(const char* name) {
		Constructor(name);
	}

	UBO() {
		Constructor("");
	}

	~UBO() {
		glDeleteBuffers(1, &ID);
	}

	int GetID() {
		return ID;
	}
	string GetName() {
		return name;
	}
	void SetName(string name) {
		this->name = name;
	}

	void Bind(GLuint bindingPoint) const {
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ID);
	}


	void Update(const T& data) {
		glBindBuffer(GL_UNIFORM_BUFFER, ID);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T), &data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

private:
	string name;
	GLuint ID;


	void Constructor(const string& name) {
		this->name = name;

		glGenBuffers(1, &ID);
		glBindBuffer(GL_UNIFORM_BUFFER, ID);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(T), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
#ifdef WITH_DEBUG_OUTPUT
		cout << name << " have size: " << sizeof(T) << endl;
		cout << name << " have ID:   " << ID << endl;
#endif
	}

};

struct OpenglRenderBuffer {
	OpenglRenderBuffer() {

	}
	OpenglRenderBuffer(float width, float height) {
		this->width = width;
		this->height = height;
		Init();
	}
	~OpenglRenderBuffer() {
		EraseBuffer();
	}

	void InitBuffer(int width, int height) {
		this->width = width;
		this->height = height;
		Init();
	}


	void BeginRenderBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(ColorBG.r, ColorBG.g, ColorBG.b, ColorBG.a);
		glClear(GL_COLOR_BUFFER_BIT);

	}
	void EndRenderBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void SetBG(glm::vec4 color) {
		ColorBG = color;
	}
	GLuint GetTextureID() {
		return texture;
	}

private:
	GLuint fbo;
	GLuint texture;

	glm::vec4 ColorBG;

	float width = 0, height = 0;

	void EraseBuffer() {
		glDeleteTextures(1, &texture);
		glDeleteFramebuffers(1, &fbo);
		glFinish();
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "Framebuffer deleted" << std::endl;
#endif
	}

	bool Init() {

		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);
		if (OpenglWindow::CheckOpenglError("glBindTexture"))
			return false;

		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (OpenglWindow::CheckOpenglError("glTexParameteri"))
			return false;



		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		if (!primaryMonitor) {
			std::cerr << "Failed to get primary monitor" << std::endl;
			return false;
		}

		// Get the monitor's video mode
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
		if (!mode) {
			std::cerr << "Failed to get video mode" << std::endl;
			return false;
		}



		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mode->width, mode->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		if (OpenglWindow::CheckOpenglError("glTexImage2D"))
			return false;

		glBindTexture(GL_TEXTURE_2D, 0);

		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		GLenum statusCreating = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (statusCreating != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer Render is not complete!    Status:" << OpenglWindow::GetFramebufferErrorMeaning(statusCreating) << std::endl;
			return false;
		}
		//std::cout << "SUCESS::FRAMEBUFFER:: Render Framebuffer was created!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}

};
struct OpenglVelocityBuffer {
private:
	GLuint fbo;
	GLuint texture;


	void EraseBuffer() {
		glDeleteTextures(1, &texture);
		glFlush();
		glDeleteFramebuffers(1, &fbo);
		glFlush();
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "Framebuffer deleted" << std::endl;
#endif
	}


public:
	OpenglVelocityBuffer() {

	}
	~OpenglVelocityBuffer() {
		EraseBuffer();
	}

	bool Init(int width, int height) {
		glGenTextures(1, &texture);
		glFinish();
		if (OpenglWindow::CheckOpenglError("glGenTextures"))
			return false;

		glBindTexture(GL_TEXTURE_2D, texture);
		glFinish();
		if (OpenglWindow::CheckOpenglError("glBindTexture"))
			return false;


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFinish();

		if (OpenglWindow::CheckOpenglError("glTexParameteri"))
			return false;


		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		if (!primaryMonitor) {
			std::cerr << "Failed to get primary monitor" << std::endl;
			return false;
		}

		// Get the monitor's video mode
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
		if (!mode) {
			std::cerr << "Failed to get video mode" << std::endl;
			return false;
		}

#ifdef WITH_DEBUG_OUTPUT
		std::cout << "initing texture with width: " << mode->width << "  and height: " << mode->height << endl;
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, mode->width, mode->height, 0, GL_RG, GL_FLOAT, nullptr);
		glFinish();
		if (OpenglWindow::CheckOpenglError("glTexImage2D"))
			return false;

		glBindTexture(GL_TEXTURE_2D, 0);
		glFinish();

		glGenFramebuffers(1, &fbo);
		glFinish();
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFinish();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		glFinish();
		GLenum statusCreating = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (statusCreating != GL_FRAMEBUFFER_COMPLETE) {
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer Velocity is not complete!    Status:" << OpenglWindow::GetFramebufferErrorMeaning(statusCreating) << std::endl;
			return false;
		}
#ifdef WITH_DEBUG_OUTPUT
		std::cout << "SUCESS::FRAMEBUFFER:: Framebuffer Velocity was created!" << std::endl;
#endif
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glFinish();
		return true;
	}

	void DrawBegin() {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void DrawEnd() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GLuint GetTextureID() {
		return texture;
	}
};
struct CurveBezier {
private:
	float TimeEnd = 0.f;

	float MaxValue = 0.f;

	int countSplit = 20;

	vector<glm::vec2> points_base;
	vector<glm::vec2> points_additional;




	glm::vec2 My_lerp(glm::vec2 p1, glm::vec2 p2, float t) {
		return p1 + t * (p2 - p1);
	}

	glm::vec2 My_lerpCubic(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, float t) {
		return My_lerp(My_lerp(p1, p2, t), My_lerp(p2, p3, t), t);
	}

	glm::vec2 My_lerpQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, float t) {
		return My_lerp(My_lerpCubic(p1, p2, p3, t), My_lerpCubic(p2, p3, p4, t), t);
	}


	vector<glm::vec2> points_linear_curve;

	void RenderCurve() {
		points_linear_curve.clear();

		float step = 1.f / float(countSplit);

		for (int i = 0; i < points_base.size() - 1; i++)
		{
			for (int j = 0; j < countSplit; j++)
			{
				float t = step * j;


				glm::vec2 bs1 = points_base[i];
				bs1.y *= -1.f;
				glm::vec2 bs2 = points_base[i + 1];
				bs2.y *= -1.f;

				glm::vec2 ad1 = points_additional[i * 2];
				ad1.y *= -1.f;
				glm::vec2 ad2 = points_additional[i * 2 + 1];
				ad2.y *= -1.f;

				glm::vec2 point = My_lerpQuad(bs1, ad1, ad2, bs2, t);

				if (TimeEnd < point.x)
					TimeEnd = point.x;
				if (MaxValue < (point.y))
					MaxValue = (point.y);



				points_linear_curve.push_back(point);

				//cout << "(" << point.x << ",  " << point.y << "),";
			}

		}

		sort(points_linear_curve.begin(), points_linear_curve.end(), [](glm::vec2 a, glm::vec2 b) {return a.x < b.x; });


	}

	float t_collision1(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D) {
		float   numerator = (A.x - C.x) * (C.y - D.y) - (A.y - C.y) * (C.x - D.x);
		float denumerator = (A.x - B.x) * (C.y - D.y) - (A.y - B.y) * (C.x - D.x);
		return numerator / denumerator;
	}
	float t_collision2(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D) {
		float   numerator = (A.x - C.x) * (A.y - B.y) - (A.y - C.y) * (A.x - B.x);
		float denumerator = (A.x - B.x) * (C.y - D.y) - (A.y - B.y) * (C.x - D.x);
		return numerator / denumerator;
	}

	bool itHaveCollision(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D) {
		float l1 = t_collision1(A, B, C, D);
		float l2 = t_collision2(A, B, C, D);
		if (l1 >= 0.f && l1 <= 1.f && l2 >= 0.f && l2 <= 1.f)
		{
			return true;
		}
		return false;
	}

	int findSegment(const std::vector<glm::vec2>& dotsLine, float pos_x) {
		int left = 0;
		int right = dotsLine.size() - 1;

		//int count = 0;

		while (left <= right) {
			int mid = left + (right - left) / 2;

			if (dotsLine[mid].x <= pos_x && (mid == dotsLine.size() - 1 || dotsLine[mid + 1].x > pos_x)) {
				//cout << count << endl;
				return mid;
			}
			else if (dotsLine[mid].x < pos_x) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
			//count++;
		}
		//cout << count << endl;
		return -1; // Если ползунок находится вне всех сегментов
	}

public:
	CurveBezier(vector<glm::vec2> base_points, vector<glm::vec2> additional_points) {
		points_base = base_points;
		points_additional = additional_points;


		RenderCurve();
	}

	float GetValueFromT(float t) {

		int index = findSegment(points_linear_curve, t);

		if (index != -1)
		{
			glm::vec2 timeLineBegin = glm::vec2(t, -1000.f);
			glm::vec2 timeLineEnd = glm::vec2(t, 1000.f);
			float t2 = t_collision2(timeLineBegin, timeLineEnd, points_linear_curve[index], points_linear_curve[index + 1]);

			return My_lerp(points_linear_curve[index], points_linear_curve[index + 1], t2).y;
		}
		return MaxValue;
	}

	float GetLengthCurve() {
		return TimeEnd;
	}

};
struct BatchObject {
public:
	void AddGlyphs(
		const vector<uint16_t>& Word,
		unordered_map <uint16_t, Glyph>& GlyphMap,
		const glm::mat4& model,
		const float& koef_x)
	{

		float offset = 0.f;

		int begin = vertices.size();

		for (int symbolIndex = 0; symbolIndex < Word.size(); symbolIndex++) {

			uint16_t utf8_symbol = Word[symbolIndex];
			Glyph currentGlyph = GlyphMap[utf8_symbol];



			if (utf8_symbol != 0x0020) {


				float x = currentGlyph.Plane.X + offset;
				float y = currentGlyph.Plane.Y;
				float w = currentGlyph.Plane.Width - currentGlyph.Plane.X;
				float h = currentGlyph.Plane.Height - currentGlyph.Plane.Y;
				float u = currentGlyph.Atlas.X;
				float v = currentGlyph.Atlas.Y;
				float uW = currentGlyph.Atlas.Width;
				float vH = currentGlyph.Atlas.Height;


				vertices.insert(vertices.end(), {
					x,	   y,	  u,      v,
					x + w, y,     uW, v,
					x + w, y + h, uW,  vH,
					x,     y + h, u,   vH
					});

				indices.insert(indices.end(), {
					indexOffset, indexOffset + 1, indexOffset + 2,
					indexOffset, indexOffset + 2, indexOffset + 3
					});

				indexOffset += 4;
			}

			offset += currentGlyph.advance * koef_x;
		}



		for (int i = begin; i < vertices.size(); i += 4)
		{
			glm::vec4 vert_vector(vertices[i], vertices[i + 1], 1.f, 1.f);

			vert_vector = model * vert_vector;

			vertices[i] = vert_vector.x;
			vertices[i + 1] = vert_vector.y;
		}

	}

	void AddRectangle(const glm::mat4& model) {
		int begin = vertices.size();
		vertices.insert(vertices.end(), {
			0.f,  0.f,   0.0f, 1.0f,
			0.f,  1.f,   0.0f, 0.0f,

			1.f,  1.f,   1.0f, 0.0f,
			1.f,  0.f,   1.0f, 1.0f,
			});

		indices.insert(indices.end(), {
			indexOffset, indexOffset + 1, indexOffset + 2,
			indexOffset, indexOffset + 2, indexOffset + 3
			});

		for (int i = begin; i < vertices.size(); i += 4)
		{
			glm::vec4 vert_vector(vertices[i], vertices[i + 1], 1.f, 1.f);

			vert_vector = model * vert_vector;

			vertices[i] = vert_vector.x;
			vertices[i + 1] = vert_vector.y;
		}
		indexOffset += 4;
	}


	void Init() {
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	void Draw(
		Shader* shader,
		const glm::mat4& model)
	{
		shader->use();
		shader->setMat4("model", model);


		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

		//glBindVertexArray(0);
	}

	void Draw()
	{
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

		//glBindVertexArray(0);
	}

	BatchObject() {

	}

	~BatchObject() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1,&VBO);
		glDeleteBuffers(1,&EBO);
	}

private:
	GLuint VAO, VBO, EBO;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int indexOffset = 0;

};
unordered_map <uint16_t, Glyph> ReadGlyphsFromFile(string filePath) {

	unordered_map <uint16_t, Glyph> result;

	ifstream ifn;
	ifn.open(filePath);


	uint16_t unicode = 0;

	Glyph temp;

	string line;
	while (getline(ifn, line)) {

		vector<string> t = split(line, ",");


		unicode = stoi(t[0]);
		temp.advance = stof(t[1]);
		temp.Plane.X = stof(t[2]);
		temp.Plane.Y = stof(t[3]);
		temp.Plane.Width = stof(t[4]);
		temp.Plane.Height = stof(t[5]);
		temp.Atlas.X = stof(t[6]) / 1024.f + 1.f / 2048.f;
		temp.Atlas.Y = 1.f - (stof(t[7]) / 1024.f + 1.f / 2048.f);
		temp.Atlas.Width = stof(t[8]) / 1024.f - 1.f / 2048.f;
		temp.Atlas.Height = 1.f - (stof(t[9]) / 1024.f - 1.f / 2048.f);


		result[unicode] = temp;
	}
	return result;
}
glm::vec2 GetSizesWord(vector<uint16_t> word, unordered_map <uint16_t, Glyph> symbols_map) {
	glm::vec2 result{ 0.f,0.f };

	float min_y = 10000.f;
	float max_y = -10000.f;
	for (int i = 0; i < word.size(); i++)
	{
		Glyph symbol = symbols_map[word[i]];

		result.x += symbol.advance;


		if (min_y > symbol.Plane.Y)
			min_y = symbol.Plane.Y;
		if (min_y > symbol.Plane.Height)
			min_y = symbol.Plane.Height;

		if (max_y < symbol.Plane.Y)
			max_y = symbol.Plane.Y;
		if (max_y < symbol.Plane.Height)
			max_y = symbol.Plane.Height;

	}
	result.y = max_y - min_y;
	return result;
}


namespace Intro {

	namespace Structs {
		struct MatrixBlock_Data {
			glm::mat4 view;
			glm::mat4 proj;
		};
		struct ValuesBlock_Data {
			float Time;
			float Time2;
			float Resolution[2];
		};
	};
	namespace Vars {

		float aspect = OpenglWindow::Vars::Height / OpenglWindow::Vars::Width;
		glm::mat4 proj = glm::ortho(-1.f, 1.f, -1.f * aspect, 1.f * aspect, 0.f, 100.f);
		glm::mat4 view = glm::mat4(1.0f);

		bool Inited = false;


		bool Framebuffer_resizing = false;

		float time_animation_seedLBI = 0.f;
		float offset_y;
		float time_animation_Scene = 0.f;
		const float ENDTIME_SCENE = 2.1f;
		float normalized_time = 0.f;
		float revers_time = 0.f;

		float StartTime2 = 0.f;

		bool WordContinue_SetedBlinking = false;


		float time_animation_lerped_Scene = 0.f;


		bool Pressed = false;
		bool FirstSkip = false;
		bool SecondSkip = false;
		bool FullSkip = false;
		float x_offset = 0.f;
		float x_offset_left = 0.f;

		glm::mat4 LeftObjectsMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x_offset_left, 0.f, 0.f));
		glm::mat4 RightObjectsMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x_offset, 0.f, 0.f));
		glm::mat4 MatrixRightSolid = glm::translate(glm::mat4(1.f), glm::vec3(x_offset, 0.f, 0.f));
		glm::mat4 MatrixLeftSolid = glm::translate(glm::mat4(1.f), glm::vec3(x_offset_left, -0.5f, 0.f));

		glm::mat4 LeftSolidMatrix_Last;
		glm::mat4 RightSolidMatrix_Last;
		glm::mat4 seedLBIMatrix_Last;

		float TimeBegin = 0.f;
		CurveBezier* curve_seedLBI_move = nullptr;

		const glm::vec3 color_Whiteyellow = { 1.f, 1.f, 0.82f };
		const glm::vec3 color_Black = { 0.f,0.f,0.f };
		const glm::vec3 color_Blue = { 0.29f, 0.5f, 0.73f };

		unordered_map <uint16_t, Glyph> GlyphMap;

		OpenglTexture texture_MSDF_AtlasSymbols;
		OpenglTexture texture_MSDF_Disigned8080;
		OpenglTexture texture_MSDF_Disigned_seedLBI_production;
		OpenglRenderBuffer BufferRender;
		OpenglVelocityBuffer BufferVelocity;

		vector<uint16_t>
			Word_Lentnyaya_Praktika,
			Word_Edition,
			Word_Emulator,
			Word_Processora,
			Word_Intel_8080,
			Word_Version,
			Word_Avtor_Korzhunov_a_c,
			Word_Gruppa_IM2105B,
			Word_Nauch_ruk_CheridnichenkoOM,
			Word_Update,
			Word_Added,
			Word_Optimazed,
			Word_PressAnyKey,
			Word_ForContinue;
		vector<vector<uint16_t>>
			ListWord_added,
			ListWord_optimazed;

		Structs::MatrixBlock_Data mbd;
		Structs::ValuesBlock_Data vbd;

		UBO<Structs::MatrixBlock_Data>* MatrixBlock;
		UBO<Structs::ValuesBlock_Data>* ValuesBlock;

		Shader* shaderVelocity = nullptr;
		Shader* shaderSolid = nullptr;
		Shader* shaderSolidLeftText = nullptr;
		Shader* shaderSolidRightText = nullptr;
		Shader* shaderSolidRight8080 = nullptr;
		Shader* shaderGradientLeftText = nullptr;
		Shader* shaderGradientRightText = nullptr;
		Shader* shaderGradient_seedLBI = nullptr;
		Shader* shaderFinalImage = nullptr;

		BatchObject LetnayaaPractica_Edition;
		BatchObject AllLeftText;
		BatchObject RightColoredText;
		BatchObject RightText;
		BatchObject RightContinue;
		BatchObject DesignedText8080;
		BatchObject Designed_seedLBI;
		BatchObject LeftSolid;
		BatchObject RightSolid;
		BatchObject FinalSolid;


		enum IDsTextureShader {
			shaderID_MSDF_AtlasMap,
			shaderID_MSDF_8080,
			shaderID_MSDF_seedLBI,
			shaderID_BufferRender,
			shaderID_BufferVelocity
		};

	};
	namespace Functions {


		void LoadCurveData() {
			Vars::curve_seedLBI_move = new CurveBezier{
			{{1.908963, -0.997875},{ 1.560787, -0.094643},{ 0.871204, -0.000677},{ 0.253885, 0.003418},{ -0.048198, 1.062470},{ -0.251042, -0.002586},},
			{{1.681620, -0.998091},{ 1.610787, -0.225678},{ 1.469120, 0.263977},{ 1.404537, -0.002401},{ 0.381620, -0.002401},{ 0.337870, -0.234298},{ 0.189302, 0.363763},{ 0.200760, 1.027125},{ -0.102474, -0.002101},{ -0.189681, -0.002425},}
			};
		}
		void LoadGlyphsInfo() {
			//GlyphMap = ReadGlyphsFromFile("out.csv");
			Vars::GlyphMap[32] = Glyph{ 0.25, Rectanglee { 0.00048828125, 0.99951171875, -0.00048828125, 1.00048828125}, Rectanglee { 0, 0, 0, 0} };
			Vars::GlyphMap[33] = Glyph{ 0.275390625, Rectanglee { 0.953125, 0.208984375, 0.974609375, 0.1171875}, Rectanglee { 0.05613438412547112, -0.01092498190701008, 0.2236507683992386, 0.6809905171394348} };
			Vars::GlyphMap[34] = Glyph{ 0.37841796875, Rectanglee { 0.21484375, 0.9931640625, 0.2529296875, 0.955078125}, Rectanglee { 0.04354256018996239, 0.3896576762199402, 0.3348754048347473, 0.6809905171394348} };
			Vars::GlyphMap[35] = Glyph{ 0.58642578125, Rectanglee { 0.2978515625, 0.6591796875, 0.37109375, 0.5673828125}, Rectanglee { 0.0164466854184866, -0.01092498190701008, 0.5699790716171265, 0.6809905171394348} };
			Vars::GlyphMap[36] = Glyph{ 0.58642578125, Rectanglee { 0.4501953125, 0.1123046875, 0.5205078125, 0.0009765625}, Rectanglee { 0.01443221420049667, -0.09832483530044556, 0.5461146831512451, 0.7392570972442627} };
			Vars::GlyphMap[37] = Glyph{ 0.771484375, Rectanglee { 0.0009765625, 0.740234375, 0.09765625, 0.6474609375}, Rectanglee { 0.02157612703740597, -0.01820830255746841, 0.7499082684516907, 0.6809905171394348} };
			Vars::GlyphMap[38] = Glyph{ 0.716796875, Rectanglee { 0.1201171875, 0.3076171875, 0.2109375, 0.2138671875}, Rectanglee { 0.02218585647642612, -0.01820830255746841, 0.7068180441856384, 0.6882738471031189} };
			Vars::GlyphMap[39] = Glyph{ 0.2138671875, Rectanglee { 0.2548828125, 0.9931640625, 0.271484375, 0.955078125}, Rectanglee { 0.04138370230793953, 0.3896576762199402, 0.1724834889173508, 0.6809905171394348} };
			Vars::GlyphMap[40] = Glyph{ 0.29345703125, Rectanglee { 0.9111328125, 0.603515625, 0.9443359375, 0.4892578125}, Rectanglee { 0.0217118002474308, -0.1784413754940033, 0.2766280472278595, 0.6809905171394348} };
			Vars::GlyphMap[41] = Glyph{ 0.29345703125, Rectanglee { 0.9111328125, 0.7197265625, 0.9443359375, 0.60546875}, Rectanglee { 0.0168289877474308, -0.1784413754940033, 0.2717452347278595, 0.6809905171394348} };
			Vars::GlyphMap[42] = Glyph{ 0.58642578125, Rectanglee { 0.59375, 0.9990234375, 0.6513671875, 0.943359375}, Rectanglee { 0.07471325248479843, 0.258557915687561, 0.5117125511169434, 0.6809905171394348} };
			Vars::GlyphMap[43] = Glyph{ 0.58642578125, Rectanglee { 0.2978515625, 0.9912109375, 0.365234375, 0.9208984375}, Rectanglee { 0.0385407879948616, 0.06919155269861221, 0.548373281955719, 0.6008740067481995} };
			Vars::GlyphMap[44] = Glyph{ 0.24072265625, Rectanglee { 0.2734375, 0.9931640625, 0.291015625, 0.955078125}, Rectanglee { 0.05116977542638779, -0.1565914005041122, 0.1895528733730316, 0.1347414404153824} };
			Vars::GlyphMap[45] = Glyph{ 0.24072265625, Rectanglee { 0.3759765625, 0.998046875, 0.41015625, 0.984375}, Rectanglee { -0.01098259445279837, 0.2002913355827332, 0.2512169778347015, 0.3095411360263824} };
			Vars::GlyphMap[46] = Glyph{ 0.24072265625, Rectanglee { 0.5224609375, 0.9990234375, 0.5400390625, 0.9794921875}, Rectanglee { 0.05116977542638779, -0.01092498190701008, 0.1895528733730316, 0.1420247703790665} };
			Vars::GlyphMap[47] = Glyph{ 0.47900390625, Rectanglee { 0.4501953125, 0.9189453125, 0.51953125, 0.8046875}, Rectanglee { -0.06615464389324188, -0.1784413754940033, 0.4582444727420807, 0.6809905171394348} };
			Vars::GlyphMap[48] = Glyph{ 0.58642578125, Rectanglee { 0.4501953125, 0.2080078125, 0.5205078125, 0.1142578125}, Rectanglee { 0.02810408920049667, -0.01820830255746841, 0.5597865581512451, 0.6882738471031189} };
			Vars::GlyphMap[49] = Glyph{ 0.58642578125, Rectanglee { 0.4501953125, 0.302734375, 0.5205078125, 0.2099609375}, Rectanglee { 0.05764510482549667, -0.01092498190701008, 0.5893275737762451, 0.6882738471031189} };
			Vars::GlyphMap[50] = Glyph{ 0.58642578125, Rectanglee { 0.5224609375, 0.7724609375, 0.58984375, 0.6796875}, Rectanglee { 0.0336579754948616, -0.01092498190701008, 0.543490469455719, 0.6882738471031189} };
			Vars::GlyphMap[51] = Glyph{ 0.58642578125, Rectanglee { 0.4501953125, 0.3984375, 0.5205078125, 0.3046875}, Rectanglee { 0.01662947982549667, -0.01820830255746841, 0.5483119487762451, 0.6882738471031189} };
			Vars::GlyphMap[52] = Glyph{ 0.58642578125, Rectanglee { 0.3759765625, 0.283203125, 0.447265625, 0.1904296875}, Rectanglee { 0.02397414669394493, -0.01092498190701008, 0.5629399418830872, 0.6882738471031189} };
			Vars::GlyphMap[53] = Glyph{ 0.58642578125, Rectanglee { 0.3759765625, 0.3779296875, 0.447265625, 0.28515625}, Rectanglee { 0.03032180294394493, -0.01820830255746841, 0.5692875981330872, 0.6809905171394348} };
			Vars::GlyphMap[54] = Glyph{ 0.58642578125, Rectanglee { 0.4501953125, 0.494140625, 0.5205078125, 0.400390625}, Rectanglee { 0.03030135482549667, -0.01820830255746841, 0.5619838237762451, 0.6882738471031189} };
			Vars::GlyphMap[55] = Glyph{ 0.58642578125, Rectanglee { 0.59375, 0.48046875, 0.66015625, 0.388671875}, Rectanglee { 0.04120588675141335, -0.01092498190701008, 0.543755054473877, 0.6809905171394348} };
			Vars::GlyphMap[56] = Glyph{ 0.58642578125, Rectanglee { 0.3759765625, 0.0947265625, 0.4482421875, 0.0009765625}, Rectanglee { 0.02033248730003834, -0.01820830255746841, 0.5665815472602844, 0.6882738471031189} };
			Vars::GlyphMap[57] = Glyph{ 0.58642578125, Rectanglee { 0.4501953125, 0.58984375, 0.5205078125, 0.49609375}, Rectanglee { 0.02493026107549667, -0.01820830255746841, 0.5566127300262451, 0.6882738471031189} };
			Vars::GlyphMap[58] = Glyph{ 0.24072265625, Rectanglee { 0.0009765625, 0.9970703125, 0.0185546875, 0.93359375}, Rectanglee { 0.05116977542638779, -0.01092498190701008, 0.1895528733730316, 0.4697742164134979} };
			Vars::GlyphMap[59] = Glyph{ 0.24072265625, Rectanglee { 0.9794921875, 0.177734375, 0.9970703125, 0.0947265625}, Rectanglee { 0.05116977542638779, -0.1565914005041122, 0.1895528733730316, 0.4697742164134979} };
			Vars::GlyphMap[60] = Glyph{ 0.58642578125, Rectanglee { 0.4501953125, 0.9931640625, 0.509765625, 0.9208984375}, Rectanglee { 0.05766430869698524, 0.06190823018550873, 0.5092301964759827, 0.6081573367118835} };
			Vars::GlyphMap[61] = Glyph{ 0.58642578125, Rectanglee { 0.3759765625, 0.982421875, 0.443359375, 0.9482421875}, Rectanglee { 0.0385407879948616, 0.2002913355827332, 0.548373281955719, 0.4624908864498138} };
			Vars::GlyphMap[62] = Glyph{ 0.58642578125, Rectanglee { 0.728515625, 0.89453125, 0.7880859375, 0.822265625}, Rectanglee { 0.07719555497169495, 0.06190823018550873, 0.5287614464759827, 0.6081573367118835} };
			Vars::GlyphMap[63] = Glyph{ 0.50146484375, Rectanglee { 0.6630859375, 0.599609375, 0.7255859375, 0.5068359375}, Rectanglee { 0.006456123664975166, -0.01092498190701008, 0.4798719882965088, 0.6882738471031189} };
			Vars::GlyphMap[64] = Glyph{ 0.71728515625, Rectanglee { 0.0009765625, 0.837890625, 0.095703125, 0.7421875}, Rectanglee { 0.001515698968432844, -0.0254916250705719, 0.7152811884880066, 0.695557177066803} };
			Vars::GlyphMap[65] = Glyph{ 0.60302734375, Rectanglee { 0.1201171875, 0.9638671875, 0.201171875, 0.8720703125}, Rectanglee { -0.006094802636653185, -0.01092498190701008, 0.6057041883468628, 0.6809905171394348} };
			Vars::GlyphMap[66] = Glyph{ 0.607421875, Rectanglee { 0.5224609375, 0.396484375, 0.5908203125, 0.3046875}, Rectanglee { 0.06346358358860016, -0.01092498190701008, 0.580579400062561, 0.6809905171394348} };
			Vars::GlyphMap[67] = Glyph{ 0.5791015625, Rectanglee { 0.3759765625, 0.4736328125, 0.447265625, 0.3798828125}, Rectanglee { 0.02812453731894493, -0.01820830255746841, 0.5670903325080872, 0.6882738471031189} };
			Vars::GlyphMap[68] = Glyph{ 0.65478515625, Rectanglee { 0.2978515625, 0.3759765625, 0.373046875, 0.2841796875}, Rectanglee { 0.05921219289302826, -0.01092498190701008, 0.6273112297058105, 0.6809905171394348} };
			Vars::GlyphMap[69] = Glyph{ 0.53662109375, Rectanglee { 0.791015625, 0.0927734375, 0.8505859375, 0.0009765625}, Rectanglee { 0.06401196122169495, -0.01092498190701008, 0.5155778527259827, 0.6809905171394348} };
			Vars::GlyphMap[70] = Glyph{ 0.5078125, Rectanglee { 0.791015625, 0.5166015625, 0.8486328125, 0.4248046875}, Rectanglee { 0.06543590873479843, -0.01092498190701008, 0.5024352073669434, 0.6809905171394348} };
			Vars::GlyphMap[71] = Glyph{ 0.64208984375, Rectanglee { 0.2978515625, 0.4716796875, 0.3720703125, 0.3779296875}, Rectanglee { 0.02843002416193485, -0.01820830255746841, 0.5892457365989685, 0.6882738471031189} };
			Vars::GlyphMap[72] = Glyph{ 0.64111328125, Rectanglee { 0.5224609375, 0.9521484375, 0.58984375, 0.8603515625}, Rectanglee { 0.0656403973698616, -0.01092498190701008, 0.575472891330719, 0.6809905171394348} };
			Vars::GlyphMap[73] = Glyph{ 0.2666015625, Rectanglee { 0.9794921875, 0.0927734375, 0.9970703125, 0.0009765625}, Rectanglee { 0.06410922855138779, -0.01092498190701008, 0.2024923264980316, 0.6809905171394348} };
			Vars::GlyphMap[74] = Glyph{ 0.37158203125, Rectanglee { 0.8525390625, 0.96875, 0.89453125, 0.8759765625}, Rectanglee { -0.007889316417276859, -0.01820830255746841, 0.3125768303871155, 0.6809905171394348} };
			Vars::GlyphMap[75] = Glyph{ 0.61376953125, Rectanglee { 0.3759765625, 0.6611328125, 0.447265625, 0.5693359375}, Rectanglee { 0.06572219729423523, -0.01092498190701008, 0.6046879887580872, 0.6809905171394348} };
			Vars::GlyphMap[76] = Glyph{ 0.49853515625, Rectanglee { 0.791015625, 0.9443359375, 0.84765625, 0.8525390625}, Rectanglee { 0.06346233934164047, -0.01092498190701008, 0.4931782782077789, 0.6809905171394348} };
			Vars::GlyphMap[77] = Glyph{ 0.80078125, Rectanglee { 0.1201171875, 0.4716796875, 0.208984375, 0.3798828125}, Rectanglee { 0.06511370837688446, -0.01092498190701008, 0.7351792454719543, 0.6809905171394348} };
			Vars::GlyphMap[78] = Glyph{ 0.64990234375, Rectanglee { 0.5224609375, 0.0927734375, 0.591796875, 0.0009765625}, Rectanglee { 0.06275160610675812, -0.01092498190701008, 0.5871507525444031, 0.6809905171394348} };
			Vars::GlyphMap[79] = Glyph{ 0.6435546875, Rectanglee { 0.21484375, 0.6318359375, 0.2919921875, 0.5380859375}, Rectanglee { 0.03020035475492477, -0.01820830255746841, 0.6128660440444946, 0.6882738471031189} };
			Vars::GlyphMap[80] = Glyph{ 0.59912109375, Rectanglee { 0.5224609375, 0.490234375, 0.5908203125, 0.3984375}, Rectanglee { 0.06590498983860016, -0.01092498190701008, 0.583020806312561, 0.6809905171394348} };
			Vars::GlyphMap[81] = Glyph{ 0.6435546875, Rectanglee { 0.21484375, 0.7451171875, 0.2919921875, 0.6337890625}, Rectanglee { 0.03020035475492477, -0.1493080854415894, 0.6128660440444946, 0.6882738471031189} };
			Vars::GlyphMap[82] = Glyph{ 0.642578125, Rectanglee { 0.3759765625, 0.7548828125, 0.447265625, 0.6630859375}, Rectanglee { 0.06523391604423523, -0.01092498190701008, 0.6041997075080872, 0.6809905171394348} };
			Vars::GlyphMap[83] = Glyph{ 0.5712890625, Rectanglee { 0.2978515625, 0.7548828125, 0.37109375, 0.6611328125}, Rectanglee { -0.004305267706513405, -0.01820830255746841, 0.5492271184921265, 0.6882738471031189} };
			Vars::GlyphMap[84] = Glyph{ 0.4833984375, Rectanglee { 0.59375, 0.66796875, 0.66015625, 0.576171875}, Rectanglee { -0.00957536231726408, -0.01092498190701008, 0.492973804473877, 0.6809905171394348} };
			Vars::GlyphMap[85] = Glyph{ 0.5947265625, Rectanglee { 0.6630859375, 0.2880859375, 0.7265625, 0.1953125}, Rectanglee { 0.05847852677106857, -0.01820830255746841, 0.5391777157783508, 0.6809905171394348} };
			Vars::GlyphMap[86] = Glyph{ 0.54052734375, Rectanglee { 0.2978515625, 0.8486328125, 0.37109375, 0.7568359375}, Rectanglee { -0.006746673956513405, -0.01092498190701008, 0.5467857122421265, 0.6809905171394348} };
			Vars::GlyphMap[87] = Glyph{ 0.88330078125, Rectanglee { 0.0009765625, 0.0927734375, 0.1181640625, 0.0009765625}, Rectanglee { 0.001253598951734602, -0.01092498190701008, 0.882535457611084, 0.6809905171394348} };
			Vars::GlyphMap[88] = Glyph{ 0.56640625, Rectanglee { 0.2978515625, 0.0927734375, 0.3740234375, 0.0009765625}, Rectanglee { -0.004488062113523483, -0.01092498190701008, 0.5708943009376526, 0.6809905171394348} };
			Vars::GlyphMap[89] = Glyph{ 0.54345703125, Rectanglee { 0.21484375, 0.4423828125, 0.29296875, 0.3505859375}, Rectanglee { -0.02300185151398182, -0.01092498190701008, 0.5669471621513367, 0.6809905171394348} };
			Vars::GlyphMap[90] = Glyph{ 0.53271484375, Rectanglee { 0.59375, 0.1865234375, 0.6611328125, 0.0947265625}, Rectanglee { 0.01144118048250675, -0.01092498190701008, 0.521273672580719, 0.6809905171394348} };
			Vars::GlyphMap[91] = Glyph{ 0.29345703125, Rectanglee { 0.953125, 0.115234375, 0.9775390625, 0.0009765625}, Rectanglee { 0.05668401345610619, -0.1784413754940033, 0.2460503578186035, 0.6809905171394348} };
			Vars::GlyphMap[92] = Glyph{ 0.47900390625, Rectanglee { 0.5224609375, 0.208984375, 0.591796875, 0.0947265625}, Rectanglee { 0.02075942046940327, -0.1784413754940033, 0.5451585650444031, 0.6809905171394348} };
			Vars::GlyphMap[93] = Glyph{ 0.29345703125, Rectanglee { 0.9111328125, 0.953125, 0.935546875, 0.8388671875}, Rectanglee { 0.04740666970610619, -0.1784413754940033, 0.2367730140686035, 0.6809905171394348} };
			Vars::GlyphMap[94] = Glyph{ 0.5, Rectanglee { 0.0205078125, 0.9970703125, 0.0859375, 0.951171875}, Rectanglee { 0.002611220115795732, 0.3313911259174347, 0.4978770613670349, 0.6809905171394348} };
			Vars::GlyphMap[95] = Glyph{ 0.5, Rectanglee { 0.0205078125, 0.94921875, 0.0888671875, 0.93359375}, Rectanglee { -0.008557902649044991, -0.1638747304677963, 0.508557915687561, -0.04005826637148857} };
			Vars::GlyphMap[96] = Glyph{ 0.5, Rectanglee { 0.5224609375, 0.9775390625, 0.5537109375, 0.9541015625}, Rectanglee { 0.09637793153524399, 0.5571740865707397, 0.3367275297641754, 0.7392570972442627} };
			Vars::GlyphMap[97] = Glyph{ 0.54052734375, Rectanglee { 0.6630859375, 0.4326171875, 0.7255859375, 0.3623046875}, Rectanglee { 0.02549909241497517, -0.01820830255746841, 0.4989149570465088, 0.51347416639328} };
			Vars::GlyphMap[98] = Glyph{ 0.53857421875, Rectanglee { 0.728515625, 0.9892578125, 0.7880859375, 0.896484375}, Rectanglee { 0.05937329307198524, -0.01820830255746841, 0.5109391808509827, 0.6809905171394348} };
			Vars::GlyphMap[99] = Glyph{ 0.4658203125, Rectanglee { 0.8525390625, 0.0712890625, 0.9091796875, 0.0009765625}, Rectanglee { 0.02635296247899532, -0.01820830255746841, 0.4560689032077789, 0.51347416639328} };
			Vars::GlyphMap[100] = Glyph{ 0.53857421875, Rectanglee { 0.728515625, 0.234375, 0.7890625, 0.1416015625}, Rectanglee { 0.0242374911904335, -0.01820830255746841, 0.4830867350101471, 0.6809905171394348} };
			Vars::GlyphMap[101] = Glyph{ 0.5244140625, Rectanglee { 0.6630859375, 0.81640625, 0.7255859375, 0.74609375}, Rectanglee { 0.02574323303997517, -0.01820830255746841, 0.4991590976715088, 0.51347416639328} };
			Vars::GlyphMap[102] = Glyph{ 0.31591796875, Rectanglee { 0.9111328125, 0.09375, 0.951171875, 0.0009765625}, Rectanglee { 0.002811973681673408, -0.01092498190701008, 0.3087114691734314, 0.6882738471031189} };
			Vars::GlyphMap[103] = Glyph{ 0.51806640625, Rectanglee { 0.59375, 0.29296875, 0.6611328125, 0.1884765625}, Rectanglee { 0.01461500860750675, -0.1857246905565262, 0.524447500705719, 0.6008740067481995} };
			Vars::GlyphMap[104] = Glyph{ 0.5419921875, Rectanglee { 0.791015625, 0.8505859375, 0.84765625, 0.7587890625}, Rectanglee { 0.05589397624135017, -0.01092498190701008, 0.4856099188327789, 0.6809905171394348} };
			Vars::GlyphMap[105] = Glyph{ 0.24462890625, Rectanglee { 0.9794921875, 0.271484375, 0.99609375, 0.1796875}, Rectanglee { 0.05652042105793953, -0.01092498190701008, 0.1876202076673508, 0.6809905171394348} };
			Vars::GlyphMap[106] = Glyph{ 0.24462890625, Rectanglee { 0.9111328125, 0.8369140625, 0.943359375, 0.7216796875}, Rectanglee { -0.05936333537101746, -0.1857246905565262, 0.1882695853710175, 0.6809905171394348} };
			Vars::GlyphMap[107] = Glyph{ 0.5322265625, Rectanglee { 0.6630859375, 0.193359375, 0.7265625, 0.1015625}, Rectanglee { 0.05603712052106857, -0.01092498190701008, 0.5367363095283508, 0.6809905171394348} };
			Vars::GlyphMap[108] = Glyph{ 0.24462890625, Rectanglee { 0.9794921875, 0.4814453125, 0.99609375, 0.3896484375}, Rectanglee { 0.05652042105793953, -0.01092498190701008, 0.1876202076673508, 0.6809905171394348} };
			Vars::GlyphMap[109] = Glyph{ 0.8701171875, Rectanglee { 0.0009765625, 0.5595703125, 0.1015625, 0.490234375}, Rectanglee { 0.05608174949884415, -0.01092498190701008, 0.8135471343994141, 0.51347416639328} };
			Vars::GlyphMap[110] = Glyph{ 0.54150390625, Rectanglee { 0.8525390625, 0.21484375, 0.9091796875, 0.1455078125}, Rectanglee { 0.05613811686635017, -0.01092498190701008, 0.4858540594577789, 0.51347416639328} };
			Vars::GlyphMap[111] = Glyph{ 0.52880859375, Rectanglee { 0.6630859375, 0.5048828125, 0.7255859375, 0.4345703125}, Rectanglee { 0.02769635803997517, -0.01820830255746841, 0.5011122226715088, 0.51347416639328} };
			Vars::GlyphMap[112] = Glyph{ 0.53857421875, Rectanglee { 0.728515625, 0.421875, 0.7890625, 0.330078125}, Rectanglee { 0.0559757724404335, -0.1784413754940033, 0.5148249864578247, 0.51347416639328} };
			Vars::GlyphMap[113] = Glyph{ 0.54150390625, Rectanglee { 0.728515625, 0.328125, 0.7890625, 0.236328125}, Rectanglee { 0.0257023349404335, -0.1784413754940033, 0.4845515787601471, 0.51347416639328} };
			Vars::GlyphMap[114] = Glyph{ 0.33154296875, Rectanglee { 0.9111328125, 0.2548828125, 0.9462890625, 0.1845703125}, Rectanglee { 0.05788551270961761, -0.01092498190701008, 0.3273684084415436, 0.5207574367523193} };
			Vars::GlyphMap[115] = Glyph{ 0.4541015625, Rectanglee { 0.791015625, 0.3525390625, 0.849609375, 0.2822265625}, Rectanglee { -0.003391296369954944, -0.01820830255746841, 0.440891295671463, 0.51347416639328} };
			Vars::GlyphMap[116] = Glyph{ 0.322265625, Rectanglee { 0.9111328125, 0.1826171875, 0.9501953125, 0.095703125}, Rectanglee { 0.007186056114733219, -0.01820830255746841, 0.3058022260665894, 0.6372905969619751} };
			Vars::GlyphMap[117] = Glyph{ 0.53955078125, Rectanglee { 0.8525390625, 0.3583984375, 0.908203125, 0.2890625}, Rectanglee { 0.05855907499790192, -0.01820830255746841, 0.4809916913509369, 0.5061908364295959} };
			Vars::GlyphMap[118] = Glyph{ 0.4443359375, Rectanglee { 0.728515625, 0.7265625, 0.7880859375, 0.658203125}, Rectanglee { -0.003370847553014755, -0.01092498190701008, 0.4481950700283051, 0.5061908364295959} };
			Vars::GlyphMap[119] = Glyph{ 0.69677734375, Rectanglee { 0.1201171875, 0.2119140625, 0.2119140625, 0.1435546875}, Rectanglee { 0.0021867745090276, -0.01092498190701008, 0.6941022872924805, 0.5061908364295959} };
			Vars::GlyphMap[120] = Glyph{ 0.44140625, Rectanglee { 0.728515625, 0.5625, 0.7890625, 0.494140625}, Rectanglee { -0.008721492253243923, -0.01092498190701008, 0.4501277506351471, 0.5061908364295959} };
			Vars::GlyphMap[121] = Glyph{ 0.44189453125, Rectanglee { 0.791015625, 0.2802734375, 0.849609375, 0.1884765625}, Rectanglee { -0.001194030861370265, -0.1857246905565262, 0.443088561296463, 0.5061908364295959} };
			Vars::GlyphMap[122] = Glyph{ 0.41845703125, Rectanglee { 0.8525390625, 0.7099609375, 0.904296875, 0.6416015625}, Rectanglee { 0.01282298378646374, -0.01092498190701008, 0.4061223268508911, 0.5061908364295959} };
			Vars::GlyphMap[123] = Glyph{ 0.29345703125, Rectanglee { 0.9111328125, 0.37109375, 0.9453125, 0.2568359375}, Rectanglee { 0.01001349929720163, -0.1784413754940033, 0.2722130715847015, 0.6809905171394348} };
			Vars::GlyphMap[124] = Glyph{ 0.5, Rectanglee { 0.9794921875, 0.3876953125, 0.99609375, 0.2734375}, Rectanglee { 0.1844501048326492, -0.1784413754940033, 0.3155498802661896, 0.6809905171394348} };
			Vars::GlyphMap[125] = Glyph{ 0.29345703125, Rectanglee { 0.9111328125, 0.4873046875, 0.9453125, 0.373046875}, Rectanglee { 0.02124396897852421, -0.1784413754940033, 0.2834435403347015, 0.6809905171394348} };
			Vars::GlyphMap[126] = Glyph{ 0.58642578125, Rectanglee { 0.1201171875, 0.9912109375, 0.1865234375, 0.9658203125}, Rectanglee { 0.04193830862641335, 0.2294246107339859, 0.544487476348877, 0.4260742962360382} };
			Vars::GlyphMap[1040] = Glyph{ 0.60302734375, Rectanglee { 0.21484375, 0.0927734375, 0.2958984375, 0.0009765625}, Rectanglee { -0.006094802636653185, -0.01092498190701008, 0.6057041883468628, 0.6809905171394348} };
			Vars::GlyphMap[1041] = Glyph{ 0.59912109375, Rectanglee { 0.5224609375, 0.677734375, 0.58984375, 0.5859375}, Rectanglee { 0.0629548504948616, -0.01092498190701008, 0.572787344455719, 0.6809905171394348} };
			Vars::GlyphMap[1042] = Glyph{ 0.607421875, Rectanglee { 0.5224609375, 0.302734375, 0.5908203125, 0.2109375}, Rectanglee { 0.06346358358860016, -0.01092498190701008, 0.580579400062561, 0.6809905171394348} };
			Vars::GlyphMap[1043] = Glyph{ 0.43505859375, Rectanglee { 0.8525390625, 0.8037109375, 0.90234375, 0.7119140625}, Rectanglee { 0.06478404253721237, -0.01092498190701008, 0.443516731262207, 0.6809905171394348} };
			Vars::GlyphMap[1044] = Glyph{ 0.6025390625, Rectanglee { 0.1201171875, 0.8701171875, 0.203125, 0.759765625}, Rectanglee { -0.01166913937777281, -0.1493080854415894, 0.6146965026855469, 0.6809905171394348} };
			Vars::GlyphMap[1045] = Glyph{ 0.53662109375, Rectanglee { 0.728515625, 0.8203125, 0.7880859375, 0.728515625}, Rectanglee { 0.06401196122169495, -0.01092498190701008, 0.5155778527259827, 0.6809905171394348} };
			Vars::GlyphMap[1046] = Glyph{ 0.806640625, Rectanglee { 0.0009765625, 0.298828125, 0.1162109375, 0.20703125}, Rectanglee { -0.0200275331735611, -0.01092498190701008, 0.8466876745223999, 0.6809905171394348} };
			Vars::GlyphMap[1047] = Glyph{ 0.56689453125, Rectanglee { 0.3759765625, 0.8505859375, 0.447265625, 0.7568359375}, Rectanglee { 0.002245631534606218, -0.01820830255746841, 0.5412114262580872, 0.6882738471031189} };
			Vars::GlyphMap[1048] = Glyph{ 0.658203125, Rectanglee { 0.4501953125, 0.802734375, 0.5205078125, 0.7109375}, Rectanglee { 0.06301619857549667, -0.01092498190701008, 0.5946986675262451, 0.6809905171394348} };
			Vars::GlyphMap[1049] = Glyph{ 0.658203125, Rectanglee { 0.4501953125, 0.708984375, 0.5205078125, 0.591796875}, Rectanglee { 0.06301619857549667, -0.01092498190701008, 0.5946986675262451, 0.8703568577766418} };
			Vars::GlyphMap[1050] = Glyph{ 0.61376953125, Rectanglee { 0.3759765625, 0.5673828125, 0.447265625, 0.4755859375}, Rectanglee { 0.06572219729423523, -0.01092498190701008, 0.6046879887580872, 0.6809905171394348} };
			Vars::GlyphMap[1051] = Glyph{ 0.54541015625, Rectanglee { 0.21484375, 0.5361328125, 0.29296875, 0.4443359375}, Rectanglee { -0.02300185151398182, -0.01092498190701008, 0.5669471621513367, 0.6809905171394348} };
			Vars::GlyphMap[1052] = Glyph{ 0.80078125, Rectanglee { 0.1201171875, 0.5654296875, 0.208984375, 0.4736328125}, Rectanglee { 0.06511370837688446, -0.01092498190701008, 0.7351792454719543, 0.6809905171394348} };
			Vars::GlyphMap[1053] = Glyph{ 0.64111328125, Rectanglee { 0.59375, 0.0927734375, 0.6611328125, 0.0009765625}, Rectanglee { 0.0656403973698616, -0.01092498190701008, 0.575472891330719, 0.6809905171394348} };
			Vars::GlyphMap[1054] = Glyph{ 0.6435546875, Rectanglee { 0.21484375, 0.8408203125, 0.2919921875, 0.7470703125}, Rectanglee { 0.03020035475492477, -0.01820830255746841, 0.6128660440444946, 0.6882738471031189} };
			Vars::GlyphMap[1055] = Glyph{ 0.62353515625, Rectanglee { 0.59375, 0.84765625, 0.6591796875, 0.755859375}, Rectanglee { 0.06413465738296509, -0.01092498190701008, 0.5594004988670349, 0.6809905171394348} };
			Vars::GlyphMap[1056] = Glyph{ 0.59912109375, Rectanglee { 0.5224609375, 0.583984375, 0.5908203125, 0.4921875}, Rectanglee { 0.06590498983860016, -0.01092498190701008, 0.583020806312561, 0.6809905171394348} };
			Vars::GlyphMap[1057] = Glyph{ 0.5791015625, Rectanglee { 0.3759765625, 0.9462890625, 0.447265625, 0.8525390625}, Rectanglee { 0.02812453731894493, -0.01820830255746841, 0.5670903325080872, 0.6882738471031189} };
			Vars::GlyphMap[1058] = Glyph{ 0.4833984375, Rectanglee { 0.59375, 0.57421875, 0.66015625, 0.482421875}, Rectanglee { -0.00957536231726408, -0.01092498190701008, 0.492973804473877, 0.6809905171394348} };
			Vars::GlyphMap[1059] = Glyph{ 0.51318359375, Rectanglee { 0.2978515625, 0.5654296875, 0.3720703125, 0.4736328125}, Rectanglee { -0.02186294458806515, -0.01092498190701008, 0.5389527678489685, 0.6809905171394348} };
			Vars::GlyphMap[1060] = Glyph{ 0.7421875, Rectanglee { 0.1201171875, 0.6640625, 0.208984375, 0.5673828125}, Rectanglee { 0.03606097400188446, -0.03277494385838509, 0.7061265110969543, 0.695557177066803} };
			Vars::GlyphMap[1061] = Glyph{ 0.56640625, Rectanglee { 0.2978515625, 0.1865234375, 0.3740234375, 0.0947265625}, Rectanglee { -0.004488062113523483, -0.01092498190701008, 0.5708943009376526, 0.6809905171394348} };
			Vars::GlyphMap[1062] = Glyph{ 0.64111328125, Rectanglee { 0.21484375, 0.953125, 0.2919921875, 0.8427734375}, Rectanglee { 0.06926285475492477, -0.1493080854415894, 0.6519285440444946, 0.6809905171394348} };
			Vars::GlyphMap[1063] = Glyph{ 0.60595703125, Rectanglee { 0.59375, 0.94140625, 0.6591796875, 0.849609375}, Rectanglee { 0.04582411050796509, -0.01092498190701008, 0.5410899519920349, 0.6809905171394348} };
			Vars::GlyphMap[1064] = Glyph{ 0.93310546875, Rectanglee { 0.0009765625, 0.48828125, 0.1064453125, 0.396484375}, Rectanglee { 0.06985586881637573, -0.01092498190701008, 0.8637378811836243, 0.6809905171394348} };
			Vars::GlyphMap[1065] = Glyph{ 0.93994140625, Rectanglee { 0.0009765625, 0.205078125, 0.1181640625, 0.0947265625}, Rectanglee { 0.06936883181333542, -0.1493080854415894, 0.950650691986084, 0.6809905171394348} };
			Vars::GlyphMap[1066] = Glyph{ 0.64599609375, Rectanglee { 0.1201171875, 0.7578125, 0.208984375, 0.666015625}, Rectanglee { -0.03205426037311554, -0.01092498190701008, 0.6380112767219543, 0.6809905171394348} };
			Vars::GlyphMap[1067] = Glyph{ 0.84765625, Rectanglee { 0.0009765625, 0.931640625, 0.0947265625, 0.83984375}, Rectanglee { 0.07083118706941605, -0.01092498190701008, 0.7773133516311646, 0.6809905171394348} };
			Vars::GlyphMap[1068] = Glyph{ 0.57666015625, Rectanglee { 0.59375, 0.38671875, 0.66015625, 0.294921875}, Rectanglee { 0.06488753110170364, -0.01092498190701008, 0.567436695098877, 0.6809905171394348} };
			Vars::GlyphMap[1069] = Glyph{ 0.61474609375, Rectanglee { 0.2978515625, 0.2822265625, 0.3740234375, 0.1884765625}, Rectanglee { 0.008695531636476517, -0.01820830255746841, 0.5840778946876526, 0.6882738471031189} };
			Vars::GlyphMap[1070] = Glyph{ 0.92138671875, Rectanglee { 0.0009765625, 0.39453125, 0.111328125, 0.30078125}, Rectanglee { 0.06312217563390732, -0.01820830255746841, 0.8934208154678345, 0.6882738471031189} };
			Vars::GlyphMap[1071] = Glyph{ 0.63037109375, Rectanglee { 0.3759765625, 0.1884765625, 0.4482421875, 0.0966796875}, Rectanglee { 0.01813522167503834, -0.01092498190701008, 0.5643842816352844, 0.6809905171394348} };
			Vars::GlyphMap[1072] = Glyph{ 0.54052734375, Rectanglee { 0.6630859375, 0.671875, 0.7255859375, 0.6015625}, Rectanglee { 0.02549909241497517, -0.01820830255746841, 0.4989149570465088, 0.51347416639328} };
			Vars::GlyphMap[1073] = Glyph{ 0.54248046875, Rectanglee { 0.6630859375, 0.099609375, 0.7265625, 0.0009765625}, Rectanglee { 0.03235547989606857, -0.01820830255746841, 0.5130546689033508, 0.7246904373168945} };
			Vars::GlyphMap[1074] = Glyph{ 0.53125, Rectanglee { 0.791015625, 0.4228515625, 0.849609375, 0.3544921875}, Rectanglee { 0.05959698557853699, -0.01092498190701008, 0.5038796067237854, 0.5061908364295959} };
			Vars::GlyphMap[1075] = Glyph{ 0.3720703125, Rectanglee { 0.8525390625, 0.8740234375, 0.89453125, 0.8056640625}, Rectanglee { 0.05900521576404572, -0.01092498190701008, 0.3794713616371155, 0.5061908364295959} };
			Vars::GlyphMap[1076] = Glyph{ 0.48095703125, Rectanglee { 0.5224609375, 0.8583984375, 0.58984375, 0.7744140625}, Rectanglee { -0.01443772576749325, -0.1274581253528595, 0.495394766330719, 0.5061908364295959} };
			Vars::GlyphMap[1077] = Glyph{ 0.5244140625, Rectanglee { 0.6630859375, 0.744140625, 0.7255859375, 0.673828125}, Rectanglee { 0.02574323303997517, -0.01820830255746841, 0.4991590976715088, 0.51347416639328} };
			Vars::GlyphMap[1078] = Glyph{ 0.6484375, Rectanglee { 0.1201171875, 0.1416015625, 0.212890625, 0.0732421875}, Rectanglee { -0.02049785479903221, -0.01092498190701008, 0.6787009835243225, 0.5061908364295959} };
			Vars::GlyphMap[1079] = Glyph{ 0.46240234375, Rectanglee { 0.8525390625, 0.287109375, 0.9091796875, 0.216796875}, Rectanglee { 0.006333431228995323, -0.01820830255746841, 0.4360493719577789, 0.51347416639328} };
			Vars::GlyphMap[1080] = Glyph{ 0.55078125, Rectanglee { 0.791015625, 0.7568359375, 0.8486328125, 0.6884765625}, Rectanglee { 0.05689099058508873, -0.01092498190701008, 0.493890255689621, 0.5061908364295959} };
			Vars::GlyphMap[1081] = Glyph{ 0.55078125, Rectanglee { 0.791015625, 0.6865234375, 0.8486328125, 0.5888671875}, Rectanglee { 0.05689099058508873, -0.01092498190701008, 0.493890255689621, 0.7246904373168945} };
			Vars::GlyphMap[1082] = Glyph{ 0.501953125, Rectanglee { 0.6630859375, 0.88671875, 0.724609375, 0.818359375}, Rectanglee { 0.05794934555888176, -0.01092498190701008, 0.5240818858146667, 0.5061908364295959} };
			Vars::GlyphMap[1083] = Glyph{ 0.43310546875, Rectanglee { 0.728515625, 0.0693359375, 0.7890625, 0.0009765625}, Rectanglee { -0.01311602350324392, -0.01092498190701008, 0.4457332193851471, 0.5061908364295959} };
			Vars::GlyphMap[1084] = Glyph{ 0.71826171875, Rectanglee { 0.21484375, 0.2783203125, 0.294921875, 0.2099609375}, Rectanglee { 0.05662889033555984, -0.01092498190701008, 0.6611445546150208, 0.5061908364295959} };
			Vars::GlyphMap[1085] = Glyph{ 0.548828125, Rectanglee { 0.791015625, 0.5869140625, 0.8486328125, 0.5185546875}, Rectanglee { 0.05567028746008873, -0.01092498190701008, 0.492669552564621, 0.5061908364295959} };
			Vars::GlyphMap[1086] = Glyph{ 0.52880859375, Rectanglee { 0.6630859375, 0.3603515625, 0.7255859375, 0.2900390625}, Rectanglee { 0.02769635803997517, -0.01820830255746841, 0.5011122226715088, 0.51347416639328} };
			Vars::GlyphMap[1087] = Glyph{ 0.52734375, Rectanglee { 0.8525390625, 0.4990234375, 0.9072265625, 0.4306640625}, Rectanglee { 0.05585308000445366, -0.01092498190701008, 0.4710023999214172, 0.5061908364295959} };
			Vars::GlyphMap[1088] = Glyph{ 0.53857421875, Rectanglee { 0.728515625, 0.65625, 0.7890625, 0.564453125}, Rectanglee { 0.0559757724404335, -0.1784413754940033, 0.5148249864578247, 0.51347416639328} };
			Vars::GlyphMap[1089] = Glyph{ 0.4658203125, Rectanglee { 0.8525390625, 0.1435546875, 0.9091796875, 0.0732421875}, Rectanglee { 0.02635296247899532, -0.01820830255746841, 0.4560689032077789, 0.51347416639328} };
			Vars::GlyphMap[1090] = Glyph{ 0.37255859375, Rectanglee { 0.8525390625, 0.6396484375, 0.9052734375, 0.5712890625}, Rectanglee { -0.01376789528876543, -0.01092498190701008, 0.3868147730827332, 0.5061908364295959} };
			Vars::GlyphMap[1091] = Glyph{ 0.44189453125, Rectanglee { 0.791015625, 0.1865234375, 0.849609375, 0.0947265625}, Rectanglee { -0.001194030861370265, -0.1857246905565262, 0.443088561296463, 0.5061908364295959} };
			Vars::GlyphMap[1092] = Glyph{ 0.66064453125, Rectanglee { 0.21484375, 0.2080078125, 0.294921875, 0.0947265625}, Rectanglee { 0.0280644353479147, -0.1784413754940033, 0.6325801014900208, 0.6737071871757507} };
			Vars::GlyphMap[1093] = Glyph{ 0.44140625, Rectanglee { 0.728515625, 0.4921875, 0.7890625, 0.423828125}, Rectanglee { -0.008721492253243923, -0.01092498190701008, 0.4501277506351471, 0.5061908364295959} };
			Vars::GlyphMap[1094] = Glyph{ 0.541015625, Rectanglee { 0.59375, 0.75390625, 0.6591796875, 0.669921875}, Rectanglee { 0.05632215738296509, -0.1274581253528595, 0.5515879988670349, 0.5061908364295959} };
			Vars::GlyphMap[1095] = Glyph{ 0.50341796875, Rectanglee { 0.8525390625, 0.5693359375, 0.90625, 0.5009765625}, Rectanglee { 0.0392310693860054, -0.01092498190701008, 0.4470970630645752, 0.5061908364295959} };
			Vars::GlyphMap[1096] = Glyph{ 0.79443359375, Rectanglee { 0.1201171875, 0.3779296875, 0.208984375, 0.3095703125}, Rectanglee { 0.06242816150188446, -0.01092498190701008, 0.7324936985969543, 0.5061908364295959} };
			Vars::GlyphMap[1097] = Glyph{ 0.8046875, Rectanglee { 0.0009765625, 0.6455078125, 0.1005859375, 0.5615234375}, Rectanglee { 0.06387380510568619, -0.1274581253528595, 0.814055860042572, 0.5061908364295959} };
			Vars::GlyphMap[1098] = Glyph{ 0.53271484375, Rectanglee { 0.2978515625, 0.9189453125, 0.37109375, 0.8505859375}, Rectanglee { -0.0301841739565134, -0.01092498190701008, 0.5233482122421265, 0.5061908364295959} };
			Vars::GlyphMap[1099] = Glyph{ 0.7236328125, Rectanglee { 0.21484375, 0.3486328125, 0.2939453125, 0.2802734375}, Rectanglee { 0.06344437599182129, -0.01092498190701008, 0.6606767177581787, 0.5061908364295959} };
			Vars::GlyphMap[1100] = Glyph{ 0.4892578125, Rectanglee { 0.8525390625, 0.4287109375, 0.908203125, 0.3603515625}, Rectanglee { 0.05831493437290192, -0.01092498190701008, 0.4807475507259369, 0.5061908364295959} };
			Vars::GlyphMap[1101] = Glyph{ 0.49755859375, Rectanglee { 0.6630859375, 0.958984375, 0.724609375, 0.888671875}, Rectanglee { 0.005214971955865622, -0.01820830255746841, 0.4713475406169891, 0.51347416639328} };
			Vars::GlyphMap[1102] = Glyph{ 0.779296875, Rectanglee { 0.1201171875, 0.0712890625, 0.212890625, 0.0009765625}, Rectanglee { 0.05616230145096779, -0.01820830255746841, 0.7553611397743225, 0.51347416639328} };
			Vars::GlyphMap[1103] = Glyph{ 0.52197265625, Rectanglee { 0.728515625, 0.1396484375, 0.7890625, 0.0712890625}, Rectanglee { 0.00568280415609479, -0.01092498190701008, 0.4645320475101471, 0.5061908364295959} };
		}
		void LoadTextures() {
#ifdef WITH_DEBUG_OUTPUT
			cout << "SetAsCurrent texture atlas from memory\n";
#endif
			Vars::texture_MSDF_AtlasSymbols.ReadFromMemory(MSDF_ATLAS);
#ifdef WITH_DEBUG_OUTPUT
			cout << "SetAsCurrent texture MSDF8080 from memory\n";
#endif
			Vars::texture_MSDF_Disigned8080.ReadFromMemory(MSDF_DESIGN_8080);
#ifdef WITH_DEBUG_OUTPUT
			cout << "SetAsCurrent texture MSDFseedLBI from memory\n";
#endif
			Vars::texture_MSDF_Disigned_seedLBI_production.ReadFromMemory(MSDF_DESIGN_seedLBI_production);
		}
		void InitBuffers() {
			Vars::BufferRender.InitBuffer(OpenglWindow::Vars::Width, OpenglWindow::Vars::Height);
			Vars::BufferRender.SetBG(glm::vec4(Vars::color_Whiteyellow, 1.f));
			Vars::BufferVelocity.Init(OpenglWindow::Vars::Width, OpenglWindow::Vars::Height);
		}
		void BindingTextures() {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, 0);


#ifdef WITH_DEBUG_OUTPUT
			cout << "Binding Atlas Texture as       " << Vars::shaderID_MSDF_AtlasMap << endl;
#endif
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Vars::texture_MSDF_AtlasSymbols.GetTextureID());

#ifdef WITH_DEBUG_OUTPUT
			cout << "Binding MSDF8080 Texture as    "<< Vars::shaderID_MSDF_8080 << endl;
#endif
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, Vars::texture_MSDF_Disigned8080.GetTextureID());

#ifdef WITH_DEBUG_OUTPUT
			cout << "Binding MSDFseedLBI Texture as " <<  Vars::shaderID_MSDF_seedLBI << endl;
#endif
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, Vars::texture_MSDF_Disigned_seedLBI_production.GetTextureID());

#ifdef WITH_DEBUG_OUTPUT
			cout << "Binding Render Texture as      " << Vars::shaderID_BufferRender << endl;
#endif
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, Vars::BufferRender.GetTextureID());

#ifdef WITH_DEBUG_OUTPUT
			cout << "Binding Velocity Texture as    " << Vars::shaderID_BufferVelocity << endl;
#endif
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, Vars::BufferVelocity.GetTextureID());
		}
		void InitWords() {
			Vars::Word_Lentnyaya_Praktika = utf8_to_utf16(u8"Release Edition");
			Vars::Word_Edition = utf8_to_utf16(u8"");

			Vars::Word_Emulator = utf8_to_utf16(u8"Эмулятор");
			Vars::Word_Processora = utf8_to_utf16(u8"Процессора");
			Vars::Word_Intel_8080 = utf8_to_utf16(u8"Intel 8080");

			Vars::Word_Version = utf8_to_utf16(u8"Версия от 08.11.2024");


			Vars::Word_Avtor_Korzhunov_a_c = utf8_to_utf16(u8"Автор:  Коржунов А. С.");
			Vars::Word_Gruppa_IM2105B = utf8_to_utf16(u8"Группа:  ИМ21-05Б");
			

			Vars::Word_Nauch_ruk_CheridnichenkoOM = utf8_to_utf16(u8"Научный  руководитель:  Чередниченко О. М.");
			Vars::Word_Update = utf8_to_utf16(u8"Обновления");
			Vars::Word_Added = utf8_to_utf16(u8"Добавлено:");
			Vars::ListWord_added = {
				{utf8_to_utf16(u8"  * Поиск в редакторе кода")},
				{utf8_to_utf16(u8"  * Многострочные комментарии")},
				{utf8_to_utf16(u8"  * Полная поддержка кирилицы")},
				{utf8_to_utf16(u8"  * Настройки горячих клавиш")},
				{utf8_to_utf16(u8"  * Улучшены возможности .set:")},
				{utf8_to_utf16(u8"  * Автосохранение")},
			};
			Vars::Word_Optimazed = utf8_to_utf16(u8"Исправлено:");
			Vars::ListWord_optimazed = {
				{utf8_to_utf16(u8"  * Неточности эмуляции")},
				{utf8_to_utf16(u8"  * Случайные вылеты")},
				{utf8_to_utf16(u8"  * Работа с окнами")},
				{utf8_to_utf16(u8"  * Руководство")},
			};
			Vars::Word_PressAnyKey = utf8_to_utf16(u8"Нажми на любую кнопку");
			Vars::Word_ForContinue = utf8_to_utf16(u8"чтобы продолжить");

		}
		void LoadShaders() {
#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader velocity\n";
#endif
			Vars::shaderVelocity = new Shader(VelocityObject_vertex, CreatingVelocity_fragment); {
				Vars::shaderVelocity->use();
				Vars::shaderVelocity->BindUniformBlock(Vars::MatrixBlock->GetName(), 0);
			}

#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader solid\n";
#endif
			Vars::shaderSolid = new Shader(DefaultObject_vertex, Solid_fragment); {
				Vars::shaderSolid->use();
				Vars::shaderSolid->set4FloatWithInfo("Color", glm::vec4(Vars::color_Blue, 1.f));

				Vars::shaderSolid->BindUniformBlock(Vars::MatrixBlock->GetName(), 0);
			}

#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader solid for left text\n";
#endif
			Vars::shaderSolidLeftText = new Shader(DefaultObject_vertex, SolidMSDF_fragment); {
				Vars::shaderSolidLeftText->use();
				Vars::shaderSolidLeftText->setInt("MSDF_texture", Vars::IDsTextureShader::shaderID_MSDF_AtlasMap);
				Vars::shaderSolidLeftText->set4Float("bgColor", glm::vec4(Vars::color_Whiteyellow, 1.f));
				Vars::shaderSolidLeftText->set4Float("fgColor", glm::vec4(Vars::color_Black, 1.f));
				Vars::shaderSolidLeftText->setFloat("pxRange", 0.1001f);

				Vars::shaderSolidLeftText->BindUniformBlock(Vars::MatrixBlock->GetName(), 0);
			}
#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader solid for right text\n";
#endif
			Vars::shaderSolidRightText = new Shader(DefaultObject_vertex, SolidMSDF_fragment); {
				Vars::shaderSolidRightText->use();
				Vars::shaderSolidRightText->setInt("MSDF_texture", Vars::IDsTextureShader::shaderID_MSDF_AtlasMap);
				Vars::shaderSolidRightText->set4Float("bgColor", glm::vec4(Vars::color_Blue, 1.f));
				Vars::shaderSolidRightText->set4Float("fgColor", glm::vec4(Vars::color_Whiteyellow, 1.f));
				Vars::shaderSolidRightText->setFloat("pxRange", 1.00f);

				Vars::shaderSolidRightText->BindUniformBlock(Vars::MatrixBlock->GetName(), 0);
				Vars::shaderSolidRightText->BindUniformBlock(Vars::ValuesBlock->GetName(), 1);
			}

#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader solid for 8080\n";
#endif
			Vars::shaderSolidRight8080 = new Shader(DefaultObject_vertex, SolidMSDF_fragment); {
				Vars::shaderSolidRight8080->use();
				Vars::shaderSolidRight8080->setInt("MSDF_texture", Vars::IDsTextureShader::shaderID_MSDF_8080);
				Vars::shaderSolidRight8080->set4Float("bgColor", glm::vec4(Vars::color_Blue, 1.f));
				Vars::shaderSolidRight8080->set4Float("fgColor", glm::vec4(Vars::color_Whiteyellow, 1.f));
				Vars::shaderSolidRight8080->setFloat("pxRange", 1.00f);

				Vars::shaderSolidRight8080->BindUniformBlock(Vars::MatrixBlock->GetName(), 0);
			}

#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader GradientMSDF for left text\n";
#endif
			Vars::shaderGradientLeftText = new Shader(DefaultObject_vertex, GradientMSDF_fragment); {
				Vars::shaderGradientLeftText->use();
				Vars::shaderGradientLeftText->setInt("MSDF_texture", Vars::IDsTextureShader::shaderID_MSDF_AtlasMap);
				Vars::shaderGradientLeftText->set4Float("bgColor", glm::vec4(Vars::color_Whiteyellow, 1.f));
				Vars::shaderGradientLeftText->set4Float("fgColor", glm::vec4(Vars::color_Blue, 1.f));

				Vars::shaderGradientLeftText->BindUniformBlock(Vars::MatrixBlock->GetName(), 0);
				Vars::shaderGradientLeftText->BindUniformBlock(Vars::ValuesBlock->GetName(), 1);
			}

#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader GradientMSDF for right text\n";
#endif
			Vars::shaderGradientRightText = new Shader(DefaultObject_vertex, GradientMSDF_fragment); {
				Vars::shaderGradientRightText->use();
				Vars::shaderGradientRightText->setInt("MSDF_texture", Vars::IDsTextureShader::shaderID_MSDF_AtlasMap);
				Vars::shaderGradientRightText->set4Float("bgColor", glm::vec4(Vars::color_Blue, 1.f));
				Vars::shaderGradientRightText->set4Float("fgColor", glm::vec4(Vars::color_Blue, 1.f));
				Vars::shaderGradientRightText->setFloat("koef", 0.8f);
				//koef
				Vars::shaderGradientRightText->BindUniformBlock(Vars::MatrixBlock->GetName(), 0);
				Vars::shaderGradientRightText->BindUniformBlock(Vars::ValuesBlock->GetName(), 1);
			}

#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader GradientMSDF for seedLBI\n";
#endif
			Vars::shaderGradient_seedLBI = new Shader(DefaultObject_vertex, GradientMSDF_fragment); {
				Vars::shaderGradient_seedLBI->use();
				Vars::shaderGradient_seedLBI->setInt("MSDF_texture", Vars::IDsTextureShader::shaderID_MSDF_seedLBI);
				Vars::shaderGradient_seedLBI->set4Float("bgColor", glm::vec4(Vars::color_Whiteyellow, 1.f));
				Vars::shaderGradient_seedLBI->set4Float("fgColor", glm::vec4(Vars::color_Blue, 1.f));
				Vars::shaderGradient_seedLBI->setFloat("pxRange", 1.f);

				Vars::shaderGradient_seedLBI->BindUniformBlock(Vars::MatrixBlock->GetName(), 0);
				Vars::shaderGradient_seedLBI->BindUniformBlock(Vars::ValuesBlock->GetName(), 1);
			}

#ifdef WITH_DEBUG_OUTPUT
			cout << "Creating shader FinalImage\n";
#endif
			Vars::shaderFinalImage = new Shader(DefaultObject_vertex, FinalImage_fragment); {
				Vars::shaderFinalImage->use();
				Vars::shaderFinalImage->setInt("currentFrame", Vars::IDsTextureShader::shaderID_BufferRender);
				Vars::shaderFinalImage->setInt("velocityBuffer", Vars::IDsTextureShader::shaderID_BufferVelocity);
				Vars::shaderFinalImage->BindUniformBlock(Vars::ValuesBlock->GetName(), 1);
				Vars::shaderFinalImage->setFloat("blurStrength", 0.1f);
				Vars::shaderFinalImage->setMat4("model", glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(3.f, 3.f, 1.f)), glm::vec3(-0.5f, -0.5f, 0.f)));
			}

		}
		void SetUBO() {
			Vars::MatrixBlock = new UBO<Structs::MatrixBlock_Data>();
			Vars::ValuesBlock = new UBO<Structs::ValuesBlock_Data>();

			Vars::MatrixBlock->SetName("MatrixBlock");
			Vars::ValuesBlock->SetName("ValuesBlock");

			Vars::mbd.view = Vars::view;
			Vars::mbd.proj = Vars::proj;

			Vars::vbd.Resolution[0] = OpenglWindow::Vars::Width;
			Vars::vbd.Resolution[1] = OpenglWindow::Vars::Height;
			Vars::vbd.Time = 0.f;
			Vars::vbd.Time2 = 0.f;

			Vars::MatrixBlock->Bind(0);
			Vars::ValuesBlock->Bind(1);

			Vars::MatrixBlock->Update(Vars::mbd);
			Vars::ValuesBlock->Update(Vars::vbd);


		}
		void CreateBatchObjects() {
			glm::vec2 Sizes_LetnyaaPractica = GetSizesWord(Vars::Word_Lentnyaya_Praktika, Vars::GlyphMap);
			glm::vec2 Sizes_Emulator = GetSizesWord(Vars::Word_Emulator, Vars::GlyphMap);
			glm::vec2 Sizes_Processora = GetSizesWord(Vars::Word_Processora, Vars::GlyphMap);

			const float size_Let_prac_Edition = (127.95f) / 1080.f;
			const float size_Emul_Proc_Intel = (135.17f) / 1080.f;
			const float size_Version = (60.f) / 1080.f;
			const float size_Avtor_Grupp = (39.5f) / 1080.f;


			{
				const glm::vec2 offset = glm::vec2(-0.896014 + 0.0018, 0.441496 - 0.0044) / size_Let_prac_Edition;

				Vars::LetnayaaPractica_Edition.AddGlyphs(
					Vars::Word_Lentnyaya_Praktika,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Let_prac_Edition, size_Let_prac_Edition, 1.f)), glm::vec3(offset.x, offset.y -0.2f, 0.f)),
					1.f
				);
				Vars::LetnayaaPractica_Edition.AddGlyphs(
					Vars::Word_Edition,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Let_prac_Edition, size_Let_prac_Edition, 1.f)), glm::vec3(0, -Sizes_LetnyaaPractica.y * 1.1f, 0.f) + glm::vec3(offset.x, offset.y, 0.f)),
					0.955f
				);

				Vars::LetnayaaPractica_Edition.Init();
			}
			{
				const glm::vec2 offsetE = glm::vec2(-0.902514 + 0.00115, 0.1475 - 0.01375) / size_Emul_Proc_Intel;
				const glm::vec2 offsetV = glm::vec2(-0.899443, -0.27839) / size_Version;
				const glm::vec2 offsetA = glm::vec2(-0.892642, -0.516931) / size_Avtor_Grupp ;
				const glm::vec2 offsetG = glm::vec2(-0.467971, -0.51708) / size_Avtor_Grupp ;

				Vars::AllLeftText.AddGlyphs(
					Vars::Word_Emulator,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Emul_Proc_Intel, size_Emul_Proc_Intel, 1.f)), glm::vec3(offsetE.x, offsetE.y, 0.f)),
					1.f);
				Vars::AllLeftText.AddGlyphs(
					Vars::Word_Processora,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Emul_Proc_Intel, size_Emul_Proc_Intel, 1.f)), glm::vec3(0.f, -Sizes_Emulator.y * 1.16f, 0.f) + glm::vec3(offsetE.x, offsetE.y, 0.f)),
					1.f);
				Vars::AllLeftText.AddGlyphs(
					Vars::Word_Intel_8080,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Emul_Proc_Intel, size_Emul_Proc_Intel, 1.f)), glm::vec3(0.f, -Sizes_Emulator.y * 1.16f - Sizes_Processora.y * 1.19f, 0.f) + glm::vec3(offsetE.x, offsetE.y, 0.f)),
					0.985f);

				Vars::AllLeftText.AddGlyphs(
					Vars::Word_Version,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Version, size_Version, 1.f)), glm::vec3(offsetV.x, offsetV.y, 0.f)),
					0.985f);
				Vars::AllLeftText.AddGlyphs(
					Vars::Word_Avtor_Korzhunov_a_c,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Avtor_Grupp, size_Avtor_Grupp, 1.f)), glm::vec3(offsetA.x, offsetA.y + 0.15f, 0.f)),
					1.055f);
				Vars::AllLeftText.AddGlyphs(
					Vars::Word_Gruppa_IM2105B,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Avtor_Grupp, size_Avtor_Grupp, 1.f)), glm::vec3(offsetG.x, offsetG.y + 0.15f, 0.f)),
					1.015f);

				/*
				Vars::AllLeftText.AddGlyphs(
					Vars::Word_Nauch_ruk_CheridnichenkoOM,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(size_Avtor_Grupp, size_Avtor_Grupp, 1.f)), glm::vec3(offsetA.x, offsetA.y - 1.4f, 0.f)),
					1.055f);
					*/



				Vars::AllLeftText.Init();
			}
			{

				Vars::RightColoredText.AddGlyphs(
					Vars::Word_Added,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((40.5f) / 1080.f, (40.5f) / 1080.f, 1.f)), glm::vec3(9.84221 - 2.71282 + 1.55, 5.58108 + 0.9 - 0.947842, 0.f)),
					1.f);

				Vars::RightColoredText.AddGlyphs(
					Vars::Word_Optimazed,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((40.5f) / 1080.f, (40.5f) / 1080.f, 1.f)), glm::vec3(9.84221 - 2.71282 + 1.55 - 0.0688341, 5.58108 + 0.9 - 0.947842 - 8.9500, 0.f)),
					1.f);

				Vars::RightColoredText.Init();
			}
			{


				glm::vec2 offsett(0.f, 0.f);
				for (int i = Vars::ListWord_added.size() - 1; i >= 0; i--) {
					Vars::RightText.AddGlyphs(
						Vars::ListWord_added[i],
						Vars::GlyphMap,
						glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((38.5f) / 1080.f, (38.5f) / 1080.f, 1.f)), glm::vec3(9.84221 - 0.25, 5.58108 - 6.10001 + offsett.y, 0.f)),
						0.955f);
					offsett.y += GetSizesWord(Vars::ListWord_added[i], Vars::GlyphMap).y * 1.17f;
				}
				offsett = glm::vec2(0.f, 0.f);
				for (int i = Vars::ListWord_optimazed.size() - 1; i >= 0; i--) {


					Vars::RightText.AddGlyphs(
						Vars::ListWord_optimazed[i],
						Vars::GlyphMap,
						glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((38.5f) / 1080.f, (38.5f) / 1080.f, 1.f)), glm::vec3(9.84221 - 0.25, 5.58108 - 6.10001 + offsett.y - 7.61801, 0.f)),
						0.955f);

					offsett.y += GetSizesWord(Vars::ListWord_optimazed[i], Vars::GlyphMap).y * 1.17f;
				}

				Vars::RightText.AddGlyphs(
					Vars::Word_Update,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((54.5f) / 1080.f, (54.5f) / 1080.f, 1.f)), glm::vec3(9.84221, 5.58108, 0.f)),
					0.955f);

				Vars::RightText.AddGlyphs(
					Vars::Word_Added,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((40.5f) / 1080.f, (40.5f) / 1080.f, 1.f)), glm::vec3(9.84221 - 2.71282 + 1.55, 5.58108 + 0.9 - 0.947842, 0.f)),
					1.f);

				Vars::RightText.AddGlyphs(
					Vars::Word_Optimazed,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((40.5f) / 1080.f, (40.5f) / 1080.f, 1.f)), glm::vec3(9.84221 - 2.71282 + 1.55 - 0.0688341, 5.58108 + 0.9 - 0.947842 - 8.9500, 0.f)),
					1.f);

				Vars::RightText.Init();
			}
			{
				Vars::RightContinue.AddGlyphs(
					Vars::Word_PressAnyKey,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((54.5f) / 1080.f, (54.5f) / 1080.f, 1.f)), glm::vec3(7.43813, -9.28191, 0.f)),
					0.955f);

				Vars::RightContinue.AddGlyphs(
					Vars::Word_ForContinue,
					Vars::GlyphMap,
					glm::translate(glm::scale(glm::mat4(1.f), glm::vec3((54.5f) / 1080.f, (54.5f) / 1080.f, 1.f)), glm::vec3(8.73713, -10.135, 0.f)),
					0.955f);

				Vars::RightContinue.Init();
			}
			{
				Vars::DesignedText8080.AddRectangle(glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(0.235f, 0.235f, 1.f)), glm::vec3(1.56793 + 0.0815001, 1.18986 + 0.1215, -0.2f)));
				Vars::DesignedText8080.AddRectangle(glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(0.235f, 0.235f, 1.f)), glm::vec3(1.56793 + 0.0815001 + 1.0178, 1.18986 + 0.1215, -0.2f)));
				Vars::DesignedText8080.Init();
			}
			{
				Vars::Designed_seedLBI.AddRectangle(glm::translate(glm::mat4(1.f), glm::vec3(-0.5f, 0.f, 0.f)));
				Vars::Designed_seedLBI.Init();
			}
			{
				Vars::LeftSolid.AddRectangle(glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(2.f, 4.f, 1.f)), glm::vec3(-0.867f, -0.5f, 0.f)));
				Vars::LeftSolid.Init();
			}
			{
				Vars::RightSolid.AddRectangle(glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(1.f, 4.f, 1.f)), glm::vec3(0.265f, -0.5f, -1.3f)));
				Vars::RightSolid.Init();
			}
			{
				Vars::FinalSolid.AddRectangle(glm::translate(glm::scale(glm::mat4(1.f), glm::vec3(3.f, 3.f, 1.f)), glm::vec3(-0.5f, -0.5f, 0.f)));
				Vars::FinalSolid.Init();
			}
		}

		void CheckWindowResizing() {
			if (OpenglWindow::Vars::FrameBufferSizeWasChanged) {

				
				if (OpenglWindow::Vars::Height < OpenglWindow::Vars::Width)
				{
					Vars::aspect = OpenglWindow::Vars::Height / OpenglWindow::Vars::Width;
				}
				else {
					Vars::aspect = OpenglWindow::Vars::Width / OpenglWindow::Vars::Height;
				}
				Vars::proj = glm::ortho(-1.f, 1.f, -1.f * Vars::aspect, 1.f * Vars::aspect, 0.f, 100.f);

				Vars::mbd.proj = Vars::proj;
				Vars::mbd.view = Vars::view;

				Vars::vbd.Resolution[0] = OpenglWindow::Vars::Width;
				Vars::vbd.Resolution[1] = OpenglWindow::Vars::Height;

				Vars::MatrixBlock->Update(Vars::mbd);
				Vars::ValuesBlock->Update(Vars::vbd);

				OpenglWindow::Vars::FrameBufferSizeWasChanged = false;
			}
		}

	};
	namespace Functions_Drawing {

		void Draw_FinalBuffer() {
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, Vars::BufferRender.GetTextureID());
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, Vars::BufferVelocity.GetTextureID());
			Vars::shaderFinalImage->use();
			Vars::shaderFinalImage->setFloat("blurStrength",((1.f/OpenglWindow::GetDeltaTime())/120.f)*0.15f);
			//std::cout << ((1.f/(OpenglWindow::GetDeltaTime()))/120.f)*0.1f << endl;
			Vars::FinalSolid.Draw();
		}

		void Draw_RenderBuffer() {
			Vars::BufferRender.BeginRenderBuffer();



			Vars::shaderSolid->use();

			Vars::shaderSolid->setMat4("model", Vars::MatrixLeftSolid);
			Vars::shaderSolid->set4Float("Color", glm::vec4(Vars::color_Whiteyellow, 1.f));

			Vars::LeftSolid.Draw();

			Vars::shaderSolid->setMat4("model", Vars::MatrixRightSolid);
			Vars::shaderSolid->set4Float("Color", glm::vec4(Vars::color_Blue, 1.f));

			Vars::RightSolid.Draw();





			Vars::AllLeftText.Draw(Vars::shaderSolidLeftText, Vars::LeftObjectsMatrix);
			Vars::LetnayaaPractica_Edition.Draw(Vars::shaderGradientLeftText, Vars::LeftObjectsMatrix);
			Vars::DesignedText8080.Draw(Vars::shaderSolidRight8080, Vars::RightObjectsMatrix);

			Vars::shaderSolidRightText->use();
			Vars::shaderSolidRightText->setMat4("model", Vars::RightObjectsMatrix);
			//if (WordContinue_SetedBlinking)
			Vars::shaderSolidRightText->setBool("BlinkingMode", false);

			Vars::RightText.Draw();

			if (Vars::WordContinue_SetedBlinking)
			{
				Vars::shaderSolidRightText->setBool("BlinkingMode", true);
				Vars::RightContinue.Draw();
			}


			//if (time_animation_seedLBI < 1.9f)
			Vars::Designed_seedLBI.Draw(Vars::shaderGradient_seedLBI, glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.f - 1.5f * Vars::offset_y, -0.3f)));

			Vars::BufferRender.EndRenderBuffer();
		}

		void Draw_VelocityBuffer() {
			Vars::BufferVelocity.DrawBegin(); {

				Vars::shaderVelocity->use();

				Vars::shaderVelocity->setMat4("prev_model", Vars::LeftSolidMatrix_Last);
				Vars::shaderVelocity->setMat4("model", Vars::MatrixLeftSolid);
				Vars::LeftSolid.Draw();

				Vars::shaderVelocity->setMat4("prev_model", Vars::RightSolidMatrix_Last);
				Vars::shaderVelocity->setMat4("model", Vars::MatrixRightSolid);
				Vars::RightSolid.Draw();

				//if (time_animation_seedLBI < 1.9f) {
				Vars::shaderVelocity->setMat4("model", glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.f - 1.5f * Vars::offset_y, -0.3f)));
				Vars::shaderVelocity->setMat4("prev_model", Vars::seedLBIMatrix_Last);
				Vars::Designed_seedLBI.Draw();
				//}
			}

			Vars::seedLBIMatrix_Last = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.f - 1.5f * Vars::offset_y, -0.3f));
			Vars::RightSolidMatrix_Last = glm::translate(glm::mat4(1.f), glm::vec3(Vars::x_offset, 0.f, 0.f));
			Vars::LeftSolidMatrix_Last = Vars::MatrixLeftSolid;
		}
	}


	void Destructor() {
		Intro::Vars::texture_MSDF_AtlasSymbols.~OpenglTexture();
		Intro::Vars::texture_MSDF_Disigned8080.~OpenglTexture();
		Intro::Vars::texture_MSDF_Disigned_seedLBI_production.~OpenglTexture();
		Intro::Vars::BufferRender.~OpenglRenderBuffer();
		Intro::Vars::BufferVelocity.~OpenglVelocityBuffer();

		Intro::Vars::MatrixBlock->~UBO();
		Intro::Vars::ValuesBlock->~UBO();

		Intro::Vars::shaderVelocity->~Shader();
		Intro::Vars::shaderSolid->~Shader();
		Intro::Vars::shaderSolidLeftText->~Shader();
		Intro::Vars::shaderSolidRightText->~Shader();
		Intro::Vars::shaderSolidRight8080->~Shader();
		Intro::Vars::shaderGradientLeftText->~Shader();
		Intro::Vars::shaderGradientRightText->~Shader();
		Intro::Vars::shaderGradient_seedLBI->~Shader();
		Intro::Vars::shaderFinalImage->~Shader();

		Intro::Vars::LetnayaaPractica_Edition.~BatchObject();
		Intro::Vars::AllLeftText.~BatchObject();
		Intro::Vars::RightColoredText.~BatchObject();
		Intro::Vars::RightText.~BatchObject();
		Intro::Vars::RightContinue.~BatchObject();
		Intro::Vars::DesignedText8080.~BatchObject();
		Intro::Vars::Designed_seedLBI.~BatchObject();
		Intro::Vars::LeftSolid.~BatchObject();
		Intro::Vars::RightSolid.~BatchObject();
		Intro::Vars::FinalSolid.~BatchObject();
	}

	void Init() {
		if (Vars::Inited == false) {

			Functions::LoadCurveData();
			Functions::LoadGlyphsInfo();
			Functions::InitWords();
			Functions::CreateBatchObjects();
			Functions::InitBuffers();
			Functions::LoadTextures();
			Intro::Functions::BindingTextures();
			Functions::SetUBO();
			Functions::LoadShaders();

			


			Vars::TimeBegin = glfwGetTime();
#ifdef WITH_DEBUG_OUTPUT
			cout << Vars::TimeBegin << endl;
#endif
			Vars::Inited = true;
		}
		else {
			cout << "Intro was inited\n";
		}
	}


	void Draw() {
		if (!Vars::Inited)
			return;
		Functions_Drawing::Draw_VelocityBuffer();
		Functions_Drawing::Draw_RenderBuffer();
		Functions_Drawing::Draw_FinalBuffer();
	}

	void Update() {
		if (!Vars::Inited)
			return;

		Functions::CheckWindowResizing();




		static bool firstTouch = true;

		
		//if (glfwGetKey(OpenglWindow::Vars::window, GLFW_KEY_Z) == GLFW_PRESS || firstTouch)
		if (firstTouch)
		{
			firstTouch = false;
			Vars::StartTime2 = 0.f;
			Vars::time_animation_lerped_Scene = 0.f;
			Vars::TimeBegin = glfwGetTime();
			Vars::FirstSkip = false;
			Vars::SecondSkip = false;
			Vars::FullSkip = false;
			Vars::BufferRender.SetBG(glm::vec4(Vars::color_Whiteyellow, 1.f));

			Vars::WordContinue_SetedBlinking = false;

		}
		

		if (isAnyKeyDown(OpenglWindow::Vars::window) == GLFW_PRESS)
		{
			if (Vars::Pressed == false)
			{
				//cout << "Pressed" << endl;
				Vars::Pressed = true;

				if (Vars::FirstSkip == false)
				{
					//cout << "First" << endl;
					Vars::TimeBegin -= Vars::ENDTIME_SCENE + 1.75f;
					Vars::FirstSkip = true;
				}
				else if (Vars::FullSkip == false && Vars::time_animation_lerped_Scene >= Vars::ENDTIME_SCENE - 0.55f) {
					Vars::BufferRender.SetBG({ 0.f,0.f,0.f,0.f });
					//cout << "Second" << endl;
					Vars::SecondSkip = true;

					Vars::TimeBegin = glfwGetTime();
					Vars::TimeBegin -= Vars::ENDTIME_SCENE + 1.7f;
					Vars::FullSkip = true;
				}
			}

		}
		else {
			Vars::Pressed = false;
		}


		Vars::time_animation_Scene = (glfwGetTime() - Vars::TimeBegin - 1.3) * 1.f + 0.3f;
		if (Vars::FullSkip) {
			Vars::time_animation_Scene = (glfwGetTime() - Vars::TimeBegin - 1.75) * 2.6f - 1.7f;
		}


		if (Vars::time_animation_lerped_Scene >= Vars::ENDTIME_SCENE - 0.55f)
		{
			if (Vars::StartTime2 <= 0.f)
			{
				Vars::StartTime2 = glfwGetTime();
			}

			Vars::FirstSkip = true;
			Vars::WordContinue_SetedBlinking = true;
		}

		if (Vars::time_animation_Scene > Vars::ENDTIME_SCENE)
		{

			if (Vars::SecondSkip == false)
			{
				Vars::time_animation_Scene = Vars::ENDTIME_SCENE;
			}

			Vars::FirstSkip = true;
		}



		float TimesLerping = pow(0.06f, OpenglWindow::GetDeltaTime());


		if (Vars::FirstSkip)
		{
			float From = Vars::offset_y;
			float To = 3.5;
			Vars::offset_y = To + TimesLerping * (From - To);
		}
		else {
			Vars::time_animation_seedLBI = Vars::time_animation_Scene + 1.3f - 0.3f;
			float To = 1.f + Vars::curve_seedLBI_move->GetValueFromT(Vars::time_animation_seedLBI) * 0.8f;
			Vars::offset_y = To;
		}




		// a = (a-b)*pow(r,dt) + b   r = 0.05
		Vars::time_animation_lerped_Scene = (Vars::time_animation_lerped_Scene - Vars::time_animation_Scene) * TimesLerping + Vars::time_animation_Scene;

		//cout << time_animation_Scene << "    " << time_animation_lerped_Scene << endl;

		Vars::normalized_time = Vars::time_animation_lerped_Scene / 2.f;
		Vars::revers_time = 1.f - Vars::normalized_time;

		Vars::x_offset = pow(Vars::revers_time, 4.f);
		Vars::x_offset_left = -pow(Vars::revers_time, 4.f);
		if (Vars::FullSkip)
		{
			Vars::x_offset_left = -pow(Vars::revers_time * 1.1f, 4.f);
		}


		Vars::LeftObjectsMatrix = glm::translate(glm::mat4(1.f), glm::vec3(Vars::x_offset_left, 0.f, 0.f));
		Vars::RightObjectsMatrix = glm::translate(glm::mat4(1.f), glm::vec3(Vars::x_offset, 0.f, 0.f));

		Vars::MatrixRightSolid = glm::translate(glm::mat4(1.f), glm::vec3(Vars::x_offset, 0.f, 0.f));
		Vars::MatrixLeftSolid = glm::translate(glm::mat4(1.f), glm::vec3(Vars::x_offset_left, -0.5f, 0.f));


		Vars::vbd.Time = glfwGetTime() + 1.5f;
		Vars::vbd.Time2 = glm::clamp(pow((float)glfwGetTime() - Vars::StartTime2, 1.05f), 0.f, 1.f);
		Vars::ValuesBlock->Update(Vars::vbd);
	}


	bool FirstMoveAchivied() {
		return Vars::time_animation_lerped_Scene >= Vars::ENDTIME_SCENE - 0.55f;
	}

	bool IsEnd() {
		return Vars::time_animation_lerped_Scene > (Vars::ENDTIME_SCENE * 4.f + 0.3f);
	}

};







#endif // !I8080_SCENE_INTRO_H