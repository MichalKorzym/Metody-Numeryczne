#include <iostream>
#include <cmath>


using namespace std;




double* Gauss_Elimination(unsigned int n, double** A, double* B)
{

	double tmp,tmp2;
	int k;
	int* W = new int[n];
	double* X = new double[n];
	double** AB = new double*[n];
	for (int i = 0; i < n; i++) AB[i] = new double[n+1];
	//laczenie tablicy A z wyrazami wolnymi 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			if (j == n)
			{
				AB[i][j] = B[i];
			}
			else
			{
				AB[i][j] = A[i][j];
			}
		}
	}
	for (int i = 0; i <= n; i++)
		W[i] = i;
	
	for (int i = 0; i < n - 1; i++)
	{
		 k = i;
		 for (int j = i + 1; j < n; j++)
		 {
			 if (fabs(AB[i][W[k]]) < fabs(AB[i][W[j]]))
			 k = j;
		 }
				
			swap(W[k], W[i]);
			for (int j = i + 1; j < n; j++)
			{
				if (fabs(AB[i][W[i]]) < 0)
					return 0; 
				
				tmp = -AB[j][W[i]] / (AB[i][W[i]]);
				for (k = i + 1; k <= n; k++)
					AB[j][W[k]] += tmp * AB[i][W[k]];


			}
		
	}
	//obliczanie wartosci wektora X
	for (int i = n - 1; i >= 0; i--)
	{

		if (fabs(AB[i][W[i]]) < 0)
			return 0;
		
		tmp2 = AB[i][n];
		for (int j = n - 1; j >= i + 1; j--)
			tmp2 -= AB[i][W[j]] * X[W[j]];
		X[W[i]] = tmp2 / AB[i][W[i]];


	}
	return X;

}





int main()
{
	int n;
	//rozmiar tablicy
	cout << "Podaj ilosc elementow tablicy kwadratowej" << endl;
	cin >> n;

	double** A = new double* [n];
	double* B = new double [n];
	//uzupelnienie wyrazow wolnych
	cout << "podaj wyrazy wolne" << endl;

	for (int i = 0; i < n; i++) {
		cin >> B[i];
	}
	//uzupelnienie tablicy rownan
	for (int i = 0; i < n; i++) A[i] = new double[n];
	cout << "tablica (uklad rownan)" << endl;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> A[i][j];
			
	}
	cout << endl;	
	double* result = new double[n];
	//wywolanie funkcji
		 result= Gauss_Elimination(n, A, B);
	//wypisanie wyniku
	cout << endl << endl;
	cout << "Wektor rozwiazania " << endl; 
	for (int i = 0; i < n; i++) {
		cout <<"x"<<i+1<<":"<< result[i] << endl;
	}
	delete[] result;
	delete[] B;
	for (int i = 0; i < n; i++) delete[] A[i];
	delete[] A;

	system("pause");
	return 0;
	
}