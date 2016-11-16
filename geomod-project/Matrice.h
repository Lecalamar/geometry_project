#ifndef MATRICE_H
#define MATRICE_H

class Matrice {
	private:
		int nl, nc;
		float **tab;
	public:
		Matrice(int a, int b);
		int getNL();
		int getNC();
		void put(int i, int j, float f);
		float get(int i, int j);
		void display();
		Matrice transpose();
		Matrice solve(Matrice b);
		Matrice multiply(Matrice A);
};
#endif
