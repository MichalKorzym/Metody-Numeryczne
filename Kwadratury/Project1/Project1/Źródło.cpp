#include <iostream>
#include <fstream>
using namespace std;


//funckcje 
 // funkcja sinx+x^2+4 do zadania 1/2
static double function(double x)
{
	return sin(x)+pow(x,2)+4;
}

//funkcja zadanie 4
static double functionEx4(double x)
{
	return (double) pow(x,2) *(double)pow(sin(x),3);
}
//funkcja zadanie 5
static double functionEx5(double x)
{
	return exp(pow(x,2)) * (x - 1);
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

// drugi wielomian
static double polynomial2(double x)
{
	double coefs[] = { 1,-2,-6,5,0.4 };
	int arrSize = sizeof(coefs) / sizeof(coefs[0]);
	return horner(arrSize, coefs, x);
}
//zadanie 1
//pobierane z pliku 
//wezly nierownoodlegle
double trapezoidalMethodNon_UniformGrid(double function(double), double* x,unsigned int notEqualKnotsCount)
{

	double result = 0;
	
	for (int i = 0; i < notEqualKnotsCount-1; i++)
		result += (((x[i + 1] - x[i]) / 2) * function(x[i])) + (((x[i + 1] - x[i]) / 2) * function(x[i + 1]));
	

	return result;
}

//wezly rownoodlegle
double trapezoidalMethodUniformGrid(double function(double),double h ,double xp,double xk)
{
	
	double result = 0;
	
	double numberOfKnots = (xk - xp) / h;;
	for (int i = 1; i < numberOfKnots; i++) {

		result = result + function(xp + i * h);

	}
	result = (result + (function(xk) + function(xp)) / 2) * h;

	return result;
}

double simpsoneMethod(double function(double), double h,double xp,double xk)
{
	double result = 0;
	
	double numberOfKnots = (xk-xp) / h;
	for (double i = 1; i <= numberOfKnots / 2; i++)
	{
		
		result += function((2 * i - 2)*h+xp) + 4 * function((2 * i - 1)*h+xp) + function((2 * i)*h+xp);

	}
	result = (result * h) / 3;

	return result;
}



int main()
{	
	
	unsigned int notEqualKnotsCount;

	//wczytywanie danych
	ifstream data("data.txt");
	data >> notEqualKnotsCount;
	double* notEqualIntervalsKnots = new double[notEqualKnotsCount];
	for (int i = 0; i < notEqualKnotsCount; i++)
	{
		data >> notEqualIntervalsKnots[i];
	}

	data.close();

	
	cout << "ZADANIE1 " << endl;
	cout << "Metoda trapezow dla wezlow nie rownoodleglych" << endl;
	cout <<"Wynik: "<< trapezoidalMethodNon_UniformGrid(function, notEqualIntervalsKnots, notEqualKnotsCount)<<endl;
	cout << "ZADANIE2" << endl;
	cout <<"Metoda trapezow dla wezlow rownoodleglych" << endl;
	cout <<"Wynik: "<< trapezoidalMethodUniformGrid(function, 0.05,-2,2) << endl;
	cout << "Metoda simposna (parabol) dla wezlow rownoodlegch" << endl;
	cout <<"Wynik: "<< simpsoneMethod(function, 0.05, -2 ,2)<<endl<<endl;
	cout << "Wyniki dla funkcji z zadania4 x^2*sin^3(x)" << endl;
	cout << "Wynik dla metody trapezow: " << trapezoidalMethodUniformGrid(functionEx4, 0.01,0,4.5) << endl;
	cout << "Wynik dla simpsona: " << simpsoneMethod(functionEx4,0.01,0,4.5) << endl<<endl;
	cout << "Wyniki dla funkcji z zadania 5 exp(x^2*(x-1))" << endl;
	cout << "Wynik dla metody trapezow: " << trapezoidalMethodUniformGrid(functionEx5,0.05,-2,2) << endl;
	cout << "Wynik dla simpsona: " << simpsoneMethod(functionEx5,0.05,-2,2) << endl<<endl;
	cout << "Wyniki dla wielomianu, zadanie 3 " << endl;
	cout << "Wielomian 1" << endl;
	cout <<"Metoda trapezow: " <<trapezoidalMethodUniformGrid(polynomial1, 0.05,-2,2)<<endl;
	cout << "Metoda simpsona: " << simpsoneMethod(polynomial1 ,0.05,-2,2) << endl;
	cout << "Wielomian 2 " << endl;
	cout << "Metoda trapezow: " << trapezoidalMethodUniformGrid(polynomial2, 0.05, -2, 2) << endl;
	cout << "Metoda simpsona: " << simpsoneMethod(polynomial2, 0.05, -2, 2) << endl;
	cout << endl;
	cout << "|Testowanie ilosci krokow|" << endl;
	cout << "FUNKCJA ZADANIE 4" << endl;
	double i = 0.02;
	while (i  <= 0.1) {

		cout << "Metoda trapezow: " << trapezoidalMethodUniformGrid(functionEx4, i, 0, 4.5) << "\t";
		cout << "Simpson: " << simpsoneMethod(functionEx4, i, 0, 4.5) << "\t";
		cout << "Krok calkowania " << i << endl;
		i=i+0.02;
	}
	cout <<endl<< endl;
	i = 0.02;
	cout << "FUNKCJA ZADANIE 5" << endl;
	while ( i <= 0.1) {
	
		cout << "Metoda trapezow: " << trapezoidalMethodUniformGrid(functionEx5, i, -2, 2) << "\t";
		cout << "Simpson: " << simpsoneMethod(functionEx5, i, -2, 2) << "\t";
		cout << "Krok calkowania " << i << endl;
		i = i + 0.02;
	}
	delete[] notEqualIntervalsKnots;
	return 0;
	system("pause");

}