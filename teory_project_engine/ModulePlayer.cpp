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

	shotFx = app->audio->LoadFx("Assets/canonShoot.wav");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	app->textures->Unload(canonBase);
	app->textures->Unload(canonShooter);

	balls.clear();

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	// Angle
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		if (angle > -55) {
			angle -= speed * dt;
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		if (angle < 12) {
			angle += speed * dt;
		}
	}

	// Movement
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		if (pos.x > 10) {
			pos.x -= speed * dt;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		if (pos.x < 400) {
			pos.x += speed * 2 * dt;
		}
	}
	// Shoot
	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		if (balls.count() < MAX_BALLS) {
			AddBall();
		}
	}

	// ============================================
	//				   DRAW THINGS
	// ============================================

	app->renderer->Blit(canonShooter, pos.x, pos.y, angle, 0, 1.0f, 38, 52);

	app->renderer->Blit(canonBase, pos.x - 7, pos.y + 30);

	// ============================================
	//                   BALLS
	// ============================================

	// Check die
	for (p2List_item<Ball*>* item = balls.getFirst(); item != NULL; item = item->next) {
		if (item->data->position.x > app->scene_intro->BGSize.x) {
			if (DeleteBall(item->data) == true) {
				break;
			}
		}
	}

	p2List_item<Ball*>* c = balls.getFirst();

	while (c != NULL) {
		
		c->data->position.x += 0.2f * dt;

		// =====================
		//         DRAW
		// =====================
		app->renderer->Blit(c->data->sprite, c->data->position.x, c->data->position.y);
		
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::AddBall() {

	// Create a new ball
	Ball* ball = new Ball(pos, app->textures->Load("Assets/canonBall.png"), NULL);

	app->audio->PlayFx(shotFx);

	// Add ball to the balls list
	balls.add(ball);
}

bool ModulePlayer::DeleteBall(Ball* b) {

	p2List_item<Ball*>* c =balls.getFirst();

	bool ballDeleted = false;

	while (c != NULL && ballDeleted == false) {
		
		if (c->data == b) {

			app->textures->Unload(c->data->sprite);
			//app->physics->theWorld->UnloadBody(c->data->body);
			balls.del(c);
			ballDeleted = true;

			return true;
		}
		c = c->next;
	}

	return false;
}

