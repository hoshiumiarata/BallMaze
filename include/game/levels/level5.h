#pragma once

#include "level.h"

class Level5 : public Level
{
public:
	virtual void start() override;
	virtual void tick(float dt) override;
protected:
	virtual void resetLevel() override;
	virtual bool lost() override;
	virtual std::wstring getTitle() const override;
	virtual std::shared_ptr<Scene> getNextScene() const override;
	virtual std::string getLevelPath() const override;

private:
	bool trapActivated = false;
	PhysicsBody* floorButtonBody;
	PhysicsBody* trapBody;
	PhysicsBody* hiddenDoorBody;

	vec3 originalHiddenDoorPosition;
	vec3 originalFloorPosition;
	Quaternion originalTrapRotation;

	Sequence trapSequence;
};