#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Skybox.h"
#include "Shader.h"
#include "GameObject.h"

union SDL_Event;
class Scene1 : public Scene {
public:
	explicit Scene1();
	virtual ~Scene1();

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

};


#endif // !SCENE1_H