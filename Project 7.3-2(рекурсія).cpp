// Lab_7_3-2.cpp
// < Кузів Назар >
// Лабораторна робота № 7.3
// Опрацювання динамічних багатовимірних масивів(рекурсія 2)
// Варіант 6

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int rowCount, const int colCount,
	const int Low, const int High, int i, int j)
{
	a[i][j] = Low + rand() % (High - Low + 1);

	if (j < colCount - 1)
		Create(a, rowCount, colCount, Low, High, i, j + 1);
	else
		if (i < rowCount - 1)
			Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << setw(4) << a[i][j];
	if (j < colCount - 1)
		Print(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1)
		{
			cout << endl;
			Print(a, rowCount, colCount, i + 1, 0);
		}
		else
			cout << endl << endl;
}
bool IsMinInRowN(int** a, const int rowNo, const int max, const int colCount, int colNo)
{
	if (a[rowNo][colNo] < max)
		return false;
	if (colNo < colCount - 1)
		return IsMinInRowN(a, rowNo, max, colCount, colNo + 1);
	else
		return true;
}
bool IsMaxInColK(int** a, const int colNo, const int min, const int rowCount, int rowNo)
{
	if (a[rowNo][colNo] > min)
		return false;
	if (rowNo < rowCount - 1)
		return IsMaxInColK(a, colNo, min, rowCount, rowNo + 1);
	else
		return true;
}
void SaddlePointRow(int** a, const int rowCount, const int colCount, int& No, const int rowNo, int colNo)
{
	if (IsMinInRowN(a, rowNo, a[rowNo][colNo], colCount, 0) &&
		IsMaxInColK(a, colNo, a[rowNo][colNo], rowCount, 0))
	{
		cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;
	}
	if (colNo < colCount - 1)
		SaddlePointRow(a, rowCount, colCount, No, rowNo, colNo + 1);
}
void SaddlePoints(int** a, const int rowCount, const int colCount, int& No, int rowNo)
{
	SaddlePointRow(a, rowCount, colCount, No, rowNo, 0);
	if (rowNo < rowCount - 1)
		SaddlePoints(a, rowCount, colCount, No, rowNo + 1);
}

int main()
{
	srand((unsigned)time(NULL));
	int Low = -5;
	int High = 35;

	int rowCount, colCount;

	cout << "rowCount = "; cin >> rowCount;
	cout << "colCount = "; cin >> colCount;

	int** arr = new int* [rowCount];

	for (int i = 0; i < rowCount; i++)
		arr[i] = new int[colCount];

	Create(arr, rowCount, colCount, Low, High, 0, 0);
	cout << endl;
	Print(arr, rowCount, colCount, 0, 0);

	cout << endl;
	cout << "Saddle points: min in row & max in col" << endl;
	cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
	int No = 0;
	SaddlePoints(arr, rowCount, colCount, No, 0);
	

	for (int i = 0; i < rowCount; i++)
		delete[] arr[i];
	delete[] arr;

	return 0;
}
