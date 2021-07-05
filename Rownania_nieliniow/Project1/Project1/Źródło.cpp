#include <iostream>
using namespace std;

#define EPSILON 0.0001


//test
static double testowaFunkcja(double x)
{
	return -pow(x, 2) - 4;
}
static double function1(double x)
{


	return pow(x, 3) + pow(x, 2) - 3 * x - 3;
}


//pochodna
static double derativeOne(double x)
{
	return 3 * pow(x, 2) + 2 * x - 3;
}


static double function2(double x)
{
	return pow(x, 2) - 2;
}
static double derativeTwo(double x)
{
	return 2 * x;
}

static double function3(double x)
{
	return sin(pow(x, 2)) - pow(x, 2);
}
static double derativeThreeAndFour(double x)
{
	return 2 * x*(cos(pow(x, 2)) - 1);
}

static double function4(double x)
{
	return sin(pow(x, 2)) - pow(x, 2) + 0.5;
}


//obliczanie pochodnej metoda roznic skonczonych
static double Counting_Deratives(double function(double), double x)
{
	return (function(x + 0.05)-function(x)) / 0.05;
}

//metoda newtona rhapsona obliczanie pochodnej numerycznie
static double  Newton_Rhapson(double function(double),double x)
{
	cout << "Punkt startowy: " << x << endl;
	double tmp = x - function(x) / Counting_Deratives(function, x);


	while (fabs(tmp) >= EPSILON) {
		tmp = function(x) / Counting_Deratives(function,x);
		x = x - tmp;
	}

	return x;
}

// metoda newtona rhapsona obliczanie pochodnej analitycznie
static double  Newton_Rhapson_Analytical(double function(double),double derative(double), double x)
{

	cout << "Punkt startowy: " << x << endl;
	double tmp = x - function(x) / derative( x);


	while (fabs(tmp) >= EPSILON) {
		
		tmp = function(x) / derative(x);
		x = x - tmp;
	}

	return x;
}


//falszywe linie
static double Falsi_Method(double x0, double x1, double function(double))
{
		//sprawdzenie czy wprowadzony przedzial jest poprawny 
	cout << "Przedzial, : poczatek " << x0 << " koniec " << x1 << endl;


	if (function(x0) * function(x1) > 0) {
		cout << "Bledny przedzial funkcja na koncach musi miec rozne znaki " << endl;


	}
	else
	{

		double tmp = x0;
		do {
			tmp = x0 - (function(x0) * (x1 - x0)) / (function(x1) - function(x0));
			if (function(tmp) == 0)
				break;

			if (function(x0) * function(tmp) < 0)
				x1 = tmp;

			else
				x0 = tmp;

		} while (fabs(function(tmp)) >= EPSILON);
		return tmp;
	}
}

//bisekcja
static double Bisection_Method(double x0, double x1, double function(double))
{
	cout << "Przedzial, : poczatek " << x0 << " koniec " << x1 << endl;
	if (function(x0) * function(x1) > 0) {
		cout << "Bledny przedzial funkcja na koncach musi miec rozne znaki " << endl;
	
	}
	else
	{
		double tmp = x0;

		while (x1 - x0 >= EPSILON)
		{
			tmp = (x0 + x1) / 2;

			if (fabs(function(tmp)) < EPSILON)
				break;
			else if (function(tmp) * function(x0) < 0)
				x1 = tmp;
			else
				x0 = tmp;
		}

		return tmp;
	}

}

//metoda siecznych
static double Secant_Method(double x0, double x1, double function(double))
{
	double tmp,tmp2,check;
	cout << "Przedzial, : poczatek " << x0 << " koniec " << x1 << endl;
	if (function(x0) * function(x1) > 0)
	{

		cout << "Bledny przedzial funkcja na koncach musi miec rozne znaki " << endl;

	}
	else
	{
		do {
			tmp = (x0 * function(x1) - x1 * function(x0)) / (function(x1) - function(x0)); //przeksztalcenie x0-(x1-x0)*f(x0)/f(x1)-f(x0)
			
			if (function(x1) * function(x0)==0)
				break;

			x0 = x1;
			x1 = tmp;

			tmp2 = (x0 * function(x1) - x1 * function(x0)) / (function(x1) - function(x0));
			
			} while (fabs(tmp2 - tmp) >= EPSILON);
		return tmp;
		}
	}
	
	
	
		
	
	


	




int main()

{
	double x0;
	 //Metoda NEWTONA-RHAPSONA

	cout << "========================================" << endl;
	cout << "   Metoda NR ca³ka liczona numerycznie            " << endl;
	cout << "========================================" << endl;
	x0 = Newton_Rhapson( function1, -2);
	cout <<"Newton-Rhapson f1 pierwsze miejsce zerowe "<< x0<<endl;

	x0 = Newton_Rhapson(function1, 0);
	cout << "Newton-Rhapson f1 drugie miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson(function1, 1);
	cout << "Newton-Rhapson f1 trzecie miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson(function2, -1);
	cout << "Newton-Rhapson f2 pierwsze miejsce zerowe " << x0 << endl;


	x0 = Newton_Rhapson(function2, 1);
	cout << "Newton-Rhapson f2  drugie miejsce zerowe " << x0 << endl;


	x0 = Newton_Rhapson(function3, 5);
	cout << "Newton-Rhapson f3 miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson(function4, -5);
	cout << "Newton-Rhapson f4 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson(function4, 5);
	cout << "Newton-Rhapson f4 drugie miejsce zerowe " << x0 << endl;
	cout << endl;

	cout << "========================================" << endl;
	cout << "   Metoda NR ca³ka liczona analitycznie           " << endl;
	cout << "========================================" << endl;

	x0 = Newton_Rhapson_Analytical(function1,derativeOne, -2);
	cout << "Newton-Rhapson f1 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson_Analytical(function1, derativeOne, 0);
	cout << "Newton-Rhapson f1 drugie miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson_Analytical(function1, derativeOne, 1);
	cout << "Newton-Rhapson f1 trzecie miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson_Analytical(function2, derativeTwo,-1);
	cout << "Newton-Rhapson f2 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson_Analytical(function2,derativeTwo, 1);
	cout << "Newton-Rhapson f2  drugie miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson_Analytical(function3, derativeThreeAndFour, 5);
	cout << "Newton-Rhapson f3 miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson_Analytical(function4, derativeThreeAndFour, -5);
	cout << "Newton-Rhapson f4 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Newton_Rhapson_Analytical(function4, derativeThreeAndFour, 5);
	cout << "Newton-Rhapson f4 drugie miejsce zerowe " << x0 << endl;
	cout << endl;

	//Metoda siecznych

	cout << "========================================" << endl;
	cout << "             Metoda siecznych           " << endl;
	cout << "========================================" << endl;




	x0 = Secant_Method(-2, -1.5, function1);
	cout << "Secant f1 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Secant_Method(-1.5, -0.5, function1);
	cout << "Secant  f1 drugie miejsce zerowe " << x0 << endl;

	x0 = Secant_Method(1, 2, function1);
	cout << "Secant  f1 trzecie miejsce zerowe " << x0 << endl;

	x0 = Secant_Method(-2.5, -0.5, function2);
	cout << "Secant f2 pierwsze miejsce zerowe  " << x0 << endl;

	x0 = Secant_Method(0.5 , 2.5, function2);
	cout << "Secant f2 drugie miejsce zerowe  " << x0 << endl;

	x0 = Secant_Method(-3, 0.5, function3);
	cout << "Secant f3 miejse zerowe " << x0 << endl;

	x0 = Secant_Method(-2, -1, function4);
	cout << "Secant f4 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Secant_Method(1, 2, function4);
	cout << "Secant f4 drugie miejsce zerowe " << x0 << endl;

	cout << endl;


	//FALSI

	cout << "========================================" << endl;
	cout << "             Regula Falsi           " << endl;
	cout << "========================================" << endl;



	x0 = Falsi_Method(1,2 , function1);
	cout <<"Falsi f1 pierwsze miejsce zerowe "<<x0<<endl;

	x0 = Falsi_Method(-1.5, -0.5, function1);
	cout << "Falsi f1 drugie miejsce zerowe  " << x0 << endl;

	x0 = Falsi_Method(-2, -1.5, function1);
	cout << "Falsi f1 trzecie miejsce zerowe " << x0 << endl;

	x0 = Falsi_Method(-2.5, -0.5, function2);
	cout << "Falsi f2 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Falsi_Method(0.5, 2.5, function2);
	cout << "Falsi f2 drugie miejsce zerowe " << x0 << endl;

	x0 = Falsi_Method(-3, 0.5, function3);
	cout << "Falsi f3 miejsce zerowe " << x0 << endl;

	x0 = Falsi_Method(-2, 1, function4);
	cout << "Falsi f4 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Falsi_Method(1,2 , function4);
	cout << "Falsi f4 drugie miejsce zerowe " << x0 << endl;
	cout << endl;
	cout << "========================================" << endl;
	cout << "              Metoda Bisekcji            " << endl;
	cout << "========================================" << endl;

	//Bisekcja
	x0 = Bisection_Method(-2, -1.5, function1);
	cout << "Bisection f1 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Bisection_Method(-1.5, 0.5, function1);
	cout << "Bisection f1 drugie miejsce zerowe " << x0 << endl;


	x0 = Bisection_Method(1, 2, function1);
	cout << "Bisection f1 trzecie miejsce zerowe " << x0 << endl;


	x0 = Bisection_Method(-2.5, -0.5, function2);
	cout << "Bisection f2 pierwsze miejsce zerowe " << x0 << endl;

	x0 = Bisection_Method(0.5, 2.5, function2);
	cout << "Bisection f2 drugie miejsce zerowe " << x0 << endl;


	x0 = Bisection_Method(-3, 0.5, function3);
	cout << "Bisection f3 miejsce zerowe " << x0 << endl;

	x0 = Bisection_Method(-2, -1, function4);
	cout << "Bisection pierwsze miejsce zerowe " << x0 << endl;

	x0 = Bisection_Method(1, 2, function4);
	cout << "Bisection drugie miejsce zerowe " << x0 << endl;


	system("pause");
	return 0;


}