#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Shader.h"
#include "GameObject.h"
#include "Timer.h"

union SDL_Event;
class Scene3 : public Scene {
public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;

private:
	Skybox *skyboxPtr;
	Camera *cameraPtr;
	Mesh *meshPtr;
	Shader *shaderPtr;
	GameObject *gameobjPtr;
	unsigned int noiseTexture;
	float time;
};


#endif 