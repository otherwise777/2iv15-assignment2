#pragma once
#include "IntegrationScheme.h"

class Euler :
	public IntegrationScheme
{
public:
	Euler(void);

	virtual string getName(void);

	virtual void DerivEval(std::vector<Particle*> pVector,  std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt );

	~Euler(void);
};

