#pragma once
#include "entityx/entityx.h"
#include "btBulletDynamicsCommon.h"
#include"../Components/Physics.h"

using namespace entityx;

class PhysicsSystem : public entityx::System<PhysicsSystem>, public entityx::Receiver<entityx::ComponentAddedEvent<Physics>> {

	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver; 
	btDiscreteDynamicsWorld* dynamicsWorld;

public:
	PhysicsSystem();

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		dynamicsWorld->stepSimulation(dt, 10);

		es.each<Transform, Physics>([dt](Entity entity, Transform& transform, Physics& physics) {
			physics.updateTransform(transform);
		});
	};

	void configure(entityx::EventManager &event_manager) {
		event_manager.subscribe<entityx::ComponentAddedEvent<Physics>>(*this);
	}


	void receive(const entityx::ComponentAddedEvent<Physics>& event) {
		dynamicsWorld->addRigidBody(event.component->body);
	}

	~PhysicsSystem();
};
