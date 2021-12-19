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
	update_status PostUpdate();
	bool CleanUp();

private:
	float dt = 1.0f / 60;
	bool debug;
};