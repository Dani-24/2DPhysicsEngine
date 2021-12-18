#include "Collisions.h"
#include "PhysBody.h"
#include "p2List.h"

class BrmmPhysEngine {
public:
	BrmmPhysEngine() {};
	~BrmmPhysEngine() {};

	bool CleanUp();

	p2List<PhysBody*> bodies;

	void AddBody(PhysBody* body);
	void DeleteBody(PhysBody* body);

	void Step(float dt);

public:


private:

};