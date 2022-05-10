#include "Hashes.h"


int readInteger(std::istream& input)
{
	string tmp;
	int output;
	getline(input, tmp);
	stringstream myString(tmp);
	if (myString >> output)
		return output;
	else
		return INT_MAX;
}

string stringifyFile(const char* filename)
{
	ifstream fileIn;
	fileIn.open(filename);

	std::ostringstream sstr;
	sstr << fileIn.rdbuf();
	return sstr.str();

	fileIn.close();
}

// private member funcions

void HashTable::calcHash(std::string input)
{
	uint64_t output = initVal;
	for (char it : input) 
	{
		output += it;
		output *= multiplier;
	}
	index = output; // selects 3 bits from the integer
}


void HashTable::insert(string input)
{
	calcHash(input);
#if defined(_DEBUG)
	cout << static_cast<int>(index) << " ";
#endif
	if (buckets[index] == input); // do nothing
	else if (buckets[index] == string())
		buckets[index] = input;
	else
	{
		// linear search for next blank spot
		uint8_t loopEnd = index++;
		for (; index != loopEnd 
			&& buckets[index] != string(); index++);

		// if next blank spot found
		if (buckets[index] == string())
			buckets[index] = input; // put string in blank spot
		else
			cerr << "\nThe podcast list is already full.\n" << endl;
			full = true;
	}
#if defined(_DEBUG)
	cout << static_cast<int>(index) << endl;
#endif
}

void HashTable::erase(string input)
{
	calcHash(input); // if buckets at hash does equal input
	if (buckets[index] == input) 
	{
		buckets[index] = string(); // replace with empty string
		full = false; // the array has lost a value and is not full
	}
	else // if buckets at hash does not equal input
	{
		// loop end becomes current index
		// index iterates until it comes back to loopEnd,
		// buckets at index equals the input string, or buckets at
		// index is blank. 

		uint8_t loopEnd = index++;
		for (; index != loopEnd 
			&& buckets[index] != input; index++);
		
		// after the for loop
		// if buckets at index is equal to the input, buckets
		// at index gets reset and the array is not full

		if (buckets[index] == input)
		{
			buckets[index] = string(); // replace with empty string
			full = false;
		}
		else
			cout << "\nCannot find specified podcast.\n" << endl;
	}
}

void HashTable::podcastDialog(std::function<void(string)> func)
{
	string tmpString;
	cout << "Input the name of the podcast:" << endl;

	getline(cin, tmpString);
	func(tmpString);
}


void HashTable::deserialize()
{
	string tmpLine;
	fileIn.open("podcasts.txt");
	while (std::getline(fileIn, tmpLine))
		insert(tmpLine);

	fileIn.close();
}

void HashTable::serialize()
{
	fileOut.open("podcasts.txt", std::ofstream::out | std::ofstream::trunc);

	for (int n = 0; n < SIZE; n++)
	{
		if (buckets[n] != string())
			fileOut << buckets[n] << endl;
	}

	fileOut.close();
}

void HashTable::print()
{
	cout << endl << "Podcasts: " << endl;
	for (int n = 0; n < SIZE; n++) 
	{
		if (buckets[n] != string())
			cout << n << ", " << buckets[n] << endl;
	}
	cout << endl;
}

bool HashTable::isFull()
{
	return full;
}

// public member funcions

HashTable::HashTable() :
	initVal(0),
	multiplier(2),
	index(0),
	full(false)
{
	for (int n = 0; n < SIZE; n++) 
	{
		buckets[n] = string();
	}

	deserialize();
}

HashTable::HashTable(unsigned int init, unsigned int mult) :
	initVal(init),
	multiplier(mult),
	index(0),
	full(false)
{
	for (int n = 0; n < SIZE; n++)
	{
		buckets[n] = string();
	}

	deserialize();
}

void HashTable::menu()
{
	int selection;
	cout << stringifyFile("menuItems.txt") << endl;
	selection = readInteger(cin);
	selectItem(selection);
}

void HashTable::selectItem(uint selection)
{
	std::function<void(string)> f;
	switch (selection) 
	{
	case 1:
		f = [=](string a) 
		{
			this->insert(a);
		};
		podcastDialog(f);
		break;
	case 2:
		f = [=](string a)
		{
			this->erase(a);
		};
		podcastDialog(f);
		break;
	case 3:
		print();
		break;
	case 4:
		serialize();
		break;
	case 5:
		exit(EXIT_SUCCESS);
	default:
		cout << "\nThat is not a valid option.\n" << endl;
		menu();
		break;
	}
}