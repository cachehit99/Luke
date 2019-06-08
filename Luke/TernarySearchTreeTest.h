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

	vector<string> keys = tst.Keys();
	int i = 0;
	for (i = 0; i < keys.size() - 1; ++i)
	{
		cout << keys[i] << " -> ";
	}
	cout << keys[i] << endl << endl;

	tst.Remove("shore");
	tst.Remove("the");
	tst.Remove("sells");
	tst.Remove("shells");
	tst.Remove("she");
	tst.Remove("by");
	tst.Remove("sea");

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
	cout << "The number of words: " << words.size() << endl << endl;

	// Insert
	cout << "Insertion Time" << endl;
	auto s = steady_clock::now();
	TernarySearchTree<int> tst2;
	for (int i = 0; i < words.size(); ++i)
	{
		tst2.Put(words[i], i);
	}
	auto e = steady_clock::now();
	auto d = duration_cast<milliseconds>(e - s);
	cout << "TST: " << d.count() << endl;

	s = steady_clock::now();
	map<string, int> m;
	for (int i = 0; i < words.size(); ++i)
	{
		m[words[i]] = i;
	}
	e = steady_clock::now();
	d = duration_cast<milliseconds>(e - s);
	cout << "MAP: " << d.count() << endl << endl;

	// Get
	cout << "Retrieval Time" << endl;
	s = steady_clock::now();
	for (size_t i = words.size(); i > 0; --i)
	{
		auto a = tst2.Get(words[i - 1]);
	}
	e = steady_clock::now();
	d = duration_cast<milliseconds>(e - s);
	cout << "TST: " << d.count() << endl;

	s = steady_clock::now();
	for (size_t i = words.size(); i > 0; --i)
	{
		int a = m[words[i - 1]];
	}
	e = steady_clock::now();
	d = duration_cast<milliseconds>(e - s);
	cout << "MAP: " << d.count() << endl << endl;

	// Travese
	cout << "Traversal Time" << endl;
	s = steady_clock::now();
	int idx = 0;
	for (auto& key : tst2.Keys())
	{
		idx++;
	}
	e = steady_clock::now();
	d = duration_cast<milliseconds>(e - s);
	cout << "TST: " << d.count() << endl;

	s = steady_clock::now();
	for (auto it = m.begin(); it != m.end(); ++it)
	{
		idx--;
	}
	e = steady_clock::now();
	d = duration_cast<milliseconds>(e - s);
	cout << "MAP: " << d.count() << endl << endl;

	// Remove
	cout << "Removal Time" << endl;
	s = steady_clock::now();
	for (int i = 0; i < words.size(); ++i)
	{
		tst2.Remove(words[i]);
	}
	e = steady_clock::now();
	d = duration_cast<milliseconds>(e - s);
	cout << "TST: " << d.count() << endl;

	s = steady_clock::now();
	for (int i = 0; i < words.size(); ++i)
	{
		m.erase(words[i]);
	}
	e = steady_clock::now();
	d = duration_cast<milliseconds>(e - s);
	cout << "MAP: " << d.count() << endl << endl;


}