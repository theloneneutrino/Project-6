#pragma once
#include "using.h"

typedef unsigned uint;

constexpr uint8_t SIZE = 8;

int readInteger(std::istream& input);
string stringifyFile(const char*);

class HashTable {
private:
	string buckets[SIZE];
	
	ifstream fileIn;
	ofstream fileOut;
	uint initVal;
	uint multiplier;
	uint8_t index : 3;
	bool full;

	void calcHash(string);
	void insert(string);
	void erase(string);

	void podcastDialog(std::function<void(string)>);

	void deserialize();
	void serialize();
	void print();
	bool isFull();
public:
	HashTable();
	HashTable(unsigned int, unsigned int);
	
	void menu();
	void selectItem(uint);
};