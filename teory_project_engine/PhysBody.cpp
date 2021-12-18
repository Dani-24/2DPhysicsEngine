#include "PhysBody.h"

PhysBody::PhysBody() {

}
PhysBody::~PhysBody() {
	position.x = velocity.x = acceleration.x = force.x = position.y = velocity.y = acceleration.y = force.y = 
	mass = width = height = angle = surface = density = angularVelocity = angularAcceleration = liftCo = dragCo = NULL;

	gravityScale = 1.0f;
	physicsEnabled = true;
}

//void PhysBody::RotatePhysBody(float rotation) {
//
//}

void PhysBody::AddForce(fPoint force) {
	this->force.x += force.x;
	this->force.y += force.y;
}

void PhysBody::ResetForces() {
	force.x = 0;
	force.y = 0;
}