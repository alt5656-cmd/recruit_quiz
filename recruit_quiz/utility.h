#pragma once
#include<vector>

//配列シャッフル
void Shuffle(std::vector<int>& indices);

std::vector<int>CreateRandomIndices(int n);

//間違った番号の配列を作成する
//n   作成する番号の範囲
//correctIndex   正解の番号
std::vector<int> CreateWrongIndices(int n, int correctIndex);