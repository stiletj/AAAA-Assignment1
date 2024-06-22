//Main loop

//bind cpp object to lua
//<Class, function name, function pointer: return type (Class::*)(input arguments)>("Class name", "function name", function pointer)

#include <iostream>
#include "Scripting.h"
#include "ECS.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "terrain.h"
#include "GraphicsUtility.h"
#include "WorldPhysics.h"
#include "MeshRenderer.h"
#include "Renderer.h"
#include "Shader.h"
#include "LightingManager.h"
#include "Skybox.h"
#include "UI.h"
#include "InputHandler.h"
#include "Timer.h"

// Window dimensions
const int WIDTH = 1920;
const int HEIGHT = 1080;

// Camera paramete/rs
glm::vec3 cameraPosition = glm::vec3(0, 0, 0);
glm::vec3 cameraFront = glm::vec3(1.0f, 0.0f, 0.0f); // Initial camera front direction
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // Up vector

//Camera camera1(cameraPosition, cameraFront, cameraUp, 0.0, 0.0); 

float cameraSpeed = 1.1f; // Adjust the camera movement speed

// Initial camera angles
float yaw = 0.0f; // Yaw is initialized to face towards negative z-axis
float pitch = 0.0f; // Pitch is initialized to face horizontally

bool renderingMode = true;

// Function to handle keyboard input for player movement and camera control
/*void processInput(GLFWwindow* window)
{
	// Forward/backward movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * cameraFront;

	// Strafe movement
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	// Camera rotation
	const float sensitivity = 0.1f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		yaw -= sensitivity;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		yaw += sensitivity;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		pitch += sensitivity;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		pitch -= sensitivity;

	// Clamp pitch to prevent camera flipping
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// Update camera front vector based on yaw and pitch
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	// Toggle between solid color and wireframe views when 'c' key is pressed
	static bool cKeyPressed = false;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		if (!cKeyPressed) {
			if (renderingMode) {
				// Switch to wireframe
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				renderingMode = 0;
			}
			else {
				// Switch to solid color
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				renderingMode = 1;
			}
			cKeyPressed = true;
		}
	}
	else {
		cKeyPressed = false;
	}
}*/

ECS registry;
MeshLoader loader;
Scripting mainScript;

bool useTerrain = false;

//ECS
// AddEntity
ENTITY AddEntity(Transform trans, bool render)
{
	ENTITY ent(registry.AddEntity(trans, render));

	return ent;
}

// CreateTerrain
ENTITY CreateTerrain(std::string filepath, int size, int patchSize, float zfar, Transform trans, bool render)
{
	ENTITY entity(AddEntity(trans, render));

	registry.AddComponent<Terrain>(entity, filepath, size, patchSize, zfar);

	return entity;
}

void UseTerrain(bool use)
{
	useTerrain = use;
}

// AddMesh
void AddMesh(ENTITY entity, WholeMesh& mesh)
{
	registry.AddComponent<WholeMesh>(entity, mesh.materials, mesh.meshes);
}

// AddPhysicsBody
void AddPhysicsBody(ENTITY entity)
{
	registry.AddComponent<PhysicsBody>(entity);
}

// AddCamera
void AddCamera(ENTITY entity, glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up, double pitch, double yaw)
{
	registry.AddComponent<Camera>(entity, pos, lookAt, up, pitch, yaw);
}

// DeleteEntity
void DeleteEntity(ENTITY entity)
{
	registry.DeleteEntity(entity);
}

// DeleteMesh
void DeleteMesh(ENTITY entity)
{
	registry.DeleteComponent<WholeMesh>(entity);
}

// DeletePhysicsBody
void DeletePhysicsBody(ENTITY entity)
{
	registry.DeleteComponent<PhysicsBody>(entity);
}

// Delete Camera
void DeleteCamera(ENTITY entity)
{
	registry.DeleteComponent<Camera>(entity);
}

// GetMesh
WholeMesh& GetMesh(ENTITY entity)
{
	return registry.GetComponent<WholeMesh>(entity);
}

// GetPhysicsBody
PhysicsBody GetPhysicsBody(ENTITY entity)
{
	return registry.GetComponent<PhysicsBody>(entity);
}

void setEntityPhysicsBody(ENTITY entity, Physics body)
{
	registry.GetComponent<PhysicsBody>(entity).Set(body);
}

// GetCamera
Camera GetCamera(ENTITY entity)
{
	return registry.GetComponent<Camera>(entity);
}

// GetTransform
Transform GetTransform(ENTITY entity)
{
	return registry.GetComponent<Transform>(entity);
}

void SetEntityTransformRotation(ENTITY entity, glm::vec3 rot)
{
	registry.GetComponent<Transform>(entity).m_rot = rot;
}

void SetEntityTransformScale(ENTITY entity, glm::vec3 scale)
{
	registry.GetComponent<Transform>(entity).m_scale = scale;
}

// GetToRender
bool GetToRender(ENTITY entity)
{
	return registry.GetComponent<ToRender>(entity).toRender;
}

//GetTerrain
Terrain& GetTerrain(ENTITY entity)
{
	return registry.GetComponent<Terrain>(entity);
}

//MeshLoader
// LoadMesh
bool LoadMesh(std::string filepath)
{
	return loader.LoadMesh(filepath);
}

// GetMesh
WholeMesh RetrieveMesh()
{
	return loader.GetMesh();
}

//Scripting
// AddScript
bool AddScript(std::string filepath)
{
	if (mainScript.LoadScript("scripts/" + filepath) < 0)
	{
		return false;
	}

	return true;
}


//InputHandling
void BindKey(GUKey key, std::function<void()> func1, std::function<void()> func2, std::function<void()> func3)
{
	InputHandler::bindKey(key, func1, func2, func3);
}

void BindMouse(GUMouseButton mouse, std::function<void()> func1, std::function<void()> func2)
{
	InputHandler::bindMouse(mouse, func1, func2);
}

//GLM
glm::vec3 normalize(glm::vec3 vec)
{
	return glm::normalize(vec);
}

glm::vec3 crossProduct(glm::vec3 a, glm::vec3 b)
{
	return glm::cross(a, b);
}

void MousePosFunc(std::function<void(double, double)> func)
{
	InputHandler::bindMousePos(func);
}

//Physics
void AddForce(PhysicsBody body, glm::vec3 force)
{
	applyForceToRB(body.Get().GetRigidBody(), force);
}

void SetVelocity(PhysicsBody body, glm::vec3 force)
{
	setVelocityToRB(body.Get().GetRigidBody(), force);
}

PhysicsBody getPhysicsBody(ENTITY entity)
{
	return registry.GetComponent<PhysicsBody>(entity);
}

void GetEntityTransform(ENTITY entity)
{
	registry.GetComponent<Transform>(entity);
}

void UpdatePhysicsBody()
{
	ENTITY ent;

	for (entt::entity entity : registry.Contains<PhysicsBody>())
	{
		ent.Set(entity);

		rp3d::Vector3 pos = registry.GetComponent<PhysicsBody>(ent).Get().GetRigidBody()->getTransform().getPosition();

		//std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

		registry.GetComponent<Transform>(ent).m_pos = Vec3ToGLM(pos);
	}
	for (entt::entity entity : registry.Contains<Camera>()) {
		ent.Set(entity);
		//registry.GetComponent<Transform>(ent).m_pos = registry.GetComponent<Camera>(ent).GetPosition();
		//registry.GetComponent<Camera>(ent).SetForwardVector(registry.GetComponent<Transform>(ent).m_rot);
		//registry.GetComponent<Camera>(ent).SetUpVector(registry.GetComponent<Transform>(ent).m_scale);
	}
}

glm::vec3 GetGravity()
{
	return Vec3ToGLM(WorldPhysics::GetGravity());
}

void drawMode(bool wireBool)
{
	if (wireBool)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void empty() {}

void SetLuaObjects()
{
//Set Lua objects
//Data Structures
	//glm::vec3
	mainScript.RegisterCppObject<glm::vec3>(
		"Vector3",
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z);


	//ENTITY
	mainScript.RegisterCppObject<ENTITY,
		char*, unsigned int(ENTITY::*)(),
		char*, void(ENTITY::*)(entt::entity)>("ENTITY",
			"Get", &ENTITY::Get,
			"Set", &ENTITY::Set);

	//bodytype
	mainScript.RegisterCppEnum<
		char*, bodytype,
		char*, bodytype,
		char*, bodytype>("BodyType",
			"STATIC", bodytype::STATIC,
			"KINEMATIC", bodytype::KINEMATIC,
			"DYNAMIC", bodytype::DYNAMIC);

	//Keys
	mainScript.RegisterCppEnum<
		char*, unsigned int>("GUKey",
			"KEY_W", KEY_W);

	//Mouses
	mainScript.RegisterCppEnum<
		char*, unsigned int>("GUMouse",
			"MOUSE_BUTTON_LEFT", MOUSE_BUTTON_LEFT);

//Components
	//Transform
	mainScript.RegisterCppObject<Transform,
		char*, glm::vec3 (Transform::*)(unsigned int),
		char*, void(Transform::*)(unsigned int, glm::vec3)>("Transform",
			"Get", &Transform::Get,
			"Set", &Transform::Set);

	//PhysicsBody
	mainScript.RegisterCppObject<PhysicsBody,
		char*, Physics (PhysicsBody::*)(),
		char*, void (PhysicsBody::*)(Physics&)>("PhysicsBody",
			"Get", &PhysicsBody::Get,
			"Set", &PhysicsBody::Set);

	//WholeMesh
	mainScript.RegisterCppObject<WholeMesh>("WholeMesh");

	//Camera
	mainScript.RegisterCppObject<Camera,
		char*, const glm::vec3(Camera::*)() const,
		char*, const glm::vec3(Camera::*)() const,
		char*, const glm::vec3(Camera::*)() const,
		char*, const double(Camera::*)() const,
		char*, const double(Camera::*)() const,
		char*, void(Camera::*)(glm::vec3, glm::vec3, glm::vec3, double, double)>("Camera",
			"position", &Camera::GetPosition,
			"lookAt", &Camera::GetForwardVector,
			"upVect", &Camera::GetUpVector,
			"pitch", &Camera::GetPitch,
			"yaw", &Camera::GetYaw,
			"Set", &Camera::Set);

	//PointLightSource


	//SpotLightSource


	//DirectionalLightSource


	//Terrain


//Classes
	//Scripting
	mainScript.SetCPPFunction<bool(*)(std::string)>("AddScript", &AddScript);

	//ECS
	mainScript.SetCPPFunction<ENTITY (*)(Transform, bool)>("CreateEntity", &AddEntity);
	//mainScript.SetCPPFunction<ENTITY (*)(std::string, int, Transform, bool)>("CreateTerrain", &AddTerrain);
	mainScript.SetCPPFunction<void (*)(ENTITY, glm::vec3, glm::vec3, glm::vec3, double, double)>("AddCamera", &AddCamera);
	mainScript.SetCPPFunction<void (*)(ENTITY, WholeMesh&)>("AddMesh", &AddMesh);
	mainScript.SetCPPFunction<void (*)(bool)>("UseTerrain", &UseTerrain);
	mainScript.SetCPPFunction<void (*)(ENTITY)>("AddPhysicsBody", &AddPhysicsBody);
	mainScript.SetCPPFunction<PhysicsBody(*)(ENTITY)>("GetPhysicsBody", &GetPhysicsBody);
	mainScript.SetCPPFunction<void (*)(ENTITY, Physics)>("setEntityPhysicsBody", &setEntityPhysicsBody);
	mainScript.SetCPPFunction<Transform(*)(ENTITY)>("GetTransform", &GetTransform);
	mainScript.SetCPPFunction<Camera(*)(ENTITY)>("GetCamera", &GetCamera);
	mainScript.SetCPPFunction<void(*)(ENTITY, glm::vec3)>("SetEntityTransformScale", &SetEntityTransformScale);
	mainScript.SetCPPFunction<void(*)(ENTITY, glm::vec3)>("SetEntityTransformRotation", &SetEntityTransformRotation);

	//Materials
	mainScript.RegisterCppObject<Material,
		char*, void(Material::*)(glm::vec3),
		char*, void(Material::*)(glm::vec3),
		char*, void(Material::*)(float),
		char*, void(Material::*)(glm::vec3),
		char*, const std::string(Material::*)() const,
		char*, void(Material::*)(std::string),
		char*, void(Material::*)(std::string) >("Material",
			"SetAmbientColour", &Material::SetAmbient,
			"SetSpecularColour", &Material::SetSpecular,
			"SetSpecularExponent", &Material::SetSpecularExponent,
			"SetDiffuseColour", &Material::SetDiffuse,
			"name", &Material::GetName,
			"SetName", &Material::SetName,
			"SetTexture", &Material::SetTextureFile);

	//MeshLoader
	mainScript.SetCPPFunction<bool(*)(std::string)>("LoadMesh", &LoadMesh);
	mainScript.SetCPPFunction<WholeMesh(*)()>("GetMesh", &RetrieveMesh);

	//Physics
	mainScript.RegisterCppObject<Physics,
		char*, void(Physics::*)(glm::vec3, float, bodytype, bool),
		char*, void(Physics::*)(glm::vec3, glm::vec3),
		char*, void(Physics::*)(glm::vec3, float),
		char*, void(Physics::*)(glm::vec3, float, float),
		char*, void(Physics::*)(glm::vec3, int, int, float, float, float*, int, glm::vec3),
		char*, void(Physics::*)(float),
		char*, void(Physics::*)(float), 
		char*, float(Physics::*)()>("Physics",
			"AddRigidbody", &Physics::addRigidBody,
			"AddBoxCollider", &Physics::addBox,
			"AddSphereCollider", &Physics::addSphere,
			"AddCapsuleCollider", &Physics::addCapsule,
			"AddHeightFieldCollider", &Physics::addHeightField,
			"SetFriction", &Physics::SetFrictionCoefficient,
			"SetBounciness", &Physics::SetBounciness, 
			"GetMass", &Physics::GetMass);

	//WorldPhysics
	mainScript.SetCPPFunction<void(*)(PhysicsBody, glm::vec3)>("AddForce", &AddForce);
	mainScript.SetCPPFunction<void(*)(PhysicsBody, glm::vec3)>("SetVelocity", &SetVelocity);
	mainScript.SetCPPFunction<glm::vec3(*)()>("GetGravity", &GetGravity);

	//InputHandler
	//mainScript.RegisterCppObject<InputHandler,
	//	char*, void(InputHandler::*)(GUKey, std::function<void()>), 
	//	char*, void(InputHandler::*)(GUMouseButton, std::function<void()>)>("InputHandler",
	//		"BindKey", &InputHandler::bindKey, 
	//		"BindMouse", &InputHandler::bindMouse);

	mainScript.SetCPPFunction<void(*)(GUKey, std::function<void()>, std::function<void()>, std::function<void()>)>("BindKey", &BindKey);
	mainScript.SetCPPFunction<void(*)(GUMouseButton, std::function<void()>, std::function<void()>)>("BindMouse", &BindMouse);
	mainScript.SetCPPFunction<void(*)(std::function<void(double, double)>)>("MousePosFunc", &MousePosFunc);

	mainScript.SetCPPFunction<glm::vec3(*)(glm::vec3)>("normalize", &normalize);
	mainScript.SetCPPFunction<glm::vec3(*)(glm::vec3, glm::vec3)>("crossProduct", &crossProduct);
	mainScript.SetCPPFunction<void(*)(bool)>("drawMode", &drawMode);

}

void Start() {}

void Update() {}

int main(int argc, char* argv[])
{
	MeshRenderer meshRend;
	Renderer renderer;
	LightingManager lightingManager;

	/*glm::vec3 pos(cameraPosition);
	glm::vec3 rot(0, 0, 0);
	glm::vec3 scale(1, 1, 1);
	Transform trans(pos, rot, scale);
	ENTITY ent(AddEntity(trans, true));
	AddCamera(ent, cameraPosition, cameraFront, cameraUp, 0.0, 0.0);*/

	GraphicsUtility::Initialise();
	GraphicsUtility::Window window = GraphicsUtility::CreateWindow("window");
	GraphicsUtility::makeContextCurrent(window);
	GraphicsUtility::initialiseOpenGLExtensions();

	GraphicsUtility::Enable(GraphicsEnum::DEPTH_TEST);

	SetLuaObjects();


	Shader shaderT("resources/shaders/terrain.shader");
	Shader shaderL("resources/shaders/lighting.shader");
	Shader shaderS("resources/shaders/skybox.shader");
	Shader shader("resources/shaders/basic.shader");
	//Shader shaderMT("resources/shaders/multiTexture.shader");

	unsigned int dLight1 = lightingManager.CreateLight(glm::vec3(1, 1, 1), 0.4f, 0.7f, glm::vec3(-1, 0, 0));
	lightingManager.ActivateDirLight(dLight1);

	//unsigned int pLight1 = lightingManager.CreateLight({ 1.f, 0.f, 0.f }, 0.03f, 1.f, { 1, 1, 1 }, { 1.f, 0.2f, 0.f });
	//lightingManager.ActivatePointLight(pLight1);		gives generic linker error

	InputHandler input(window);

	std::string filename = "scripts/TheMainScript.lua";

	if (mainScript.LoadScript(filename))
	{
		return -1;
	}
	/*for (entt::entity entity : registry.Contains<PhysicsBody>())
	{
		std::cout << "bean" << std::endl;
		PhysicsBody physics;
		Physics body;
		body.addRigidBody(glm::vec3(0, 0, 0), 1, 0, true);
		body.addBox(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
		std::cout << "bean" << std::endl;
		registry.GetComponent<PhysicsBody>(entity).Set(body);
		std::cout << "bean" << std::endl;
	}
	*/

	WorldPhysics::inializeWorldPhysics(0, -9.8f, 0);

	SetWorldBoundary(rp3d::Vector3(190, 151, 220), rp3d::Vector3(531, 600, 629), 5);

	for (entt::entity entity : registry.Contains<Camera>())
	{
		std::cout << (unsigned int)entity << std::endl;

		if (GetToRender(entity))
		{
			std::cout << "found camera" << std::endl;
		}
	}

	//MeshLoader object;
	//object.LoadMesh("resources/models/4Story_Mat.obj");

	/*glm::vec3 pos1(0, 0, 0);
	glm::vec3 rot1(0, 0, 0);
	glm::vec3 scale1(1, 1, 1);
	Transform trans1(pos1, rot1, scale1);
	ENTITY obj(AddEntity(trans1, true));
	AddMesh(obj, object.GetMesh());*/

	Terrain terrain;

	//terrain.genFaultFormation(32, 1025, -50, 1, 0.8, true, 33, 1000.0f);
	terrain.loadHeightMap("resources/heightmaps/VirusTerrain3.raw", 1025, 33, 1200.0f);
	//terrain.loadTerrainTexture("resources/textures/grass.jpg"); 
	terrain.addProceduralTexture("resources/textures/grass_dirt.jpg");
	terrain.addProceduralTexture("resources/textures/grass.jpg");
	terrain.addProceduralTexture("resources/textures/rock.jpg");
	terrain.addProceduralTexture("resources/textures/snow.jpg");
	terrain.createProceduralTexture(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 250.0f);
	terrain.loadDetailMapTexture("resources/textures/detail_map.jpg");

	Physics terrainRigid;

	std::vector<float> heights;
	float minHeight = {};
	float maxHeight = {};
	for (int i = 0; i < terrain.getSize(); i++)
	{
		for (int j = 0; j < terrain.getSize(); j++)
		{
			if (j == 0 && i == 0) {
				minHeight = terrain.getHeight(i, j);
				maxHeight = terrain.getHeight(i, j);
			}
			if (terrain.getHeight(i, j) < minHeight)
				minHeight = terrain.getHeight(i, j);
			if (terrain.getHeight(i, j) > maxHeight)
				maxHeight = terrain.getHeight(i, j);
			heights.push_back(terrain.getHeight(i, j));
		}
	}

	terrainRigid.addRigidBody(glm::vec3(0, 0, 0), 0, bodytype::STATIC, false);
	//we are adding the heightfield at 0,0,0. BUT THE terrain is not being drawn at 0,0,0
	terrainRigid.addHeightField(glm::vec3(terrain.getSize() / 2, 190, terrain.getSize() / 2), terrain.getSize(), terrain.getSize(), minHeight, maxHeight, heights.data(), 1, glm::vec3(1, 1, 1));
	terrainRigid.GetRigidBody()->getCollider(0)->getMaterial().setBounciness(0.0);
	terrainRigid.GetRigidBody()->getCollider(0)->getMaterial().setFrictionCoefficient(10.0);

	//terrainRigid.addBox(glm::vec3(0, 0, 0), glm::vec3(1000, 1, 1000));
	rp3d::CollisionCallback::ContactPair;

	//terrain.loadTexture("resources/textures/money.jpg");
	//Skybox skybox(std::vector<std::string>({ "resources/textures/day1_right.png", "resources/textures/day1_left.png", "resources/textures/day1_top.png", "resources/textures/day1_bottom.png", "resources/textures/day1_front.png", "resources/textures/day1_back.png" }));
	Skybox skybox(std::vector<std::string>({ "resources/textures/mossymountains_right.png", "resources/textures/mossymountains_left.png", "resources/textures/mossymountains_up.png", "resources/textures/mossymountains_down.png", "resources/textures/mossymountains_front.png", "resources/textures/mossymountains_back.png" }));
	//Skybox skybox(std::vector<std::string>({ "resources/textures/mountain_right.png", "resources/textures/mountain_left.png", "resources/textures/mountain_top.png", "resources/textures/mountain_bottom.png", "resources/textures/mountain_front.png", "resources/textures/mountain_back.png" }));
	//registry.GetComponent<Camera>(ent).Set(glm::vec3(20, 10, 20), glm::vec3(2.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);

	const char* items[] = { "Item 1", "Item 2", "Item 3" };
	int itemCount = sizeof(items) / sizeof(items[0]);
	int currentItem = 0; // Initial selected item index

	//Call start function
	mainScript.CallLUAFunction<void(*)()>("Start", &Start);


	/*Transform playertrans;
	playertrans.m_pos = glm::vec3(512, 200, 512);
	playertrans.m_rot = glm::vec3(0, 0, 0);
	playertrans.m_scale = glm::vec3(1, 1, 1);

	ENTITY ENplayer;

	ENplayer = registry.AddEntity(playertrans, true);

	//input.bindKey(KEY_W, W);
	Physics player;
	player.addRigidBody(registry.GetComponent<Transform>(ENplayer).m_pos, 10, bodytype::DYNAMIC, true);
	player.addCapsule(glm::vec3(0, 0, 0), 5, 10);
	//player.addBox(glm::vec3(0, 0, 0), glm::vec3(5, 10, 5));
	player.GetRigidBody()->getCollider(0)->getMaterial().setBounciness(0.0);
	player.GetRigidBody()->getCollider(0)->getMaterial().setFrictionCoefficient(10.0);

	registry.AddComponent<PhysicsBody>(ENplayer);
	setEntityPhysicsBody(ENplayer, player);

	registry.AddComponent<Camera>(ENplayer);
	*/

	BindKey(KEY_ESCAPE, [window]() { GraphicsUtility::setWindowShouldClose(window, true); }, empty, empty);

	bool cameraSet;
	while (!GraphicsUtility::shouldClose(window))
	{
		//processInput(window);	
		//glm::vec3 meme(player.GetRigidBody()->getTransform().getPosition().x, player.GetRigidBody()->getTransform().getPosition().x, player.GetRigidBody()->getTransform().getPosition().x);
		//std::cout << player.GetRigidBody()->getTransform().getPosition().x << " " << player.GetRigidBody()->getTransform().getPosition().y << " " << player.GetRigidBody()->getTransform().getPosition().z << std::endl;

		Timer::Instance().Update();
		WorldPhysics::accumulate(Timer::Instance().GetDeltaTime());
		WorldPhysics::updatePhysics();
		UpdatePhysicsBody();

		cameraSet = false;

		GraphicsUtility::SetClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		GraphicsUtility::Clear(GraphicsEnum::COLOR_BUFFER_BIT | GraphicsEnum::DEPTH_BUFFER_BIT);

		entt::entity camera;
		glm::mat4 view;
		glm::mat4 projection;
		Transform camPos;
		glm::vec3 LODcamPos = glm::vec3(0, 0, 0);
		Camera cam;

		//Call update function
		mainScript.CallLUAFunction<void(*)()>("Update", &Update);

		for (entt::entity entity : registry.Contains<Camera>())
		{
			camPos = registry.GetComponent<Transform>(entity);

			if (registry.HasComponent<PhysicsBody>(entity))
			{
				camPos.m_pos = Vec3ToGLM(registry.GetComponent<PhysicsBody>(entity).Get().GetRigidBody()->getTransform().getPosition());
			}

			LODcamPos = camPos.m_pos;
			cameraSet = true;
		}

		view = glm::lookAt(camPos.m_pos, camPos.m_pos + camPos.m_rot, camPos.m_scale);
		// Set the projection matrix
		projection = glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 10000.0f); // Adjust far clipping plane to 10000.0f
		// Set up camera view matrix


		if (cameraSet)
		{
			meshRend.Render(registry, renderer, shaderL, view, projection);
		}
		else
		{
			std::cout << "Error: No camera object found in the scene" << std::endl;
		}

		if (useTerrain)
		{
			terrain.render(renderer, shaderT, view, projection, LODcamPos);
		}
		//terrain.render(renderer, shaderT, camera1.getViewMatrix(), camera1.getProjectionMatrix(GraphicsUtility::GetWindowWidth(window), GraphicsUtility::GetWindowHeight(window), true, 90, 0.1f, 10000.f, 0.f));
		skybox.Render(renderer, shaderS, view, projection);

		// Swap front and back buffers
		GraphicsUtility::swapBuffers(window);
		// Poll for and process events
		GraphicsUtility::pollEvents();
	}

	input.ClearBindings(window);

	WorldPhysics::CleanUp();

	GraphicsUtility::Terminate();

	return 0;
}