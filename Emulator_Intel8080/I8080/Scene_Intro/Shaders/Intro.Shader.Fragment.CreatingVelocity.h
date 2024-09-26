#pragma once
const char* CreatingVelocity_fragment =
"#version 330 core\n"
"in vec4 fragPrevPos;\n"
"in vec4 fragCurrPos;\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    vec2 a = (fragCurrPos.xy / fragCurrPos.w) * 0.5 + 0.5;\n"
"    vec2 b = (fragPrevPos.xy / fragPrevPos.w) * 0.5 + 0.5;\n"
"    FragColor = vec4(vec2((a - b) * 15.f),0.f,1.f);\n"
//"    FragColor = fragCurrPos;\n"
"}\n";