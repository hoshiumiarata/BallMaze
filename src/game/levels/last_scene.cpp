#include "game/levels/last_scene.h"

void LastScene::start()
{
	Scene::start();

	exitButton = getEngine()->getInput()->createButton();
	exitButton->addKeyboardKey(Keyboard::Key::Escape);

	spriteShader = std::make_shared<GLSLShaderProgram>();
	spriteShader->addShader(ShaderProgram::ShaderType::Vertex, getEngine()->getFileManager()->readFileToString("assets/shaders/sprite.vert"));
	spriteShader->addShader(ShaderProgram::ShaderType::Fragment, getEngine()->getFileManager()->readFileToString("assets/shaders/sprite.frag"));
	spriteShader->link({
		{ "position", 0 },
		{ "texCoord", 1 }
	});

	font = std::make_shared<Font>("assets/fonts/Mplus1p-Regular.ttf");
	font->setSize(48);

	Node* textNode = getRoot().addChild();
	auto textComponent = textNode->addComponent<TextComponent>(spriteShader, font);
	textComponent->setText(L"最後までプレイしてくれて\nありがとうございます！");
	textComponent->setHorizontalAlign(Sprite::HorizontalAlign::Center);
	textComponent->setVerticalAlign(Sprite::VerticalAlign::Center);
	textNode->setLocalTransform(Transform({ 0.5f, 0.5f }));
}

void LastScene::tick(float dt)
{
	Scene::tick(dt);

	if (exitButton->isPressed())
	{
		getEngine()->stop();
		return;
	}
}
