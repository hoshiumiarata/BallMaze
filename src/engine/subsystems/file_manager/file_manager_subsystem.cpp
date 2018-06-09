#include "engine/subsystems/file_manager/file_manager_subsystem.h"

#include <exception>
#include <fstream>

std::string FileManagerSubSystem::readFileToString(const std::string & path)
{
	std::ifstream in(path, std::ios::in | std::ios::binary);
	if (!in)
		throw std::runtime_error(getName() + ": Cannot open file " + path);

	std::string result;

	in.seekg(0, std::ios::end);
	result.resize(static_cast<size_t>(in.tellg()));
	in.seekg(0, std::ios::beg);
	in.read(&result[0], result.size());
	in.close();

	return result;
}

bool FileManagerSubSystem::init()
{
	return true;
}

bool FileManagerSubSystem::update(float dt)
{
	return true;
}

bool FileManagerSubSystem::postUpdate()
{
	return true;
}

bool FileManagerSubSystem::destroy()
{
	return true;
}

const std::string FileManagerSubSystem::getName() const
{
	return "File Manager";
}
