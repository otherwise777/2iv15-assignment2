#pragma once
#include "RigidBody.h"

class Rectangle : public RigidBody
{
public:
	Rectangle(void);

	void Rectangle::act(float* u, float* v);

	~Rectangle(void);
};

