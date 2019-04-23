#include <iostream>
#include <glew.h>
#include "Skybox.h"
#include "Camera.h"
#include "Scene1.h"
#include "Shader.h"


Scene1::Scene1() {
}


Scene1::~Scene1() {
}

bool Scene1::OnCreate() {
	
	skyboxPtr = new Skybox();
	skyboxPtr->OnCreate();
	cameraPtr = new Camera();

	return true;
}

void Scene1::OnDestroy() {
	if (skyboxPtr) delete skyboxPtr, skyboxPtr = nullptr;
	if (cameraPtr) delete cameraPtr, cameraPtr = nullptr;
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {
	skyboxPtr->HandleEvents(sdlEvent);
}

void Scene1::Update(const float deltaTime_) {}

void Scene1::Render() const {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(skyboxPtr->getShader()->getProgram());
	glUniformMatrix4fv(skyboxPtr->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(skyboxPtr->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, Matrix4());
	glDepthMask(GL_FALSE);
	skyboxPtr->Render();
	glDepthMask(GL_TRUE);
}
