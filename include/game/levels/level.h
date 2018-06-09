#pragma once
#include <map>

#include "engine.h"
#include "game/components/orbit_camera.h"
#include "game/components/player_controller.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Level : public Scene
{
public:
	virtual ~Level() override;

	virtual void start() override;
	virtual void tick(float dt) override;

protected:
	virtual void resetPlayer();
	virtual void resetCamera();
	virtual void resetLevel();

	virtual bool lost() = 0;

	bool playerIsLowerThan(float height);

	virtual std::wstring getTitle() const = 0;
	virtual std::shared_ptr<Scene> getNextScene() const = 0;
	virtual std::string getLevelPath() const = 0;
 
	std::shared_ptr<GLSLShaderProgram> standardShader;
	std::shared_ptr<GLSLShaderProgram> spriteShader;
	std::shared_ptr<Font> font;

	Node* player;
	PhysicsBody* playerPhysicsBody;
	Node* level;
	Node* startPoint;
	OrbitCamera* orbitCamera;
	PhysicsWorld* physicsWorld;

private:
	void initShaders();
	void initPhysicsWorld();
	void initLevel();
	void initStartPoint();
	void initPlayer();
	void initCamera();
	void initPlayerController();
	void initControls();
	void initTrigger();
	void showLevelTitle();
	Node* loadNode(const std::string& filename, Node* parent = nullptr);
	Node* createNode(const aiScene* scene, const aiNode* sceneNode, Node* parent, const std::vector<std::shared_ptr<Mesh>>& meshes, const std::vector<std::shared_ptr<Material>>& materials, const std::map<std::string, std::shared_ptr<LightSource>>& lights);

	Sequence showLevelTitleSequence;
	std::unique_ptr<InputButton> exitButton;
};