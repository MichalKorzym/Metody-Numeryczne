#include <iostream>

using namespace std;

#define EPSILON 0.1

//schemat hornera
 double horner(unsigned int degree, double* wsp, double x) {
	
	double wynik = wsp[degree - 1];
	for (int i = degree - 2; i >= 0; i--)
		wynik = wynik * x + wsp[i];

	return wynik;
}

 //funkcja wagowa
 double wageFunction(double x)
 {
	 return 1;
 }
 
 //mnozenie wspolczynnikow
 double createPolynomial(double* coefs, double* coefs2, double x,double n)
 {
	
	 return horner(n, coefs, x) * horner(n, coefs2, x);
 }
 /*
 double  multiplyTwoFunctions(double (*f1)(double), double (*f2)(double), double (*wF)(double), double x)
 {

	 return (f1(x) * f2(x) * wF(x));
 }
 */

 //metoda trapezow
 double trapezoidalMethodUniformGrid( double h, double xp, double xk,double *f1,double *f2,double wF(double),double n)
 {
	 
	 double result = 0;	
	 double numberOfKnots = (xk - xp) / h;
	 for (int i = 1; i < numberOfKnots; i++) {

		 result = result + createPolynomial(f1,f2, xp + i * h,n)*wF(xp + i * h);

	 }
	 result = (result + (createPolynomial(f1,f2,xk,n)* wF(xk) + (createPolynomial(f1, f2, xp,n))*wF(xp)) / 2) * h;

	 return result;
 }
 //funkcja sprawdzajaca czy baza jest ortogonalna 
 bool ifOrtogonal(double** coefs, double n, double a, double b, double wf(double))
 {
	 bool check = true;


	 for (int i = 0; i < n; i++)
		 for (int j = 0; j < n; j++) {
			 cout << "Iloczyn skalarny elementu  " << i << " oraz " << j << " wynik: " << (trapezoidalMethodUniformGrid(0.05, a, b, coefs[i], coefs[j], wf, n));
			 cout << endl;
			 if (i != j) {
				
				 if ((trapezoidalMethodUniformGrid(0.05, a, b, coefs[i], coefs[j], wf, n)) > EPSILON) {
					 check = false;
				 }
			 }
		 }

	 return check;
 }

 //odejmowanie tablic wspolczynnikow
 double* subPoly(double* coefs, double* coefs2,double n)
 {
	 
	
	 double* newCoefs = new double[n];
	 for (int i = 0; i <n; i++)
		 newCoefs[i] = coefs[i] - coefs2[i];

	 return newCoefs;
 }
 //mnozenie wspolczynnikow przez stal
 double* multiplyCoefs(double* coefs, double x,double n)
 {
	 double* newCoefs = new double[n];
	
	 for (int i = 0; i < n; i++)
		newCoefs[i] = coefs[i] * x;


	 return newCoefs;
 }

 double* sumCoefs(double* coefs, double* coefs2,double n)
 {

	 
	 double* newCoefs = new double[n];
	 for (int i = 0; i < n; i++)
		 newCoefs[i] = coefs[i] + coefs2[i];

	 return newCoefs;
 }


//gram-schmidt
double** gramSchmidt(double a, double b, unsigned int n, double **f,double (*wf)(double))
{
	


	double** coefsArray = new double*[n];
	for (int i = 0; i < n; i++)
		coefsArray[i] = new double[n];


	for(int i=0;i<n;i++)
	for (int k = 0; k < n; k++) {
		if (k == 0)
			coefsArray[i][0] = 1;
		else
		coefsArray[i][k] = 0;
	}
	
	
	for (int i = 1; i < n; i++)
	{
		coefsArray[i] = f[i];
		
		double* sum = new double[n];
		for (int k = 0; k < n; k++)
			sum[k] = 0;

		for (int j = 0; j < i; j++)
		{
			double division = trapezoidalMethodUniformGrid(0.05, a, b, f[i], coefsArray[j], wf,n) / trapezoidalMethodUniformGrid(0.05, a, b, coefsArray[j], coefsArray[j], wf,n);
			coefsArray[i] = subPoly(coefsArray[i], multiplyCoefs( coefsArray[j], division,n),n);
		//	sum = sumCoefs(sum, multiplyCoefs(coefsArray[j], division));


		}
		
		//coefsArray[i] = subPoly(f[i], sum);
	}
	

			
	return coefsArray;

}



double* multiplyByVector(double* coefs, double* vector,double n)
{
	double* newCoefs = new double[n+1];
	for (int i = 0; i < n+1; i++)
		newCoefs[i] = 0;


	for (int i = 0; i < n; i++)
	{
		if (coefs[0] !=0 )
			newCoefs[0] = 0;
		newCoefs[i + 1] = coefs[i]*vector[1];
	}
	return newCoefs;
	
}

//beta jest stala
double* addBeta(double* vector, double beta, double n)
{
	double* newVector = new double[n];
	newVector = vector;
	
	newVector[0] = vector[0] + beta;
	return newVector;
}


//funkcja obliczajaca gamme
double gamma( double a, double b, double* coef,double* coef2, double(*wf)(double),double n)
{
	return -(trapezoidalMethodUniformGrid(0.05, a, b, coef,coef, wf,n) /
		trapezoidalMethodUniformGrid(0.05, a, b, coef2, coef2, wf,n));
}


//funkcja obliczajaca bete
double beta( double a, double b, double* coef, double* vector, double(*wf)(double),double n)
{
	return -(trapezoidalMethodUniformGrid(0.05, a, b, multiplyByVector(coef, vector,n), coef, wf,n) / trapezoidalMethodUniformGrid(0.05, a, b, coef, coef, wf,n));
}

//funkcja mnozaca dwa wielomiany
double* multiplyTwoPolynomials(double* coefs, double* coefs2, double n)
{
	double* newCoefs = new double[n + n - 1];

	for (int i = 0; i < n + n - 1; i++)
	{
		newCoefs[i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		
		for (int j = 0; j < n; j++)
		{
			newCoefs[i + j] += coefs[i] * coefs2[j];
		}
	}
	return newCoefs;
}



//the three-part rule
double** triModule(double **f,double a,double b,double (*wf)(double),double n)
{
	double* vector = new double[n];
	for (int j = 0; j < n; j++)
		if (j == 1)
			vector[j] = 1;
		else
			vector[j] = 0;

	double** polyArray = new double* [n];
	for (int i = 0; i < n; i++)
		polyArray[i] = new double[2*n-1];


	polyArray[0] = f[0];
	polyArray[1] = multiplyTwoPolynomials(polyArray[0],(addBeta(vector, beta(a, b, polyArray[0], vector, wf,n),n)),n);
	

		for (int k = 2; k < n; k++)
		{
			
			polyArray[k] = sumCoefs( multiplyTwoPolynomials(polyArray[k - 1],addBeta(vector , beta(a, b, polyArray[k - 1], vector, wf,n),n),n),multiplyCoefs(polyArray[k - 2], gamma(a, b, polyArray[k - 1], polyArray[k - 2], wf,n),n),n);
		}


	return polyArray;

}



int main()
{
	
	double degree=5;
	double a = -1;
	double b = 1;
	double aPrim = 0;
	double** fcoefs = new double*[degree];
	for (int i = 0; i < degree; i++)
		fcoefs[i] = new double[degree];

	double fCof1[] = { 1,0,0,0,0 };
	double fCof2[] = { 0,1,0,0,0 };
	double fCof3[] = { 0,0,1,0,0 };
	double fCof4[] = { 0,0,0,1,0 };
	double fCof5[] = { 0,0,0,0,1 };
	fcoefs[0] = fCof1;
	fcoefs[1] = fCof2;
	fcoefs[2] = fCof3;
	fcoefs[3] = fCof4;
	fcoefs[4] = fCof5;


	double** resultGramSchmidt = new double* [degree];
	for (int i = 0; i < degree; i++)
		resultGramSchmidt[i] = new double[degree];


	resultGramSchmidt = gramSchmidt(a, b, degree, fcoefs, wageFunction);

	cout << "Baza dla ortogonalizacji Grama-Schmidta na przedziale (-1,1)";
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultGramSchmidt[i][j]<<" ";
	}
	cout << endl<<endl;

	double** resultTriModule = new double* [degree];
	for (int i = 0; i < degree; i++)
		resultTriModule[i] = new double[degree];

	resultTriModule = triModule(fcoefs, a, b, wageFunction, degree);
	cout << "Baza dla reguly trojczlonowej na przedziale (-1,1)";
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultTriModule[i][j] << " ";
	}
	cout <<endl<< endl;
	cout << "Sprawdzenie czy baza na przedziale (-1,1) jest ortogonalna " << endl;
	if (ifOrtogonal(resultGramSchmidt, degree, a, b, wageFunction) && ifOrtogonal(resultTriModule, degree, a, b, wageFunction))
		cout << "Ortogonalna" << endl;
	else
		cout << "Nieortogonalna" << endl;

	cout << endl;
	resultGramSchmidt = gramSchmidt(aPrim, b, degree, fcoefs, wageFunction);
	cout << "Baza dla ortogonalizacji Grama-Schmidta na przedziale (0,1)";
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultGramSchmidt[i][j] << " ";
	}
	cout << endl<<endl;
	
	resultTriModule = triModule(fcoefs, aPrim, b, wageFunction, degree);
	cout << "Baza dla reguly trojczlonowej na przedziale (0,1)";
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultTriModule[i][j] << " ";
	}

	cout << endl<<endl;

	cout << "Sprawdzenie czy baza na przedziale (0,1) jest ortogonalna " << endl;
	if (ifOrtogonal(resultGramSchmidt, degree, aPrim, b, wageFunction) && ifOrtogonal(resultTriModule, degree, aPrim, b, wageFunction))
		cout << "Ortogonalna" << endl;
	else
		cout << "Nieortogonalna" << endl;


	system("pause");
	return 0;

}