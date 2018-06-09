#include "game/levels/level.h"

Level::~Level() = default;

void Level::start()
{
	Scene::start();

	initShaders();
	initPhysicsWorld();
	initLevel();
	initStartPoint();
	initPlayer();
	initCamera();
	initPlayerController();
	initControls();
	initTrigger();
	showLevelTitle();
}

void Level::tick(float dt)
{
	Scene::tick(dt);
	if (exitButton->isPressed())
	{
		getEngine()->stop();
		return;
	}

	if (lost())
		resetLevel();
}

void Level::resetPlayer()
{
	Transform startPointTransform = startPoint->getWorldTransform();
	playerPhysicsBody->setWorldTransform(startPointTransform);
	playerPhysicsBody->stop();
}

void Level::resetCamera()
{
	orbitCamera->setAngleX(0.5f);
	orbitCamera->setAngleY(0.0f);
}

void Level::resetLevel()
{
	resetPlayer();
	resetCamera();
}

bool Level::playerIsLowerThan(float height)
{
	return player->getWorldTransform().position.getY() < height;
}

void Level::initShaders()
{
	standardShader = std::make_shared<GLSLShaderProgram>();
	standardShader->addShader(ShaderProgram::ShaderType::Vertex, getEngine()->getFileManager()->readFileToString("assets/shaders/default.vert"));
	standardShader->addShader(ShaderProgram::ShaderType::Fragment, getEngine()->getFileManager()->readFileToString("assets/shaders/default.frag"));
	standardShader->link({ 
		{ "position", 0 },
		{ "normal", 1 },
		{ "texCoord", 2 }
	});

	spriteShader = std::make_shared<GLSLShaderProgram>();
	spriteShader->addShader(ShaderProgram::ShaderType::Vertex, getEngine()->getFileManager()->readFileToString("assets/shaders/sprite.vert"));
	spriteShader->addShader(ShaderProgram::ShaderType::Fragment, getEngine()->getFileManager()->readFileToString("assets/shaders/sprite.frag"));
	spriteShader->link({
		{ "position", 0 },
		{ "texCoord", 1 }
	});
}

void Level::initPhysicsWorld()
{
	auto physicsWorldComponent = getRoot().addComponent<PhysicsWorldComponent>();
	physicsWorld = physicsWorldComponent->getPhysicsWorld();
}

void Level::initLevel()
{
	level = loadNode(getLevelPath());
	level->setLocalTransform(Transform({ 0.0f, 0.0f, 0.0f }, Quaternion(), { 0.01f, 0.01f, 0.01f }));

	const std::string StaticPrefix = "Static";
	const std::string KinematicPrefix = "Kinematic";

	for (auto& child : level->getChilds())
	{
		auto meshComponent = child->findComponent<MeshComponent>();
		if (meshComponent)
		{
			Transform transform = child->getWorldTransform();
			auto mesh = meshComponent->getMesh();
			auto shape = getEngine()->getPhysics()->createMeshShape(mesh, transform.scale);
			auto body = physicsWorld->createPhysicsBody(shape, transform.position, transform.rotation, 0.0f);
			body->setFriction(1.0f);
			if (child->getName().substr(0, StaticPrefix.size()) == StaticPrefix)
				child->addComponent<StaticBodyComponent>(std::move(body));
			else if (child->getName().substr(0, KinematicPrefix.size()) == KinematicPrefix)
				child->addComponent<KinematicBodyComponent>(std::move(body));
		}
	}
}

void Level::initStartPoint()
{
	startPoint = level->findChild("Start", true);
}

void Level::initPlayer()
{
	player = loadNode("assets/models/player.fbx");
	player->setWorldTransform(startPoint->getWorldTransform());
	player->updateLocalTransform([](auto& transform) {
		transform.scale = { 0.01f, 0.01f, 0.01f };
	});
	Transform transform = player->getWorldTransform();
	auto shape = getEngine()->getPhysics()->createSphereShape(1.0f);
	float mass = 1.0f;
	auto body = physicsWorld->createPhysicsBody(shape, transform.position, transform.rotation, mass);
	body->setRestitution(0.5f);
	body->setFriction(10.0f);
	body->setRollingFriction(0.5f);
	body->setSpinningFriction(0.5f);
	playerPhysicsBody = body.get();
	player->addComponent<DynamicBodyComponent>(std::move(body));
}

void Level::initCamera()
{
	Node* cameraNode = getRoot().addChild();
	cameraNode->addComponent<CameraComponent>(getEngine()->getCamera());
	orbitCamera = cameraNode->addComponent<OrbitCamera>(player, 10.0f);
}

void Level::initPlayerController()
{
	player->addComponent<PlayerController>(orbitCamera);
}

void Level::initControls()
{
	exitButton = getEngine()->getInput()->createButton();
	exitButton->addKeyboardKey(Keyboard::Key::Escape);
}

void Level::initTrigger()
{
	auto triggerNode = getRoot().findChild("LevelClearTrigger", true);

	auto meshComponent = triggerNode->findComponent<MeshComponent>();
	Transform transform = triggerNode->getWorldTransform();
	auto mesh = meshComponent->getMesh();
	auto shape = getEngine()->getPhysics()->createMeshShape(mesh, transform.scale);
	auto body = physicsWorld->createPhysicsBody(shape, transform.position, transform.rotation, 0.0f);
	auto trigger = triggerNode->addComponent<TriggerComponent>(std::move(body));

	triggerNode->removeComponents<MeshComponent>();
	trigger->getPhysicsBody()->disableContactResponse();

	trigger->addTrigger(playerPhysicsBody, [this]() {
		getEngine()->getSceneManager()->setScene(getNextScene());
	});
}

void Level::showLevelTitle()
{
	font = std::make_shared<Font>("assets/fonts/Mplus1p-Regular.ttf");
	font->setSize(48);

	Node* textNode = getRoot().addChild();
	auto textComponent = textNode->addComponent<TextComponent>(spriteShader, font);

	showLevelTitleSequence = Sequence{
		std::make_shared<CallFunction>([=]() {
			textComponent->setVerticalAlign(Sprite::VerticalAlign::Center);
			textComponent->setHorizontalAlign(Sprite::HorizontalAlign::Center);
			textComponent->setText(getTitle());
			textNode->setLocalTransform(Transform({ 0.5f, 0.25f }));
		}),

		std::make_shared<WaitAction>(2.0f),

		std::make_shared<LinearAction>(2.0f, 100, 1.0f, 0.0f, [=](float value) {
			textComponent->setAlpha(value);
		}),

		std::make_shared<CallFunction>([=]() {
			textNode->removeFromParent();
		}),
	};
	showLevelTitleSequence.start(getEngine());
}

Node* Level::loadNode(const std::string& filename, Node* parent)
{
	if (!parent)
		parent = &getRoot();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_Triangulate |
		aiProcess_GenNormals |
		aiProcess_SortByPType);

	if (!scene)
		throw std::runtime_error(importer.GetErrorString());

	std::vector<std::shared_ptr<Mesh>> meshes;

	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		auto sceneMesh = scene->mMeshes[i];
		auto mesh = std::make_shared<Mesh>();

		std::vector<vec3> vertices(sceneMesh->mNumVertices);
		std::vector<vec3> normals(sceneMesh->mNumVertices);
		std::vector<unsigned int> indices(sceneMesh->mNumFaces * 3);
		std::vector<vec2> texCoords(sceneMesh->HasTextureCoords(0) ? sceneMesh->mNumVertices : 0);

		for (unsigned int j = 0; j < vertices.size(); j++)
		{
			vertices[j] = { sceneMesh->mVertices[j].x, sceneMesh->mVertices[j].y, sceneMesh->mVertices[j].z };
			normals[j] = { sceneMesh->mNormals[j].x, sceneMesh->mNormals[j].y, sceneMesh->mNormals[j].z };
		}

		for (unsigned int j = 0; j < sceneMesh->mNumFaces; j++)
		{
			const auto& face = sceneMesh->mFaces[j];
			indices[j * 3] = face.mIndices[0];
			indices[j * 3 + 1] = face.mIndices[1];
			indices[j * 3 + 2] = face.mIndices[2];
		}

		for (size_t j = 0; j < texCoords.size(); j++)
		{
			auto& texCoord = sceneMesh->mTextureCoords[0][j];
			texCoords[j] = { texCoord.x, texCoord.y };
		}

		mesh->setVertices(vertices);
		mesh->setNormals(normals);
		mesh->setIndices(indices);
		mesh->setTexCoords(texCoords);

		meshes.push_back(mesh);
	}

	std::vector<std::shared_ptr<Material>> materials;

	for (unsigned int i = 0; i < scene->mNumMaterials; i++)
	{
		auto sceneMaterial = scene->mMaterials[i];
		auto material = std::make_shared<Material>(standardShader);

		float opacity = 1.0f;
		float shininessStrength = 1.0f;

		auto a = sceneMaterial->mProperties[0];
		auto b = sceneMaterial->mProperties[1];

		sceneMaterial->Get(AI_MATKEY_OPACITY, opacity);
		sceneMaterial->Get(AI_MATKEY_SHININESS_STRENGTH, shininessStrength);

		aiColor3D color;
		if (sceneMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color) == aiReturn_SUCCESS)
			material->setAmbient({ color.r, color.g, color.b, opacity });

		if (sceneMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == aiReturn_SUCCESS)
			material->setDiffuse({ color.r, color.g, color.b, opacity });

		if (sceneMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) == aiReturn_SUCCESS)
			material->setSpecular({ color.r * shininessStrength, color.g * shininessStrength, color.b * shininessStrength, opacity });

		if (sceneMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, color) == aiReturn_SUCCESS)
			material->setEmission({ color.r, color.g, color.b, opacity });

		float shininess = 0.0f;
		if (sceneMaterial->Get(AI_MATKEY_SHININESS, shininess) == aiReturn_SUCCESS)
			material->setShininess(shininess);

		materials.push_back(material);
	}

	std::map<std::string, std::shared_ptr<LightSource>> lights;

	for (unsigned int i = 0; i < scene->mNumLights; i++)
	{
		auto light = scene->mLights[i];
		auto lightSource = std::make_shared<LightSource>();

		const vec4 ambient = { light->mColorAmbient.r, light->mColorAmbient.g, light->mColorAmbient.b, 1.0f };
		const vec4 diffuse = { light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b, 1.0f };
		const vec4 specular = { light->mColorSpecular.r, light->mColorSpecular.g, light->mColorSpecular.b, 1.0f };
		const vec3 direction = { light->mDirection.x, light->mDirection.y, light->mDirection.z };
		const vec3 position = { light->mPosition.x, light->mPosition.y, light->mPosition.z };

		const float attenuationConstant = light->mAttenuationConstant > 1e-5 ? light->mAttenuationConstant : 1.0f;

		switch (light->mType)
		{
		case aiLightSource_AMBIENT:
			lightSource->ambientLight(ambient);
			break;
		case aiLightSource_DIRECTIONAL:
			lightSource->directionalLight(ambient, diffuse, specular, direction);
			break;
		case aiLightSource_POINT:
			lightSource->pointLight(ambient, diffuse, specular, position, attenuationConstant, light->mAttenuationLinear, light->mAttenuationQuadratic);
			break;
		}

		lights.insert(std::make_pair(std::string(light->mName.data, light->mName.length), lightSource));
	}

	return createNode(scene, scene->mRootNode, parent, meshes, materials, lights);
}

Node* Level::createNode(const aiScene* scene, const aiNode* sceneNode, Node* parent, const std::vector<std::shared_ptr<Mesh>>& meshes, const std::vector<std::shared_ptr<Material>>& materials, const std::map<std::string, std::shared_ptr<LightSource>>& lights)
{
	Node* node = parent->addChild();

	node->setName(std::string(sceneNode->mName.data, sceneNode->mName.length));

	aiVector3D scale, position;
	aiQuaternion rotation;
	sceneNode->mTransformation.Decompose(scale, rotation, position);

	node->setLocalTransform(Transform({ position.x, position.y, position.z }, Quaternion(rotation.x, rotation.y, rotation.z, rotation.w), { scale.x, scale.y, scale.z }));

	for (unsigned int i = 0; i < sceneNode->mNumMeshes; i++)
	{
		unsigned int meshIndex = sceneNode->mMeshes[i];
		unsigned int materialIndex = scene->mMeshes[meshIndex]->mMaterialIndex;
		node->addComponent<MeshComponent>(meshes[meshIndex], materials[materialIndex]);
	}

	auto light = lights.find(node->getName());

	if (light != lights.end())
	{
		auto lightSource = light->second;
		node->addComponent<LightComponent>(lightSource);
	}

	for (unsigned int i = 0; i < sceneNode->mNumChildren; i++)
		createNode(scene, sceneNode->mChildren[i], node, meshes, materials, lights);

	return node;
}
