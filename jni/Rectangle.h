#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <DrawableObject.h>

class Rectangle : public DrawableObject
{
public:

	Rectangle();
	~Rectangle();

	void init();
	void update(float deltaTime);

	void createVertices(Vector3 color, float size);

	Vector3 _direction;
	float _speed;

};

#endif
