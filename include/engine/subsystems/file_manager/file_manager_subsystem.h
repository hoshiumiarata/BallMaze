#pragma once

#include <string>

#include "../subsystem_interface.h"

class FileManagerSubSystem : public ISubSystem
{
public:
	virtual std::string readFileToString(const std::string& path);

	virtual bool init() override;
	virtual bool update(float dt) override;
	virtual bool postUpdate() override;
	virtual bool destroy() override;

	virtual const std::string getName() const override;
};