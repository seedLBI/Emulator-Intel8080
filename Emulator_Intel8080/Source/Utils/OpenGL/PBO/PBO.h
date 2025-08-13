#ifndef PBO_H
#define PBO_H

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Config_Compilier.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <iostream>


extern const char* vertex_shader_text;
extern const char* fragment_shader_text;


class PBO {

public:
	PBO(GLFWwindow* window);
	~PBO();

	void fill(unsigned char* src);

	GLuint tex_id;

private:
    GLFWwindow* window;

	GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;

	GLuint vbo_id = 0;
	GLuint vao_id = 0;
	GLuint uv_id = 0;

	GLuint mvp_loc = 0;
	GLuint tex_loc = 0;

	GLuint pbo_ids = 0;
	int pbo_i = 0;
	unsigned char* buffers_data;
	unsigned char* buffers[2];
};








#endif 
