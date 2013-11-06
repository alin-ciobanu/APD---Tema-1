#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER 100
#define N 100
#define NC 50

int max (int a, int b) {

	if (a >= b)
		return a;
	return b;

}

int min (int a, int b) {

	if (a <= b)
		return a;
	return b;

}

int maxC (int v[], int n) {

	int max = v[0];
	int pos = 0;
	int i;
	for (i = 1; i < n; i++) {
		if (v[i] > max) {
			max = v[i];
			pos = i;
		}
	}
	
	return pos;

}

int main (int argc, char** argv) {

	int s; // numarul de saptamani
	sscanf(argv[1], "%d", &s);
	FILE* in = fopen(argv[2], "r");
	FILE* out = fopen(argv[3], "w");
	
	int n; // dimensiunea matricei
	int nc; // numarul de culori
	int config[N][N];
	int config_aux[N][N];
	int dmin[NC]; // distantele minime pentru fiecare culoare
	int nr_culori[NC]; // numarul de senatori care apartin fiecarei culori

	int i, j, k, l, m, p;
	
	fscanf(in, "%d ", &n);
	fscanf(in, "%d ", &nc);
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(in, "%d ", &config[i][j]);
		}
	}
	
	for (k = 0; k < nc; k++) {
		nr_culori[k] = 0;
	}
	
	for (l = 1; l <= s; l++) {
		
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
		
				for (k = 0; k < nc; k++) {
					dmin[k] = INT_MAX;
				}

				for (m = 0; m < n; m++) {
					for (p = 0; p < n; p++) {
						if (!(i == m && j == p)) {
							dmin[config[m][p]] = min (dmin[config[m][p]], max(abs(i - m), abs(j - p)));
						}
					}
				}
				
				for (k = 0; k < nc; k++) {
					if (dmin[k] == INT_MAX) {
						dmin[k] = 0;
					}
				}				
				config_aux[i][j] = maxC (dmin, nc);

			}
		}
		
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				config[i][j] = config_aux[i][j];
				nr_culori[config[i][j]] += 1; 
			}
		}
		
		for (k = 0; k < nc - 1; k++) {
			fprintf(out, "%d ", nr_culori[k]);
			nr_culori[k] = 0;
		}
		fprintf(out, "%d\n", nr_culori[nc - 1]);
		nr_culori[nc - 1] = 0;

	}
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1; j++) {
			fprintf(out, "%d ", config[i][j]);
		}
		fprintf(out, "%d\n", config[i][n - 1]);
	}
	
	fclose(in);
	fclose(out);

	return 0;
}

