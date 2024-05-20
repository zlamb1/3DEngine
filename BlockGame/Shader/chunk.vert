#version 460 core

layout (location = 0) in vec3 v_Pos; 

uniform mat4 m_Projection; 
uniform mat4 m_View; 

void main() {
	gl_Position = m_Projection * m_View * vec4(v_Pos, 1.0); 
}