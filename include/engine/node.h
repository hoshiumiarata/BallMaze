#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <functional>
#include <string>

#include "components/component.h"
#include "math/transform.h"

#include "mixins/engine_access_mixin.h"

class Node : public EngineAccessMixin
{
public:
	~Node();

	Node* addChild();
	Node* findChild(const std::string& name, bool recursive = false);
	const std::vector<std::unique_ptr<Node>>& getChilds() const;
	void removeChild(Node* child);

	template <typename ComponentType, typename... Args>
	ComponentType* addComponent(Args... args);

	void update(float dt);

	template <typename ComponentType>
	ComponentType* findComponent() const;

	template <typename ComponentType>
	std::vector<ComponentType*> findComponents() const;

	template <typename ComponentType>
	void removeComponents();

	Node* getParent() const;
	void setParent(Node* parent);
	void removeFromParent();

	const std::string& getName() const;
	void setName(const std::string& name);

	const Transform& getLocalTransform() const;
	void setLocalTransform(const Transform& transform);
	void updateLocalTransform(const std::function<void(Transform&)>& updater);
	const mat4& getWorldTransformationMatrix() const;
	Transform getWorldTransform() const;
	void setWorldTransform(const Transform& transform);
	void updateWorldTransform(const std::function<void(Transform&)>& updater);

	void updateWorldTransformationMatrix();
private:
	std::vector<std::unique_ptr<Node>> childs;
	std::vector<std::unique_ptr<Component>> components;

	Node* parent = nullptr;

	std::string name;

	Transform localTransform;
	mat4 worldTransformationMatrix = mat4::identity();
};

template <typename ComponentType, typename... Args>
ComponentType* Node::addComponent(Args... args)
{
	ComponentType* component = new ComponentType(std::forward<Args>(args)...);
	component->setEngine(getEngine());
	component->setParent(this);
	components.push_back(std::unique_ptr<ComponentType>(component));
	component->initialize();
	return component;
}

template<typename ComponentType>
inline ComponentType* Node::findComponent() const
{
	for (const auto& component : components)
	{
		if (auto castedComponent = dynamic_cast<ComponentType*>(component.get()))
			return castedComponent;
	}

	return nullptr;
}

template<typename ComponentType>
inline std::vector<ComponentType*> Node::findComponents() const
{
	std::vector<ComponentType*> resultComponents;

	for (auto& component : components)
	{
		if (auto castedComponent = dynamic_cast<ComponentType*>(component.get()))
			resultComponents.push_back(castedComponent);
	}

	return resultComponents;
}

template<typename ComponentType>
inline void Node::removeComponents()
{
	components.erase(
		std::remove_if(components.begin(), components.end(), [](const auto& component) {
			return dynamic_cast<ComponentType*>(component.get()) != nullptr;
		}),
		components.end());
}