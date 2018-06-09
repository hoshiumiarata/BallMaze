#include "engine/subsystems/graphics/opengl/opengl_graphics_subsystem.h"
#include "engine/subsystems/graphics/opengl/opengl_vertex_buffer.h"
#include "engine/subsystems/graphics/opengl/opengl_index_buffer.h"
#include "engine/subsystems/graphics/opengl/opengl_mesh_renderer.h"
#include "engine/subsystems/graphics/opengl/opengl_texture.h"
#include "engine/subsystems/graphics/opengl/glsl_shader_program.h"
#include "engine/engine.h"
#include "engine/mesh.h"
#include "engine/subsystems/window_manager/window_manager_subsystem.h"
#include "engine/subsystems/graphics/mesh_renderer.h"
#include "engine/subsystems/graphics/sprite.h"
#include "engine/subsystems/graphics/material.h"

#include <algorithm>
#include <unordered_set>

bool OpenGLGraphicsSubSystem::init()
{
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initConsts();

	return true;
}

bool OpenGLGraphicsSubSystem::update(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

bool OpenGLGraphicsSubSystem::postUpdate()
{
	auto camera = getEngine()->getCamera();

	viewportSetup();
	
	if (camera)
		renderMeshes(camera.get());

	renderSprites();

	lightSources.clear();

	// glFlush();
	return true;
}

bool OpenGLGraphicsSubSystem::destroy()
{
	spriteSquareTexCoords.reset();
	spriteSquareVertices.reset();
	spriteSquareIndices.reset();
	spriteSquareVertexArrayBuffer.reset();
	return true;
}

std::unique_ptr<VertexBuffer> OpenGLGraphicsSubSystem::createVertexBuffer()
{
	return std::make_unique<OpenGLVertexBuffer>();
}

std::unique_ptr<IndexBuffer> OpenGLGraphicsSubSystem::createIndexBuffer()
{
	return std::make_unique<OpenGLIndexBuffer>();
}

std::shared_ptr<MeshRenderer> OpenGLGraphicsSubSystem::createMeshRenderer(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material)
{
	return std::make_shared<OpenGLMeshRenderer>(this, mesh, material);
}

std::shared_ptr<Texture> OpenGLGraphicsSubSystem::createTexture()
{
	return std::make_shared<OpenGLTexture>();
}

const std::string OpenGLGraphicsSubSystem::getName() const
{
	return "OpenGL Graphics";
}

void OpenGLGraphicsSubSystem::initConsts()
{
	LightAmbient.resize(MaxLightSourceNum);
	LightDiffuse.resize(MaxLightSourceNum);
	LightSpecular.resize(MaxLightSourceNum);
	LightPosition.resize(MaxLightSourceNum);
	LightConstantAttenuation.resize(MaxLightSourceNum);
	LightLinearAttenuation.resize(MaxLightSourceNum);
	LightQuadraticAttenuation.resize(MaxLightSourceNum);

	for (size_t i = 0; i < MaxLightSourceNum; i++)
	{
		std::string lightStr = "lights[" + std::to_string(i) + "].";
		LightAmbient[i] = lightStr + "ambient";
		LightDiffuse[i] = lightStr + "diffuse";
		LightSpecular[i] = lightStr + "specular";
		LightPosition[i] = lightStr + "position";
		LightConstantAttenuation[i] = lightStr + "constantAttenuation";
		LightLinearAttenuation[i] = lightStr + "linearAttenuation";
		LightQuadraticAttenuation[i] = lightStr + "quadraticAttenuation";
	}

	spriteSquareVertexArrayBuffer = std::make_unique<OpenGLVertexArrayBuffer>();

	spriteSquareVertices = createVertexBuffer();
	spriteSquareVertices->setData({
		vec3{ 0.0f, 0.0f, 0.0f },
		vec3{ 0.0f, 1.0f, 0.0f },
		vec3{ 1.0f, 1.0f, 0.0f },
		vec3{ 1.0f, 0.0f, 0.0f }
	});
	spriteSquareVertexArrayBuffer->enableAttribute(0, 3);

	spriteSquareTexCoords = createVertexBuffer();
	spriteSquareTexCoords->setData({
		vec2{ 0.0f, 0.0f },
		vec2{ 0.0f, 1.0f },
		vec2{ 1.0f, 1.0f },
		vec2{ 1.0f, 0.0f }
	});
	spriteSquareVertexArrayBuffer->enableAttribute(1, 2);

	spriteSquareIndices = createIndexBuffer();
	spriteSquareIndices->setData({
		0, 1, 2, 0, 2, 3
	});
}

void OpenGLGraphicsSubSystem::viewportSetup()
{
	auto windowManager = getEngine()->getWindowManager();
	glViewport(0, 0, windowManager->getWindowWidth(), windowManager->getWindowHeight());
}

void OpenGLGraphicsSubSystem::ligthsSetup(GLSLShaderProgram* shader)
{
	for (size_t i = 0; i < MaxLightSourceNum; i++)
	{
		LightSource* lightSource = &DefaultLightSource;
		std::shared_ptr<LightSource> lightSourceShared;
		if (i < lightSources.size() && (lightSourceShared = lightSources[i].lock()))
			lightSource = lightSourceShared.get();

		shader->setUniform(LightAmbient[i], lightSource->ambient);
		shader->setUniform(LightDiffuse[i], lightSource->diffuse);
		shader->setUniform(LightSpecular[i], lightSource->specular);
		shader->setUniform(LightPosition[i], lightSource->position);
		shader->setUniform(LightConstantAttenuation[i], lightSource->constantAttenuation);
		shader->setUniform(LightLinearAttenuation[i], lightSource->linearAttenuation);
		shader->setUniform(LightQuadraticAttenuation[i], lightSource->quadraticAttenuation);
	}
}

void OpenGLGraphicsSubSystem::renderMeshes(Camera* camera)
{
	auto projectionMatrix = camera->getProjectionMatrix();
	auto viewMatrix = camera->getViewMatrix();

	std::unordered_set<ShaderProgram*> usedShaders(renderQueue.size());

	while (!renderQueue.empty())
	{
		if (auto meshRenderer = renderQueue.front().lock())
		{
			auto mesh = meshRenderer->getMesh();
			auto material = meshRenderer->getMaterial();
			auto vao = dynamic_cast<OpenGLMeshRenderer*>(meshRenderer.get())->getVertexArrayBuffer();
			auto texture = material->getTexture();
			auto hasTexture = texture && !mesh->getTexCoords().empty();
			auto shader = dynamic_cast<GLSLShaderProgram*>(material->getShader().get());
			auto shaderWasInitialized = usedShaders.find(shader) != usedShaders.end();
			auto modelMatrix = meshRenderer->getWorldTransformationMatrix();
			auto modelViewMatrix = viewMatrix * modelMatrix;
			auto normalMatrix = mat3(modelViewMatrix).inversed().transposed();

			shader->enable();

			if (!shaderWasInitialized)
			{
				shader->setUniform(ProjectionMatrix, projectionMatrix);
				shader->setUniform(ViewMatrix, viewMatrix);
			}

			shader->setUniform(ModelViewMatrix, modelViewMatrix);
			shader->setUniform(NormalMatrix, normalMatrix);

			shader->setUniform(MaterialHasTexture, hasTexture);

			if (hasTexture)
			{
				glActiveTexture(GL_TEXTURE0);
				texture->bind();
				shader->setUniform(MaterialTexture, 0);
			}

			shader->setUniform(MaterialAmbient, material->getAmbient());
			shader->setUniform(MaterialDiffuse, material->getDiffuse());
			shader->setUniform(MaterialSpecular, material->getSpecular());
			shader->setUniform(MaterialEmission, material->getEmission());
			shader->setUniform(MaterialShininess, material->getShininess());

			if (!shaderWasInitialized)
				ligthsSetup(shader);

			vao->bind();
			meshRenderer->getIndicesBuffer()->bind();
			glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);

			shader->disable();

			usedShaders.insert(shader);
		}
		renderQueue.pop_front();
	}
}

void OpenGLGraphicsSubSystem::renderSprites()
{
	auto windowManager = getEngine()->getWindowManager();
	auto windowWidth = windowManager->getWindowWidth();
	auto windowHeight = windowManager->getWindowHeight();

	while (!spriteRenderQueue.empty())
	{
		if (auto sprite = spriteRenderQueue.front().lock())
		{
			auto shader = dynamic_cast<GLSLShaderProgram*>(sprite->getShader().get());
			auto texture = dynamic_cast<OpenGLTexture*>(sprite->getTexture().get());

			vec2 size{ sprite->getWidth() / windowWidth, sprite->getHeight() / windowHeight };
			vec2 align;
			
			switch (sprite->getHorizontalAlign())
			{
			case Sprite::HorizontalAlign::Left:
				break;
			case Sprite::HorizontalAlign::Center:
				align.setX(-size.getX() / 2.0f);
				break;
			case Sprite::HorizontalAlign::Right:
				align.setX(-size.getX());
				break;
			}

			switch (sprite->getVerticalAlign())
			{
			case Sprite::VerticalAlign::Top:
				break;
			case Sprite::VerticalAlign::Center:
				align.setY(-size.getY() / 2.0f);
				break;
			case Sprite::VerticalAlign::Bottom:
				align.setY(-size.getY());
				break;
			}

			shader->enable();

			glActiveTexture(GL_TEXTURE0);
			texture->bind();
			shader->setUniform(SpriteTexture, 0);

			shader->setUniform(SpriteColor, sprite->getColor());

			auto modelMatrix = sprite->getTransform().getTransformationMatrix();
			shader->setUniform(ModelMatrix, modelMatrix);
			shader->setUniform(SpriteSize, size);
			shader->setUniform(SpriteAlign, align);

			spriteSquareVertexArrayBuffer->bind();
			spriteSquareIndices->bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			shader->disable();
		}
		spriteRenderQueue.pop_front();
	}
}
