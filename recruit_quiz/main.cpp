#include <iostream>
#include <string>
#include<vector>
#include <random>

using namespace std;

struct Question
{
	string q;
	string a;
};

int main()
{
	vector<Question> questions(3);

	random_device rd;
	mt19937 rand(rd());

	int x = uniform_int_distribution<>(1, 30)(rand);
	int y = uniform_int_distribution<>(1, 30)(rand);
	questions[0].q = to_string(x) + "x" + to_string(y) + "の答えは?";
	questions[0].a = to_string(x * y);

	x = uniform_int_distribution<>(1, 30)(rand);
	y = uniform_int_distribution<>(1, 30)(rand);
	questions[1].q = to_string(x*y) + "÷" + to_string(y) + "の答えは?";
	questions[1].a = to_string(x);

	x = uniform_int_distribution<>(1, 100)(rand);
	y = uniform_int_distribution<>(1, 10)(rand);
	int z = uniform_int_distribution<>(1, 10)(rand);
	int w = uniform_int_distribution<>(1, 10)(rand);
	questions[2].q = to_string(x) + "-(" + to_string(y*w) + "+" + to_string(z*w) + ")÷" + to_string(w) + "の答えは?";
	questions[2].a = to_string(x - (y + z));

	x = uniform_int_distribution<>(1, 10)(rand);
	y = uniform_int_distribution<>(1, 5)(rand) * 2;
	questions.push_back({
		"面積" + to_string(x * y / 2) + "cm^2、底辺" + to_string(y) + "cmの三角形の高さを求めよ", to_string(x)
		});

	x = uniform_int_distribution<>(1, 10)(rand);
	y = uniform_int_distribution<>(1, 5)(rand)*3;
	questions.push_back({ "底面積の半径" + to_string(x) + "cm、高さ" + to_string(y) + "cmの円錐がある。\n" + "この円錐の体積をXπcm^3とする。Xの値を求めよ。" ,
		to_string(x * x * y / 3)});

	x = uniform_int_distribution<>(1, 5)(rand) * 3;
	questions.push_back({
		"半径" + to_string(x) + "cmの球がある。\n" + "この球の体積をXπcm^3とする。Xの値を求めよ。"
		,to_string(x * x * x * 4/3)
		});

	cout << "[リクルート試験対策クイズ]\n";

	for (const auto& e : questions) {
		cout << e.q << "\n";

		string answer;
		cin >> answer;
		if (answer == e.a)
		{
			cout << "正解!\n";
		}
		else
		{
			cout << "間違い!正解は" << e.a << "\n";
		}
	}
}