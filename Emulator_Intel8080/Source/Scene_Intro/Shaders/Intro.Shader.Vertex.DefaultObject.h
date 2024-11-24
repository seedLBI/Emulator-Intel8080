#pragma once
const char* DefaultObject_vertex =
"#version 330 core\n"
"layout(location = 0) in vec2 aPosition;\n"
"layout(location = 1) in vec2 aTexCoord;\n"
"layout(std140) uniform MatrixBlock\n"
"{\n"
"	mat4 view;\n"
"	mat4 proj;\n"
"};\n"
"uniform mat4 model;\n"
"out vec2 TexCoord;\n"
"out float Position_X;\n"
"void main() {\n"
"	Position_X = (aPosition.x + 1.0)/2.0;\n"
"	TexCoord = vec2(aTexCoord.x,aTexCoord.y);\n"
"	gl_Position = proj * view * model * vec4(aPosition,0.f,1.f);\n"
"}\n";