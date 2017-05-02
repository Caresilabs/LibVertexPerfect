#include "MeshColliderData.h"
#include "Graphics/OBJLoader.h"


MeshColliderData::MeshColliderData(const OBJMesh* mesh)
{
	auto meshData = mesh->GetMeshData();
	for (auto& dc : meshData->drawcalls) {
		// append the drawcall indices
		for (auto& tri : dc.tris) {
			auto p0 = meshData->vertices[tri.vi[0]];
			auto p1 = meshData->vertices[tri.vi[1]];
			auto p2 = meshData->vertices[tri.vi[2]];
			addTriangle({ p0.Pos.x, p0.Pos.y, p0.Pos.z }, { p1.Pos.x, p1.Pos.y, p1.Pos.z }, { p2.Pos.x, p2.Pos.y, p2.Pos.z });
		}
	}
}

