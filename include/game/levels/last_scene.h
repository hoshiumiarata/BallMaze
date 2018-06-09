#pragma once

#include "engine.h"

class LastScene : public Scene
{
public:
	virtual void start() override;
	virtual void tick(float dt) override;
private:
	std::shared_ptr<GLSLShaderProgram> spriteShader;
	std::shared_ptr<Font> font;
	std::unique_ptr<InputButton> exitButton;
};