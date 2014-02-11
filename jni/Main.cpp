#include <time.h>
#include <android/input.h>
#include <android/log.h>
#include <android/looper.h>

#include <android_native_app_glue.h>
#include <Game.h>

#define _USE_MATH_DEFINES

#define LOG(message, ...) __android_log_print(ANDROID_LOG_DEBUG, "NativeActivitySample", message, ## __VA_ARGS__)

static const float NANOSECONDS_IN_SECOND = 1000000000.0f;
static const float FRAME_INTERVAL = 1.0f/60.0f;

static bool hasFocus = false;

static void run(android_app* application);
static void processMessage(android_app* application, int32_t message);
static int32_t processInput(android_app* application, AInputEvent* event);

void android_main(android_app* application)
{
	Game game;
	application->userData = &game;
	application->onAppCmd = processMessage;
	application->onInputEvent = processInput;

	run(application);
}

static void run(android_app* application)
{
	bool isRunning = true;
	int id;
	android_poll_source* source;

	timespec previousTime;
	timespec currentTime;
	bool update = false;
	float elapsedTime; // Time in seconds since the previous update
	/** Four different clocks */
	clock_gettime(CLOCK_MONOTONIC, &previousTime);

	Game* game = reinterpret_cast<Game*>(application->userData);

	while(isRunning)
	{
		while((id = ALooper_pollAll(0, NULL, NULL, reinterpret_cast<void**>(&source))) >= 0)
		{
			if(source != NULL)
				source->process(application, source);

			if(application->destroyRequested != 0)
				isRunning = false;
		}

		clock_gettime(CLOCK_MONOTONIC, &currentTime);


		// Combine seconds and nanoseconds
		// Guard against too big deltatimes by always updating.
		elapsedTime = currentTime.tv_sec - previousTime.tv_sec + ((currentTime.tv_nsec - previousTime.tv_nsec) / NANOSECONDS_IN_SECOND);

		if( elapsedTime >= FRAME_INTERVAL)
		{
			update = true;
			previousTime = currentTime;
		}

		if(hasFocus)
		{
			if(update)
			{
				if( elapsedTime > 0.0f)
				{
					game->update(elapsedTime);
					update = false;
				}
			}
			game->draw();
		}
	}
}

static void processMessage(android_app* application, int32_t message)
{
	Game* game = reinterpret_cast<Game*>(application->userData);

	switch(message)
	{
		case APP_CMD_GAINED_FOCUS:
			LOG("Focus gained");
			hasFocus = true;

			break;

		case APP_CMD_INIT_WINDOW:
			LOG("Window created");
			game->initialise(application->window);

			break;

		case APP_CMD_LOST_FOCUS:
			LOG("Focus lost");
			hasFocus = false;

			break;

		case APP_CMD_TERM_WINDOW:
			game->deinitialise();
			LOG("Window destroyed");

			break;
	}
}

static int32_t processInput(android_app* application, AInputEvent* event)
{
	if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		Game* game = reinterpret_cast<Game*>(application->userData);
		game->processTouch(AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));

		return 1;
	}
	else
	{
		return 0;
	}
}
