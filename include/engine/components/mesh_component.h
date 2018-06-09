#pragma once

#include <memory>

#include "component.h"

class Mesh;
class Material;
class MeshRenderer;

class MeshComponent : public Component
{
public:
	MeshComponent(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);

	std::shared_ptr<Mesh> getMesh() const;
	std::shared_ptr<Material> getMaterial() const;

	virtual void initialize() override;
	virtual void tick(float dt) override;
private:
	void updateMesh();

	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
	std::shared_ptr<MeshRenderer> meshRenderer;
};

