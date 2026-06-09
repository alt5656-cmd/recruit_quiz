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
			s += std::string(" 1:") + data[answers[0]].meaning + "\n";
			s += std::string(" 2:") + data[answers[1]].meaning + "\n";
			s += std::string(" 3:") + data[answers[2]].meaning + "\n";

			questions.push_back({ s, to_string(correctNo) });
		}
		break;
	}



	return questions;
}