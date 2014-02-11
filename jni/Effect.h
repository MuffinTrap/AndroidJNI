#ifndef MUFFINTRAP_EFFECT_H
#define MUFFINTRAP_EFFECT_H

#include <string>
#include <GLES2/gl2.h>

/** Class for a complete shared program */

class Effect
{
public:

	Effect(const std::string& vertexShaderSource, const std::string fragmentShaderSource);
	~Effect();

	void apply() const;
	void unapply() const;

	void initialize();
	void deinitialize();

	GLint getAttribIndex(const std::string& attribName);
	GLint getUniformIndex(const std::string& uniformName);

private:

	// Don't allow copying instances
	Effect(const Effect& copy);
	Effect& operator =(const Effect& effect);

	GLuint createShader(const GLenum shaderType, const std::string &shaderSource);
	void linkShaderProgram(GLuint &programObject);

	void destroyShader(GLuint &shaderObject);
	void destroyProgram(GLuint &programObject);


	/** Android shuts down the graphic context when app is
	 * suspended. We save the source to restore the context on revive
	 */
	std::string _vertexSource;
	std::string _fragmentSource;

	GLuint _shaderProgram; 	/**< ID of the shader program */
	GLuint _vertexShader; 	/**< ID of the vertex shader */
	GLuint _fragmentShader; /**< ID of the fragment shader */


};

#endif
