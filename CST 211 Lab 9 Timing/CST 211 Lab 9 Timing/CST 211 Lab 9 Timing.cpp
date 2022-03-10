// CST 211 Lab 9 Timing Experiments.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;

#include "Array.h"
#include "BSTree.h"
#include "BST_Node.h"
#include "Exception.h"
#include "HashFunctions.h"
#include "HashTable.h"
#include "List.h"
#include "Node.h"

template <class C>
void arrInsertion(C& container);
template <class C>
void listInsertion(C& container);
template <class C>
void treeInsertion(C& container);
template <class C>
void tableInsertion(C& container);

template <class C>
void arrSearch(C& container);
template <class C>
void listSearch(C& container);
template <class C>
void treeSearch(C& container);
template <class C>
void tableSearch(C& container);


int main()
{
	Array<string> arr(300000);					// I know that this code is cold spaghetti, it works though :)
	List<string> list;
	BSTree<string> tree;
	HashTable<string, int> table(300000);
	table.setHash(Hashes::ASCIIHash);

	// Array
	cout << "## Array ##" << endl;
	arrInsertion(arr);
	arrSearch(arr);

	// List
	cout << "\n## List ##" << endl;
	listInsertion(list);
	listSearch(list);

	// BSTree
	cout << "\n## BSTree ##" << endl;
	treeInsertion(tree);
	treeSearch(tree);

	// HashTable
	cout << "\n## Hash Table ##" << endl;
	tableInsertion(table);
	tableSearch(table);
}

template <class C>
void arrInsertion(C& container) // yes, excellent design, definitelly OCP compliant probably inflats times
{
	std::ifstream myfile("Mein Kampf.txt");
	if (myfile.is_open())
	{
		double avgTime = 0;
		auto totalStart = high_resolution_clock::now();
		long i = 0;
		while (myfile)
		{
			auto insertStart = high_resolution_clock::now();
			string word = "";
			myfile >> word;
			container[i] = word;
			i++;
			auto insertEnd = high_resolution_clock::now();
			auto time = duration_cast<nanoseconds>(insertEnd - insertStart).count();
			avgTime = (avgTime + time) / i;
		}
		auto totalEnd = high_resolution_clock::now();
		auto totalTime = duration_cast<milliseconds>(totalEnd - totalStart).count();
		cout << "Total Insertion Time: " << totalTime << " ms" << endl;
		cout << "Average Insertion Time: " << avgTime << " ns" << endl;
	}
	myfile.close();
}

template<class C>
void listInsertion(C& container)
{
	std::ifstream myfile("Mein Kampf.txt");
	if (myfile.is_open())
	{
		double avgTime = 0;
		auto totalStart = high_resolution_clock::now();
		long i = 0;
		while (myfile)
		{
			auto insertStart = high_resolution_clock::now();
			string word = "";
			myfile >> word;
			container.Append(word);
			i++;
			auto insertEnd = high_resolution_clock::now();
			auto time = duration_cast<nanoseconds>(insertEnd - insertStart).count();
			avgTime = (avgTime + time) / i;
		}
		auto totalEnd = high_resolution_clock::now();
		auto totalTime = duration_cast<milliseconds>(totalEnd - totalStart).count();
		cout << "Total Insertion Time: " << totalTime << " ms" << endl;
		cout << "Average Insertion Time: " << avgTime << " ns" << endl;
	}
	myfile.close();
}

template<class C>
void treeInsertion(C& container)
{
	std::ifstream myfile("Mein Kampf.txt");
	if (myfile.is_open())
	{
		double avgTime = 0;
		auto totalStart = high_resolution_clock::now();
		long i = 0;
		while (myfile)
		{
			auto insertStart = high_resolution_clock::now();
			string word = "";
			myfile >> word;
			container.insert(word);
			i++;
			auto insertEnd = high_resolution_clock::now();
			auto time = duration_cast<nanoseconds>(insertEnd - insertStart).count();
			avgTime = (avgTime + time) / i;
		}
		auto totalEnd = high_resolution_clock::now();
		auto totalTime = duration_cast<milliseconds>(totalEnd - totalStart).count();
		cout << "Total Insertion Time: " << totalTime << " ms" << endl;
		cout << "Average Insertion Time: " << avgTime << " ns" << endl;
	}
	myfile.close();
}

template<class C>
void tableInsertion(C& container)
{
	std::ifstream myfile("Mein Kampf.txt");
	if (myfile.is_open())
	{
		double avgTime = 0;
		auto totalStart = high_resolution_clock::now();
		long i = 0;
		while (myfile)
		{
			auto insertStart = high_resolution_clock::now();
			string word = "";
			myfile >> word;
			container.Insert(word, 0);
			i++;
			auto insertEnd = high_resolution_clock::now();
			auto time = duration_cast<nanoseconds>(insertEnd - insertStart).count();
			avgTime = (avgTime + time) / i;
		}
		auto totalEnd = high_resolution_clock::now();
		auto totalTime = duration_cast<milliseconds>(totalEnd - totalStart).count();
		cout << "Total Insertion Time: " << totalTime << " ms" << endl;
		cout << "Average Insertion Time: " << avgTime << " ns" << endl;
	}
	myfile.close();
}

template <class C>
void arrSearch(C& container)
{
	string words[12] = {"envisaged",
						"expedient",
						"recommences",
						"Pan-German",
						"Christian-Socialist",
						"Consciousness",
						"Starnberg",
						"Socialist",
						"Versailles",
						"unsympathic",
						"parliamentary",
						"unwillingly" };
	double avgTime = 0;
	auto totalStart = high_resolution_clock::now();
	long i = 1;
	
	for (auto word : words)
	{
		for (int j = 0; j < 299999; j++)
		{
			auto searchStart = high_resolution_clock::now();
			if (container[j] == word)
			{
				auto searchEnd = high_resolution_clock::now();
				auto time = duration_cast<nanoseconds>(searchEnd - searchStart).count();
				avgTime = (avgTime + time) / i;
				i++;
				break;
			}
		}
	}
	auto totalEnd = high_resolution_clock::now();
	auto totalTime = duration_cast<milliseconds>(totalEnd - totalStart).count();
	cout << "Total Search Time: " << totalTime << " ms" << endl;
	cout << "Average Search Time: " << avgTime << " ns" << endl;
}

template<class C>
void listSearch(C& container)
{
	string words[12] = { "envisaged",
						"expedient",
						"recommences",
						"Pan-German",
						"systematic",
						"Consciousness",
						"Starnberg",
						"Socialist",
						"Versailles",
						"unsympathic",
						"parliamentary",
						"unwillingly" };
	double avgTime = 0;
	auto totalStart = high_resolution_clock::now();
	long i = 1;

	for (auto word : words)
	{
		auto searchStart = high_resolution_clock::now();
		if (container.findNode(word))
		{
			auto searchEnd = high_resolution_clock::now();
			auto time = duration_cast<nanoseconds>(searchEnd - searchStart).count();
			avgTime = (avgTime + time) / i;
			i++;
		}
	}

	auto totalEnd = high_resolution_clock::now();
	auto totalTime = duration_cast<milliseconds>(totalEnd - totalStart).count();
	cout << "Total Search Time: " << totalTime << " ms" << endl;
	cout << "Average Search Time: " << avgTime << " ns" << endl;
}

template<class C>
void treeSearch(C& container)
{
	string words[12] = { "envisaged",
					"expedient",
					"recommences",
					"Pan-German",
					"systematic",
					"Consciousness",
					"Starnberg",
					"Socialist",
					"Versailles",
					"unsympathic",
					"parliamentary",
					"unwillingly" };
	double avgTime = 0;
	auto totalStart = high_resolution_clock::now();
	long i = 1;

	for (auto word : words)
	{
		auto searchStart = high_resolution_clock::now();
		container.delete_(word);
		auto searchEnd = high_resolution_clock::now();
		auto time = duration_cast<nanoseconds>(searchEnd - searchStart).count();
		avgTime = (avgTime + time) / i;
		i++;
	}

	auto totalEnd = high_resolution_clock::now();
	auto totalTime = duration_cast<nanoseconds>(totalEnd - totalStart).count();
	cout << "Total Search Time: " << totalTime << " ns" << endl;
	cout << "Average Search Time: " << avgTime << " ns" << endl;
}

template<class C>
void tableSearch(C& container)
{
	string words[12] = { "envisaged",
				"expedient",
				"recommences",
				"Pan-German",
				"systematic",
				"Consciousness",
				"Starnberg",
				"Socialist",
				"Versailles",
				"unsympathic",
				"parliamentary",
				"unwillingly" };
	double avgTime = 0;
	auto totalStart = high_resolution_clock::now();
	long i = 1;

	for (auto word : words)
	{
		auto searchStart = high_resolution_clock::now();
		container.Delete(word);
		auto searchEnd = high_resolution_clock::now();
		auto time = duration_cast<nanoseconds>(searchEnd - searchStart).count();
		avgTime = (avgTime + time) / i;
		i++;
	}

	auto totalEnd = high_resolution_clock::now();
	auto totalTime = duration_cast<nanoseconds>(totalEnd - totalStart).count();
	cout << "Total Search Time: " << totalTime << " ns" << endl;
	cout << "Average Search Time: " << avgTime << " ns" << endl;
}

