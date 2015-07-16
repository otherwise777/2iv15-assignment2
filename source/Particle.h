#pragma once

#include <gfx/vec2.h>
#include "RigidBody.h"

class Particle : public RigidBody
{
public:

	Particle(const Vec2f & ConstructPos);
	virtual ~Particle(void);

	void reset();

	void drawSpeed(void);
	void drawForce(void);
	void draw();

	int id;
	Vec2f m_ConstructPos;
	Vec2f m_Position;
	Vec2f m_Velocity;
	Vec2f m_Force;
};
