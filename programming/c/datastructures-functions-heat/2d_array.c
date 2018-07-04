#include <stdio.h>
#include <stdlib.h>

#define NX 256
#define NY 256
#define DX 0.01
#define DY 0.01

typedef struct {
	int size[2];
	double spacing[2];
	double sq_spacing[2];
	double field[NX+2][NY+2];
} temp_field;

void init_field(temp_field *field){
	int i,j;
	int nx, ny;
	nx = (*field).size[0];
	ny = (*field).size[1];

	// Initialize first the zeros
	for(i=1;i<=nx;i++)for(j=1;j<=ny;j++){
		(*field).field[i][j]=0;
	}

	// Initial conditions for left and right
	for(i=0;i<=(nx+1);i++){
		(*field).field[i][0]=20.0;
		(*field).field[i][ny+1]=70.0;
	}

	// and top and bottom boundaries
	for(i=0;i<=(ny+1);i++){
		(*field).field[0][i]=85.0;
		(*field).field[nx+1][i]=5.0;
	}
}


int main()
{
	int i,j;
	temp_field field0;
	init_field(&field0);
	double laplacian[NX][NY];

	for(i=1;i<=NX;i++)for(j=1;j<=NY;j++){
		laplacian[i-1][j-1] = (field0->field[i-1][j]-2*field0->field[i][j] + field0->field[i+1][j])/(DX*DX) + (field0->field[i][j-1]-2*field0->field[i][j] + field0->field[i][j+1])/(DY*DY);
	}

	return 0;
}
