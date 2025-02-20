#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>

class Mesh
{
public:
	Mesh()
	{ }


	Mesh(GLfloat* vertices, int count) 
	{
		setup(vertices, count);
	}
	
	~Mesh() {
		layout.clear();
	}

	void setup(GLfloat* vertices, int count)
	{
		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
		vertexCount = count;
	}

	void AddLayout(int element) {
		layout.push_back(element);
		stride += element;
	}

	void Draw() {
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		GenerateLayout();
		glDrawArrays(GL_TRIANGLES, 0,/* vertexCount/ stride*/ 100);
	}

	void BindIndexBuffer(GLint* indexBuffer, GLint indCount) {
		indexCount = indCount;
		glGenBuffers(1, &index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indCount * sizeof(GLuint), indexBuffer, GL_STATIC_DRAW);
	}


	void DrawElements() {
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		GenerateLayout();
		glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, nullptr);
	}

private:
	void GenerateLayout() {
		GLintptr vertexOffset = 0;
		for (unsigned int i = 0; i < layout.size(); i++) {
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (GLvoid*)(vertexOffset));
			vertexOffset += layout[i] * sizeof(float);
		}
	}

	int stride;
	GLuint vboId;
	GLuint vaoId;
	GLuint index_buffer;
	GLfloat* vertices;
	std::vector<int> layout;
	int vertexCount;
	int indexCount;
};

#endif