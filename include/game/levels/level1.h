#pragma once

#include "level.h"

class Level1 : public Level
{
public:
	virtual void start() override;
	virtual void tick(float dt) override;
protected:
	virtual bool lost() override;
	virtual std::wstring getTitle() const override;
	virtual std::shared_ptr<Scene> getNextScene() const override;
	virtual std::string getLevelPath() const override;
};