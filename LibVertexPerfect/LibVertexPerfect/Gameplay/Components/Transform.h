#pragma once

#include "../../Math/mat.h"
//include "LinearMath/btQuaternion.h"

using namespace linalg;

class Transform {

public:
	

	vec3f Position;
	vec3f Scale;
	vec3f Rotation;

	Transform() : Scale(1, 1, 1) {

	}

	mat4f GetMatrix() {
		auto rot = mat4f::rotation(Rotation.z, { 0, 0, 1 }) *  mat4f::rotation(Rotation.y, { 0, 1, 0 }) 
			* mat4f::rotation(Rotation.x, { 1, 0, 0 })
			;
		//return mat4f::translation(Position) * mat4f::rotation(Rotation.x, Rotation.y, Rotation.z) * mat4f::scaling(Scale);
		//return  mat4f::rotation(Rotation.x, Rotation.y, Rotation.z);
		return mat4f::translation(Position) * rot;
	}
};
