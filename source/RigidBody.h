#pragma once
using namespace std;

#include <cmath>
#include <GL/glut.h>

class RigidBody
{
public:
	RigidBody(void);

	void draw(void);

	~RigidBody(void);

private:
	void calculateCenterOfMass(void);
};

