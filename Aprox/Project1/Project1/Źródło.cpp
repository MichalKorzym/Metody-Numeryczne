#include <iostream>

using namespace std;


//schemat hornera
double horner(unsigned int degree, double* wsp, double x) {

	double wynik = wsp[degree - 1];
	for (int i = degree - 2; i >= 0; i--)
		wynik = wynik * x + wsp[i];

	return wynik;
}

double funcEx1(double x)
{
	return  sin(-x) + exp(-x) - pow(x, 3);
	
}


//funkcja wagowa
double wageFunction(double x)
{
	return 1;
}

/*
double  multiplyTwoFunctions(double f1(double), double f2(double), double wF(double), double x)
{

	return (f1(x) * f2(x) * wF(x));;
}
*/
double createPolynomial(double* coefs, double* coefs2, double x, double n)
{

	return horner(n, coefs, x) * horner(n, coefs2, x);
}
double trapezoidalMethodUniformGrid(double h, double xp, double xk, double* f1, double* f2, double wF(double), double n)
{

	double result = 0;
	double numberOfKnots = (xk - xp) / h;
	for (int i = 1; i < numberOfKnots; i++) {

		result = result + createPolynomial(f1, f2, xp + i * h, n) * wF(xp + i * h);

	}
	result = (result + (createPolynomial(f1, f2, xk, n) * wF(xk) + (createPolynomial(f1, f2, xp, n)) * wF(xp)) / 2) * h;

	return result;
}

double multiplyFunctionAndCoefs(double* coefs, double function(double), double x,double n)
{
	return horner(n, coefs, x) * function(x);
}

double trapezoidalMethodUniformGridForFunction(double h, double xp, double xk, double* f1, double function(double), double wF(double), double n)
{

	double result = 0;
	double numberOfKnots = (xk - xp) / h;
	for (int i = 1; i < numberOfKnots; i++) {

		result = result + multiplyFunctionAndCoefs(f1, function, xp + i * h, n) * wF(xp + i * h);

	}
	result = (result + (multiplyFunctionAndCoefs(f1, function, xk, n) * wF(xk) + (multiplyFunctionAndCoefs(f1, function, xp, n)) * wF(xp)) / 2) * h;

	return result;
}

double* dividePoly(double* coefs,  double x,double n)
{
	double* newCoefs = new double[n];

	for (int i = 0; i < n; i++) {
		newCoefs[i] = coefs[i] / x;
		
	}

	return newCoefs;
}



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




bool getSolution(double** A, double* x, double* b, unsigned int n)

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


	x[n - 1] = y[n - 1] / A[n - 1][n - 1];

	//backwards
	for (int i = n - 1; i >= 0; i--)
	{
		double tmp = 0;

		if (A[i][i] == 0) {
			cout << "Dividing by zero" << endl;
			return false;
		}

		for (int j = i + 1; j < n; j++)
			tmp += (A[i][j] * x[j]);

		x[i] = (y[i] - tmp) / (A[i][i]);


	}
	delete[] y;
	return true;

}



void ortonormalization(double** coefs,  double n, double a, double b, double wF(double))
{
	for (int i = 0; i < n; i++) {
		double norm =sqrt(trapezoidalMethodUniformGrid(0.05, a, b, coefs[i], coefs[i], wF, n));
			coefs[i] = dividePoly(coefs[i], norm, n);
	}

}





double* Approximation(double a, double b, double **f, double wf(double), double function(double), unsigned int degree)
{

	//cout<<(function(3));
	double* alfa = new double[degree];
	double* B = new double[degree];
	
	for (int i = 0; i < degree; i++) B[i] = 0;
	double** matrix = new double* [degree];
	for (int i = 0; i < degree; i++) matrix[i] = new double[degree];



	for (int i = 0; i < degree; i++) {
		B[i] = trapezoidalMethodUniformGridForFunction(0.05, a, b, f[i],function, wf,degree);
		//cout << B[i]<<endl;
	}

	for (int i = 0; i < degree; i++)
		for (int j = 0; j < degree; j++)
			matrix[i][j] = trapezoidalMethodUniformGrid(0.05, a, b, f[i], f[j], wf,degree);

	/*
	for (int i = 0; i < sizeof(f); i++)
	{
		cout << endl;
		for (int j = 0; j <sizeof(f); j++)
			cout << matrix[i][j] << " ";
	}
	*/
	LuDecomposition(matrix, degree);
	getSolution(matrix, alfa, B, degree);

	return alfa;
		
}




double* subPoly(double* coefs, double* coefs2, double n)
{


	double* newCoefs = new double[n];
	for (int i = 0; i < n; i++)
		newCoefs[i] = coefs[i] - coefs2[i];

	return newCoefs;
}

double* multiplyCoefs(double* coefs, double x, double n)
{
	double* newCoefs = new double[n];

	for (int i = 0; i < n; i++)
		newCoefs[i] = coefs[i] * x;


	return newCoefs;
}

double* sumCoefs(double* coefs, double* coefs2, double n)
{


	double* newCoefs = new double[n];
	for (int i = 0; i < n; i++)
		newCoefs[i] = coefs[i] + coefs2[i];

	return newCoefs;
}


//gram-schmidt
double** gramSchmidt(double a, double b, unsigned int n, double** f, double (*wf)(double))
{



	double** coefsArray = new double* [n];
	for (int i = 0; i < n; i++)
		coefsArray[i] = new double[n];


	for (int i = 0; i < n; i++)
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
			double division = trapezoidalMethodUniformGrid(0.05, a, b, f[i], coefsArray[j], wf, n) / trapezoidalMethodUniformGrid(0.05, a, b, coefsArray[j], coefsArray[j], wf, n);
			coefsArray[i] = subPoly(coefsArray[i], multiplyCoefs(coefsArray[j], division, n), n);
			//	sum = sumCoefs(sum, multiplyCoefs(coefsArray[j], division));


		}

		//coefsArray[i] = subPoly(f[i], sum);
	}



	return coefsArray;

}



double* multiplyByVector(double* coefs, double* vector, double n)
{
	double* newCoefs = new double[n + 1];
	for (int i = 0; i < n + 1; i++)
		newCoefs[i] = 0;


	for (int i = 0; i < n; i++)
	{
		if (coefs[0] != 0)
			newCoefs[0] = 0;
		newCoefs[i + 1] = coefs[i] * vector[1];
	}
	return newCoefs;

}

double* addBeta(double* vector, double beta, double n)
{
	double* newVector = new double[n];
	newVector = vector;

	newVector[0] = vector[0] + beta;
	return newVector;
}



//funkcja obliczajaca gamme
double gamma(double a, double b, double* coef, double* coef2, double(*wf)(double), double n)
{
	return -(trapezoidalMethodUniformGrid(0.05, a, b, coef, coef, wf, n) /
		trapezoidalMethodUniformGrid(0.05, a, b, coef2, coef2, wf, n));
}


//funkcja obliczajaca bete
double beta(double a, double b, double* coef, double* vector, double(*wf)(double), double n)
{
	return -(trapezoidalMethodUniformGrid(0.05, a, b, multiplyByVector(coef, vector, n), coef, wf, n) / trapezoidalMethodUniformGrid(0.05, a, b, coef, coef, wf, n));
}


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
double** triModule(double** f, double a, double b, double (*wf)(double), double n)
{
	double* vector = new double[n];
	for (int j = 0; j < n; j++)
		if (j == 1)
			vector[j] = 1;
		else
			vector[j] = 0;

	double** polyArray = new double* [n];
	for (int i = 0; i < n; i++)
		polyArray[i] = new double[2 * n - 1];


	polyArray[0] = f[0];
	polyArray[1] = multiplyTwoPolynomials(polyArray[0], (addBeta(vector, beta(a, b, polyArray[0], vector, wf, n),n)), n);


	for (int k = 2; k < n; k++)
	{

		polyArray[k] = sumCoefs(multiplyTwoPolynomials(polyArray[k - 1], addBeta(vector, beta(a, b, polyArray[k - 1], vector, wf, n),n), n), multiplyCoefs(polyArray[k - 2], gamma(a, b, polyArray[k - 1], polyArray[k - 2], wf, n), n), n);
	}


	return polyArray;

}











int main()
{

	double a = -1;
	double b = 1;
	double aPrim = 0;
	unsigned int degree = 5;
	//double (**functions)(double) = new (double(*[degree])(double));
	double** fcoefs = new double* [degree];
	for (int i = 0; i < degree; i++)
		fcoefs[i] = new double[degree];

	double cof1[] = { 1,0,0,0,0 };
	double cof2[] = { 0,1,0,0,0 };
	double cof3[] = { 0,0,1,0,0 };
	double cof4[] = { 0,0,0,1,0 };
	double cof5[] = { 0,0,0,0,1 };
	fcoefs[0] = cof1;
	fcoefs[1] = cof2;
	fcoefs[2] = cof3;
	fcoefs[3] = cof4;
	fcoefs[4] = cof5;
	double* alfa = new double[degree];
	// Aproksymacja baza podstawowa 1,x,x2,x3,x4
	cout << "Aproksymacja bazy podstawowej " << endl;
	alfa=Approximation(a, b, fcoefs, wageFunction, funcEx1,degree);
	for (int i = 0; i < degree; i++) cout << alfa[i] << endl;
	cout << endl;



	double** resultGramSchmidt = new double* [degree];
	for (int i = 0; i < degree; i++)
		resultGramSchmidt[i] = new double[degree];
	double** resultTriModule = new double* [degree];
	for (int i = 0; i < degree; i++)
		resultTriModule[i] = new double[degree];


	
	resultGramSchmidt = gramSchmidt(a, b, degree, fcoefs, wageFunction);

	cout << "Baza dla ortogonalizacji Grama-Schmidta na przedziale (-1,1)";
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultGramSchmidt[i][j] << " ";
	}
	cout << endl << endl;


	resultTriModule = triModule(fcoefs, a, b, wageFunction, degree);
	cout << "Baza dla reguly trojczlonowej na przedziale (-1,1)";
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultTriModule[i][j] << " ";
	}
	cout << endl << endl;
	ortonormalization(resultGramSchmidt, degree, a, b, wageFunction);
	cout << "Baza po ortonormalizacji dla Grama-Schmidta na przedziale (-1,1)" << endl;
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultGramSchmidt[i][j] << " ";
	}
	cout <<endl<<endl;

	cout << "Wartosci po aproksymacji dla bazy metody Grama-Schmidta na przedziale (-1,1)" << endl;
	alfa=Approximation(a, b, resultGramSchmidt, wageFunction, funcEx1, degree);
	for (int i = 0; i < degree; i++) cout << alfa[i] << endl;


	cout << endl << endl;
	cout << "Baza po ortonormalizacji dla reguly trojczlonowej na przedziale (-1,1)" << endl;

	ortonormalization(resultTriModule, degree, a, b, wageFunction);
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultTriModule[i][j] << " ";
	}
	cout << endl<<endl;
	

	cout << "Wynik aproksymacji dla bazy z reguly trojczlonowej na przedziale (-1,1)" << endl;
	alfa=Approximation(a,b, resultTriModule, wageFunction, funcEx1, degree);
	for (int i = 0; i < degree; i++) cout << alfa[i] << endl;
	cout << endl << endl;

	
	/// przedzial (0,1)
	resultGramSchmidt = gramSchmidt(aPrim, b, degree, fcoefs, wageFunction);

	cout << "Baza dla ortogonalizacji Grama-Schmidta na przedziale (0,1)";
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultGramSchmidt[i][j] << " ";
	}
	cout << endl << endl;

	

	resultTriModule = triModule(fcoefs, aPrim, b, wageFunction, degree);
	cout << "Baza dla reguly trojczlonowej na przedziale (0,1)";
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultTriModule[i][j] << " ";
	}

	cout << endl << endl;
	ortonormalization(resultGramSchmidt, degree, aPrim, b, wageFunction);
	cout << "Baza po ortonormalizacji dla Grama-Schmidta na przedziale (0,1)" << endl;
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultGramSchmidt[i][j] << " ";
	}
	cout << endl<<endl;

	cout << "Wartosci po aproksymacji dla metody Grama-Schmidta na przedziale (0,1)" << endl;
	alfa=Approximation(aPrim, b, resultGramSchmidt, wageFunction, funcEx1, degree);
	for (int i = 0; i < degree; i++) cout << alfa[i] << endl;
	cout << endl << endl;



	cout << endl;
	cout << "Baza po ortonormalizacji dla reguly trojczlonowej na przedziale (0,1)" << endl;
	ortonormalization(resultTriModule, degree, a, b, wageFunction);
	for (int i = 0; i < degree; i++) {
		cout << endl;
		for (int j = 0; j < degree; j++)
			cout << resultTriModule[i][j] << " ";
	}
	cout << endl << endl;
	cout << "Wynik aproksymacji dla bazy z reguly trojczlonowej na przedziale (0,1)" << endl;
	alfa=Approximation(aPrim, b, resultTriModule, wageFunction, funcEx1, degree);
	for (int i = 0; i < degree; i++) cout << alfa[i] << endl;



	system("pause");
	return 0;
}