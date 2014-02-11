#ifndef MUFFINTRAP_VERTEX_H
#define MUFFINTRAP_VERTEX_H

#include <GLES2/gl2.h>
#include <Vector3.h>

class Vertex
{
public:
		Vertex();
		Vertex(Vector3 position);
		Vertex(Vector3 position, Vector3 color);

		void setPos(GLfloat x, GLfloat y, GLfloat z);
		void setPos(const Vector3& position);
		void setColor(GLfloat r, GLfloat g, GLfloat b);
		void setColor(const Vector3& position);


		//GLfloat data[7];


		GLfloat _x;
		GLfloat _y;
		GLfloat _z;

		GLfloat _r;
		GLfloat _g;
		GLfloat _b;
		GLfloat _a;

};

#endif
