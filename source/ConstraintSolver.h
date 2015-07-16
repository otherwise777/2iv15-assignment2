#pragma once

using namespace std;

#include <Vector>

#include "Particle.h"
#include "Matrix.h"
#include "IConstraint.h""
#include "linearSolver.h"

class ConstraintSolver
{
public:
	ConstraintSolver(void);

	static void Calculate(std::vector<Particle*> pVector, std::vector<IConstraint*> constraints, float ks, float kd);

	~ConstraintSolver(void);
};

