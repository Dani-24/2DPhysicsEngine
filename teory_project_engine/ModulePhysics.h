#pragma once
#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "BrmmPhysEngine.h"

class Environment {
public:
	fPoint wind = { 1.0f, 1.0f };
	float density = 1;
};

struct Ground {
	PhysBody* groundBody;

	fPoint position = { 0, SCREEN_HEIGHT - 90 };

	SDL_Texture* groundTexture;
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status Update(float dt);
	update_status PostUpdate();
	bool CleanUp();

	// PhysBody functions

	PhysBody* CreateBall(fPoint position, int radius);

	PhysBody* CreateRect(fPoint position, int width, int height);

	PhysBody* CreateSolidRect(fPoint position, int width, int height);

	void DestroyBodyFromAstralPlane(PhysBody* physB);

	Ground* CreateGround();
	void CreateEnvironment();

	void DebugDraw();

private:
	bool debug;

	Ground* ground;

public:
	BrmmPhysEngine* za_Warudo; // the physics world
};