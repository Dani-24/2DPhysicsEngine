#include "BrmmPhysEngine.h"
#include "Globals.h"
#include "Application.h"
#include "math.h"

bool BrmmPhysEngine::CleanUp() {

	bodies.clear();

	return true;
}

// ==========================================================
//							Engine
// ==========================================================
void BrmmPhysEngine::Step(float dt) {

	p2List_item<PhysBody*>* physBodies;

	ApplyForces(physBodies);
	Integrator(physBodies, dt);
	CheckCollisions(physBodies);
}

void BrmmPhysEngine::ApplyForces(p2List_item<PhysBody*>*& c) {
	for (c = bodies.getFirst(); c != NULL; c = c->next) {
		// Only Dynamic bodies:
		if (c->data->getBodyType() == PhysBodyType::DYNAMIC_BODY) {
			PhysBody* b = c->data;
			fPoint forceGravity = ForceGravity(b->getMass());

			c->data->AddForce(forceGravity);
			c->data->setGravityScale(forceGravity.y);
		}
	}
}

void BrmmPhysEngine::Integrator(p2List_item<PhysBody*>*& c, float dt) {
	// Calculate Accelerations / Velocities

	for (c = bodies.getFirst(); c != NULL; c = c->next) {
		if (c->data->getBodyType() == PhysBodyType::DYNAMIC_BODY) {
			AccelerationLinear(c->data);
			AccelerationAngular(c->data);

			VelocityLinear(c->data, dt);
			VelocityAngular(c->data, dt);

			//RotateBody;
		}
		c->data->ResetForce();
		c->data->ResetTorque();
	}
}

void BrmmPhysEngine::CheckCollisions(p2List_item<PhysBody*>*& c) {
	p2List_item<PhysBody*>* c2;

	for (c = bodies.getFirst(); c != NULL; c = c->next) {
		for (c2 = c->next; c2 != NULL; c2 = c2->next) {
			float distBetweenAxis = 0;// = CalculateModule;
			bool sphere = false;
			bool staticBody = false;

			if (c->data->getBodyType() == PhysBodyType::STATIC_BODY && c2->data->getBodyType() == PhysBodyType::STATIC_BODY) {
				staticBody = true;
			}
			if (c->data->getRadius() + c2->data->getRadius() > distBetweenAxis && sphere) {
				//Collision(c->data, c2->data);
			}
			else if (!sphere && !staticBody) {
				float volume = 0; // = CollisionBox(c->data, c2->data);
				if (volume != 0) {
					// Add buoyance force
					c2->data->AddForce(ForceBuoyance(c2->data, volume));
					c2->data->AddForce({ 300, 0 }); 
				}
			}
		}
	}
}

// ==========================================================
//							Bodies
// ==========================================================

void BrmmPhysEngine::AddBody(PhysBody* body) {
	bodies.add(body);
}

void BrmmPhysEngine::DeleteBody(PhysBody* body) {
	p2List_item<PhysBody*>* c;

	for (c = bodies.getFirst(); c != NULL; c = c->next)
	{
		if (c->data == body)
		{
			bodies.del(c);
		}
	}
}

// ==========================================================
//					Engine Calculations
// ==========================================================

// Accelerations / Velocities ----------------------------
void BrmmPhysEngine::AccelerationLinear(PhysBody* body) {
	// Newton Law: F = m * a ---> a = f / m		(applied on X and Y axis)
	body->setLinearAcceleration({ body->GetForce().x / body->getMass(), body->GetForce().y / body->getMass() });
}

void BrmmPhysEngine::AccelerationAngular(PhysBody* body) {
	// I = m * r^2
	float inertia = body->getMass() * pow(body->getRadius(),2);

	// Set Angular Acceleration
	body->setAngularAcceleration(body->GetTorque() / inertia);
}

void BrmmPhysEngine::VelocityLinear(PhysBody* body, float dt) {
	// X = Xo + Vo * t + 1 / a * t^2
	// V = Vo + a * t
	float positionX =  body->getPosition().x + body->getLinearVelocity().x * dt + 0.5f * body->getLinearAcceleration().x * pow(dt, 2);
	float positionY = body->getPosition().y + body->getLinearVelocity().y * dt + 0.5f * body->getLinearAcceleration().y * pow(dt, 2);

	float velocityX = body->getLinearVelocity().x + body->getLinearAcceleration().x * dt;
	float velocityY = body->getLinearVelocity().y + body->getLinearAcceleration().y * dt;

	//(*Tried to do this with fPoints but restricted conversion error :D)

	body->setPosition({ positionX, positionY });
	body->setLinearVelocity({ velocityX, velocityY });
}

void BrmmPhysEngine::VelocityAngular(PhysBody* body, float dt) {
	// X = Xo + Wo * t + 1 / a * t^2
	// V = Wo + a * t
	
	// Position
	body->setAngularPosition(body->GetPositionAngular() + body->getAngularVelocity() * dt * 0.5f * body->getAngularAcceleration() * pow(dt, 2));
	// Velocity
	body->setAngularVelocity(body->getAngularVelocity() + body->getAngularAcceleration() * dt);
}

// Forces ---------------------------
fPoint BrmmPhysEngine::ForceGravity(float mass) {
	fPoint forceG = { 0, mass * gravity };
	return forceG;
}

fPoint BrmmPhysEngine::ForceDrag(fPoint velocity, float density) {

	//velocity = NormalizeVec(velocity);
	float dragModule;
	dragModule = 0.5f * density; // pow(velRelative, 2) * surface * cd

	fPoint forceDrag = { -dragModule* velocity.x, -dragModule * velocity.y };
	return forceDrag;
}

fPoint BrmmPhysEngine::ForceBuoyance(PhysBody* body, float volume) {
	fPoint forceBuoy = { 0, (1 * abs(body->getGravityScale()) * volume) * -1 };
	return forceBuoy;
}