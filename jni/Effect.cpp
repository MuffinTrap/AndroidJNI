#include <Effect.h>

#include <android/log.h>
												// logs errors
#define LOG_ERROR(message, ...) __android_log_print(ANDROID_LOG_ERROR, "NativeActivitySample", message, ## __VA_ARGS__)

using namespace std;

Effect::Effect(const string& vertexShaderSource, const string fragmentShaderSource)
:
		_vertexSource(vertexShaderSource)
	,	_fragmentSource(fragmentShaderSource)
	,   _shaderProgram(0u)		// Init to zero, which means no program or shader
	,	_vertexShader(0u)
	,	_fragmentShader(0u)
{


}

Effect::~Effect()
{


}

void Effect::apply() const
{
	glUseProgram(_shaderProgram);
}

void Effect::unapply() const
{
	glUseProgram(0u);

}

void Effect::initialize()
{
	_shaderProgram = glCreateProgram();
	if( _shaderProgram == 0u)
	{
		LOG_ERROR("[OpenGL ES 2] Could not create shader program");
	}
	_vertexShader = createShader(GL_VERTEX_SHADER, _vertexSource);
	_fragmentShader = createShader(GL_FRAGMENT_SHADER, _fragmentSource);
	linkShaderProgram(_shaderProgram);
}

void Effect::deinitialize()
{}

/*
 * PRIVATE METHODS
 */

GLuint Effect::createShader(const GLenum shaderType, const string &shaderSource)
{
	const GLuint shaderObject = glCreateShader(shaderType);
	if(shaderObject == 0u)
	{
		LOG_ERROR("[OpenGL ES 2] Could not create shader");
	}
	const GLchar* cShaderSource = shaderSource.c_str();
	// We only have 1 string/line in our source. Null terminated source, no length given.
	glShaderSource(shaderObject, 1, &cShaderSource, NULL);
	glCompileShader(shaderObject);

	// Check if shader compiled
	GLint shaderParameter;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &shaderParameter);
	if(shaderParameter == GL_FALSE)
	{
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &shaderParameter);
		GLchar* log = new char[shaderParameter]; // Length of the log + \0'
								//       how much info,   ref.how many characters were written,  destination
		glGetShaderInfoLog(shaderObject, shaderParameter, NULL, log);

		LOG_ERROR("[OpenGL ES 2] Failed to compile a shader:\n %s", log);
		delete[] log;
		return 0u;
	}

	glAttachShader(_shaderProgram, shaderObject);

	return shaderObject;
}

void Effect::linkShaderProgram(GLuint &programObject)
{
	glLinkProgram(_shaderProgram);
	GLint programParameter;
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &programParameter);

	if(programParameter == GL_FALSE)
	{
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &programParameter);
		GLchar* log = new char[programParameter];
		glGetProgramInfoLog(_shaderProgram, programParameter, NULL, log);
		LOG_ERROR("[OpenGL ES 2] Failed to link a shader:\n %s", log);
		delete[] log;
	}
}

void Effect::destroyShader(GLuint &shaderObject)
{
	glDeleteShader(shaderObject);
	_shaderProgram = 0u;
}

void Effect::destroyProgram(GLuint &programObject)
{
	glDeleteProgram(programObject);
	_shaderProgram = 0u;
}

GLint Effect::getAttribIndex(const string& attribName)
{
	GLint index = glGetAttribLocation(_shaderProgram, attribName.c_str());
	if(index == -1)
	{
		LOG_ERROR("Could not find index for attribute %s", attribName.c_str());
	}
	return index;
}

GLint Effect::getUniformIndex(const string& uniformName)
{
	GLint index = glGetUniformLocation(_shaderProgram, uniformName.c_str());
	if(index == -1)
	{
		LOG_ERROR("Could not find index for uniform %s", uniformName.c_str());
	}
	return index;
}
