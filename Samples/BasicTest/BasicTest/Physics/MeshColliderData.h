#pragma once
#include "btBulletDynamicsCommon.h"
#include "Graphics/MeshInstance.h"
#include "LVP.h"

class MeshColliderData : public btTriangleMesh
{
public:
	MeshColliderData(const OBJMesh* mesh);

};

