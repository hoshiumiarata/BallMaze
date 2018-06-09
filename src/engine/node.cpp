#include "engine/node.h"

Node::~Node()
{
	childs.clear();
	components.clear();
}

Node* Node::addChild()
{
	auto child = std::make_unique<Node>();
	Node* childPtr = child.get();
	child->setEngine(getEngine());
	child->setParent(this);
	childs.push_back(std::move(child));
	return childPtr;
}

Node* Node::findChild(const std::string& name, bool recursive)
{
	for (auto& child : childs)
	{
		if (child->getName() == name)
			return child.get();
	}

	if (recursive)
	{
		for (auto& child : childs)
		{
			if (auto node = child->findChild(name, recursive))
				return node;
		}
	}

	return nullptr;
}

const std::vector<std::unique_ptr<Node>>& Node::getChilds() const
{
	return childs;
}

void Node::removeChild(Node* child)
{
	auto it = std::find_if(childs.begin(), childs.end(), [&](auto& c) { return c.get() == child; });
	if (it != childs.end())
		childs.erase(it);
}

void Node::update(float dt)
{
	for (const auto& component : components)
		component->tick(dt);

	for (const auto& child : childs)
		child->update(dt);
}

Node* Node::getParent() const
{
	return parent;
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
	updateWorldTransformationMatrix();
}

void Node::removeFromParent()
{
	getParent()->removeChild(this);
}

const std::string& Node::getName() const
{
	return name;
}

void Node::setName(const std::string& name)
{
	this->name = name;
}

const Transform& Node::getLocalTransform() const
{
	return localTransform;
}

void Node::setLocalTransform(const Transform& transform)
{
	localTransform = transform;
	updateWorldTransformationMatrix();
}

void Node::updateLocalTransform(const std::function<void(Transform&)>& updater)
{
	updater(localTransform);
	updateWorldTransformationMatrix();
}

const mat4& Node::getWorldTransformationMatrix() const
{
	return worldTransformationMatrix;
}

Transform Node::getWorldTransform() const
{
	return Transform(getWorldTransformationMatrix());
}

void Node::updateWorldTransformationMatrix()
{
	if (parent)
		worldTransformationMatrix = parent->getWorldTransformationMatrix() * localTransform.getTransformationMatrix();
	else
		worldTransformationMatrix = localTransform.getTransformationMatrix();

	for (auto& child : childs)
		child->updateWorldTransformationMatrix();
}

void Node::setWorldTransform(const Transform& transform)
{
	if (parent)
	{
		auto localTransformationMatrix = parent->getWorldTransformationMatrix().inversed() * transform.getTransformationMatrix();
		localTransform = Transform(localTransformationMatrix);
	}
	else
	{
		localTransform = transform;
	}

	updateWorldTransformationMatrix();
}

void Node::updateWorldTransform(const std::function<void(Transform&)>& updater)
{
	Transform worldTransform = parent ? getWorldTransform() : localTransform;
	updater(worldTransform);

	if (parent)
	{
		auto localTransformationMatrix = parent->getWorldTransformationMatrix().inversed() * worldTransform.getTransformationMatrix();
		localTransform = Transform(localTransformationMatrix);
	}
	else
		localTransform = worldTransform;
	
	updateWorldTransformationMatrix();
}
