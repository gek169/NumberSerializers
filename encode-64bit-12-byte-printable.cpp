#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>

//Idea: We extract sets of 6 bits.
//Turn them into ascii printable chars
//Allows Facebook to serialize 64 bit numbers into gcc strings.
std::string serialize_num(uint64_t num){
	char target[12] = {0};
	for(int i = 0; i < 11; i++)
		{target[i] = (num & 63) + '0';num >>= 6;}
	return std::string(target);
}

uint64_t deserialize_num(std::string str){
	uint64_t num = 0;
	for(int i = 0; i < 11; i++)
		{num |= (uint64_t)(str[i]-'0')<<((i)*6);}
	return num;
}

int main(int argc, char** argv){
	std::string mystr;
	srand(time(NULL));
	uint64_t n = 171410984908091417 * (uint64_t)rand() + (uint64_t)rand() + (uint64_t)rand() + (uint64_t)rand();
	if(argc > 1){
		mystr = std::string(argv[1]);
		n = strtoull(mystr.c_str(),0,10);
	}
	mystr = serialize_num(n);
	uint64_t n_2 = deserialize_num(mystr);
	std::cout << "String representation is: \n" << mystr << "\nBut after conversion back... it's \n" << n_2 << 
	"\nIt should be: " << n << std::endl;
}
