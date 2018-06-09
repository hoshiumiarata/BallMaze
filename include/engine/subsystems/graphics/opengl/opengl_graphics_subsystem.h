#pragma once

#include "../graphics_subsystem.h"

#include "../light_source.h"
#include "../vertex_buffer.h"
#include "../index_buffer.h"

#include "opengl_vertex_array_buffer.h"

#include <GL/glew.h>

class Camera;
class GLSLShaderProgram;
class Material;

class OpenGLGraphicsSubSystem : public GraphicsSubSystem
{
public:
	virtual bool init() override;
	virtual bool update(float dt) override;
	virtual bool postUpdate() override;
	virtual bool destroy() override;

	virtual std::unique_ptr<VertexBuffer> createVertexBuffer() override;
	virtual std::unique_ptr<IndexBuffer> createIndexBuffer() override;
	virtual std::shared_ptr<MeshRenderer> createMeshRenderer(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material) override;
	virtual std::shared_ptr<Texture> createTexture() override;

	virtual const std::string getName() const override;
private:
	void initConsts();
	void viewportSetup();
	void ligthsSetup(GLSLShaderProgram* shader);
	void renderMeshes(Camera* camera);
	void renderSprites();

	const size_t MaxLightSourceNum = 8;
	const std::string ProjectionMatrix = "projectionMatrix";
	const std::string ModelMatrix = "modelMatrix";
	const std::string ModelViewMatrix = "modelViewMatrix";
	const std::string ViewMatrix = "viewMatrix";
	const std::string NormalMatrix = "normalMatrix";

	const std::string MaterialHasTexture = "material.hasTexture";
	const std::string MaterialTexture = "material.texture";
	const std::string MaterialAmbient = "material.ambient";
	const std::string MaterialDiffuse = "material.diffuse";
	const std::string MaterialSpecular = "material.specular";
	const std::string MaterialEmission = "material.emission";
	const std::string MaterialShininess = "material.shininess";

	LightSource DefaultLightSource;

	std::vector<std::string> LightAmbient;
	std::vector<std::string> LightDiffuse;
	std::vector<std::string> LightSpecular;
	std::vector<std::string> LightPosition;
	std::vector<std::string> LightConstantAttenuation;
	std::vector<std::string> LightLinearAttenuation;
	std::vector<std::string> LightQuadraticAttenuation;

	const std::string SpriteSize = "spriteSize";
	const std::string SpriteAlign = "spriteAlign";
	const std::string SpriteColor = "spriteColor";
	const std::string SpriteTexture = "spriteTexture";

	std::unique_ptr<VertexBuffer> spriteSquareTexCoords;
	std::unique_ptr<VertexBuffer> spriteSquareVertices;
	std::unique_ptr<IndexBuffer> spriteSquareIndices;
	std::unique_ptr<OpenGLVertexArrayBuffer> spriteSquareVertexArrayBuffer;
};