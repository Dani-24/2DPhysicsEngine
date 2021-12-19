#include "Collisions.h"
#include "PhysBody.h"
#include "p2List.h"

enum TypesOfBodies {
	PLAYER,
	/* everybody wants to be my*/ ENEMY,
	CANONBALL
};

class BrmmPhysEngine {
public:
	BrmmPhysEngine() {};
	~BrmmPhysEngine() {};

	bool CleanUp();

	p2List<PhysBody*> bodies;

	void AddBody(PhysBody* body);
	void DeleteBody(PhysBody* body);

	// Engine
	void Step(float dt);

	void ApplyForces(p2List_item<PhysBody*>* &item);
	void Integrator(p2List_item<PhysBody*>*& item, float dt);
	void CheckCollisions(p2List_item<PhysBody*>*& item);

	float GetGravity() { return gravity; };

	// Forces

	fPoint ForceGravity(float mass);
	fPoint ForceDrag(fPoint velocity, float density);
	fPoint ForceBuoyance(PhysBody* body, float volume);

	// Accelerations / Velocities

	void AccelerationLinear(PhysBody* body);
	void AccelerationAngular(PhysBody* body);

	// Velocity Verlet
	void VelocityLinear(PhysBody* body, float dt);
	// Angular Velocity Verlet
	void VelocityAngular(PhysBody* body, float dt);

private:
	float dt;
	bool debug;

	float gravity = 9.8f;
};

class Environment {
public:
	fPoint wind = {1, 1};
	float density = 1;
};

struct Ground {
	iPoint position = { 0, SCREEN_HEIGHT - 195 };
};