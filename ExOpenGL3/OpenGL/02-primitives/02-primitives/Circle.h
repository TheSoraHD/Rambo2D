#ifndef _CIRCLE_INCLUDE
#define _CIRCLE_INCLUDE


#include "ShaderProgram.h"


// Given a point (x, y) and a size (width, height) in pixels Circle creates 
// a VBO with two triangles. Vertices in the VBO have only a position
// attribute (no colors or texture coordinates)


class Circle
{

public:
	// Circles can only be created inside an OpenGL context
	static Circle *createCircle(float x, float y, float width, float height, ShaderProgram &program);

	Circle(float x, float y, float width, float height, ShaderProgram &program);

	void render() const;
	void free();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation;

};


#endif // _Circle_INCLUDE

