#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

int main() {

	int N;
	int **a, **b, **c;
	int sum = 0;
	string answer = "";

	cout << "Input N (max 13000)\nN = ";
	cin >> N;

	clock_t t;
	t = clock();

	try {

		a = new int*[N];
		b = new int*[N];
		c = new int*[N];

		for (int i = 0; i < N; i++) {

			a[i] = new int[N];
			b[i] = new int[N];
			c[i] = new int[N];
		}
	}
	catch (bad_alloc) {

		cout << "Bad alloc\n";
		cin.get();
		return 1;

	}

	auto allocation = double((clock() - t)) / CLOCKS_PER_SEC;

	cout << "Allocation time : " << setprecision(30) << allocation
		<< endl;

	srand(time(NULL));
	t = clock();


	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {

			a[i][j] = rand() % 200 - 100;
			b[i][j] = rand() % 200 - 100;
		}

	auto filling = double((clock() - t)) / CLOCKS_PER_SEC;

	cout << "Filling time : " << setprecision(30) << filling
		<< endl;

	cout << "Work in progress...\n";

	srand(time(NULL));
	t = clock();

	for (int i = 0; i < N; i++) {
		for (int d = 0; d < N; d++) {
			for (int k = 0; k < N; k++) {
				sum = sum + a[i][k] * b[k][d];
			}

			c[i][d] = sum;
			sum = 0;
		}
	}

	auto execution = double((clock() - t)) / CLOCKS_PER_SEC;

	cout << "Execution time : " << setprecision(30) << execution
		<< endl;

	cout << "Do you wan't to save results of multiplcation in file? Y/N: ";
	cin >> answer;
	if (answer[0] == 'Y' || answer[0] == 'y') {

		ofstream fout;
		fout.open("results.txt");

		fout << "Allocation time: " << setprecision(30) << allocation << endl
			<< "Filling time:\t " << filling << endl
			<< "Execution time:\t " << execution << endl;
		fout << "Results:\n";

		for (int i = 0; i < N; i++) {
			for (int d = 0; d < N; d++)
				fout << c[i][d] << "\t";
			fout << endl;
		}
	}

	srand(time(NULL));
	t = clock();

	cout << "Press <Enter> to clean memory\n";
	cin.get(); cin.get();

	for (int i = 0; i<N; i++) {

		delete[] a[i];
		delete[] b[i];
		delete[] c[i];
	}

	delete[] a;
	delete[] b;
	delete[] c;

	cout << "Memory is cleaned.\nBye!\n";
	cin.get();

	return 0;
}