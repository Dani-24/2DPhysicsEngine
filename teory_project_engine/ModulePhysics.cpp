#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating 2D Physics environment");

	debug = app->scene_intro->debug;

	return true;
}

update_status ModulePhysics::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");
	return true;
}
