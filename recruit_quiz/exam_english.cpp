#include "exam_english.h"
#include "utility.h"
#include <random>
using namespace std;

QuestionList CreateEnglishWordExam()
{
	const struct {
		const char* word;
		const char* reading;
		const char* meaning;
	}data[] = {
		{"state", "ステート", "状態"},
		{"business", "ビジネス", "事務、仕事"},
		{"abstract", "アブストラクト", "抽象的"},
		{"concrete", "コンクリート", "具体的"},
		{"digital", "デジタル", "数字で情報を伝える"},
		{"analogue", "アナログ", "類似している、類似物"},
		{"exchange", "エクスチェンジ", "交換、両替、為替"},
		{"infrastructure", "インフラストラクチャ", "下部構造、基盤となる施設や設備"},
		{"knowledge", "ナレッジ", "知識"},
		{"credit", "クレジット", "信用"},
	};
	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	const int type = uniform_int_distribution<>(0, 3)(rd);
	switch (type)
	{
	case 0:
	for (int i = 0; i < quizCount; i++)
	{
		const auto& e = data[indices[i]];
		questions.push_back({"「" + string(e.meaning) + "」を意味する英単語を答えよ", e.word});
	}
	break;
	case 1:
		for (int i = 0; i < quizCount; i++)
		{
			const auto& e = data[indices[i]];
			questions.push_back({ "カタカナの読み「" + string(e.reading) + "」に対応する英単語を答えよ", e.word });
		}
		break;

	case 2:
		for (int i = 0; i < quizCount; i++)
		{
			const auto& e = data[indices[i]];
			questions.push_back({string(e.word) + "の読みをカタカナで答えよ", e.reading });
		}
		break;

	case 3:
		for (int i = 0; i < quizCount; i++)
		{
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			string s = "「" + string(data[correctIndex].word) + "」を意味として正しい番号を選べ\n";
			s += string(" 1:") + data[answers[0]].meaning + "\n";
			s += string(" 2:") + data[answers[1]].meaning + "\n";
			s += string(" 3:") + data[answers[2]].meaning + "\n";

			questions.push_back({ s, to_string(correctNo) });
		}
		break;
	}



	return questions;
}

QuestionList CreateEnglishPhraseExam()
{
	const struct {
		const char* phrase;
		const char* meaning;
		const char* example;
		const char* translation;
		int blankCount;
		int blankOptions[3];
	}data[] = {
		{"too [A] to [B]", "とても[A]なので[B]できない","The tea was too hot to drink.","そのお茶はとても熱かったので飲めなかった。", 2, {3,5}},

		{"be looking forward to [a]", "[A]を楽しみにする", "I'm looking forward to seeing you", "あなたに会うのを楽しみにしています。", 3, {1, 2, 3}},
		{"according to [A]", "[A]によると", "According to the weather forcast, today is rain", "天気予報によると、今日は雨だ。", 2, {0,1}},
		{"as soon as [A]", "[A]するとすぐに", "As soon as I arrive, I will call you", "到着したらすぐに電話します。", 3,{0,1,2}},
		{"be not supposed to [A]", "[A]してはいけないことになっている", "You are not supposed to enter this room","この部屋に入ってはいけません。", 3,{2,3,4}},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	int type = uniform_int_distribution<>(0, 2)(rd);
	switch (type)
	{
	case 0:
		for (int i = 0; i < quizCount; i++)
		{
			const auto& e = data[indices[i]];
			vector<string>words;
			const char* start = e.example;
			for (const char* p = e.example; *p; p++)
			{
				if (*p == ' ')
				{
					words.push_back(string(start, p));
					start = p + 1;
				}
			}
			words.push_back(string(start));

			//穴にする単語の位置
			int n = uniform_int_distribution<>(0, e.blankCount - 1)(rd);
			int blankIndex = e.blankOptions[n];

			//穴にする位置の単語を答えにする
			string a = words[blankIndex];

			//穴にする位置の単語を空欄にする
			words[blankIndex] = "[ ? ]";

			//単語を文に復元
			string s = words[0];
			for (int j = 1; j < words.size(); j++)
			{
				s += " " + words[j];
			}

			//問題文と答えを追加
			questions.push_back({"[ ? ]に適切な語を入れて英文を完成させよ\n" + string(e.translation) + "\n" + s,a});
		}
		break;
	case 1:
		for (int i = 0; i < quizCount; i++)
		{
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			string s = "「" + string(data[correctIndex].phrase) + "」を意味として正しい番号を選べ\n";
			s += string(" 1:") + data[answers[0]].meaning + "\n";
			s += string(" 2:") + data[answers[1]].meaning + "\n";
			s += string(" 3:") + data[answers[2]].meaning + "\n";

			questions.push_back({ s, to_string(correctNo) });
		}
		break;
	case 2:
		for (int i = 0; i < quizCount; i++)
		{
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			string s = "「" + string(data[correctIndex].meaning) + "」に対応する定型文を選べ\n";
			s += string(" 1:") + data[answers[0]].phrase + "\n";
			s += string(" 2:") + data[answers[1]].phrase + "\n";
			s += string(" 3:") + data[answers[2]].phrase + "\n";

			questions.push_back({ s, to_string(correctNo) });
		}

		break;
	}

	return questions;
}