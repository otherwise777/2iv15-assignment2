#include "RungeKutta4thOrder.h"


RungeKutta4thOrder::RungeKutta4thOrder(void)
{
	positions = std::vector<Vec2f>();
}

string RungeKutta4thOrder::getName(void)
{
	return "4th order Runge Kutta";
}

void RungeKutta4thOrder::DerivEval(std::vector<Particle*> pVector, std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt )
{
	// Clear positions vector
	positions.clear();

	// clear forces and store positions
	for (unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Force[0] = 0;
		pVector[i] -> m_Force[1] = 0;

		positions.push_back(pVector[i] -> m_Position);
	}

	//runge-kutta
	std::vector<Vec2f> k1;
	std::vector<Vec2f> k2;
	std::vector<Vec2f> k3;
	std::vector<Vec2f> k4;

	// Accumulate forces
	for(unsigned int i = 0; i < forces.size(); i++) {
		forces[i] -> apply();
	}

	ConstraintSolver::Calculate(pVector, constraints, 100, 2);
	
	for (int i = 0; i < pVector.size(); i++)
	{
		pVector[i]->m_Velocity += ((pVector[i]->m_Force * dt));
		k1.push_back(pVector[i]->m_Velocity);
		pVector[i]->m_Position += pVector[i]->m_Velocity * (dt / 2);
	}

	// Clear forces
	for(unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Force = 0;
	}

	// Accumulate forces
	for(unsigned int i = 0; i < forces.size(); i++) {
		forces[i] -> apply();
	}

	ConstraintSolver::Calculate(pVector, constraints, 100, 2);
	
	for (int i = 0; i < pVector.size(); i++)
	{
		pVector[i]->m_Velocity += (pVector[i]->m_Force * dt);
		k2.push_back(pVector[i]->m_Velocity);
		pVector[i]->m_Position = positions[i] + pVector[i]->m_Velocity * (dt / 2);
	}

	// Clear forces
	for(unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Force = 0;
	}

	// Accumulate forces
	for(unsigned int i = 0; i < forces.size(); i++) {
		forces[i] -> apply();
	}

	ConstraintSolver::Calculate(pVector, constraints, 100, 2);
	
	//save k3 and set position for k4
	for (int i = 0; i < pVector.size(); i++)
	{
		pVector[i]->m_Velocity += (pVector[i]->m_Force * dt);
		k3.push_back(pVector[i]->m_Velocity);
		pVector[i]->m_Position = positions[i] + pVector[i]->m_Velocity * dt;
	}
	
	// Clear forces
	for(unsigned int i = 0; i < pVector.size(); i++) {
		pVector[i] -> m_Force = 0;
	}

	// Accumulate forces
	for(unsigned int i = 0; i < forces.size(); i++) {
		forces[i] -> apply();
	}

	ConstraintSolver::Calculate(pVector, constraints, 100, 2);
	
	//save k4 and use it to calculate the actual position
	for (int i = 0; i < pVector.size(); i++)
	{
		pVector[i]->m_Velocity += (pVector[i]->m_Force * dt);
		k4.push_back(pVector[i]->m_Velocity);
		pVector[i]->m_Position = positions[i] + (dt / 6)*(k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
	}
}

RungeKutta4thOrder::~RungeKutta4thOrder(void)
{
}
