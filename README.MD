# Dear Facebook: How to efficiently serialize a 64 bit number

it takes slightly less than 10 characters, however you can't simply get rid of the tenth character.

Base95 is the most efficient however I suspect you don't want space or `"` in your serialized numbers.

This should allow you to efficiently use GCC strings which can only store 10 characters.

~Gek
