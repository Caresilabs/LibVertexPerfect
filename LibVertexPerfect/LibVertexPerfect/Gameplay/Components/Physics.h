#pragma once
#include "btBulletDynamicsCommon.h"
#include "Transform.h"

class Physics {
	

public:

	btRigidBody* body;

	/*linalg::vec3f GetPosition() {
		btTransform trans;
		body->getMotionState()->getWorldTransform(trans);
		trans.getRotation().get
		return linalg::vec3f(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	}*/

	void updateTransform(Transform& transform) {
		btTransform trans;
		body->getMotionState()->getWorldTransform(trans);

		float yaw, pitch, roll;
		trans.getRotation().getEulerZYX(roll, yaw, pitch);
		transform.Rotation = vec3f(pitch, yaw, roll);

		transform.Position = linalg::vec3f(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	}

	//todo delete shape
	Physics(linalg::vec3f pos = linalg::vec3f(), btCollisionShape* shape = nullptr, float mass = 1.f) {
		btTransform tr;
		tr.setIdentity();
		tr.setOrigin({ pos.x, pos.y, pos.z });
		//tr.setOrigin(btVector3(transform->position.x, transform->position.y, transform->position.z));
		//tr.setRotation(transform->rotation);
		btMotionState* motion = new btDefaultMotionState(tr);
		
		btVector3 inertia(0, 0, 0);
		if (mass > 0)
			shape->calculateLocalInertia(mass, inertia);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motion, shape, inertia);
		//rbInfo.m_friction = 20;
		body = new btRigidBody(rbInfo);
	}

	~Physics() {
		delete body->getMotionState();
		delete body;
	}

};
