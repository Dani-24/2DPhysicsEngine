#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
//#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	pos.x = 100;
	pos.y = 450;
	angle = 0;

	canonBase = app->textures->Load("Assets/canonBase.png");
	canonShooter = app->textures->Load("Assets/canonMove.png");
	ball.graphic = app->textures->Load("Assets/canonBall.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	app->textures->Unload(canonBase);
	app->textures->Unload(canonShooter);
	app->textures->Unload(ball.graphic);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		if (angle > -120) {
			angle -= speed;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		if (angle < 12) {
			angle += speed;
		}
	}

	// ============================================
	//				   DRAW THINGS
	// ============================================

	app->renderer->Blit(canonShooter, pos.x, pos.y, angle, 0, 1.0f, 38, 52);

	app->renderer->Blit(canonBase, pos.x - 7, pos.y + 30);

	return UPDATE_CONTINUE;
}



