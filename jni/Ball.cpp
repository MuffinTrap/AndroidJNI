#include <Ball.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

#include <Vertex.h>

#include <android/log.h>
#define LOG(message, ...) __android_log_print(ANDROID_LOG_DEBUG, "NativeActivitySample", message, ## __VA_ARGS__)

	Ball::Ball()
	{
		_position = Vector3(0,0,0);
		_vertexAmount = 0;
		_indicesAmount = 0;

		init();
	}

	Ball::Ball(Vector3 position, float radius)
	{

		_position = position;
		_vertexAmount = 0;
		_indicesAmount = 0;

		init();
	}

	Ball::~Ball()
	{

	}

	void Ball::init()
	{
		_direction = Vector3(0,0,0);
		_speed = 0.0f;
		_position = Vector3(0,0,0);
	}

	void Ball::update(float deltaTime)
	{

	}



	void Ball::createVertices(Vector3 color, float size)
	{
		// Divide circle
		// vertex 0 is center
		// create indices to be a triangle fan
		_size = size;
		int vertexAmount = 12;
		_vertexAmount = vertexAmount + 1;
		_verticesArray = new Vertex[_vertexAmount];


		_verticesArray[0].setPos( 0.0f, 0.0f, 0.0f);
		_verticesArray[0].setColor(color);


		float x;
		float y;
		float nx;
		float ny;
		float cs;
		float sn;

		float cAngle;

		float pi = M_PI;
		float angle = (pi * 2.0f) / (float)(vertexAmount);
		cAngle = 0.0f;
		Vector3 vertexPos(0.0f, size, 0.0f);


		for(int i = 1; i < _vertexAmount; i++)
		{
			cs = cos(cAngle);
			sn = sin(cAngle);
			x = vertexPos.x;
			y = vertexPos.y;
			nx = x * cs - y * sn;
			ny = x * sn + y * cs;
			_verticesArray[i].setPos(nx, ny, 0.0f);
			_verticesArray[i].setColor(color.x, color.y, color.z);
			cAngle += angle;
		}

		for(int i = 0; i < _vertexAmount; i++)
		{

			LOG("Ball Vertex %d at %f : %f", i, _verticesArray[i]._x, _verticesArray[i]._y);
			//LOG("Ball Vertex %d is %f : %f : %f", i,_verticesArray[i]._r, _verticesArray[i]._g, _verticesArray[i]._b);
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

		for(int i = 0; i < _vertexAmount; i++)
			{
				for(int d = 0; d < 7; d++)
				{
						LOG("Ball pushing vertex data to dataArray %d:%d = %f", i,d, _dataArray[d]);
				}
			}

		// Create indices
		// 1 triangle from each vertex
		_indicesAmount = 3 * vertexAmount;
		_indicesArray = new unsigned short[_indicesAmount];
		int triangles = vertexAmount;
		unsigned short indice = 1;

		for(int i = 0; i < triangles; i++)
		{
			_indicesArray[i * 3] = 0; // Middlepoint
			_indicesArray[(i*3)+1] = indice;
			indice++;
			if(indice > vertexAmount)
			{
				indice = 1;
			}
			_indicesArray[(i*3)+2] = indice;
			// No increase, share the vertex
		}

		LOG("Ball has %d indices", _indicesAmount);
		for(int i = 0; i < _indicesAmount; i++)
		{
			LOG("Ball indice at %d", _indicesArray[i]);
		}

	}

	void Ball::randomColors()
	{
		_verticesArray[0].setColor(1.0f, 1.0f, 1.0f);

		/*
		for(int i = 0; i < _vertexAmount; i++)
		{
			float colorR = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float colorG = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			float colorB = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			_verticesArray[i].setColor(colorR, colorG, colorB);
		}
		*/

	}

