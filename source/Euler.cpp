#include "Euler.h"

Euler::Euler(void)
{
}

string Euler::getName(void)
{
	return "Euler";
}

void Euler::DerivEval(std::vector<Particle*> pVector, std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt )
{
	// clear forces
	for (int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Force[0] = 0;
		pVector[i] -> m_Force[1] = 0;
	}

	// Apply forces
	for(int i = 0; i < forces.size(); i++) {
		forces[i] -> apply();
	}

	// Solve constraints
	ConstraintSolver::Calculate(pVector, constraints, 60, 5);

	// increase vel for each particle
	for (int i = 0; i < pVector.size(); i++) {
		pVector[i]->m_Velocity += pVector[i] -> m_Force * dt;
	}

	// Displace particles with velocity
	for (int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Position += (pVector[i] -> m_Velocity) * dt;
	}
}

Euler::~Euler(void)
{
}
