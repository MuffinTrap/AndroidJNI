#include <Vertex.h>

	Vertex::Vertex()
	:
				_x(0.0f),
				_y(0.0f),
				_z(0.0f),
				_r(1.0f),
				_g(1.0f),
				_b(1.0f),
				_a(1.0f)
	{


	}


	Vertex::Vertex(Vector3 position)
	:
			_x(position.x),
			_y(position.y),
			_z(position.z),
			_r(1.0f),
			_g(1.0f),
			_b(1.0f),
			_a(1.0f)
	{


	}

	Vertex::Vertex(Vector3 position, Vector3 color)
	:
				_x(position.x),
				_y(position.y),
				_z(position.z),
				_r(color.x),
				_g(color.y),
				_b(color.z),
				_a(1.0f)
	{


	}

	void Vertex::setPos(GLfloat x, GLfloat y, GLfloat z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	void Vertex::setPos(const Vector3& position)
	{
		_x = position.x;
		_y = position.y;
		_z = position.z;
	}

	void Vertex::setColor(GLfloat r, GLfloat g, GLfloat b)
	{
		_r = r;
		_g = g;
		_b = b;

	}

	void Vertex::setColor(const Vector3& color)
		{
			_r = color.x;
			_g = color.y;
			_b = color.z;

		}
