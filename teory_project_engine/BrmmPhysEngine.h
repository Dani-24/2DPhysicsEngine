#pragma once

#include "Collisions.h"
#include "p2List.h"
#include "PhysBody.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class BrmmPhysEngine {
public:
	BrmmPhysEngine() {};
	~BrmmPhysEngine() {};

	bool CleanUp();

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
	fPoint ForceLift() {};

	// Accelerations / Velocities

	void AccelerationLinear(PhysBody* body);
	void AccelerationAngular(PhysBody* body);

	// Velocity Verlet
	void VelocityLinear(PhysBody* body, float dt);
	// Angular Velocity Verlet
	void VelocityAngular(PhysBody* body, float dt);

	float Module(float x, float y);
	void Unitary(float x, float y);

public:
	p2List<PhysBody*> bodies;

private:
	// As dt is x1000 all what use dt is /1000 (Should fix that dtX1000 but i have no time sorry :D)
	float gravity = 0.1f / 1000;
};