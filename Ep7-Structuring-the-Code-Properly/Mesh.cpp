#include "Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
}

void Mesh::createMesh(GLfloat* vertices, GLint numOfVertices)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])* numOfVertices*3, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderMesh()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Mesh::clearMesh()
{
	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
}

Mesh::~Mesh()
{
	clearMesh();
}