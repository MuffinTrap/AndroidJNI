#include <CheckGLError.h>

void CheckGLError::checkGLError()
{
	GLenum errorCode = glGetError();

	if(errorCode != GL_NO_ERROR)
	{
		switch(errorCode)
		{
			case GL_INVALID_ENUM:
				LOG("GLenum argument out of range");
			break;

			default:
				LOG("GL error detected");
			break;

		}
	}

}
