// binaryNumbers2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <bitset>
#include <limits>
#include <iostream>
#include <math.h>
#include <queue>

using namespace std;

bitset<32> & Sum(bitset<32> & a, bitset<32> & b) {
	bitset<32> res;
	int c = 0,n,p;
	for (int i = 0; i < 32; i++) {
		p = a[i] + b[i] + c;
		n = (p) % 2;
		res[i] = n;
		c = (p) / 2;
	}
	return res;
}

bitset<32>& ToTwo(int a)
{
	cout << bitset<32>(a) << endl;
	bitset<32> res;
	int k;
	bool flag = false ,minus = a < 0;
	if (minus) res = ~res;
	int b = abs(a);

	for (int i = 0; b != 0 && i < 32; i++) {
		k = b % 2;
		if (minus) {
			if (flag) {
				k = (k + 1) % 2;
			}
			else {
				flag = k == 1;
			}
		}
		res[i] = k;
		b = b / 2;
	}
	
	return res;
}

bitset<32> toFloat(float a) {

	bitset<32> res;
	bool flag = false;

	if (a < 0) {
		res[31] = 1;
		a *= -1;
	}
	int p = 127;
	int t = 0;
	int e = 128;
	float q = pow(2, p);

	while (t <= 23 && p >= 0) {
		if (a >= q) {
			if (flag)
			{
				res[23 - t] = 1;
			}
			else
			{
				flag = true;
				e = p;
			}
			a -= q;
		}

		if (flag) t++;
		q /= 2;
		p--;
	}
	while (t <= 23 && p >= -127) {
		a *= 2;
		if (a >= 1) {
			a -= 1;
			if (flag) {
				res[23 - t] = 1;
			}
			else
			{
				flag = true;
				e = p;
			}
		}
		if (flag) t++;
		p--;
	}
	if (e == 128) return res;
	e += 127;
	for (int i = 0; i < 8; i++) {
		res[i + 23] =  e%2;
		e /= 2;
	}
	
	return res;
}

bitset<32> & SumFloat(bitset<32> & a, bitset<32> & b) {
	bitset<32> res;
	int c = 0, n, p;
	for (int i = 0; i < 32; i++) {
		p = a[i] + b[i] + c;
		n = (p) % 2;
		res[i] = n;
		c = (p) / 2;
	}
	return res;
}

int main()
	{	
	float a = -0.000000000000003;
	int* rf = reinterpret_cast<int*>(&a);
	cout << bitset<32>(*rf) << endl;
	bitset<32> t = toFloat(a);
	cout << t << endl;	

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
