#include <iostream>
#include <ctime>
#include <time.h>
#include <math.h>
#include <random>
using namespace std;


double function1(double x)
{
	return	pow(x, 2)* pow(sin(x), 3);
}

double function2(double x)
{
	return pow(x, 2) * exp(pow(x, 2)) * (x - 1);
}

double getRand()
{
	//cout << (double)rand()/RAND_MAX<<endl;
	return (double)rand()/ RAND_MAX;
}

double  getRandomDevice()
{
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<double> dis(0.0,1.0);
	//cout << dis(gen) << endl;
	return dis(gen);
}

double MonteCarlo(double xp, double xk, int n,double function(double),double randGen())
{
	
	


	double result = 0;
	double randomPoint;
	double tmp;
	for (int i = 0; i < n; i++)
	{
		randomPoint = xp + (xk - xp) * randGen();
		tmp = function(randomPoint);
		result = result + tmp;


	}

	result = result / n;
	result = result * abs(xk - xp);
	return result;

}
double trapezoidalMethodUniformGrid(double function(double), double h, double xp, double xk)
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
	srand(time(NULL));
	cout << "Metoda Monte Carlo " << endl;
	double f1Integrate = MonteCarlo(0, 4.5,10, function1,getRand);
	double f2Integrate = MonteCarlo(-2, 2, 10, function2,getRand);
	cout << "Monte Carlo Wynik dla funkcji 1 rand() dla 10 " << endl;
	cout << f1Integrate << endl;
	cout << "Monte Carlo Wynik dla funkcji 2 rand() dla 10" << endl;
	cout << f2Integrate << endl;



	double f1IntegrateDevice = MonteCarlo(0, 4.5, 10, function1, getRandomDevice);
	double f2IntegrateDevice = MonteCarlo(-2, 2, 10, function2, getRandomDevice);
	cout << "Monte Carlo Wynik dla funkcji 1 randDevice dla 10" << endl;
	cout << f1IntegrateDevice << endl;
	cout << "Monte Carlo Wynik dla funkcji 2 randDevice dla 10" << endl;
	cout << f2IntegrateDevice << endl;
	cout << endl << endl;

	 f1Integrate = MonteCarlo(0, 4.5, 100, function1, getRand);
	f2Integrate = MonteCarlo(-2, 2, 100, function2, getRand);
	cout << "Monte Carlo Wynik dla funkcji 1 rand() dla 100" << endl;
	cout << f1Integrate << endl;
	cout << "Monte Carlo Wynik dla funkcji 2 rand() dla 100" << endl;
	cout << f2Integrate << endl;

	 f1IntegrateDevice = MonteCarlo(0, 4.5, 100, function1, getRandomDevice);
	 f2IntegrateDevice = MonteCarlo(-2, 2, 100, function2, getRandomDevice);
	cout << "Monte Carlo Wynik dla funkcji 1 randDevice dla 100 " << endl;
	cout << f1IntegrateDevice << endl;
	cout << "Monte Carlo Wynik dla funkcji 2 randDevice dla 100" << endl;
	cout << f2IntegrateDevice << endl;


	cout << endl << endl;

	 f1Integrate = MonteCarlo(0, 4.5, 1000, function1, getRand);
	 f2Integrate = MonteCarlo(-2, 2, 1000, function2, getRand);
	cout << "Monte Carlo Wynik dla funkcji 1 rand() dla 1000" << endl;
	cout << f1Integrate << endl;
	cout << "Monte Carlo Wynik dla funkcji 2 rand() dla 1000 " << endl;
	cout << f2Integrate << endl;



	 f1IntegrateDevice = MonteCarlo(0, 4.5, 1000, function1, getRandomDevice);
	f2IntegrateDevice = MonteCarlo(-2, 2, 1000, function2, getRandomDevice);
	cout << "Monte Carlo Wynik dla funkcji 1 randDevice dla 1000 " << endl;
	cout << f1IntegrateDevice << endl;
	cout << "Monte Carlo Wynik dla funkcji 2 randDevice dla 1000" << endl;
	cout << f2IntegrateDevice << endl;


	cout << endl << endl;

	 f1Integrate = MonteCarlo(0, 4.5, 1000000, function1, getRand);
	 f2Integrate = MonteCarlo(-2, 2, 1000000, function2, getRand);
	cout << "Monte Carlo Wynik dla funkcji 1 rand () dla 1000000" << endl;
	cout << f1Integrate << endl;
	cout << "Monte Carlo Wynik dla funkcji 2 rand () dla 1000000" << endl;
	cout << f2Integrate << endl;



	 f1IntegrateDevice = MonteCarlo(0, 4.5, 1000000, function1, getRandomDevice);
	 f2IntegrateDevice = MonteCarlo(-2, 2, 1000000, function2, getRandomDevice);
	cout << "Monte Carlo Wynik dla funkcji 1 randDevice dla 1000000" << endl;
	cout << f1IntegrateDevice << endl;
	cout << "Monte Carlo Wynik dla funkcji 2 randDevice dla 1000000" << endl;
	cout << f2IntegrateDevice << endl;

	cout << endl << endl;




	cout << "Metoda Simpsona " << endl;

	f1Integrate = simpsoneMethod(function1, 0.45, 0, 4.5);
	f2Integrate = simpsoneMethod(function2, 0.4, -2, 2);
	cout << "Wynik dla simpsoneMethod funkcja 1 dla 10" << endl;
	cout << f1Integrate << endl;
	cout << "Wynik dla simpsoneMethod funkcja 2 dla 10" << endl;
	cout << f2Integrate << endl;

	cout << endl << endl;


	f1Integrate = simpsoneMethod(function1, 0.045, 0, 4.5);
	f2Integrate = simpsoneMethod(function2, 0.04, -2, 2);
	cout << "Wynik dla simpsoneMethod funkcja 1 dla 100" << endl;
	cout << f1Integrate << endl;
	cout << "Wynik dla simpsoneMethod funkcja 2 dla 100" << endl;
	cout << f2Integrate << endl;


	cout << endl << endl;


	f1Integrate = simpsoneMethod(function1, 0.0045, 0, 4.5);
	f2Integrate = simpsoneMethod(function2, 0.004, -2, 2);
	cout << "Wynik dla simpsoneMethod funkcja 1 dla 1000" << endl;
	cout << f1Integrate << endl;
	cout << "Wynik dla simpsoneMethod funkcja 2 dla 1000" << endl;
	cout << f2Integrate << endl;


	cout << endl << endl;


	f1Integrate = simpsoneMethod(function1, 0.0000045, 0, 4.5);
	f2Integrate = simpsoneMethod(function2, 0.000004, -2, 2);
	cout << "Wynik dla simpsoneMethod funkcja 1 dla 1000000" << endl;
	cout << f1Integrate << endl;
	cout << "Wynik dla simpsoneMethod funkcja 2 dla 1000000" << endl;
	cout << f2Integrate << endl;


	cout << endl << endl;
	cout << "METODA TRAPEZOW" << endl;

	f1Integrate = trapezoidalMethodUniformGrid(function1, 0.45, 0, 4.5);
	f2Integrate = trapezoidalMethodUniformGrid(function2, 0.4, -2, 2);
	cout << "Wynik dla metody trapezow funkcja 1 dla 10" << endl;
	cout << f1Integrate << endl;
	cout << "Wynik dla metody trapezow funkcja 2 dla 10" << endl;
	cout << f2Integrate << endl;


	cout << endl << endl;

	f1Integrate = trapezoidalMethodUniformGrid(function1, 0.045, 0, 4.5);
	f2Integrate = trapezoidalMethodUniformGrid(function2, 0.04, -2, 2);
	cout << "Wynik dla metody trapezow funkcja 1 dla 100" << endl;
	cout << f1Integrate << endl;
	cout << "Wynik dla metody trapezow funkcja 2 dla 100" << endl;
	cout << f2Integrate << endl;


	cout << endl << endl;

	f1Integrate = trapezoidalMethodUniformGrid(function1, 0.0045, 0, 4.5);
	f2Integrate = trapezoidalMethodUniformGrid(function2, 0.004, -2, 2);
	cout << "Wynik dla metody trapezow funkcja 1 dla 1000" << endl;
	cout << f1Integrate << endl;
	cout << "Wynik dla metody trapezow funkcja 2 dla 1000" << endl;
	cout << f2Integrate << endl;


	cout << endl << endl;

	f1Integrate = trapezoidalMethodUniformGrid(function1, 0.0000045, 0, 4.5);
	f2Integrate = trapezoidalMethodUniformGrid(function2, 0.000004, -2, 2);
	cout << "Wynik dla metody trapezow funkcja 1 dla 1000000" << endl;
	cout << f1Integrate << endl;
	cout << "Wynik dla metody trapezow funkcja 2 dla 1000000" << endl;
	cout << f2Integrate << endl;


	cout << endl << endl;

	system("pause");
	return 0;
}