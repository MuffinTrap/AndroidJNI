#ifndef WALL_H
#define WALL_H

#include <Vector3.h>

class Wall
{
public:

	Wall();
	Wall(Vector3 position, Vector3 normal);

	Vector3 _position;
	Vector3 _normal;
};

#endif
