#pragma once
#include <iostream>
#include <iomanip>
#include "TernarySearchTree.h"


void TestTernarySearchTree()
{
	TernarySearchTree<int> tst;

	tst.Put("she", 0);
	tst.Put("sells", 1);
	tst.Put("shells", 3);
	tst.Put("by", 4);
	tst.Put("the", 5);
	tst.Put("sea", 6);
	tst.Put("shore", 7);

	vector<string> keywords = { "sea", "sells", "shoe" };
	for (auto& keyword : keywords)
	{
		auto v = tst.Get(keyword);
		cout << setw(10) << left << keyword << ": ";
		if (v.has_value())
		{
			cout << v.value() << endl;
		}
		else
		{
			cout << "unknown" << endl;
		}
	}


	ifstream in("words.txt");
	if (!in.is_open())
	{
		return;
	}

	vector<string> words;
	int value = 0;
	while (!in.eof())
	{
		string word;
		in >> word;
		words.push_back(word);
	}
	in.close();
	cout << "The number of words: " << words.size() << endl;

	const auto s1 = steady_clock::now();
	TernarySearchTree<int> tst2;
	for (int i = 0; i < words.size(); ++i)
	{
		tst.Put(words[i], i);
	}
	const auto e1 = steady_clock::now();
	const auto d1 = duration_cast<milliseconds>(e1 - s1);
	cout << d1.count() << endl;

	const auto s2 = steady_clock::now();
	map<string, int> m;
	for (int i = 0; i < words.size(); ++i)
	{
		m[words[i]] = i;
	}
	const auto e2 = steady_clock::now();
	const auto d2 = duration_cast<milliseconds>(e2 - s2);
	cout << d2.count() << endl;

	const auto s3 = steady_clock::now();
	for (size_t i = words.size(); i > 0; --i)
	{
		auto a = tst.Get(words[i - 1]);
	}
	const auto e3 = steady_clock::now();
	const auto d3 = duration_cast<milliseconds>(e3 - s3);
	cout << d3.count() << endl;

	const auto s4 = steady_clock::now();
	for (size_t i = words.size(); i > 0; --i)
	{
		int a = m[words[i - 1]];
	}
	const auto e4 = steady_clock::now();
	const auto d4 = duration_cast<milliseconds>(e4 - s4);
	cout << d4.count() << endl;
}