#include <EGL/egl.h>
#include <GraphicsAdapter.h>
#include <Effect.h>

#include <Wall.h>
#include <Ball.h>
#include <Rectangle.h>

#ifndef GAME_H
#define GAME_H

struct Color
{
	float red;
	float green;
	float blue;
};


class Game
{
public:

	Game();

	~Game();

	void deinitialise();
	
	void draw();
	void drawDrawable(DrawableObject& object);
	void drawStatic();

	void initialise(EGLNativeWindowType windowHandle);

	void processTouch(const float locationX, const float locationY);

	void update(const float elapsedTime);
	bool checkCollision(DrawableObject& object, Wall& wall, float deltaTime);

private:

	GraphicsAdapter _graphicsAdapter;
	Color _clearColor;

	Game(const Game& game);
	Effect* _shaderEffect;

	Game& operator =(const Game& game);


};

#endif
