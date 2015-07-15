#include "RigidBody.h"

int size = 4;
float positions[8];
float scale = 0.5;
float position[] = {0.5, 0.5};
float velocity[] = {0.0001, 0};
float rotation = 0;
float momentum = 0.001;

RigidBody::RigidBody(void)
{
	positions[0] = -0.5f;
	positions[1] = 0.5f;
	positions[2] = 0.5f;
	positions[3] = 0.5f;
	positions[4] = 0.5f;
	positions[5] = -0.5f;
	positions[6] = -0.5f;
	positions[7] = -0.5f;
}


void RigidBody::calculateCenterOfMass(void)
{

}

void RigidBody::draw(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	
	position[0] += velocity[0];
	position[1] += velocity[1];
	rotation += momentum;

	float pos[2];
	for (int i = 0; i < size; i++) {

		// apply rotation
		pos[0] = (positions[i * 2] * cos(rotation) + positions[i * 2 + 1] * sin(rotation));
		pos[1] = (-positions[i * 2] * sin(rotation) + positions[i * 2 + 1] * cos(rotation));

		// apply scale
		pos[0] *= scale;
		pos[1] *= scale;

		// apply translation
		pos[0] +=  position[0];
		pos[1] +=  position[1];

		glVertex2f(pos[0], pos[1]);
	}
	glEnd();
}

RigidBody::~RigidBody(void)
{
}
