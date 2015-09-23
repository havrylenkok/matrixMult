#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

int main() {

	int N;
	vector<vector <int>> a, b, c;

	cout << "Input N (max 13000)\nN = ";
	cin >> N;

	clock_t t;
	t = clock();

	try {

		vector<int> temp;
		for (long i = 0; i < N; i++) {

			a.push_back(temp);
			a[i].reserve(N);

			b.push_back(temp);
			b[i].reserve(N);

			c.push_back(temp);
			c[i].reserve(N);

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

			a[i].push_back(rand() % 200 - 100);
			b[i].push_back(rand() % 200 - 100);
			c[i].push_back(rand() % 200 - 100);
		}

	cout << "Filling time : " << setprecision(30) << double((clock() - t)) / CLOCKS_PER_SEC
		<< endl;

	cout << "Press <Enter> to clean memory\n";
	cin.get(); cin.get();

	for (int i = 0; i < N; i++) {

		a[i].clear();
		b[i].clear();
		c[i].clear();
	}

	a.clear();
	b.clear();
	c.clear();

	cout << "Cleaning memory done!\nGood bye =)\n";
	cin.get();

	return 0;
}