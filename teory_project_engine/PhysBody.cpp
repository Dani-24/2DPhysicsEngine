#include "PhysBody.h"

PhysBody::PhysBody() {

}
PhysBody::~PhysBody() {

	// Clean
	position.x = velocity.x = acceleration.x = force.x = position.y = velocity.y = acceleration.y = force.y =
	mass = width = height = angle = surface = density = angularVelocity = angularAcceleration = liftCo = dragCo = torque = NULL;

	gravityScale = 1.0f;
	physicsEnabled = true;
}

// Forces
void PhysBody::AddForce(fPoint force) {
	this->force.x += force.x;
	this->force.y += force.y;
}

void PhysBody::ResetForce() {
	force.x = 0;
	force.y = 0;
}

// Torques
void PhysBody::AddTorque(fPoint appliedForce, fPoint d)
{
	torque += (appliedForce.x * d.y) - (force.y * d.x);
}

void PhysBody::ResetTorque() {
	torque = 0;
}