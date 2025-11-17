# Huffman-Coding-Project
-Write tests in binary for decompression, tests with minheap vectors for deserialization/serialization. MAKE SURE EVERYTHING WORKS BEFORE MOVING ONTO THE NEXT THING!


# How to run/test
1. Download/Git clone the repository and enter the folder you just downloaded (should be called huffman-coding-project or something similar).

2. Then open the terminal in the folder. In the terminal type
```
Make
```
and then
```
./HuffmanCoder
```
The terminal output from the program will explain the rest. Just make sure you have a .txt file ready in the same folder as the executable.

# Notes on the project
-I wanted to learn how to use smart pointers, which I think I did successfully, but they were
definitely a challenge.

-Writing tests helps a lot. Test every little thing. I get anxious when building a large piece
of code without testing, because if something goes wrong you have to search a giant file to find
it, massive headache. Instead build small components, test each one, then build bigger components
with those.

-Working with bits was incredibly challenging. I think C++ was not designed to work with bits so
I had to use libraries like bitset which were confusing to use and involved a lot of type conversion.

-To work with bits I had to use casts which were also confusing but very interesting once learned.
Reinterpret cast is kind of like changing the file extension, the data stays the same but the way
the computer interprets it is different, which I find very cool.

-I forgot to make the Huffman tree and minheap use the chars as tiebreaker. This meant that if count
was equal sometimes it would choose different nodes, which caused my binary file to get decoded wrongly.
Thanks to the tests I quickly saw that the codes were different after remaking the tree, so I knew
something was causing some ambiguity there. I knew it was the chars causing ambiguity because I thought
about adding a tie breaker as chars but decided it was unnessecary. Turns out it was nessecary!
