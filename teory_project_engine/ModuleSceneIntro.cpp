#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	BGSize.x = 1920;
	BGSize.y = 645;

	app->renderer->camera.x = app->renderer->camera.y = 0;

	// Assets

	background = app->textures->Load("Assets/bg.png");

	app->audio->PlayMusic("Assets/bgMusic.ogg");

	enemy = app->textures->Load("Assets/penguin.png");
	fPoint posEnemy = { 1600, 200 };
	enemyBody = app->physics->CreateSolidRect(posEnemy, 150, 200);

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	app->textures->Unload(background);

	return true;
}

update_status ModuleSceneIntro::Update(float dt)
{
	//(Camera movement at ModuleRender.cpp Update();)

	// Debug Mode Control
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		app->setDebugMode();

		if (app->getDebugMode() != true) {
			app->audio->ChangeVolume(0);
		}
		else {
			app->audio->ChangeVolume(128);
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		SetDeltaTime30Fps();
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		SetDeltaTime60Fps();
	}

	// ====================
	//   Draw Background:
	// ====================

	app->renderer->Blit(background, 0, 0);

	app->renderer->Blit(enemy, enemyBody->getPosition().x, enemyBody->getPosition().y);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::SetDeltaTime60Fps() {
	app->setDeltaTime(60);
}

void ModuleSceneIntro::SetDeltaTime30Fps() {
	app->setDeltaTime(30);
}