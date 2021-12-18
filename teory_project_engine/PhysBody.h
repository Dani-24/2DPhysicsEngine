#include"p2Point.h"

enum class PhysBodyType {
	STATIC_BODY = 0,
	KINEMATIC_BODY,
	DYNAMIC_BODY
};

// BODY states ??????????????????????????

class PhysBody {
public:
	PhysBody();
	~PhysBody();

	// ======================================
	// Variables setters
	// ======================================

	void setBodyDimensions(float width, float height) { this->width = width; this->height = height; };

	void setMass(float mass) { this->mass = mass; };
	void setSurface(float surface) { this->surface = surface; };
	void setGravityScale(float gravityScale) { this->gravityScale = gravityScale; };
	void setPosition(fPoint position) { this->position = position; };
	void setRotation(float angle) { this->angle = angle; };
	void setDensity(float density) { this->density = density; };
	
	void setLinearVelocity(fPoint velocity) { this->velocity = velocity; };
	void setAngularVelocity(float angularVelocity) { this->angularVelocity = angularVelocity; };

	void setLinearAcceleration(fPoint acceleration) { this->acceleration = acceleration; };
	void setAngularAcceleration(float angularAcceleration) { this->angularAcceleration = angularAcceleration; };

	// Set the body type to STATIC_BODY, KINEMATIC_BODY or DYNAMIC_BODY
	void setBodyType(PhysBodyType type) { this->type = type; };

	void setLiftCoefficient(float liftCo) { this->liftCo = liftCo; };
	void setDragCoefficient(float dragCo) { this->dragCo = dragCo; };

	// ======================================
	// Variables getters
	// ======================================

	void getBodyDimensions(float& width, float& height) { width = this->width; height = this->height; }

	float getWidht() { return width; };
	float getHeight() { return height; };

	float getMass() { return mass; };
	float getSurface() { return surface; };
	float getGravityScale() { return gravityScale; };
	float getDensity() { return density; };

	fPoint getPosition() { return position; };
	float getRotation() { return angle; };
	

	fPoint getLinearVelocity() { return velocity; };
	float getAngularVelocity() { return angularVelocity; };

	fPoint getLinearAcceleration() { return acceleration; };
	float getAngularAcceleration() { return angularAcceleration; };

	PhysBodyType getBodyType() { return type; };

	float getLiftCoefficient() { return liftCo; };
	float getDragCoefficient() { return dragCo; };

	// ======================================
	// Interactions
	// ======================================

	//void RotatePhysBody(float rotation); // idk if i'm gonna use it

	void AddForce(fPoint force);
	//void AddTorque(fPoint force, fPoint distance);

	void ResetForces();

	void EnablePhysics() { physicsEnabled = true; };
	void DisablePhysics() { physicsEnabled = false; };

	// Are physics enabled on this PhysBody?
	bool PhysicsState() { return physicsEnabled; };


	// ================= Añadir impulso ????¿¿¿???? =======================

private:

	// --- Body Properties ---
	fPoint position;
	float mass;
	float width;
	float height;
	float angle;
	PhysBodyType type;
	float surface;
	float density;

	// --- Linear ---
	fPoint velocity;
	fPoint acceleration;

	// --- Angular ---
	float angularVelocity;
	float angularAcceleration;

	// --- Forces ---
	float gravityScale = 1.0f;

	fPoint force;

	//float torque;

	float liftCo;
	float dragCo;

	bool physicsEnabled = true;

	// PhysBodyCollider:
	//fPoint* bodyColliders = new fPoint[10];
};