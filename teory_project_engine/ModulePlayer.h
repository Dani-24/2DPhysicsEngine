#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#define MAX_BALLS 5

class PhysBody;

struct Object
{
	SDL_Texture* sprite;
	PhysBody* body;
	fPoint position;
	Object() : sprite(NULL), body(NULL)
	{}
};

struct Ball : Object {
	// ipoint for initial position, texture physbody and the fx
	Ball(fPoint position, SDL_Texture* texture, PhysBody* body) {
		this->position = position;
		this->sprite = texture;
		this->body = body;
	}
	~Ball() {}

	int radius;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	// Create a new ball from canon
	void AddBall();
	// Check if balls should be deleted
	bool DeleteBall(Ball* b);

public:

	p2List<Ball*> balls;

	SDL_Texture* canonBase, * canonShooter;

	uint shotFx, hitFx;

	fPoint pos;

	float angle, shootAngle, shootForce = 0.02f, speed = 0.05f;
};