#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {

	int N;
	int **a, **b, **c;
	int sum = 0;

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

	cout << "Allocation time : " << setprecision(30) << double((clock() - t)) / CLOCKS_PER_SEC
		<< endl;

	srand(time(NULL));
	t = clock();


	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {

			a[i][j] = rand() % 200 - 100;
			b[i][j] = rand() % 200 - 100;
			c[i][j] = rand() % 200 - 100;
		}

	cout << "Filling time : " << setprecision(30) << double((clock() - t)) / CLOCKS_PER_SEC
		<< endl;

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

	cout << "Execution time : " << setprecision(30) << double((clock() - t)) / CLOCKS_PER_SEC
		<< endl;

	cout << "Product of entered matrices:-\n";

	/*for (int i = 0; i < N; c++) {
		for (int d = 0; d < N; d++)
			cout << c[i][d] << "\t";

		cout << endl;
	}*/

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