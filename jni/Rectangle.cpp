#include <Rectangle.h>
#include <GLES2/gl2.h>
#include <Vertex.h>


#include <android/log.h>
#define LOG(message, ...) __android_log_print(ANDROID_LOG_DEBUG, "NativeActivitySample", message, ## __VA_ARGS__)

static Vector3 VERTICES[] =
{
		Vector3(-1.0f, 1.0f, 0.0f),
		Vector3(1.0f, 1.0f, 0.0f),
		Vector3(1.0f, -1.0f, 0.0f),
		Vector3(-1.0f, -1.0f, 0.0f),
};

Rectangle::Rectangle()
{


}

Rectangle::~Rectangle()
{

}

void Rectangle::init()
{
	_direction = Vector3(0,0,0);
	_speed = 0.0f;
	_position = Vector3(0,0,0);
}

void Rectangle::update(float deltaTime)
{
	Vector3 movement = _direction * _speed * deltaTime;
	_position = _position + movement;
}

void Rectangle::createVertices(Vector3 color, float size)
{
	_size = size;
	// Create vertices

	// Create indices
	_vertexAmount = 4;
	_verticesArray = new Vertex[4];
	for(int i = 0; i < 4; i++)
	{
		_verticesArray[i].setPos(VERTICES[i] * size);
		_verticesArray[i].setColor(color.x, color.y, color.z);
	}

	_dataArray = new float[7 * _vertexAmount];
	for(int i = 0; i < 4; i++)
	{
		for(int d = 0; d < 7; d++)
		{
			_dataArray[i*7 +0] = _verticesArray[i]._x;
			_dataArray[i*7 +1] = _verticesArray[i]._y;
			_dataArray[i*7 +2] = _verticesArray[i]._z;
			_dataArray[i*7 +3] = _verticesArray[i]._r;
			_dataArray[i*7 +4] = _verticesArray[i]._g;
			_dataArray[i*7 +5] = _verticesArray[i]._b;
			_dataArray[i*7 +6] = _verticesArray[i]._a;

		}

	}

	for(int i = 0; i < 4; i++)
	{
		for(int d = 0; d < 7; d++)
		{
				LOG("Rectangle pushing vertex data to dataArray %d:%d = %f", i,d, _dataArray[d]);
		}
	}

	for(int i = 0; i < _vertexAmount; i++)
	{

		LOG("Rectangle Vertex %d at %f : %f", i,_verticesArray[i]._x, _verticesArray[i]._y);
		LOG("Rectangle Vertex %d color is %f : %f : %f : %f", i,_verticesArray[i]._r, _verticesArray[i]._g, _verticesArray[i]._b, _verticesArray[i]._a);
	}


	_indicesAmount = 6;

	_indicesArray = new unsigned short[6];
	_indicesArray[0] = 0;
	_indicesArray[1] = 1;
	_indicesArray[2] = 2;
	_indicesArray[3] = 2;
	_indicesArray[4] = 3;
	_indicesArray[5] = 0;

}
