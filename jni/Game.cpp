#include <GLES2/gl2.h>
#include <Game.h>
#include <Math.h>

#include <Wall.h>

#include <Vertex.h>
#include <DrawableObject.h>
#include <Ball.h>
#include <Triangle.h>
#include <Rectangle.h>


#include <android/log.h>
#define LOG(message, ...) __android_log_print(ANDROID_LOG_DEBUG, "NativeActivitySample", message, ## __VA_ARGS__)

// Default values : these are overwritten by getting the correct ones from the effect
static unsigned int ATTRIB_POSITION = 0u;
static unsigned int ATTRIB_COLOR = 1u;

static unsigned int UNIFORM_MESHPOSITION = 0u;

// SHADERS

static const GLchar* VERTEX_SOURCE =
		"attribute vec3 attrPosition;	\n"
		"attribute vec4 attrColor;		\n"
		"uniform vec3 meshPosition;		\n"
		"								\n"
		"varying vec4 varyColor; 		\n"
		"void main()					\n"
		"{								\n"
		"								\n"
		"gl_Position = vec4(attrPosition, 1.0) + vec4(meshPosition, 1.0); \n"
		"varyColor = attrColor;			\n"
		"}";

static const GLchar* FRAGMENT_SOURCE =
		"varying vec4 varyColor; \n"
		"void main() 			\n"
		"{						\n"
		"	gl_FragColor = varyColor;//vec4(1.0, 0.0, 0.0, 1.0); \n"
		"}";

static const GLfloat VERTICES[] =
{
		1.0f, 1.0, 0.3f,					// 0  oikea yla
		1.0f, 1.0f, 0.0f, 1.0f,				//  red
		0.0f, 1.0f, 0.0f,					// 1  keski yla
		1.0f, 1.0f, 0.0f, 1.0f,				// yellow
		0.0f, 0.5f,	0.0f,				// 2  keski yla-keski
		1.0f, 1.0f, 0.0f, 1.0f,			// blue
		1.0f, 0.5f,	0.0f,				// 3  keski oikea
		1.0f, 1.0f, 0.0f, 1.0f			// cyan
};

static const unsigned short INDICES[] =
{ 0,1,2,
  2,3,0};

static float randomChangeCounter = 0.0f;

static Wall rightWall;
static Wall leftWall;
static Wall topWall;
static Wall bottomWall;

static Ball ball;
static Rectangle box;
static Triangle triangle;

static bool collisionHappened = false;


Game::Game()
{
	_clearColor.red = 0.2f;
	_clearColor.green = 0.2f;
	_clearColor.blue = 0.2f;

	_shaderEffect = new Effect(VERTEX_SOURCE, FRAGMENT_SOURCE);

}

Game::~Game() { }

void Game::deinitialise()
{
	_shaderEffect->deinitialize();
	delete _shaderEffect;
	_graphicsAdapter.deinitialise();
}

void Game::draw()
{
	glClearColor(_clearColor.red, _clearColor.green, _clearColor.blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_shaderEffect->apply();
		//drawStatic();
		drawDrawable(box);
		//drawDrawable(triangle);
		//drawDrawable(ball);

	_shaderEffect->unapply();

	_graphicsAdapter.swapBuffers();
}

void Game::drawDrawable(DrawableObject& object)
{
	// LOG("Drawing object with %d vertices and %d indices", object._vertexAmount, object._indicesAmount);

	GLint positionAttributes = 3;
	GLint colorAttributes = 4;
	GLsizei vertexSize = sizeof(Vertex);//sizeof(GL_FLOAT) * positionAttributes + sizeof(GL_FLOAT) * colorAttributes;
	GLsizei positionSizei = sizeof(GL_FLOAT) * positionAttributes;
	GLuint positionSize = sizeof(GL_FLOAT) * positionAttributes;
	GLuint colorSize = sizeof(GL_FLOAT) * colorAttributes;
						// Position, n elements, type, normalized, bytes to next

	//glEnableVertexAttribArray(ATTRIB_POSITION);
	//glEnableVertexAttribArray(ATTRIB_COLOR);

	//LOG("Drawing drawable to %f,%f,%f", object._position.x, object._position.y, object._position.z);
	glUniform3f(UNIFORM_MESHPOSITION, object._position.x, object._position.y, object._position.z);

	/** Pointer arimethics 101
	 *
	 *  float[] data {2, 1, 0}->   data + 1  =  data[1] = 1.0f
	 *
	 *  Vertex[] vertices {c,b,a} ->  vertices + 1  = vertices[1] = b.x
	 */

	float* positionStart = &object._verticesArray[0]._x;
	float* colorStart = &object._verticesArray[0]._r;

	glVertexAttribPointer(ATTRIB_POSITION, 	positionAttributes, GL_FLOAT, GL_FALSE, vertexSize, positionStart );
	glVertexAttribPointer(ATTRIB_COLOR, 	colorAttributes, 	GL_FLOAT, GL_FALSE, vertexSize, colorStart );

	// The number of indices in the indices array,
	// NOT the number of unique indices
	// LOG("Drawing %d indices", object._indicesAmount);

	glDrawElements(GL_TRIANGLES, object._indicesAmount, GL_UNSIGNED_SHORT, object._indicesArray);

	//glDisableVertexAttribArray(ATTRIB_POSITION);
	//glDisableVertexAttribArray(ATTRIB_COLOR);
}

void Game::drawStatic()
{
	GLint positionAttributes = 3;
	GLint colorAttributes = 4;
	GLsizei vertexSize = sizeof(Vertex);//sizeof(GL_FLOAT) * positionAttributes + sizeof(GL_FLOAT) * colorAttributes;
	GLuint positionSize = sizeof(GL_FLOAT) * positionAttributes;
	GLuint colorSize = sizeof(GL_FLOAT) * colorAttributes;

	glUniform3f(UNIFORM_MESHPOSITION, 0.0f, 0.0f, 0.0f);
						// Position, n elements, type, normalized, bytes to next
	glVertexAttribPointer(ATTRIB_POSITION, positionAttributes, GL_FLOAT, GL_FALSE, vertexSize, VERTICES);
	glVertexAttribPointer(ATTRIB_COLOR,    colorAttributes,    GL_FLOAT, GL_FALSE, vertexSize, VERTICES + 3);

	// The number of indices in the indices array,
	// NOT the number of unique indices
	GLint amountTriangles = 2;
	GLint amountIndices = amountTriangles * 3;
	glDrawElements(GL_TRIANGLES, amountIndices, GL_UNSIGNED_SHORT, INDICES);


}

void Game::initialise(EGLNativeWindowType windowHandle)
{
	_graphicsAdapter.initialise(windowHandle);
	glViewport(0, 0, _graphicsAdapter.width(), _graphicsAdapter.height());
	_shaderEffect->initialize();

	ATTRIB_POSITION = _shaderEffect->getAttribIndex("attrPosition");
	ATTRIB_COLOR = _shaderEffect->getAttribIndex("attrColor");

	UNIFORM_MESHPOSITION = _shaderEffect->getUniformIndex("meshPosition");

	LOG("Index of position attribute is %d ", ATTRIB_POSITION);
	LOG("Index of color attribute is %d ", ATTRIB_COLOR);

	glEnableVertexAttribArray(ATTRIB_POSITION);
	glEnableVertexAttribArray(ATTRIB_COLOR);

	// Balls and walls
	rightWall._position.setValues(0.9f, 0.0f, 0.0f);
	rightWall._normal.setValues(-1.0f, 0.0f, 0.0f);

	triangle.init();
	triangle._position.setValues(-0.5f, -0.5f, 0.0f);
	triangle.createVertices(Vector3(1.0f, 1.0f, 0.0f), 0.5f);


	box.init();
	box._position.setValues(0.1f, 0.1f, 0.1f);
	box.createVertices(Vector3(1.0f, 0.0f, 0.0f), 0.1f);
	box._speed = 0.1f;
	box._direction.setValues(1.0f, 1.0f, 0.0f);
	box._direction.normalize();



	ball.init();
	ball._position.setValues(-0.7f, 0.6f, 0.0f);
	ball.createVertices(Vector3(0.1f, 1.0f, 1.0f), 0.4f);

}

void Game::processTouch(const float locationX, const float locationY)
{
	/*
	_clearColor.red = locationX / _graphicsAdapter.width();
	_clearColor.blue = locationY / _graphicsAdapter.height();
	*/
}

void Game::update(const float elapsedTime)
{
	// Fun fun here!

	if(!collisionHappened)
	{
		box.update(elapsedTime);
		if(box._position.x > 1.0f || box._position.x < -1.0f)
		{

		}
		// Check collision with the right wall
		if(checkCollision(box, rightWall, elapsedTime) )
		{

			if(!collisionHappened)
			{
				collisionHappened = !collisionHappened;
			}
		}
	}
}

bool Game::checkCollision(DrawableObject& object, Wall& wall, float deltaTime)
{
	// wall to object
	Vector3 wTo = object._position - wall._position;
	// wall to objet along wall normal component
	Vector3 wToN = wall._normal * Vector3::dot(wTo, wall._normal);
	float distanceN = wToN.getMagnitude();
	if( (distanceN - object._size) < 0.0f )
	{
		LOG("distance to wall is %f", distanceN );

		// Move ball to collision point
		Vector3 position = object._position;
		LOG("position is %f,%f,%f", position.x, position.y, position.z );
		LOG("direction is %f,%f,%f", object._direction.x, object._direction.y, object._direction.z );
		object.update(-deltaTime);

		// Position and distance along collision line before collision
		Vector3 prevPosition = object._position;
		Vector3 prevwTo = prevPosition - wall._position;
		Vector3 prevwToN = wall._normal * Vector3::dot(prevwTo, wall._normal);
		float distancePrevCollN = prevwToN.getMagnitude();
		LOG("PrevPosition is %f,%f,%f", prevPosition.x, prevPosition.y, prevPosition.z );

		Vector3 movement = position - prevPosition;
		LOG("movement is %f,%f,%f", movement.x, movement.y, movement.z );

		// Projection of the total movement against wall normal
		float movementNdot = Vector3::dot(movement, wall._normal);
		Vector3 movementN = wall._normal * movementNdot;
		float movementNdistance = movementN.getMagnitude();

		float moveDistance = movement.getMagnitude();

		LOG("moveDistance is %f, along collision line is %f", moveDistance, movementNdistance );

		// distanceN must be smaller than size ?!~~   needs work., if object really fast
		// (distance+size)/moveDistance is how much of the movement was spent inside wall
		// 1.0f - this is the amount before wall
		LOG(" distanceN is %f, size is %f, movementNdistance is %f",  distanceN,object._size, movementNdistance);
		float ratio = (object._size - distanceN)/movementNdistance;
		float scaleAmount = 1.0f - ratio;
		LOG("scaleAmount is %f", scaleAmount );
		object.update(deltaTime * scaleAmount);

		// Calculate new direction
		Vector3 directionNormal = wall._normal * Vector3::dot(object._direction, wall._normal);
		LOG("directionNormal is %f,%f,%f", directionNormal.x, directionNormal.y, directionNormal.z );
		LOG("Direction is %f,%f,%f", object._direction.x, object._direction.y, object._direction.z );
		object._direction = object._direction - (directionNormal * 2.0f);
		LOG("new direction is %f,%f,%f", object._direction.x, object._direction.y, object._direction.z );

		// update with the leftover time
		object.update(deltaTime * (1.0f - scaleAmount));
		// Collision!
		LOG("Object collided to wall at %f,%f,%f", wall._position.x, wall._position.y, wall._position.z );
		return true;
	}

	return false;
}

