#pragma once
#include "Module.h"
#include "Globals.h"

#include "BrmmPhysEngine.h"

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

private:

	bool debug;

	BrmmPhysEngine* za_Warudo; // the physics world
};