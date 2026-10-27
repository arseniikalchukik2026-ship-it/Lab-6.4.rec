#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
using namespace std;

void Create(double* a, const int size, const int Low, const int High, int i)
{
	a[i] = Low + (double)rand() / RAND_MAX * (High - Low);
	if (i < size - 1)
		Create(a, size, Low, High, i + 1);
}

void Print(double* a, const int size, int i)
{
	cout << setw(8) << fixed << setprecision(2) << a[i];
	if (i < size - 1)
		Print(a, size, i + 1);
	else
		cout << endl;
}

double Min(double* a, const int size, int i, double min)
{
	if (a[i] < min)
		min = a[i];
	if (i < size - 1)
		return Min(a, size, i + 1, min);
	else
		return min;
}

// індекс першого додатного елемента, або -1, якщо таких немає
int FirstPositiveIndex(double* a, const int size, int i)
{
	if (a[i] > 0)
		return i;
	if (i < size - 1)
		return FirstPositiveIndex(a, size, i + 1);
	else
		return -1;
}

// індекс останнього додатного елемента, або -1, якщо таких немає
// (перегляд з кінця масиву, тому i зменшується)
int LastPositiveIndex(double* a, int i)
{
	if (a[i] > 0)
		return i;
	if (i > 0)
		return LastPositiveIndex(a, i - 1);
	else
		return -1;
}

// сума елементів від індексу i до last (сам last не входить)
double SumBetween(double* a, const int last, int i)
{
	if (i < last)
		return a[i] + SumBetween(a, last, i + 1);
	else
		return 0;
}

// сума елементів між першим і останнім додатними; 0, якщо між ними нічого немає
double SumBetweenFirstAndLastPositive(double* a, const int size)
{
	int first = FirstPositiveIndex(a, size, 0);
	int last = LastPositiveIndex(a, size - 1);
	if (first == -1 || first == last)
		return 0;
	return SumBetween(a, last, first + 1);
}

// зсув елементів з номерами від k до j-1 на одну позицію вправо
void ShiftRight(double* a, const int k, int j)
{
	if (j > k)
	{
		a[j] = a[j - 1];
		ShiftRight(a, k, j - 1);
	}
}

// спочатку всі нулі, потім усі інші; відносний порядок збережено
// k - позиція, куди ставити наступний нуль
void MoveZerosToFront(double* a, const int size, int i, int k)
{
	if (a[i] == 0)
	{
		ShiftRight(a, k, i);
		a[k] = 0;
		k++;
	}
	if (i < size - 1)
		MoveZerosToFront(a, size, i + 1, k);
}

int main()
{
	srand((unsigned)time(NULL));   // ініціалізація генератора випадкових чисел

	int n;
	cout << "n = ";
	cin >> n;

	int Low = -5;
	int High = 5;

	double* a = new double[n];     // створили динамічний масив

	Create(a, n, Low, High, 0);
	Print(a, n, 0);

	cout << "Min = " << Min(a, n, 0, a[0]) << endl;
	cout << "Sum = " << SumBetweenFirstAndLastPositive(a, n) << endl;

	MoveZerosToFront(a, n, 0, 0);
	Print(a, n, 0);

	delete[] a;                    // звільнили динамічний масив
	return 0;
}