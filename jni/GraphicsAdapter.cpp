#include <android/native_window.h>
#include <GraphicsAdapter.h>

GraphicsAdapter::GraphicsAdapter()
	: _display(EGL_NO_DISPLAY),
	  _surface(EGL_NO_SURFACE),
	  _context(EGL_NO_CONTEXT),
	  _width(0u),
	  _height(0u) { }

GraphicsAdapter::~GraphicsAdapter() { }

void GraphicsAdapter::deinitialise()
{
	eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(_display, _context);
	eglDestroySurface(_display, _surface);
	eglTerminate(_display);

	_context = EGL_NO_CONTEXT;
	_surface = EGL_NO_SURFACE;
	_display = EGL_NO_DISPLAY;
}

unsigned int GraphicsAdapter::height() const
{
	return _height;
}

void GraphicsAdapter::initialise(EGLNativeWindowType windowHandle)
{
	const EGLint CONFIG_ATTRIBUTES[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	const EGLint CONTEXT_ATTRIBUTES[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(_display, NULL, NULL);

	EGLConfig config;
	EGLint configCount = 1;
	eglChooseConfig(_display, CONFIG_ATTRIBUTES, &config, configCount, &configCount);

	_surface = eglCreateWindowSurface(_display, config, windowHandle, NULL);
	_context = eglCreateContext(_display, config, EGL_NO_CONTEXT, CONTEXT_ATTRIBUTES);
	eglMakeCurrent(_display, _surface, _surface, _context);

	eglQuerySurface(_display, _surface, EGL_WIDTH, reinterpret_cast<EGLint*>(&_width));
	eglQuerySurface(_display, _surface, EGL_HEIGHT, reinterpret_cast<EGLint*>(&_height));
}

void GraphicsAdapter::swapBuffers() const
{
	eglSwapBuffers(_display, _surface);
}

unsigned int GraphicsAdapter::width() const
{
	return _width;
}
