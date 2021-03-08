#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstdarg>
//IDEA
//use base 95 to encode and decode our numbers.
//

#define DIVCONST 93

unsigned char encode_char(uint64_t& n){
	unsigned char enc = n%DIVCONST;
	n/=DIVCONST;
	enc+= '!';
	if(enc >= '"') enc++;
	return enc;
}
uint64_t decode_char(unsigned char c, unsigned int i){
	uint64_t result;
	if(c >= '"') c--;
	c -= '!';
	result = c;
	//We now have to reproduce its placement.
	for(unsigned int j = 0; j < i; j++) result *= DIVCONST;
	return result;
}
std::string serialize_num(uint64_t num){
	char target[11] = {0};
	for(int i = 0; i < 10; i++)
		{target[i] = encode_char(num);}
	return std::string(target);
}

uint64_t deserialize_num(std::string str){
	uint64_t num = 0;
	for(int i = 0; i < 10; i++)
		{num += decode_char(str[i], i);}
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
