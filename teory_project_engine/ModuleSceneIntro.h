#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"

class ModuleSceneIntro;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void SetDeltaTime60Fps();
	void SetDeltaTime30Fps();

public:

	SDL_Texture* background;

	PhysBody* player_lose;
	uint player_lose_fx;

	iPoint BGSize;

	SDL_Texture* enemy;
	PhysBody* enemyBody;
};
