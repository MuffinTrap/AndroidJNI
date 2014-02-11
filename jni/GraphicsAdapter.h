#include <EGL/egl.h>

#ifndef GRAPHICSADAPTER_H
#define GRAPHICSADAPTER_H

class GraphicsAdapter
{
public:

	GraphicsAdapter();

	~GraphicsAdapter();

	void deinitialise();

	unsigned int height() const;

	void initialise(EGLNativeWindowType windowHandle);

	void swapBuffers() const;

	unsigned int width() const;

private:

	EGLDisplay _display;
	EGLSurface _surface;
	EGLContext _context;
	unsigned int _width;
	unsigned int _height;

	GraphicsAdapter(const GraphicsAdapter& graphicsAdapter);

	GraphicsAdapter& operator =(const GraphicsAdapter& graphicsAdapter);
};

#endif
