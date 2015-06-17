#pragma once

#include <gfx/vec2.h>
#include <Singleton.h>

class FieldToolbox : public Singleton<FieldToolbox>
{
public:
	FieldToolbox(void);
	virtual ~FieldToolbox(void);

	void LinearSolver(float a, float c, ScalarField *SolutionField);
	void LinearSolver(float a, float c, VectorField *SolutionField);
};
