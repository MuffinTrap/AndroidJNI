#ifndef BALL_H
#define BALL_H

#include <DrawableObject.h>
//#include <Vector3.h>
//#include <Vertex.h>

class Ball : public DrawableObject
{
public:
	Ball();
	Ball(Vector3 position, float radius);
	~Ball();

	void init();
	void update(float deltaTime);

	void createVertices(Vector3 color, float size);

	void randomColors();

};

#endif
