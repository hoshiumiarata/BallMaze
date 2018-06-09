#pragma once

#include <memory>
#include <deque>
#include <vector>

#include "../subsystem_interface.h"

class VertexBuffer;
class IndexBuffer;
class Texture;
class MeshRenderer;
class Sprite;
class Mesh;
class Material;
struct LightSource;

class GraphicsSubSystem : public ISubSystem
{
public:
	virtual std::unique_ptr<VertexBuffer> createVertexBuffer() = 0;
	virtual std::unique_ptr<IndexBuffer> createIndexBuffer() = 0;
	virtual std::shared_ptr<MeshRenderer> createMeshRenderer(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) = 0;
	virtual std::shared_ptr<Texture> createTexture() = 0;

	void addToRenderQueue(const std::weak_ptr<MeshRenderer>& meshRenderer);
	void addSpriteToRenderQueue(const std::weak_ptr<Sprite>& sprite);
	void addLightSource(const std::weak_ptr<LightSource>& lightSource);
protected:
	std::deque<std::weak_ptr<MeshRenderer>> renderQueue;
	std::deque<std::weak_ptr<Sprite>> spriteRenderQueue;
	std::vector<std::weak_ptr<LightSource>> lightSources;
};