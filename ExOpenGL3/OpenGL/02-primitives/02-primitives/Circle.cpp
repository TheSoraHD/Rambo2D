#include <GL/glew.h>
#include <GL/gl.h>
#include "Circle.h"


Circle *Circle::createCircle(float x, float y, float radius, ShaderProgram &program)
{
	Circle *circle = new Circle(x, y, radius, program);

	return circle;
}


void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	}
	glEnd();
}


Circle::Circle(float x, float y, float radius, ShaderProgram &program)
{
	float vertices[12] = {x, y, x + width, y, x + width, y + height, x, y, x + width, y + height, x, y + height };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2);
}


void Circle::render() const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Circle::free()
{
	glDeleteBuffers(1, &vbo);
}

