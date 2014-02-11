#include <DrawableObject.h>
#include <Vertex.h>



DrawableObject::DrawableObject()
{

}


DrawableObject::~DrawableObject()
{
	if(_vertexAmount > 0)
	{
		delete[] _verticesArray;
		delete[] _indicesArray;
		if(_dataArray != 0)
		{
			delete[] _dataArray;
		}
	}

}

void DrawableObject::setColor(Vector3 color)
{
	_color = color;
}

