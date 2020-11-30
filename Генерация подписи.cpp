#include<iostream>
#include <math.h>
#include <conio.h>

using namespace std;

int module(int t, int p)           //для отрицательного числа   
{
	do { t = t + p; } while (t < 0);
	return t; 
}         

int doublelambda(int x, int y, int a, int p)          //лямбда для удвоения точки
{
	int chislo1, chislo2,lambda1;
	chislo1 = 3 * (pow(x,2)) + a;
	chislo2 = 2 * y;
	if (chislo2 < 0) { chislo1 = -chislo1; chislo2 = -chislo2; }
	if (chislo2 == 0) cout << "error";
	else
	{
		int flag = 0;
		//l*chislo=1 (mod p)
		for (int i = 1; i < p; i++)
		{
			int temp = (i * chislo2)%p;
			if (temp < 0) temp = module(temp, p);
			if (temp == 1) flag = 1;
			if (flag == 1) { chislo2 = i; break; }
		}
		lambda1 = (chislo1 * chislo2) % p;
		if (lambda1 < 0) lambda1 = module(lambda1, p);
		return lambda1;
	}
}    

int doublGx(int x, int y, int a, int p)      //поиск x3 для удвоенной точки
{
	int nx = pow(doublelambda(x, y, a, p), 2) - 2 * x;
	nx = nx % p;
	if (nx < 0) nx = module(nx, p);
	return nx;
}

int doublGy(int x, int y, int a, int p)   //поиск y3 для удвоенной точки
{
	int ny = doublelambda(x, y, a, p) * (x - doublGx(x, y, a, p)) - y;
	ny = ny % p;
	if (ny < 0) ny = module(ny, p);
	return ny;
}

int sumlambda(int x1, int y1, int x2, int y2, int p)   //поиск лямбды для суммы точек
{
	int chislo1, chislo2, lambda2;
	chislo1 = y2-y1;
	chislo2 = x2-x1;
	if (chislo2 < 0) { chislo1 = -chislo1; chislo2 = -chislo2; }
	if (chislo2 == 0) cout << "error";
	else
	{
		int flag = 0;
		//l*chislo=1 (mod p)
		for (int i = 1; i < p; i++)
		{
			int temp = (i * chislo2) % p;
			if (temp < 0) temp = module(temp, p);
			if (temp == 1) flag = 1;
			if (flag == 1) { chislo2 = i; break; }
		}
		lambda2 = (chislo1 * chislo2) % p;
		if (lambda2 < 0) lambda2 = module(lambda2, p);
		return lambda2;
	}
}

int sumx(int x1, int y1, int x2, int y2, int p)   //x3 для суммы
{
	int nx = pow(sumlambda(x1, y1, x2, y2, p),2) - x1 - x2;
	nx = nx % p;
	if (nx < 0) nx = module(nx, p);
	return nx;
}

int sumy(int x1, int y1, int x2, int y2, int x3, int p)   //y3 для суммы
{
	int ny = sumlambda(x1, y1, x2, y2, p) * (x1 - x3) - y1;
	ny = ny % p;
	if (ny < 0) ny = module(ny, p);
	return ny;
}

int finalx(int x1, int y1, int x2, int y2, int p)
{
	int x3;
	x3 = sumx(x1, y1, x2, y2, p);
	return x3;
}

int finaly(int x1, int y1, int x2, int y2, int p)
{
	int x3, y3;
	x3 = sumx(x1, y1, x2, y2, p);
	y3 = sumy(x1, y1, x2, y2, x3, p);
	return y3;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int k = 6, Gx = 416, Gy = 55, p = 751, a = -1, b = 1, q = 13, h = 5, d = 12, dx3, dy3,finx;
	if (k < 1) cout << "error";
	else if (k == 1) { dx3 = Gx; dy3 = Gy; cout << "kG = (" << Gx << ';' << Gy << ')'; }
	else if (k >= 2)
	{
		dx3 = doublGx(Gx, Gy, a, p);
		dy3 = doublGy(Gx, Gy, a, p);
		if (k == 2) { cout << "kG = (" << dx3 << ';' << dy3 << ')'; }
		else
		{
			int x1 = dx3, y1 = dy3, x2 = Gx, y2 = Gy;
			for (int j = 3; j <= k; j++)
			{
				int dx3 = finalx(x1, y1, x2, y2, p);
				int dy3 = finaly(x1, y1, x2, y2, p);
				x1 = dx3;
				y1 = dy3;
			}
			finx = x1;
			cout << "kG = (" << x1 << ';' << y1 << ')' << endl;
		}
	}

			int r = finx % q;                             //r
			cout << "r=" << r << endl;

			int z;                                       //z
			int flag = 0;
			for (int i = 1; i < q; i++)
			{
				int temp = (i * k) % q;
				if (temp == 1) flag = 1;
				if (flag == 1) { z = i; break; }
			}
			cout << "z=" << z << endl;

			int s;                                      //s
			s = (z * (h + d * r)) % q;
			cout << "s=" << s << endl;

			cout << "Цифровая подпись данного абонента для сообщения: (" << r << ',' << s << ')' << endl;

		
	}
