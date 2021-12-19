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
	void setAngularPosition(float angle) { angularPosition = angle; };

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

	float getRadius() { return radius; };

	fPoint getPosition() { return position; };
	float getRotation() { return angle; };
	float& GetPositionAngular() { return angularPosition; };

	fPoint getLinearVelocity() { return velocity; };
	float getAngularVelocity() { return angularVelocity; };

	fPoint getLinearAcceleration() { return acceleration; };
	float getAngularAcceleration() { return angularAcceleration; };

	PhysBodyType getBodyType() { return type; };

	float getLiftCoefficient() { return liftCo; };
	float getDragCoefficient() { return dragCo; };

	fPoint GetForce() { return force; };
	float GetTorque() { return torque; };

	// ======================================
	// Interactions
	// ======================================

	void AddForce(fPoint force);
	void ResetForce();

	// Add a torque by a force (By default at distance 1 what is the center of the mass
	void AddTorque(fPoint force, fPoint d = { 1,1 });
	void ResetTorque();

	void EnablePhysics() { physicsEnabled = true; };
	void DisablePhysics() { physicsEnabled = false; };

	// Are physics enabled on this PhysBody?
	bool PhysicsState() { return physicsEnabled; };

	// ================= Añadir impulso ????¿¿¿???? =======================

private:

	// --- Body Properties ---
	fPoint position = { 0,0 };
	float mass;
	float width;
	float height;
	float angle;
	PhysBodyType type;
	float surface;
	float radius = 0;
	float density;

	// --- Linear ---
	fPoint velocity = { 0,0 };
	fPoint acceleration = { 0,0 };

	// --- Angular ---
	float angularPosition = 0;
	float angularVelocity = 0;
	float angularAcceleration = 0;

	// --- Forces ---
	float gravityScale = 1.0f;

	fPoint force = { 0,0 };
	float torque = 0;

	float liftCo;
	float dragCo;

	bool physicsEnabled = true;
};