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

//慣用句作成
QuestionList CreateIdiomExam()
{
	static const struct
	{
		const char* idiom;
		const char* meaning;
	}data[] = {
		{"気のおけない","気づかいがいらない"},
		{"琴線に触れる","心から感動する"},
		{"汚名をそそぐ","名誉を挽回する"},
		{"言質を取る","証拠となる言葉を聞き出す"},
		{"糠に釘","効き目がない"},
	};

	constexpr int quizCount = 5;
	QuestionList question;
	question.reserve(quizCount);   //容量確保　　容量が不明な場合push_backするごとにメモリを確保しに行くことになるので、
	//ある程度入れる目安が決まっている場合、する方がよい  = 生配列とほぼ一緒
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++)
	{
		//間違った番号をランダムに選ぶ
		const int correctIndex = indices[i];
		vector<int> answers = CreateWrongIndices(size(data), correctIndex);

		//ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 3)(rd);
		answers[correctNo - 1] = correctIndex;

		//問題作成
		string s = "「" + string(data[correctIndex].idiom) + "」を意味として正しい番号を選べ";
		for (int j = 0; j < 3; j++)
		{
			s += "\n " + to_string(j + 1) + ":" + data[answers[j]].meaning;
		}

		question.push_back({ s,to_string(correctNo) });
	}

	return question;
}


QuestionList CreateHomophoneExam()
{
	const struct {
		const char* reading;
		struct {
			const char* kanji;
			const char* meaning;
		}words[3];
	}data[] = {
		{"じき",{
		{"時期","何かを行うとき、期間"},
		{"時機","物事を行うのによい機会"}}},
		{"そうぞう",{
		{"想像","実際には経験していない事柄を思い描くこと"},
		{"創造","新しいものを作り上げること"}}},
		{"ほしょう",{
		{"保証","間違いがなく確かであると約束すること"},
		{"保障","権利や地位などが維持されるように保護し守ること"},
		{"補償","損失をおぎなって償うこと"}}},
		{"たいしょう",{
		{"対象","行為の目標となるもの"},
		{"対称","2つの図形や物事が互いに釣り合っていること"},
		{"対照","見比べること、違いが際立つこと"}}},
		{"あやまる",{
		{"謝る","失敗について許しを求める"},
		{"誤る","間違った判断をする"}}},
		{"おさめる",{
		{"納める","金や物を渡すべきところに渡す"},
		{"治める","乱れている物事を落ち着いて穏やかな状態にする"},
		{"修める","行いや人格を正しくする、学問や技芸などを学んで身に着ける"}}},
	};


	constexpr int quizCount = 5;
	QuestionList question;
	question.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++)
	{
		const auto& e = data[indices[i]];

		//要素数を計算
		int count = 0;
		for (; count < size(e.words); count++)
		{
			if (!e.words[count].kanji) {
				break;
			}
		}


		//正しい番号を選択
		const int correctNo = uniform_int_distribution<>(1, count)(rd);

		//問題文を作成
		const vector<int> answers = CreateRandomIndices(count);
		string s = "「" + string(e.words[answers[correctNo - 1]].kanji) + "」の意味として正しい番号を選べ";
		for (int j = 0; j < count; j++)
		{
			s += "\n　" + to_string(j + 1) + ":" + e.words[answers[j]].meaning;
		}
		question.push_back({ s, to_string(correctNo) });
	}

	return question;
}

QuestionList CreateAntonyExam()
{
	const struct {
		const char* kanji[2];
	}data[] = {
		{"意図","恣意"},{"需要","供給" },
		{"故意","過失"},{"曖昧","明瞭" },
		{"緊張","弛緩"},{"過疎","過密" },
		{"栄転","左遷"},{"消費","生産" },
		{"異端","正統"},{"尊敬","軽蔑" },
	};

	constexpr int quizCount = 5;
	QuestionList question;
	question.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	for (int i = 0; i < quizCount; i++)
	{
		const int correctIndex = indices[i];
		vector<int> answers = CreateWrongIndices(size(data), correctIndex);

		//ランダムな位置を正しい番号で上書き
		const int correctNo = uniform_int_distribution<>(1, 3)(rd);
		answers[correctNo - 1] = correctIndex;

		//問題作成
		const int object = uniform_int_distribution<>(0, 1)(rd);
		const int other = (object + 1) % 2;
		string s = "「" + string(data[correctIndex].kanji[object]) + "」の対義語として正しい番号を選べ";
		for (int j = 0; j < 4; i++)
		{
			s += "\n　" + to_string(j + 1) + ":" + data[answers[j]].kanji[other];
		}
		question.push_back({ s,to_string(correctNo) });
	}
	return question;
}