
#ifndef MUFFINTRAP_VECTOR3
#define MUFFINTRAP_VECTOR3


class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3(const Vector3& other);
    Vector3();
    Vector3(float x, float y, float z );


    void setValues(float px, float py, float pz);
    void normalize();
    float getMagnitude();

    static float dot(const Vector3& a, const Vector3& b);
    static Vector3 cross(const Vector3& a, const Vector3& b);

    // Operator overloads
    Vector3 operator*(const float scalar);
        Vector3 operator*(const int scalar);
        Vector3 operator*(const double scalar);
    void operator*=(const float scalar);

    Vector3 operator+(const Vector3& other);
    void operator+=(const Vector3& other);

    Vector3 operator-(const Vector3& other);
    void operator-=(const Vector3& other);

    Vector3& operator=(const Vector3& other);


private:

    Vector3 multiply(const float scalar);
    void multiplySelf(const float scalar);

};

#endif // MUFFINTRAP_VECTOR3
