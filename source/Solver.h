#pragma once
using namespace std;

#include <vector>
#include "RigidBody.h"

void add_source ( int N, float * x, float * s, float dt );
void set_bnd ( int N, int b, float * x, bool * boundary );
void lin_solve ( int N, int b, float * x, float * x0, bool * boundary, float a, float c );
void diffuse ( int N, int b, float * x, float * x0, bool * boundary, float diff, float dt );
void advect ( int N, int b, float * d, float * d0, float * u, float * v, bool * boundary, float dt );
void project ( int N, float * u, float * v, float * p, float * div, bool * boundary );
void dens_step ( int N, float * x, float * x0, float * u, float * v, bool * boundary, float diff, float dt );
void vel_step ( int N, float * u, float * v, float * u0, float * v0, bool * boundary, vector<RigidBody> rigidbodies, float visc, float dt );