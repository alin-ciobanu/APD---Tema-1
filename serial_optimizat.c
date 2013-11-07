#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define BUFFER 100
#define N 100
#define NC 50

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

int allIterated (int v[], int n) {

	int i;
	for (i = 0; i < n; i++) {
		if (v[i] == 0) {
			return 0;
		}
	}
	
	return 1;

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
	
	int iS, iF, jS, jF; // variabile de parcurgere
	int cul_iter[NC]; // culori iterate
	int partide_moarte[NC];
	int last_element[NC]; // culorile care mai au un singur senator

	int pas;
	int stgJosL, stgJosC;
	int stgSusL, stgSusC;
	int drJosL, drJosC;
	int drSusL, drSusC;

	int i, j, k, l, m, p;
	
	fscanf(in, "%d ", &n);
	fscanf(in, "%d ", &nc);
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(in, "%d ", &config[i][j]);
			nr_culori[config[i][j]] += 1;
		}
	}
	
	for (k = 0; k < nc; k++) {
		if (nr_culori[k] == 0) {
			partide_moarte[k] = 1;
			last_element[k] = 0;
		}
		else if (nr_culori[k] == 1) {
			partide_moarte[k] = 0;
			last_element[k] = 1;
		}
		else {
			partide_moarte[k] = 0;
			last_element[k] = 0;
		}
		nr_culori[k] = 0;
	}

	for (l = 1; l <= s; l++) {

		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {

				pas = 1;
				// impartim spatiul de parcurgere
				// parcurgem din colt in colt
				stgJosL = i + pas;
				stgJosC = j - pas;
				stgSusL = i - pas;
				stgSusC = j - pas;
				drJosL = i + pas;
				drJosC = j + pas;
				drSusL = i - pas;
				drSusC = j + pas;
	
				for (k = 0; k < nc; k++) {
					dmin[k] = INT_MAX;
					cul_iter[k] = partide_moarte[k];
					if (last_element[k] == 1 && config[i][j] == k) {
						cul_iter[k] = 1;
					}
				}

				while (!allIterated(cul_iter, nc)) {

					if (stgSusL >= 0) { // pentru linia de sus
				
						if (stgSusC < 0) {
							jS = 0;
						}
						else {
							jS = stgSusC;
						}
						if (drSusC >= n) {
							jF = n;
						}
						else {
							jF = drSusC + 1;
						}
				
						for (k = jS; k < jF; k++) {
							if (cul_iter[config[stgSusL][k]] == 0) {
								dmin[config[stgSusL][k]] = pas;
								cul_iter[config[stgSusL][k]] = 1;
							}
						}
					}
					
					if (stgJosL < n) { // pentru linia de jos
					
						if (stgJosC < 0) {
							jS = 0;
						}
						else {
							jS = stgJosC;
						}
						
						if (drJosC >= n) {
							jF = n;
						}
						else {
							jF = drJosC + 1;
						}

						for (k = jS; k < jF; k++) {
							if (cul_iter[config[stgJosL][k]] == 0) {
								dmin[config[stgJosL][k]] = pas;
								cul_iter[config[stgJosL][k]] = 1;
							}
							
						}
					}
					
					if (stgSusC >= 0) { // pentru coloana din stanga
						
						if (stgSusL < 0) {
							iS = 0;
						}
						else {
							iS = stgSusL;
						}
						
						if (stgJosL >= n) {
							iF = n;
						}
						else {
							iF = stgJosL + 1;
						}
						
						for (k = iS; k < iF; k++) {
							if (cul_iter[config[k][stgSusC]] == 0) {
								dmin[config[k][stgSusC]] = pas;
								cul_iter[config[k][stgSusC]] = 1;
							}
						}
					}
					
					if (drSusC < n) { // pentru coloana din dreapta
					
						if (drSusL < 0) {
							iS = 0;
						}
						else {
							iS = drSusL;
						}

						if (drJosL >= n) {
							iF = n;
						}
						else {
							iF = drJosL + 1;
						}
						
						for (k = iS; k < iF; k++) {
							if (cul_iter[config[k][drSusC]] == 0) {
								dmin[config[k][drSusC]] = pas;
								cul_iter[config[k][drSusC]] = 1;
							}
						}
					}

					pas++;
					stgJosL = i + pas;
					stgJosC = j - pas;
					stgSusL = i - pas;
					stgSusC = j - pas;
					drJosL = i + pas;
					drJosC = j + pas;
					drSusL = i - pas;
					drSusC = j + pas;

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
			if (nr_culori[k] == 0) {
				partide_moarte[k] = 1;
				last_element[k] = 0;
			}
			else if (nr_culori[k] == 1) {
				last_element[k] = 1;
				partide_moarte[k] = 0;
			}
			else {
				partide_moarte[k] = 0;
				last_element[k] = 0;
			}
			nr_culori[k] = 0;
		}
		fprintf(out, "%d\n", nr_culori[nc - 1]);
		if (nr_culori[nc - 1] == 0) {
			partide_moarte[nc - 1] = 1;
			last_element[nc - 1] = 0;
		}
		else if (nr_culori[nc - 1] == 1) {
			last_element[nc - 1] = 1;
			partide_moarte[nc - 1] = 0;
		}
		else {
			partide_moarte[nc - 1] = 0;
			last_element[nc - 1] = 0;
		}
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

