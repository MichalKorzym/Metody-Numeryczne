#include <iostream>


using namespace std;

double dTdt(double t,double T)
{
	double alfa = -0.00000000001;
	double beta = 0;

	return alfa * (pow(T, 4) - beta);
}




void euler(double t0,  double tk,double T)
{
	double h = (t0 + tk) /12000; //0,025
	
	while (t0 < tk)
	{
	
		T = T + h * dTdt(t0, T);
		t0 = t0 + h;

		}
	cout << T << endl;
}

void Heuna(double t0, double tk,double T)
{

	double h = (t0 + tk) /12000;

	
	while (t0 < tk)
	{
		T = T + (0.5 * h * (dTdt(t0, T) + dTdt(t0 + h, T + h * dTdt(t0, T))));
		t0 = t0 + h;
	}
	cout << T << endl;
}

void modifyEuler(double t0, double tk, double T)
{
	double h = (t0 + tk) /12000;

	while (t0 < tk)
	{
		T = T + h * dTdt(t0 + (0.5 * h), T + (0.5 * h * dTdt(t0, T)));
		t0 = t0 + h;
	}
	cout << T << endl;

}

void RK(double t0, double tk, double T)
{
	double h = (t0 + tk) / 12000;

	
	double k1, k2, k3, k4;
	while(t0<tk)
	{
		k1 = dTdt(t0, T);
		k2 = dTdt(t0 + (0.5 * h), T + (0.5 * h * k1));
		k3 = dTdt(t0 + (0.5 * h), T + (0.5 * h * k2));
		k4 = dTdt(t0 + h, T + (h * k3));
		T = T + h*(double)((k1 + 2 * k2 + 2 * k3 + k4)) / 6;
		t0 = t0 + h;

	}

	cout << T << endl;

}

int main()
{
	
		cout << "Metoda Eulera" << endl;
		euler(0, 300, 1200);
		cout << "Metoda Heuna " << endl;
		Heuna(0, 300, 1200);
		cout << "Zmodyfikowana metoda Eulera" << endl;
		modifyEuler(0, 300, 1200);
		cout << "Metoda Rungego-Kutty" << endl;
		RK(0, 300, 1200);
		cout << endl;
	

	system("pause");

	return 0;

}