#pragma once
#include "integrationscheme.h"

class RungeKutta4thOrder :
	public IntegrationScheme
{
public:
	RungeKutta4thOrder(void);

	virtual string getName(void);

	virtual void DerivEval(std::vector<Particle*> pVector,  std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt);

	~RungeKutta4thOrder(void);

private:
	std::vector<Vec2f> positions;

};

