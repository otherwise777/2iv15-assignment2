#include "MidPoint.h"

MidPoint::MidPoint(void)
{
	positions = std::vector<Vec2f>();
}

string MidPoint::getName(void)
{
	return "Midpoint";
}

void MidPoint::DerivEval(std::vector<Particle*> pVector, std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt )
{
	// Clear positions vector
	positions.clear();

	// clear forces and store positions
	for (unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Force[0] = 0;
		pVector[i] -> m_Force[1] = 0;

		positions.push_back(pVector[i] -> m_Position);
	}

	// Apply forces
	for(unsigned int i = 0; i < forces.size(); i++) {
		forces[i] -> apply();
	}

	ConstraintSolver::Calculate(pVector, constraints, 100, 2);

	// increase velocity for each particle
	for (unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i]->m_Velocity += pVector[i] -> m_Force * dt;
	}

	// Displace particles with velocity to midpoint
	for (unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Position += (pVector[i] -> m_Velocity) * (dt / 2);
	}

	// clear forces
	for (unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Force[0] = 0;
		pVector[i] -> m_Force[1] = 0;
	}

	// Calculate forces on midpoint
	for(unsigned int i = 0; i < forces.size(); i++) {
		forces[i] -> apply();
	}

	ConstraintSolver::Calculate(pVector, constraints, 100, 2);

	// Displace particle from startposition
	for (unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Velocity += pVector[i] -> m_Force * dt;
		pVector[i] -> m_Position = positions[i] + pVector[i] -> m_Velocity * dt;
	}
}

MidPoint::~MidPoint(void)
{
}
