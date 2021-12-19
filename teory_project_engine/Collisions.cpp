//#include "Collisions.h"
//
//// Constructors / Destructors
//Collisions::Collisions() {
//
//}
//
//Collisions::~Collisions() {
//
//}
//
//// Collision Solver
//
//void Collisions::Collision(PhysBody* physA, PhysBody* physB) {
//	// =====================================
//	// Get Variables from bodies:
//	// =====================================
//	fPoint velocityBodyA = physA->getLinearVelocity();
//	fPoint velocityBodyB = physB->getLinearVelocity();
//
//	fPoint subVel = velocityBodyA - velocityBodyB;
//
//	fPoint positionBodyA = physA->getPosition();
//	fPoint positionBodyB = physB->getPosition();
//
//	fPoint subPos = positionBodyA - positionBodyB;
//
//	float massBodyA = physA->getMass();
//	float massBodyB = physB->getMass();
//
//	float bothMass = 2 * massBodyB / ( massBodyA + massBodyB );
//
//	float dotProduct = subVel.x * subPos.x + subVel.y * subPos.y;
//	float coefficient = bothMass * dotProduct / pow(CalcModule(subPos), 2);
//
//	// =====================================
//	//      New PhysBody A velocity
//	// =====================================
//
//	fPoint newVelocityBodyA = velocityBodyA - (subPos * coefficient);
//
//	bothMass = 2 * massBodyA / (massBodyA + massBodyB);
//	subVel = velocityBodyB - velocityBodyA;
//	subPos = positionBodyB - positionBodyA;
//
//	dotProduct = subVel.x * subPos.x + subVel.y * subPos.y;
//	coefficient = bothMass * dotProduct / pow(CalcModule(subPos), 2);
//
//	// =====================================
//	//      New PhysBody B velocity
//	// =====================================
//
//	fPoint newVelocityBodyB = velocityBodyB - (subPos * coefficient);
//
//	// ==========================================================================
//	// Check if physBodyA type is Dynamic (The only one who can be moved)
//	// ==========================================================================
//
//	if (physA->getBodyType() == PhysBodyType::DYNAMIC_BODY) {
//		physA->setLinearVelocity(newVelocityBodyA);
//
//		// Check Collisions here !
//
//		if (physA->getBodyCategory() == PhysBodyCategory::ENEMY && physB->getBodyCategory() == PhysBodyCategory::CANONBALL) {
//			// COllision!
//		}
//	}
//
//	// ==========================================================================
//	// Check if physBodyB type is Dynamic (The only one who can be moved)
//	// ==========================================================================
//
//	if (physB->getBodyType() == PhysBodyType::DYNAMIC_BODY) {
//		physB->setLinearVelocity(newVelocityBodyB);
//
//		// Check Collisions here !
//	}
//
//}
//
//// Additional functions
//
//float Collisions::CalcModule(fPoint dist) {
//	float mod = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
//	return mod;
//}