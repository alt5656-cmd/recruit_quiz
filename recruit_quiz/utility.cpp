#include"utility.h"
#include<random>
using namespace std;

//ƒ‰ƒ“ƒ_ƒ€‚È”Ô†”z—ñ‚ğì¬‚·‚é

vector<int>CreateRandomIndices(int n)
{
	vector<int> indices(n);
	for (int i = 0; i < n; i++)
	{
		indices[i] = i;
	}

	random_device rd;
	mt19937 rand(rd());
	for (int i = n - 1; i > 0; i--)
	{
		const int j = uniform_int_distribution<>(0, i)(rand);
		const int tmp = indices[i];
		indices[i] = indices[j];
		indices[j] = tmp;
	}

	return indices;
}