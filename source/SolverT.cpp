#include "Particle.h"
#include "IForce.h"
#include "IConstraint.h"

#include "IntegrationScheme.h"
#include "Euler.h"
#include "MidPoint.h"
#include "RungeKutta4thOrder.h"

#include <vector>

static IntegrationScheme * scheme = new Euler();
static int i = 0;

void simulation_step(std::vector<Particle*> pVector, std::vector<IForce*> forces, std::vector<IConstraint*> constraints, float dt)
{
	scheme ->  DerivEval(pVector,  forces, constraints, dt);
}

string getIntegrationScheme(void)
{
	return scheme -> getName();
}

void changeIntegrationScheme(void)
{
	i = ++i % 3;
	
	free(scheme);

	switch(i)
	{
		case 0:
			scheme = new Euler();
			break;
		case 1:
			scheme = new MidPoint();
			break;
		case 2:
			scheme = new RungeKutta4thOrder();
			break;
	}
}