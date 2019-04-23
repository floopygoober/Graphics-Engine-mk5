#include <iostream>
#include <glew.h>
#include"Scene2.h"
#include "ObjLoader.h"

Scene2::Scene2() {
}


Scene2::~Scene2() {
}

bool Scene2::OnCreate() {

	skyboxPtr = new Skybox();
	skyboxPtr->OnCreate();
	cameraPtr = new Camera();
	ObjLoader::loadOBJ("sphere.obj");
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("fresnelVert.glsl", "fresnelFrag.glsl");
	gameobjPtr = new GameObject(meshPtr, shaderPtr, nullptr);
	return true;
}

void Scene2::OnDestroy() {
	if (skyboxPtr) delete skyboxPtr, skyboxPtr = nullptr;
	if (cameraPtr) delete cameraPtr, cameraPtr = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (gameobjPtr) delete gameobjPtr, gameobjPtr = nullptr;
}

void Scene2::HandleEvents(const SDL_Event &sdlEvent) {
	skyboxPtr->HandleEvents(sdlEvent);
}

void Scene2::Update(const float deltaTime_) {}

void Scene2::Render() const {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(skyboxPtr->getShader()->getProgram());
	glUniformMatrix4fv(skyboxPtr->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(skyboxPtr->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, Matrix4());
	glDepthMask(GL_FALSE);
	skyboxPtr->Render();
	glDepthMask(GL_TRUE);

	GLuint program = gameobjPtr->getShader()->getProgram();
	glUseProgram(program);

	glUniformMatrix4fv(gameobjPtr->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(gameobjPtr->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, cameraPtr->getViewMatrix());
	gameobjPtr->Render();
}
