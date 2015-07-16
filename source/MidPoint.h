#pragma once
#include "integrationscheme.h"

class MidPoint :
	public IntegrationScheme
{
public:
	MidPoint(void);

	virtual string getName(void);

	virtual void DerivEval(std::vector<Particle*> pVector,  std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt);

	~MidPoint(void);

private:
	std::vector<Vec2f> positions;
};

