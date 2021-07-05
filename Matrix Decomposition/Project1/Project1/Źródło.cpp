#include <iostream>
#include <fstream>
using namespace std;



bool LuDecomposition(double** A, unsigned int n)
{
	//tworzenie macierzy L i U 
	double** L = new double* [n];
	double** U = new double* [n];

	for (int i = 0; i < n; i++)
	{
		L[i] = new double[n];
		U[i] = new double[n];

	}
	//zerowanie i ustawienie na przekatnej 1
	for (int i = 0; i < n; i++)

		for (int j = 0; j < n; j++)
		{
			if (i == j) {
				L[i][j] = 1;
				U[i][j] = 0;
			}
			else {
				L[i][j] = 0;
				U[i][j] = 0;
			}
		}
	for (int i = 0; i < n; i++)


	{

		for (int j = i; j < n; j++)
		{

			double tmp = 0;
			for (int k = 0; k < i; k++)
				tmp += (L[i][k] * U[k][j]);

			U[i][j] = A[i][j] - tmp;


		}

		for (int j = i; j < n; j++)
		{

			if (i != j) //na przekatnej 1

			{
				if (U[i][i] == 0) {
					cout << "Dividing by zero" << endl;
					return false;
				}

				double tmp = 0;
				for (int k = 0; k < i; k++)
					tmp += (L[j][k] * U[k][i]);

				L[j][i] = (A[j][i] - tmp) / U[i][i];


			}



		}



	}



	for (int i = 0; i < n; i++)
	{
		// Lower
		for (int j = 0; j < n; j++)
			cout << L[i][j] << "\t";
		cout << "\t";

		// Upper
		for (int j = 0; j < n; j++)
			cout  << U[i][j] << "\t";
		cout << endl;
	}


	//Przeksztalcenie macierzy A na L/U
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (i > j)
				A[i][j] = L[i][j];
			else
				A[i][j] = U[i][j];
	}


	for (int i = 0; i < n; i++)
	{
		delete[] L[i];
		delete[] U[i];
	}
	delete[] L;
	delete[] U;
	return true;
}




bool getSolution(double** A, double* x,double* b,unsigned int n)

{
	
	double* y = new double[n];
	//front
	y[0] = b[0];
	for (int i = 0; i < n; i++)
	{
		
			double tmp = 0;
		
			for (int j = 0; j < i; j++)
				tmp += (A[i][j] * y[j]);

			y[i] = b[i] - tmp;
		
	}


	x[n-1] = y[n-1] / A[n-1][n-1];

	//backwards
	for (int i = n - 1; i >= 0; i--)
	{
		double tmp = 0;

		if (A[i][i] == 0) {
			cout << "Dividing by zero" << endl;
			return false;
		}
		
		for (int j = i+1 ; j < n; j++)
			tmp+= (A[i][j] * x[j]);

		x[i] = (y[i] - tmp)/(A[i][i]);
		
		
	}
	delete[] y;
	return true;

}







int main()

{
	int degree;
	//wczytywanie danych
	ifstream data("data.txt");
	data >> degree;
	double** A = new double*[degree];
	for (int i = 0; i < degree; i++) A[i] = new double[degree];
	double* b = new double[degree];
	
	for (int i = 0; i < degree; i++) data >> b[i];
	for (int i = 0; i < degree; i++)
		for (int j = 0; j < degree; j++) data >> A[i][j];
	data.close();
	


	double* x = new double[degree];
	for (int i = 0; i < degree; i++) x[i]=0;


	if (LuDecomposition(A, degree)) {
		cout << "Matrix after decomposition" << endl;
		for (int i = 0; i < degree; i++)
		{
			cout << endl;
			for (int j = 0; j < degree; j++)
				cout << A[i][j] << " ";
		}
		cout << endl;
		cout << "Solution" << endl;
		if (getSolution(A, x, b, degree)) {
			for (int i = 0; i < degree; i++) cout << x[i] << endl;
			cout << endl;
		}
	}



	delete[] x;
	delete[] b;
	for (int i = 0; i < degree; i++) delete[] A[i];
	delete[] A;
	
	system("pause");
	return 0;

}