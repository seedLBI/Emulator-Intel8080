#pragma once
const char* Solid_fragment =
"#version 330 core\n"
"in vec2 TexCoord;\n"
"out vec4 fragColor;\n"
"uniform vec4 Color = vec4(0.29f, 0.5f, 0.73f, 1.f);\n"
"void main() {\n"
"    fragColor = Color;\n"
"}\n";