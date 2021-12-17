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

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	app->textures->Unload(canonBase);
	app->textures->Unload(canonShooter);

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

	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		AddBall();
	}

	// ============================================
	//				   DRAW THINGS
	// ============================================

	app->renderer->Blit(canonShooter, pos.x, pos.y, angle, 0, 1.0f, 38, 52);

	app->renderer->Blit(canonBase, pos.x - 7, pos.y + 30);


	// ============================================
	//                   BALLS
	// ============================================

	p2List_item<Object>* c = balls.getFirst();

	while (c != NULL) {
		
		c->data.position.x += 3;

		// =====================
		//         DRAW
		// =====================
		app->renderer->Blit(c->data.sprite, c->data.position.x, c->data.position.y);

		// Delete balls out of screen
		if (c->data.position.x > app->scene_intro->BGSize.x) {
			DeleteBall(c);
			c = NULL;
		}
		else {
			c = c->next;
		}
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::AddBall() {

	// Create a new ball
	Object* ball = new Object();

	ball->sprite = app->textures->Load("Assets/canonBall.png");
	ball->fx = app->audio->LoadFx("Assets/canonShoot.wav");

	app->audio->PlayFx(ball->fx);

	//ball.body = app->physics

	ball->position.x = pos.x;
	ball->position.y = pos.y;

	// Add a force to throw the ball from the canon

	// ball.body.addforce();

	// Add ball to the balls list
	balls.add(*ball);

	// Free memory
	//delete ball->sprite;
	//delete ball->body;
	delete ball;
}

void ModulePlayer::DeleteBall(p2List_item<Object>* c) {
	app->textures->Unload(c->data.sprite);
	//app->physics->world->DestroyBody(c->data.body);
	c->data.fx = NULL;
	balls.del(c);
}

