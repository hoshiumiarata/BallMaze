#pragma once

class PhysicsBody;

struct HitInfo
{
	bool hasHit;
	PhysicsBody* physicsBody;
	vec3 point;
	vec3 normal;
};