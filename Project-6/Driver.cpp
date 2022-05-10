#include "Hashes.h";

#ifdef _DEBUG
uint16_t calcTest(uint64_t);
#endif // _DEBUG



int main() 
{
	HashTable podcasts;

	cout << "Welcome to Podcast Haven(TM)!" << endl;
	for (int n = 0; n < 10; n++)
		podcasts.menu();
	podcasts.selectItem(3);
	return 0;
}

#ifdef _DEBUG
uint16_t calcTest(uint64_t input)
{
	uint16_t output = (input & 0x7000000) / 0x1000000;
	return output;
}
#endif // _DEBUG