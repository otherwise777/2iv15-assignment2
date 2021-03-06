#include "solver.h"

#define IX(i,j) ((i)+(N+2)*(j))
#define SWAP(x0,x) {float * tmp=x0;x0=x;x=tmp;}
#define FOR_EACH_CELL for ( i=1 ; i<=N ; i++ ) { for ( j=1 ; j<=N ; j++ ) {
#define END_FOR }}

void add_source ( int N, float * x, float * s, float dt )
{
	int i, size=(N+2)*(N+2);
	for ( i=0 ; i<size ; i++ ) x[i] += dt*s[i];
}

void vorticityConfinement(int N, float p[], float k[]) {

	float *forces = new float[(N + 2) * (N + 2)]();
	int *sign = new int[(N + 2) * (N + 2)]();

	int i, j;
	FOR_EACH_CELL
		float dudy = (p[IX(i, j + 1)] - p[IX(i, j - 1)]) / 2;
		float dvdx = (k[IX(i + 1, j)] - k[IX(i - 1, j)]) / 2;

		float toStore = dvdx - dudy;
		forces[IX(i, j)] = abs(toStore);

		sign[IX(i, j)] = toStore < 0 ? -1 : 1;
	END_FOR

	FOR_EACH_CELL
		float dwdx = (forces[IX(i + 1, j)] - forces[IX(i - 1, j)]) * 0.5f;
		float dwdy = (forces[IX(i, j + 1)] - forces[IX(i, j - 1)]) * 0.5f;

		float length = sqrt(dwdx * dwdx + dwdy * dwdy);

		if (length != 0){
			dwdx /= length/2;
			dwdy /= length/2;
		}

		float v2 = sign[IX(i, j)] * forces[IX(i, j)];

		p[IX(i, j)] = dwdy * -v2;
		k[IX(i, j)] = dwdx * v2;
		END_FOR

		free(forces);
		free(sign);
}

void set_bnd ( int N, int b, float * x, bool * boundary, vector<RigidBody*> rigidbodies )
{
	int i, j;

	for ( i=1 ; i<=N ; i++ ) {
		x[IX(0  ,i)] = b==1 ? -x[IX(1,i)] : x[IX(1,i)];
		x[IX(N+1,i)] = b==1 ? -x[IX(N,i)] : x[IX(N,i)];
		x[IX(i,0  )] = b==2 ? -x[IX(i,1)] : x[IX(i,1)];
		x[IX(i,N+1)] = b==2 ? -x[IX(i,N)] : x[IX(i,N)];
	}

	// Additional boundary conditions
	FOR_EACH_CELL
		if (boundary[IX(i, j)]) {
			x[IX(i, j)] = 0;
			x[IX(i - 1, j)] = b==1 ? -x[IX(i - 2, j)] : x[IX(i - 2, j)];
			x[IX(i + 1, j)] = b==1 ? -x[IX(i + 2, j)] : x[IX(i + 2, j)];
			x[IX(i, j - 1)] = b==2 ? -x[IX(i, j - 2)] : x[IX(i, j - 2)];
			x[IX(i, j + 1)] = b==2 ? -x[IX(i, j + 2)] : x[IX(i, j + 2)];
		}

		for (int r = 0; r < rigidbodies.size(); r++) {
			if (rigidbodies[r] -> pointInPolygon(i, j)) {
				x[IX(i, j)] = 0;
				x[IX(i - 1, j)] = b==1 ? -x[IX(i - 2, j)] : x[IX(i - 2, j)];
				x[IX(i + 1, j)] = b==1 ? -x[IX(i + 2, j)] : x[IX(i + 2, j)];
				x[IX(i, j - 1)] = b==2 ? -x[IX(i, j - 2)] : x[IX(i, j - 2)];
				x[IX(i, j + 1)] = b==2 ? -x[IX(i, j + 2)] : x[IX(i, j + 2)];
			}
		}
		END_FOR

			x[IX(0  ,0  )] = 0.5f*(x[IX(1,0  )]+x[IX(0  ,1)]);
		x[IX(0  ,N+1)] = 0.5f*(x[IX(1,N+1)]+x[IX(0  ,N)]);
		x[IX(N+1,0  )] = 0.5f*(x[IX(N,0  )]+x[IX(N+1,1)]);
		x[IX(N+1,N+1)] = 0.5f*(x[IX(N,N+1)]+x[IX(N+1,N)]);
}

void lin_solve ( int N, int b, float * x, float * x0, bool * boundary, vector<RigidBody*> rigidbodies, float a, float c )
{
	int i, j, k;

	for ( k=0 ; k<20 ; k++ ) {
		FOR_EACH_CELL
			x[IX(i,j)] = (x0[IX(i,j)] + a*(x[IX(i-1,j)]+x[IX(i+1,j)]+x[IX(i,j-1)]+x[IX(i,j+1)]))/c;
		END_FOR
			set_bnd ( N, b, x, boundary, rigidbodies );
	}
}

void diffuse ( int N, int b, float * x, float * x0, bool * boundary, vector<RigidBody*> rigidbodies, float diff, float dt )
{
	float a=dt*diff*N*N;
	lin_solve ( N, b, x, x0, boundary, rigidbodies, a, 1+4*a );
}

void advect ( int N, int b, float * d, float * d0, float * u, float * v, bool * boundary, vector<RigidBody*> rigidbodies, float dt )
{
	int i, j, i0, j0, i1, j1;
	float x, y, s0, t0, s1, t1, dt0;

	dt0 = dt*N;
	FOR_EACH_CELL
		x = i-dt0*u[IX(i,j)]; y = j-dt0*v[IX(i,j)];
	if (x<0.5f) x=0.5f; if (x>N+0.5f) x=N+0.5f; i0=(int)x; i1=i0+1;
	if (y<0.5f) y=0.5f; if (y>N+0.5f) y=N+0.5f; j0=(int)y; j1=j0+1;
	s1 = x-i0; s0 = 1-s1; t1 = y-j0; t0 = 1-t1;
	d[IX(i,j)] = s0*(t0*d0[IX(i0,j0)]+t1*d0[IX(i0,j1)])+
		s1*(t0*d0[IX(i1,j0)]+t1*d0[IX(i1,j1)]);
	END_FOR
		set_bnd ( N, b, d, boundary, rigidbodies );
}

void project ( int N, float * u, float * v, float * p, float * div, bool * boundary, vector<RigidBody*> rigidbodies )
{
	int i, j;

	FOR_EACH_CELL
		div[IX(i,j)] = -0.5f*(u[IX(i+1,j)]-u[IX(i-1,j)]+v[IX(i,j+1)]-v[IX(i,j-1)])/N;
	p[IX(i,j)] = 0;
	END_FOR	

		set_bnd ( N, 0, div, boundary, rigidbodies ); set_bnd ( N, 0, p, boundary, rigidbodies );

	lin_solve ( N, 0, p, div, boundary, rigidbodies, 1, 4 );

	FOR_EACH_CELL
		u[IX(i,j)] -= 0.5f*N*(p[IX(i+1,j)]-p[IX(i-1,j)]);
	v[IX(i,j)] -= 0.5f*N*(p[IX(i,j+1)]-p[IX(i,j-1)]);
	END_FOR

		set_bnd ( N, 1, u, boundary, rigidbodies ); set_bnd ( N, 2, v, boundary, rigidbodies );
}

void dens_step ( int N, float * x, float * x0, float * u, float * v, bool * boundary, vector<RigidBody*> rigidbodies, float diff, float dt )
{
	add_source ( N, x, x0, dt );
	SWAP ( x0, x ); diffuse ( N, 0, x, x0, boundary, rigidbodies, diff, dt );
	SWAP ( x0, x ); advect ( N, 0, x, x0, u, v, boundary, rigidbodies, dt );
}

void vel_step ( int N, float * u, float * v, float * u0, float * v0, bool * boundary, vector<RigidBody*> rigidbodies, float visc, float dt )
{
	add_source ( N, u, u0, dt ); add_source ( N, v, v0, dt );

	//vorticityConfinement( N, u, v );

	for (int i = 0; i < rigidbodies.size(); i++) {
		rigidbodies[i] -> calculateVelocityField();
		add_source ( N, u, rigidbodies[i]->u, dt ); 
		add_source ( N, v, rigidbodies[i]->v, dt );
	}


	SWAP ( u0, u ); diffuse ( N, 1, u, u0, boundary, rigidbodies, visc, dt );
	SWAP ( v0, v ); diffuse ( N, 2, v, v0, boundary, rigidbodies, visc, dt );
	project ( N, u, v, u0, v0, boundary, rigidbodies );
	SWAP ( u0, u ); SWAP ( v0, v );
	advect ( N, 1, u, u0, u0, v0, boundary, rigidbodies, dt ); advect ( N, 2, v, v0, u0, v0, boundary, rigidbodies, dt );
	project ( N, u, v, u0, v0, boundary, rigidbodies );


	for (int i = 0; i < rigidbodies.size(); i++) {
		rigidbodies[i] -> accumulate(u, v);
	}
}