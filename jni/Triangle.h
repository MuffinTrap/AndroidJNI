#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <DrawableObject.h>

class Triangle : public DrawableObject
{
public:
	void init();
	void update(float deltaTime);
	void createVertices(Vector3 color, float size);
};

#endif
