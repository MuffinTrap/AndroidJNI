#include <Vector3.h>
#include <math.h>

Vector3::Vector3()
: x(0.0f)
, y(0.0f)
, z(0.0f)
{

}

Vector3::Vector3(float x, float y, float z)
: x(x)
, y(y)
, z(z)
{

}

Vector3::Vector3(const Vector3& vector)
: x(vector.x)
, y(vector.y)
, z(vector.z)
{

}


void Vector3::normalize()
{
    float magnitude = getMagnitude();
    if( magnitude > 0.0f)
    {
        x = x / magnitude;
        y = y / magnitude;
        z = z / magnitude;
    }
}

float Vector3::getMagnitude()
{
    float result = (x*x) + (y*y) + (z*z);
    if( result > 0.0f)
    {
        return sqrt( result);
    }
    else
    {
        return 0.0f;
    }
}

float Vector3::dot(const Vector3& a, const Vector3& b)
{
    return ( (a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
    return Vector3( ( (a.y * b.z) - (a.z * b.y) ),
                    ( (a.z * b.x) - (a.z * b.z) ),
                    ( (a.x * b.y) - (a.y * b.z) ));

}

void Vector3::setValues(float px, float py, float pz)
{
	x = px;
	y = py;
	z = pz;
}

// Operator overloads

Vector3 Vector3::operator*(const int scalar)
{
    return multiply((float)scalar);
}

Vector3 Vector3::operator*(const float scalar)
{
    return multiply((float)scalar);
}

Vector3 Vector3::operator*(const double scalar)
{
    return multiply((float)scalar);
}

void Vector3::operator*=(const float scalar)
{
    multiplySelf(scalar);
}

Vector3 Vector3::operator+(const Vector3& other)
{
    return Vector3(x+other.x, y+other.y, z+other.z);
}

Vector3 operator+(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x+b.x, a.y+b.y, a.z+b.z);

}

void Vector3::operator+=(const Vector3& other)
{
    x+=other.x;
    y+=other.y;
    z+=other.z;
}

Vector3 Vector3::operator-(const Vector3& other)
{
    return Vector3(x-other.x, y-other.y, z-other.z);
}

Vector3 operator-(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x-b.x, a.y-b.y, a.z-b.z);

}

void Vector3::operator-=(const Vector3& other)
{
    x-=other.x;
    y-=other.y;
    z-=other.z;
}

Vector3& Vector3::operator=(const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

// Private functions

Vector3 Vector3::multiply(const float scalar)
{
    return Vector3(x * scalar, y*scalar, z*scalar);
}

void Vector3::multiplySelf(const float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

