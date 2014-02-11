#ifndef MUFFINTRAP_CHECKGLERROR
#define MUFFINTRAP_CHECKGLERROR

#include <android/log.h>
#define LOG(message, ...) __android_log_print(ANDROID_LOG_DEBUG, "NativeActivitySample", message, ## __VA_ARGS__)

#include <GLES2/gl2.h>

class CheckGLError
{
public:
	static void checkGLError();



};

#endif
