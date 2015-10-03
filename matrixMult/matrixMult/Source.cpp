#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
#include <omp.h>

using namespace std;


int main() {

	int aRows, aColumns, bRows, bColumns;
	int **a, **b, **c;
	int sum = 0;
	string answer = "";

	cout << "Input sizes of matrix A and B (max 13'000)\n\n";
	cout << "First matrix : Rows Columns = ";
	cin >> aRows >> aColumns;
	cout << "Second matrix : Rows Columns = ";
	cin >> bRows >> bColumns;

	if (aColumns != bRows) {

		cout << "\nError!\nMatrices can't be multiplied\n";
		cin.get(); cin.get();
		return 1;
	}

	clock_t t;
	t = clock();

	try {

		a = new int*[aRows];
		b = new int*[bRows];
		c = new int*[aRows];

		int maxRowCount = (aRows > bRows) ? aRows : bRows;

#pragma omp parallel num_threads(4)
{		
		#pragma omp for
		for (int i = 0; i < maxRowCount; i++) {

			if (i < aRows) a[i] = new int[aColumns];
			if (i < bRows) b[i] = new int[bColumns];
			if (i < aRows) c[i] = new int[bColumns];
		}
}
	}
	catch (bad_alloc) {

		cout << "Bad alloc (check your input!)\n";
		cin.get(); cin.get();
		return 2;

	}

	auto allocation = double((clock() - t)) / CLOCKS_PER_SEC;

	cout << "Allocation time : " << setprecision(30) << allocation
		<< endl;

	srand(time(NULL));
	t = clock();

	int maxRowCount = (aRows > bRows) ? aRows : bRows;
	int maxColumnCount = (aColumns > bColumns) ? aColumns : bColumns;

#pragma omp parallel num_threads(4)
{	
	
	for (int i = 0; i < maxRowCount; i++) {

		#pragma omp for 
		for (int j = 0; j < maxColumnCount; j++) {

			if (i < aRows && j < aColumns) a[i][j] = rand() % 200 - 100;
			if (i < bRows && j < bColumns)  b[i][j] = rand() % 200 - 100;
		}
	}
}

	
	auto filling = double((clock() - t)) / CLOCKS_PER_SEC;

	cout << "Filling time : " << setprecision(30) << filling
		 << endl;

	cout << "Work in progress...\n";

	srand(time(NULL));
	t = clock();
	
	int i, j, k;

#pragma omp parallel num_threads(4) private(j,k)
{	

#pragma omp for
	for (i = 0; i < aRows; i++) {

			for (j = 0; j < bColumns; j++) {
				
				for (k = 0; k < aColumns; k++) {
					
					sum += a[i][k] * b[k][j];
				}
				
				c[i][j] = sum;
				sum = 0;
			}
	}
}
	auto execution = double((clock() - t)) / CLOCKS_PER_SEC;	

	ofstream fout;
	fout.open("results.txt");

	cout << "Execution time : " << setprecision(30) << execution << endl;

	fout << "Allocation time: " << setprecision(30) << allocation << endl
		<< "Filling time:\t " << filling << endl
		<< "Execution time:\t " << execution << endl;

	cout << "Do you wan't to save results of multiplcation in file? Y/N: ";
	cin >> answer;
	if (answer[0] == 'Y' || answer[0] == 'y') {

		fout << "\nResults:\n";

		for (int i = 0; i < aRows; i++) {
			for (int j = 0; j < bColumns; j++)
				fout << c[i][j] << "\t";
			fout << endl;
		}
	}

	srand(time(NULL));
	t = clock();
	
	for (int i = 0; i<maxRowCount; i++) {

		if( i < aRows ) delete[] a[i];
		if( i < bRows ) delete[] b[i];
		if( i < aRows ) delete[] c[i];
	}

	delete[] a;
	delete[] b;
	delete[] c;

	cin.get(); cin.get();
	fout.close();

	return 0;
}