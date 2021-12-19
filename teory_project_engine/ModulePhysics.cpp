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

	debug = app->getDebugMode();

	za_Warudo = new BrmmPhysEngine();

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	debug = app->getDebugMode();

	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update(float dt)
{
	za_Warudo->Step(dt);

	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	// Hello :D
	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateBall(fPoint position, int radius) {
	
	// Create body
	PhysBody* body;

	// Body variables
	body->setBodyType(PhysBodyType::DYNAMIC_BODY);

	body->setPosition(position);

	body->setRadius(radius);

	// Add body to world
	za_Warudo->AddBody(body);

	// Return the created body
	return body;
}

PhysBody* ModulePhysics::CreateRect(fPoint position, int width, int height) {

}

PhysBody* ModulePhysics::CreateSolidRect(fPoint position, int width, int height) {

}

void ModulePhysics::DestroyBodyFromAstralPlane(PhysBody* physB) {
	za_Warudo->DeleteBody(physB);
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete bodies created at engine
	za_Warudo->CleanUp();

	// Delete Dio Stand - The World
	delete za_Warudo;

	return true;
}
