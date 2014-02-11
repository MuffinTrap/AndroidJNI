#include <Triangle.h>

#include <cmath>
#include <Vertex.h>

#include <android/log.h>
#define LOG(message, ...) __android_log_print(ANDROID_LOG_DEBUG, "NativeActivitySample", message, ## __VA_ARGS__)

void Triangle::init()
{
	_position = Vector3(0,0,0);
}

void Triangle::update(float deltaTime)
{

}

void Triangle::createVertices(Vector3 color, float size)
{
	_size = size;
	_vertexAmount = 3;
	_verticesArray = new Vertex[_vertexAmount];
	float cAngle;
	float x;
	float y;
	float nx;
	float ny;
	float cs;
	float sn;

	float pi = M_PI;
	float angle = (pi * 2.0f) / (float)(_vertexAmount);

	cAngle = 0.0f;
	Vector3 vertexPos(0.0f, size, 0.0f);

	for(int i = 0; i < _vertexAmount; i++)
	{
		cs = cos(cAngle);
		sn = sin(cAngle);
		x = vertexPos.x;
		y = vertexPos.y;
		nx = x * cs - y * sn;
		ny = x * sn + y * cs;
		_verticesArray[i].setPos(nx, ny, 0.0f);
		_verticesArray[i].setColor(color.x, color.y, color.z);

		LOG("Triangle vertex at %f : %f : 0.0f:// %f, %f, %f ", nx, ny, color.x, color.y, color.z);

		cAngle += angle;
	}

	_dataArray = new float[7 * _vertexAmount];
	for(int i = 0; i < _vertexAmount; i++)
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

	_indicesAmount = _vertexAmount;
	_indicesArray = new unsigned short[_vertexAmount];
	_indicesArray[0] = 0;
	_indicesArray[1] = 1;
	_indicesArray[2] = 2;
}
