#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	// Define variables
	double t, T, deltat;
	double *x, *y, *z, *x1, *y1, *z1; // Arrays for coordinates
	FILE *gp;						  // File pointer for gnuplot
	double s, b, r;					  // Constants for the Lorenz system
	double vis;						  // Visualization interval
	int M;							  // Number of points
	int k;							  // Loop variable
	double err;						  // Initial Error

	// Set the constants and parameters
	s = 10;		// Sigma
	b = 8. / 3; // Beta
	r = 28;		// Rho

	deltat = 0.01; // Integration dt
	T = 30;		   // Final time integration
	vis = .1;	   // Visualization window
	M = 1000;	   // Numer of different starting points
	err = 1e-2;	   // Random starting points differences

	// Allocate memory for arrays
	x = calloc(M, sizeof(double));
	y = calloc(M, sizeof(double));
	z = calloc(M, sizeof(double));
	x1 = calloc(M, sizeof(double));
	y1 = calloc(M, sizeof(double));
	z1 = calloc(M, sizeof(double));

	// Initialize the coordinates randomly with some error
	for (k = 0; k < M; k++)
	{
		x[k] = 1 + (drand48() - 0.5) * err;
		y[k] = 1 + (drand48() - 0.5) * err;
		z[k] = 1 + (drand48() - 0.5) * err;
	}

	// Open a pipe to gnuplot for real-time visualization
	gp = popen("gnuplot", "w");
	fprintf(gp, "set xrange [-30:30]\n");
	fprintf(gp, "set yrange [-30:30]\n");
	fprintf(gp, "set zrange [0:50]\n");

	// Time integration loop for the Lorenz system
	for (t = 0; t < T; t += deltat)
	{
		for (k = 0; k < M; k++)
		{
			// Update coordinates using the Lorenz equations
			x1[k] = x[k] + s * (y[k] - x[k]) * deltat;
			y1[k] = y[k] + (x[k] * (r - z[k]) - y[k]) * deltat;
			z1[k] = z[k] + (x[k] * y[k] - b * z[k]) * deltat;
			x[k] = x1[k];
			y[k] = y1[k];
			z[k] = z1[k];
		}
		// Visualization at regular intervals
		if (fmod(t, vis) < deltat)
		{
			fprintf(gp, "splot '-' w p pt 7 ps .2\n");
			for (k = 0; k < M; k++)
			{
				fprintf(gp, "%f %f %f\n", x[k], y[k], z[k]);
			}
			fprintf(gp, "end\n");
			fflush(gp);
		}
	}

	// Wait for user input before closing the gnuplot window
	getchar();
	// Close the gnuplot pipe
	fclose(gp);
}
