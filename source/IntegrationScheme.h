#pragma once

#include "Particle.h"
#include "IForce.h"
#include "IConstraint.h"
#include "ConstraintSolver.h"
#include <vector>

class IntegrationScheme
{
public:
	virtual string getName(void) = 0;

	virtual void DerivEval(std::vector<Particle*> pVector,  std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt ) = 0;
};
