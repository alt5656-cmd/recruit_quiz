#include"exam_japanese.h"
#include"utility.h"
#include<random>
using namespace std;

//漢字の読み取り問題
QuestionList CreateKanjiExam()
{
	static const struct {
		const char* kanji;
		const char* reading;
		const char* meaning;
	}
	data[] = {
		{"市井","しせい","人が多く集まって暮らすところ、町"},
		{"捺印","なついん","(署名と共に)印鑑を押すこと"},
		{"相殺","そうさい","足し引きの結果、差がなくなること"},
		{"凡例","はんれい","本や図表のはじめに、使い方や約束事を箇条書きにしたもの"},
		{"約定","やくじょう","約束して決めること、契約"},
	};

	constexpr int quizCount = 5;
	QuestionList question;
	question.reserve(quizCount);   //容量確保　　容量が不明な場合push_backするごとにメモリを確保しに行くことになるので、
	                                           //ある程度入れる目安が決まっている場合、する方がよい  = 生配列とほぼ一緒
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	int type = uniform_int_distribution<>(0, 1)(rd);
	if (type == 0)
	{//読み
		for (int i = 0; i < quizCount; i++)
		{
			const auto& e = data[indices[i]];
			question.push_back({ "「" + string(e.kanji) + "」の読みをひらがなで答えよ" , e.reading });
		}
	}
	else
	{
		//熟語
		for (int i = 0; i < quizCount; i++)
		{
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int> answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題作成
			string s = "「" + string(data[correctIndex].meaning) + "」を意味する熟語の番号を選べ";
			for (int j = 0; j < 3; j++)
			{
				s += "\n " + to_string(j + 1) + ":" + data[answers[j]].kanji;
			}

			question.push_back({ s,to_string(correctNo) });
		}
	}//if type

	return question;
}