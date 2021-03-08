#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>

//IDEA
//use hamming code type techniques to store an extra bit of information
//for each char.
//
inline unsigned char getnumbits(unsigned char c){
	return (
		((c&128) > 0) +
		((c&64) > 0) +
		((c&32) > 0) +
		((c&16) > 0) +
		((c&8) > 0) +
		((c&4) > 0) +
		((c&2) > 0) +
		((c&1) > 0)
	);
}
unsigned char encode_char(uint64_t& n){
	unsigned char bottom6 = n & 63; //6 bits
	unsigned char highbit = n & 64; //7th bit
	n>>=6;
	return bottom6 + '!';
}
uint64_t decode_char(unsigned char c){
	uint64_t result;
	c -= '!';
	unsigned char bottom6 = c & 63; //6 bits
	unsigned char highbit = getnumbits(bottom6)&1; //7th bit
	return c;
}
std::string serialize_num(uint64_t num){
	char target[12] = {0};
	for(int i = 0; i < 11; i++)
		{target[i] = encode_char(num);}
	return std::string(target);
}

uint64_t deserialize_num(std::string str){
	uint64_t num = 0;
	for(int i = 0; i < 11; i++)
		{num |= decode_char(str[i])<<((i)*6);}
	return num;
}

int main(int argc, char** argv){
	std::string mystr;
	srand(time(NULL));
	uint64_t n = 171410984908091417 * (uint64_t)rand() + (uint64_t)rand() + (uint64_t)rand() + (uint64_t)rand();
	if(argc > 1){
		mystr = std::string(argv[1]);
		n = strtoull(mystr.c_str(),0,10);
		if(argc > 2)
			n <<= strtoull(argv[2],0,10);
	}
	mystr = serialize_num(n);
	uint64_t n_2 = deserialize_num(mystr);
	std::cout << "String representation is: \n" << mystr << "\nBut after conversion back... it's \n" << n_2 << 
	"\nIt should be: " << n << std::endl;
}
