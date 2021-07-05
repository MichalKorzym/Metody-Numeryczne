#include <iostream>
using namespace std;

static double function1(double x)
{

	return pow(x, 2) * pow(sin(x), 3);
}
static double function2(double x)
{


	return exp(pow(x, 2)) * (x - 1);
}

//schemat hornera
static double horner(unsigned int degree, double* wsp, double x) {

	double wynik = wsp[degree - 1];
	for (int i = degree - 2; i >= 0; i--)
		wynik = wynik * x + wsp[i];

	return wynik;
}
// pierwszy wielomian
static double polynomial1(double x)
{
	double coefs[] = { 55,-2,-6,5,0.4 };
	int arrSize = sizeof(coefs) / sizeof(coefs[0]);
	return horner(arrSize, coefs, x);
}

double gaussLegandre(unsigned int n, double a, double b, double function(double))
{

	double twoKnotsX[] = { -0.577350,0.577350 };
	double twoKnotsA[] = { 1,1 };
	double threeKnotsX[] = { -0.774597,0,0.774597 };
	double threeKnotsA[] = { 0.5555556,0.888889,0.5555556 };
	double fourKnotsX[] = { -0.861136,-0.339981,0.339981 ,0.861136 };
	double fourKnotsA[] = { 0.347855,0.652145,0.652145 ,0.347655,0.236927 };
	double fiveKnotsX[] = { -0.906180,-0.538469,0,0.538469,0.906180 };
	double fiveKnotsA[] = { 0.236927,0.478629,0.568889,0.478629,0.23692 };
	double sum = 0;
	double xPrim;
	switch (n)
	{
	case 2:
		for (int i = 0; i < n; i++)
		{
			xPrim = a + ((b - a) * (twoKnotsX[i] - (-1))) / (double)(1 - (-1));
			sum += function(xPrim) * twoKnotsA[i];


		}
		break;
	case 3:
		for (int i = 0; i < n; i++)
		{
			xPrim = a + ((b - a) * (threeKnotsX[i] - (-1))) / (double)(1 - (-1));
			sum += function(xPrim) * threeKnotsA[i];


		}
		break;
	case 4:
		for (int i = 0; i < n; i++)
		{
			xPrim = a + ((b - a) * (fourKnotsX[i] - (-1))) / (double)(1 - (-1));
			sum += function(xPrim) * fourKnotsA[i];


		}
		break;
	case 5:
		for (int i = 0; i < n; i++)
		{
			xPrim = a + ((b - a) * (fiveKnotsX[i] - (-1))) / (double)(1 - (-1));
			sum += function(xPrim) * fiveKnotsA[i];


		}
		break;

	}


	sum = sum * ((b - a) / (double)(1 - (-1)));




	return sum;


}





int main()

{
	cout << "Funkcja 1" << endl;
	cout << gaussLegandre(2, 0, 4.5, function1)<<endl;
	cout << gaussLegandre(3, 0, 4.5, function1) << endl;
	cout << gaussLegandre(4, 0, 4.5, function1) << endl;
	cout << gaussLegandre(5, 0, 4.5, function1) << endl;
	cout << endl;
	cout << "Funkcja 2" << endl;
	cout << gaussLegandre(2, -2, 2, function2) << endl;
	cout << gaussLegandre(3, -2, 2, function2) << endl;
	cout << gaussLegandre(4, -2, 2, function2) << endl;
	cout << gaussLegandre(5, -2, 2, function2) << endl;
	cout << endl;
	cout << "Wielomian " << endl;
	cout << gaussLegandre(2, -2, 2, polynomial1) << endl;
	cout << gaussLegandre(3, -2, 2, polynomial1) << endl;
	cout << gaussLegandre(4, -2, 2, polynomial1) << endl;
	cout << gaussLegandre(5, - 2, 2, polynomial1) << endl;



	return 0;
	system("pause");
}