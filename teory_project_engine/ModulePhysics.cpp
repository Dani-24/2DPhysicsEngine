#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (int i = 0; i < 5; i++) {
		idleAnim.PushBack({ 0, i * 51, 720, 51 });
	}
	idleAnim.loop = true;
	idleAnim.speed = 1.0f;
}

ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	idleAnim.DeleteAnim();

	LOG("Creating 2D Physics environment");

	debug = app->getDebugMode();

	za_Warudo = new BrmmPhysEngine();

	ground = CreateGround();

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
	if (debug == true) {
		DebugDraw();
	}

	return UPDATE_CONTINUE;
}

void ModulePhysics::DebugDraw() {

	// Draw Colliders/ hitboxes / random stuff / among us /etc

	LOG("%d", idleAnim.GetCurrentFrameINT());

	idleAnim.Update();
	app->renderer->Blit(ground->groundTexture, ground->position.x, ground->position.y, 0, &idleAnim.GetCurrentFrame());
}

Ground* ModulePhysics::CreateGround() {

	Ground* g = new Ground();

	g->groundBody = CreateSolidRect(g->position, 1920, 100);

	g->groundTexture = app->textures->Load("Assets/ground.png");

	g->idleAnim = this->idleAnim;

	return g;
}

void ModulePhysics::CreateEnvironment() {
	// Wind and that stuff
}

PhysBody* ModulePhysics::CreateBall(fPoint position, int radius) {
	
	// Create body
	PhysBody* body = new PhysBody();

	// Body variables
	body->setBodyType(PhysBodyType::DYNAMIC_BODY);

	body->setPosition(position);

	body->setRadius(radius);

	body->setDensity(1.0f);

	body->setDimensions(radius, radius);

	// Add body to world
	za_Warudo->AddBody(body);

	// Return the created body
	return body;
}

PhysBody* ModulePhysics::CreateRect(fPoint position, int width, int height) {
	PhysBody* body = new PhysBody();

	body->setBodyType(PhysBodyType::DYNAMIC_BODY);

	body->setPosition(position);

	body->setDensity(1.0f);

	body->setDimensions(width, height);

	// Add body to world
	za_Warudo->AddBody(body);

	// Return created body
	return body;
}

PhysBody* ModulePhysics::CreateSolidRect(fPoint position, int width, int height) {
	PhysBody* body = new PhysBody();

	body->setBodyType(PhysBodyType::STATIC_BODY);

	body->setPosition(position);

	body->setDensity(1.0f);

	body->setDimensions(width, height);

	// Add body to world
	za_Warudo->AddBody(body);

	// Return created body
	return body;
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
