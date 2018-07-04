/* Main solver routines for heat equation solver */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "heat.h"

/* Update the temperature values using five-point stencil */
void evolve(field *curr, field *prev, double a, double dt)
{
	int i, j;
	double dx2, dy2,lap;

	/* Determine the temperature field at next time step
	 * As we have fixed boundary conditions, the outermost gridpoints
	 * are not updated. */
	dx2 = prev->dx * prev->dx;
	dy2 = prev->dy * prev->dy;

	/* TODO: Add update loops for computing the new field values
	   of 'curr' using field 'prev' */
	for(i=1;i<prev->nx;i++)
		for(j=1;j<prev->ny;j++){
		lap = (prev->data[i-1][j] - 2*prev->data[i][j] + prev->data[i+1][j])/dx2 + (prev->data[i][j-1] - 2*prev->data[i][j] + prev->data[i][j+1])/dy2;
		curr->data[i][j] = prev->data[i][j] + dt*a*lap;
	}
}


