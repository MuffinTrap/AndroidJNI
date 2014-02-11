#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <Vector3.h>

class Vertex;

class DrawableObject
{
public:

	DrawableObject();
	~DrawableObject();

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;

	virtual void createVertices(Vector3 color, float size) = 0;

	void setColor(Vector3 color);

	Vector3 _direction;
	float _speed;
	Vector3 _position;
	float _size;

	Vector3 _color;

	int _vertexAmount;
	Vertex* _verticesArray;

	int _indicesAmount;
	unsigned short* _indicesArray;

	float *_dataArray;


};

#endif
