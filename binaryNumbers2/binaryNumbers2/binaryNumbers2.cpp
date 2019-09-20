// binaryNumbers2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <bitset>
#include <limits>
#include <iostream>
#include <math.h>
#include <queue>

using namespace std;

bitset<32> & toInt(int number)
{
	bitset<32> res;
	int k;
	bool flag = false, negative = false;
	if (number < 0) {
		negative = true;
		res = ~res;
		number *= -1;
	}

	for (int i = 0; number != 0 && i < 32; i++) {
		k = number % 2;
		if (negative) {
			if (flag) {
				k = (k + 1) % 2;
			}
			else {
				flag = k == 1;
			}
		}
		res[i] = k;
		number /= 2;
	}

	return res;
}

bitset<32>& sumInt(bitset<32> & a, bitset<32> & b) {
	bitset<32> res;
	int c = 0, n, p;
	for (int i = 0; i < 32; i++) {
		p = a[i] + b[i] + c;
		n = p % 2;
		res[i] = n;
		c = p / 2;
	}
	return res;
}

bitset<32> toFloat(float number) {

	bitset<32> res;
	bool flag = false;

	if (number < 0) {
		res[31] = 1;
		number *= -1;
	}
	int p = 127;
	int mantissaCurrentSize = 0;
	int exponent = 128;
	float q = pow(2, p); 

	while (mantissaCurrentSize <= 23 && p >= 0) {
		if (number >= q) {
			if (flag)
			{
				res[23 - mantissaCurrentSize] = 1;
			}
			else
			{
				flag = true;
				exponent = p;
			}
			number -= q;
		}

		if (flag) mantissaCurrentSize++;
		q /= 2;
		p--;
	}

	while (mantissaCurrentSize <= 23 && p >= -127) {
		number *= 2;
		if (number >= 1) {
			number -= 1;
			if (flag) {
				res[23 - mantissaCurrentSize] = 1;
			}
			else
			{
				flag = true;
				exponent = p;
			}
		}
		if (flag) mantissaCurrentSize++;
		p--;
	}
	if (exponent == 128) return res;

	exponent += 127;
	for (int i = 0; i < 8; i++) {
		res[i + 23] = exponent % 2;
		exponent /= 2;
	}

	return res;
}

int getSub(bitset<32> & greaterNumber, bitset<32> lowerNumber) {
	int sub = 0, k = 0, n = 1;
	for (int i = 23; i < 31; i++) {
		if (greaterNumber[i] == 1) {
			if (lowerNumber[i] == k)
				sub += n;
			else k = 0;
		}
		else {
			if (lowerNumber[i] != k) {
				sub += n;
				k = 1;
			}
		}
		n *= 2;
	}
	return sub;
}

bitset<32> & sumMantiss(bitset<32> &greaterNumber, bitset<32> &lowerNumber, int sub) {
	int n = 0, p, i;
	bitset<32> res;
	for (i = 0; i <= 23 - sub; i++) {

		p = (i == 23 ? 1 : greaterNumber[i]) + ((i+sub) == 23 ? 1 : lowerNumber[i + sub]) + n;
		res[i] = p % 2;
		n = p / 2;
	}

	for (; i < 23; i++) {
		p = greaterNumber[i] + n;
		res[i] = p % 2;
		n = p / 2;
	}

	if (n == 1) {
		for (i = 1; i < 24; i++) {
			res[i - 1] = res[i];
		}
		for (int i = 23; i < 31; i++) {
			p = greaterNumber[i] + n;
			res[i] = p % 2;
			n = p / 2;
		}
	}
	else {
		for (int i = 23; i < 31; i++) {
			res[i] = greaterNumber[i];
		}
	}
	
	return res;
}

bitset<32>& sumFloat(bitset<32> & a, bitset<32> & b) {
	int sub = 0;
	for (int i = 30; i >= 23; i--) {
		if (a[i] > b[i]) {
			sub = getSub(a, b);
			return sumMantiss(a, b, sub);
		}
		if (a[i] < b[i]) {
			sub = getSub(b, a);
			return sumMantiss(b, a, sub);
		}
	}
	return sumMantiss(a, b, sub);
}

int main()
{
	int a, b, c;
	cout << "First integer number: ";
	cin >> a;
	bitset<32> binaryA = toInt(a);
	cout << "Reference    : " << bitset<32>(a) << endl;
	cout << "Code variant : " << binaryA << endl;
	cout << "Second integer number: ";
	cin >> b;
	bitset<32> binaryB = toInt(b);
	cout << "Reference    : " << bitset<32>(b) << endl;
	cout << "Code variant : " << binaryB << endl;

	c = a + b;
	bitset<32> binaryC = sumInt(binaryA, binaryB);
	cout << "Sum: " << a << " + " << b << " = " << c << endl;
	cout << "Reference    : " << bitset<32>(c) << endl;
	cout << "Code variant : " << binaryC << endl;

	
	float d, e, f;

	cout << "First fractional number: ";
	cin >> d;
	int* rf = reinterpret_cast<int*>(&d);
	bitset<32> binaryD = toFloat(d);
	cout << "Reference    : " << bitset<32>(*rf) << endl;
	cout << "Code variant : " << binaryD << endl;

	cout << "Second fractional number: ";
	cin >> e;
	rf = reinterpret_cast<int*>(&e);
	bitset<32> binaryE = toFloat(e);
	cout << "Reference    : " << bitset<32>(*rf) << endl;
	cout << "Code variant : " << binaryE << endl;

	f = d + e;
	cout << "Sum: " << d << " + " << e << " = " << f << endl;
	rf = reinterpret_cast<int*>(&f);
	bitset<32> binaryF = sumFloat(binaryD, binaryE);
	cout << "Reference    : " << bitset<32>(*rf) << endl;
	cout << "Code variant : " << binaryF << endl;

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
