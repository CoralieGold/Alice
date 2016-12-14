#version 330 core

in vec2 vVertexTextCoord;

out vec3 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture;

void main() {
	fFragColor = vec3(texture(uTexture, vVertexTextCoord));
};