#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <set>
struct NODE
{
	NODE* ptrs[26];
	bool eow = false;
	NODE()
	{
		for (int i = 0; i < 26; ++i)
			ptrs[i] = nullptr;
	}
};

using TrieTree = NODE*;
void init(TrieTree& root)
{
	root = nullptr;
}
bool empty(TrieTree root)
{
	return root == nullptr;
}

void add(TrieTree& t, const std::string word, size_t i)
{
	if (!t)
	{
		t = new NODE;
	}
	if ((word.length()) - 1 < i)
		t->eow = true;
	else
		add(t->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptr_empty(TrieTree t)
{
	bool res = true;
	size_t i = 0;
	while (i < 26 && res)
		if (!t->ptrs[i])
			++i;
		else
			res = false;
	return res;
}

void del(TrieTree& t, const std::string word, size_t i)
{
	if (t)
		if (i <= word.length() - 1)
			del(t->ptrs[word[i] - 'a'], word, i + 1);
		else
		{
			t->eow = false;
			if (all_ptr_empty(t))
			{
				delete t;
				t = nullptr;
			}
		}
}

void clear(TrieTree& t)
{
	for (size_t i = 0; i < 26; ++i)

		if (t->ptrs[i])
			clear(t->ptrs[i]);
	delete t;
	t = nullptr;
}

void printall(TrieTree t, std::string word)
{
	bool flag = false;
	for (size_t i = 0; i < 26; ++i)
		if (t->ptrs[i])
			flag = true;
	if (flag)
		std::cout << word << '\n';
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			printall(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

void print(TrieTree t, std::string word)
{
	if (t->eow)
	{
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			print(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

void print_words(TrieTree t, std::string word)
{
	if (all_ptr_empty(t))
		std::cout << word << '\n';
	else
	{
		for (size_t i = 0; i < 26; ++i)
			if (t->ptrs[i])
				print_words(t->ptrs[i], word + char(i + 'a'));
	}
}

void task(TrieTree& t, int vowels, std::string word = "")
{
	std::set<char> vowel = { 'a', 'A', 'e', 'E', 'u', 'U', 'o', 'O', 'i', 'I' };

	if (vowels != -2)
	{
		if (t->eow)
			std::cout << word << '\n';

		for (size_t i = 0; i < 26; ++i)
		{
			if (t->ptrs[i])
			{
				if (vowels == -1)
					task(t->ptrs[i], vowel.count(char(i + 'a')), word + char(i + 'a'));
				else
					task(t->ptrs[i], vowels == 1 && !vowel.count(char(i + 'a')) ? 0 : vowels == 0 && vowel.count(char(i + 'a')) ? 1 : -2, word + char(i + 'a'));
			}
		}
	}
}

int main()
{
	setlocale(0, "");
	std::ifstream file("input.txt");
	TrieTree root;
	int count = 0;
	bool x = 0;
	int vowels = -1;
	init(root);
	std::string word;
	while (std::getline(file, word))
	{
		if (word.length())
			add(root, word, 0);
	}
	print_words(root, "");
	std::cout << "----------------------------------------\n";
	
	task(root, vowels,word);
	
	file.close();
	clear(root);
	std::cin.get();
}
