#pragma once
#include <string>
#include<vector>

struct Question
{
	std::string q;
	std::string a;
};

using QuestionList = std::vector<Question>;