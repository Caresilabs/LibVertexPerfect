#pragma once
#include "Graphics/MeshInstance.h"

class MeshInstanceComponent {

public:
	VPtr<MeshInstance>	Instance;

	MeshInstanceComponent(VPtr<MeshInstance> instance) : Instance(instance) {

	}
};

