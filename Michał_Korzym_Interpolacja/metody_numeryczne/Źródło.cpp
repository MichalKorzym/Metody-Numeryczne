#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//schemat hornera
//zadanie1 
double horner(unsigned int degree,double *wsp,double x) {
	
	double wynik = wsp[degree-1];
	for (int i = degree-2; i >= 0; i--) 	
		wynik = wynik * x + wsp[i];

	return wynik;
}

//wielomian w postaci Newtona obliczanie wartosci
//zadanie 2
double newton_horner(unsigned int degree,double *b,double *X,double x)
{

	double y = b[degree-1];
	//cout << y << endl;
	
	for (int i = degree-2 ; i >= 0; i--)
	{

		//w_i=w_i+1*(x-x_i)+b_i
		y = y * (x - X[i]) + b[i];
	}
	return y;
	
}
//przeliczanie wspolczynnikow
//zadanie 3

double* wspPN(unsigned int degree,double *b,double *x)
{

	double *tmp = new double[degree];
	//i=n 
	tmp[degree - 1] = b[degree - 1]; 
	for (int i = degree - 2; i >= 0; i--)
	{
		tmp[i] = b[i]; 
		
		for (int j = i; j < degree - 1; j++) {
			tmp[j] = tmp[j] - tmp[j + 1] * x[i];
			
		}
	}
	//tablica ze wspolczynnikami naturalnymi
	return tmp;
}
//interpolacja Lagrange'a
//zadanie 4
double Lagrange(unsigned int degree, double *X, double *Y,double x)

{
	
	double y = 0;
	for (int i = 0; i < degree; i++)
	{
		//wielomiany bazowe
		double l_i = 1;
		for (int j = 0; j < degree; j++) {
			if (j != i) {
				l_i = l_i * (x - X[j]) / (X[i] - X[j]);
			}
		}
		y = y + Y[i] * l_i;

	}
	return y;

}
//zadanie 5
//wyznaczanie ilorazow roznicowych
double* IlorazyRoz(unsigned int degree, double* X, double* Y)
{
	double** b = new double* [degree];

	for (int i = 0; i < degree; i++) {
		b[i] = new double[i + 1];
		b[i][0] = Y[i];
	}
	for (int i = 1; i < degree; i++) {
		for (int j = 1; j <= i; j++) {
			b[i][j] = (b[i][j - 1] - b[i - 1][j - 1]) / (X[i] - X[i - j]);
		}
	}
	//wspolczynniki b to elementy przek¹tniowe
	double* b_i = new double[degree];
	for (int i = 0; i < degree; i++)
		b_i[i] = b[i][i];
	
	for (int i = 0; i < degree; i++)
		delete[] b[i];

	delete[]b;
	return  b_i;
}


int main() {


	int tmp;
	int degreeFile1a,degreeFile1b,degreeFile1c;
	int degreeFile2;
	int degreeFile3;
	int degreeFile4a,degreeFile4b,degreeFile4c;

	//POCZATEK WCZYTYWANIA DANYCH
	ifstream Polynomial1("polynomial-1.txt");

		Polynomial1 >> degreeFile1a;
		double* tab_File1a = new double[degreeFile1a];
		for (int i = 0; i < degreeFile1a; i++)
		Polynomial1 >> tab_File1a[i];
		Polynomial1 >> degreeFile1b;
		double* tab_File1b = new double[degreeFile1b];
		for (int i = 0; i < degreeFile1b; i++)
		Polynomial1 >> tab_File1b[i];
		Polynomial1 >> degreeFile1c;
		double* tab_File1c = new double[degreeFile1c];
		for (int i = 0; i < degreeFile1c; i++)
		Polynomial1 >> tab_File1c[i];
		Polynomial1.close();

		ifstream Polynomial2("polynomial-2.txt");
		Polynomial2 >> degreeFile2;
		double* tab_File2_a = new double[degreeFile2];
		for (int i = 0; i < degreeFile2; i++)
			Polynomial2 >> tab_File2_a[i];
		double* tab_File2_x = new double[degreeFile2];
		for (int i = 0; i < degreeFile2; i++)
			Polynomial2 >> tab_File2_x[i];
		Polynomial2.close();

		ifstream Polynomial3("polynomial-3.txt");
		Polynomial3 >> degreeFile3;
		double* tab_File3_xi = new double[degreeFile3];
		for (int i = 0; i < degreeFile3; i++)
			Polynomial3 >> tab_File3_xi[i];
		double* tab_File3_yi = new double[degreeFile3];
		for (int i = 0; i <degreeFile3; i++)
			Polynomial3 >> tab_File3_yi[i];
		Polynomial3.close();


		ifstream Polynomial4("polynomial-4.txt");
		Polynomial4 >> degreeFile4a;
		double* tab_File4a_xi = new double[degreeFile4a];
		double* tab_File4a_yi = new double[degreeFile4a];
		for (int i = 0; i < degreeFile4a; i++)
			Polynomial4 >> tab_File4a_xi[i];
		for (int i = 0; i < degreeFile4a; i++)
			Polynomial4 >> tab_File4a_yi[i];
		Polynomial4 >> degreeFile4b;
		double* tab_File4b_xi = new double[degreeFile4b];
		double* tab_File4b_yi = new double[degreeFile4b];
		for (int i = 0; i < degreeFile4b; i++)
			Polynomial4 >> tab_File4b_xi[i];
		for (int i = 0; i < degreeFile4b; i++)
			Polynomial4 >> tab_File4b_yi[i];
		Polynomial4 >> degreeFile4c;
		double* tab_File4c_xi = new double[degreeFile4c];
		double* tab_File4c_yi = new double[degreeFile4c];
		for (int i = 0; i < degreeFile4c; i++)
			Polynomial4 >> tab_File4c_xi[i];
		for (int i = 0; i < degreeFile4c; i++)
			Polynomial4 >> tab_File4c_yi[i];

		Polynomial4.close();

		//KONIEC WCZYTYWANIA DANYCH
		double x;
		cout << "Podaj x" << endl;
		cin >> x;

		//Wywolania metod
		cout << "Zadanie 1 " << endl;
		cout << "Zestaw danych 1 :" << endl;
		cout << horner(degreeFile1a, tab_File1a,x)<<endl;
		cout << "Zestaw danych 2:" << endl;
		cout << horner(degreeFile1b, tab_File1b,x)<<endl;
		cout << "Zestaw danych 3:" << endl;
		cout << horner(degreeFile1c, tab_File1c, x)<<endl;
		cout << endl;
		cout << "Zadanie 2 " << endl;
		cout << newton_horner(degreeFile2, tab_File2_a, tab_File2_x,x);
		cout << endl << endl;
		cout << "Zadanie 3 " << endl;
		for (int i = 0; i < degreeFile2; i++)
			cout << wspPN(degreeFile2, tab_File2_a, tab_File2_x)[i] << "  ";
		cout << endl<<endl;

		cout << "Zadanie 4 " << endl;
		cout << Lagrange(degreeFile3, tab_File3_xi, tab_File3_yi,x) << endl << endl;
		
		cout << "Zadanie 5  " << endl;
		cout << "Zestaw danych 1 :" << endl;
		for (int i = 0; i < degreeFile4a; i++)
		cout << IlorazyRoz(degreeFile4a, tab_File4a_xi, tab_File4a_yi)[i]<<"  ";
		cout << endl << endl;
		cout << "Zestaw danych 2 :" << endl;
		for (int i = 0; i < degreeFile4b; i++)
			cout << IlorazyRoz(degreeFile4b, tab_File4b_xi, tab_File4b_yi)[i] << "  ";
		cout << endl << endl;
		cout << "Zestaw danych 3 :" << endl;
		for (int i = 0; i < degreeFile4c; i++)
			cout << IlorazyRoz(degreeFile4c, tab_File4c_xi, tab_File4c_yi)[i] << "  ";
		cout << endl << endl;
		delete[]tab_File1a;
		delete[]tab_File1b;
		delete[]tab_File1c;
		delete[]tab_File2_a;
		delete[]tab_File2_x;
		delete[]tab_File3_xi;
		delete[]tab_File3_yi;
		delete[]tab_File4a_xi;
		delete[]tab_File4a_yi;
		delete[]tab_File4b_xi;
		delete[]tab_File4b_yi;
		delete[]tab_File4c_xi;
		delete[]tab_File4c_yi;

	return 0;
	system("pause");
}