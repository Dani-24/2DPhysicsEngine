#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;

	debug = false;
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

	// Audio volume

	if (debug != true) {
		app->audio->ChangeVolume(0);
	}
	else {
		app->audio->ChangeVolume(128);
	}

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	app->textures->Unload(background);

	return true;
}

update_status ModuleSceneIntro::Update()
{
	//(Camera movement at ModuleRender.cpp Update();)

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		debug = !debug;

		if (debug != true) {
			app->audio->ChangeVolume(0);
		}
		else {
			app->audio->ChangeVolume(128);
		}
	}

	// ====================
	//   Draw Background:
	// ====================

	app->renderer->Blit(background, 0, 0);

	return UPDATE_CONTINUE;
}