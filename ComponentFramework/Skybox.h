#ifndef SKYBOX_H
#define SKYBOX_H
#include <SDL.h>
#include "MMath.h"
using namespace MATH;


class Shader;
class Skybox
{
public:
	Skybox();
	~Skybox();
	bool OnCreate();
	void OnDestroy();
	void const Render();
	void HandleEvents(const SDL_Event &sdlEvent);
	inline Shader* getShader() const { return shaderPtr; }
	unsigned int textureID;
	class Mesh *meshPtr;

private:
	Matrix4 modelMatrix;
	class Shader *shaderPtr;
	class Trackball *trackballPtr;
};

#endif