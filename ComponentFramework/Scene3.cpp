#include <iostream>
#include <glew.h>
#include"Scene3.h"
#include "ObjLoader.h"

GLuint CreateNoise3D();

Scene3::Scene3() {
}

Scene3::~Scene3() {
}

bool Scene3::OnCreate() {
	noiseTexture = CreateNoise3D();
	skyboxPtr = new Skybox();
	skyboxPtr->OnCreate();
	cameraPtr = new Camera();
	ObjLoader::loadOBJ("sphere.obj");
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("noiseVert.glsl", "noiseFrag.glsl");
	gameobjPtr = new GameObject(meshPtr, shaderPtr, nullptr);
	return true;
}

void Scene3::OnDestroy() {
	if (skyboxPtr) delete skyboxPtr, skyboxPtr = nullptr;
	if (cameraPtr) delete cameraPtr, cameraPtr = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (gameobjPtr) delete gameobjPtr, gameobjPtr = nullptr;
}

void Scene3::HandleEvents(const SDL_Event &sdlEvent) {
	skyboxPtr->HandleEvents(sdlEvent);
}

void Scene3::Update(const float deltaTime_) {
	
	gameobjPtr->Update(deltaTime_);
	
}
	
void Scene3::Render() const {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	GLuint program = skyboxPtr->getShader()->getProgram();
	glUseProgram(program);

	
	glUniformMatrix4fv(skyboxPtr->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(skyboxPtr->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, Matrix4());
	glDepthMask(GL_FALSE);
	skyboxPtr->Render();
	glDepthMask(GL_TRUE);

	program = gameobjPtr->getShader()->getProgram();
	glUseProgram(program);

	glBindTexture(GL_TEXTURE_3D, noiseTexture);
	glUniform1f(gameobjPtr->getShader()->getUniformID("time"), time);
	
	glUniformMatrix4fv(gameobjPtr->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, cameraPtr->getProjectionMatrix());
	glUniformMatrix4fv(gameobjPtr->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, cameraPtr->getViewMatrix());
	gameobjPtr->Render();

	glBindTexture(GL_TEXTURE_3D, 0);
	glUseProgram(0);
}
