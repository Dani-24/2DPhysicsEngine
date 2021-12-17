#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#define MaxBalls 10


class PhysBody;

struct Object
{
	SDL_Texture* sprite;
	PhysBody* body;
	uint fx;
	iPoint position;
	Object() : sprite(NULL), body(NULL)
	{}
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddBall();
	void DeleteBall(p2List_item<Object>* c);

public:

	p2List<Object> balls;

	SDL_Texture* canonBase, * canonShooter;

	iPoint pos;

	double angle, speed = 0.5;
};