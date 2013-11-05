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

int main (int argc, char** argv) {

	int s; // numarul de saptamani
	sscanf(argv[1], "%d", &s);
	FILE* in = fopen(argv[2], "r");
	FILE* out = fopen(argv[3], "w");
	
	int n; // dimensiunea matricei
	int nc; // numarul de culori
	int config[N][N];
	int config_aux[N][N];
	int dmin[N][N][NC]; // distantele minime pentru fiecare culoare
	int nr_culori[NC]; // numarul de senatori care apartin fiecarei culori

	int i, j, k, l, m, p;
	
	fscanf(in, "%d ", &n);
	fscanf(in, "%d ", &nc);
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(in, "%d ", &config[i][j]);
			for (k = 0; k < nc; k++) {
				dmin[i][j][k] = INT_MAX;
			}
		}
	}
	
	for (k = 0; k < nc; k++) {
		nr_culori[k] = 0;
	}
	
	for (l = 1; l <= s; l++) {
		
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
		
				for (k = 0; k < nc; k++) {

						int count = 0;
						for (m = 0; m < n; m++) {
							for (p = 0; p < n; p++) {
								if (config[m][p] == k && !(i == m && j == p)) {
									dmin[i][j][k] = min (dmin[i][j][k], max(abs(i - m), abs(j - p)));
									count++;
								}
							}
						}
						if (count == 0) {
							dmin[i][j][k] = 0; 
							// nu s-a intrat niciodata in if-ul de sus
							// senatorul de culoare k este singurul de culoare k sau
							// nu mai exista senatori de culoare k
						}
						
						if (k > 0) {
							if (dmin[i][j][k] > dmin[i][j][k - 1]) {
								config_aux[i][j] = k;
							}
						}
						else { // pentru k = 0
							config_aux[i][j] = 0;
						}
				}

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

