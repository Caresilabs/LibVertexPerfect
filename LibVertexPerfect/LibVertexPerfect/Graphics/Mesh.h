#pragma once
#include <D3D11.h>
#include <vector>
#include "DrawCall.h"
#include "Shaders/ShaderProgram.h"

class Mesh {
public:
	Mesh();

	virtual void Render( ShaderProgram& shader ) const = 0;

	virtual ~Mesh();

	std::vector<material_t> materials;

protected:

	// pointers to device vertex & index arrays
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;

	ID3D11DeviceContext* DeviceContext;

	// index ranges, representing drawcalls, within an index array
	struct IndexRange {
		size_t start;
		size_t size;
		unsigned Ofs;
		int MaterialIndex;
	};

	std::vector<IndexRange> index_ranges;

	void append_materials( const std::vector<material_t>& mtl_vec ) {
		materials.insert( materials.end(), mtl_vec.begin(), mtl_vec.end() );
	}

};

class MeshData;

class OBJMesh : public Mesh {
private:
	MeshData* meshData;

public:

	OBJMesh( const std::string& file );

	void Render( ShaderProgram& shader ) const override;

	const MeshData* GetMeshData() const;

	virtual ~OBJMesh() override;

};

class CubeMesh : public Mesh {
public:

	CubeMesh();

	void Render( ShaderProgram& shader ) const override;

private:
	void CreateFace( vec3f p0, vec3f p1, vec3f p2, vec3f p3, vec3f normal );

	// our local vertex and index arrays
	std::vector<vertex_t> vertices;
	std::vector<unsigned> indices;
	unsigned nbr_indices = 0;
};


