#include "MeshComponent.h"

WholeMesh::WholeMesh()
{
	materials = std::vector<Material>();
	meshes = std::vector<Mesh>();
}

WholeMesh::WholeMesh(WholeMesh& mesh)
{
	materials = mesh.materials;
	meshes = mesh.meshes;
}

WholeMesh::WholeMesh(std::vector<Material> mats, std::vector<Mesh> mesh)
{
	materials = mats;
	meshes = mesh;
}

void WholeMesh::Clear()
{
	meshes.clear();
	materials.clear();
}
