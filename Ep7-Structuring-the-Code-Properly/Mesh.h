#pragma once

#include "GL/glew.h"

class Mesh
{
public:
	Mesh();
	void createMesh(GLfloat* vertices, GLint numOfVertices);
	void renderMesh();
	void clearMesh();
	~Mesh();
private:
	GLuint VAO, VBO;
};

