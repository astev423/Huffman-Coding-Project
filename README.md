# Huffman-Coding-Project

This project uses Huffman Coding to compress and decompress **ASCII text files**. This does not work
with UTF-8 text files or anything else, just ASCII text files. It works by getting each char in
an ASCII file (1 byte) and then uses the Huffman Coding algorithm to make binary codes for each char. 
A new file is made where each character is replaced by a binary code. Then, the decompressor reads the
binary codes and uses them to traverse the Huffman tree. 0 goes to the left child, 1 goes to the right.
Once a leaf node is reached then we have a char, so we append that to a new file and continue this 
until we translate all codes in their respective chars.

## How to run
1. Download/Git clone the repository and enter the folder you just downloaded (should be called huffman-coding-project or something similar).

2. Then open the terminal in the folder. In the terminal type
```
make
```
and then
```
./HuffmanCoder
```
The terminal output from the program will explain the rest. Just make sure you have a .txt file ready
in the same folder as the executable. You can use any .txt file you want so long as there are only
ASCII chars in it.

For example, if you have a text file named text.txt in the same directory as the executable,
then after running `./HuffmanCoder` type `1` and then `text.txt` which compresses the file.
Then simply type `./HuffmanCoder` again and type `2` to decompress the file. Your decompressed
file will be in a new text file called `decompressedTxtFile.txt`.

## How to run built in tests
1. Go into the tests directory then type
```
make
```

2. Then type
```
./TestEncodeDecode
``` 
and all 12 text files will be tested. You can see what they decompress to in `tests/textDecompressed`
and their respective text file number. Ex. txt1.txt's decompressed result will be under folder 1

## Notes on the project
-I wanted to learn how to use smart pointers, which I think I did successfully, but they were
definitely a challenge.

-Writing tests helps a lot. Test every little thing. I get anxious when building a large piece
of code without testing, because if something goes wrong you have to search a giant file to find
it, massive headache. Instead, build small components, test each one, then build bigger components
with those.

-Working with bits was incredibly challenging. I think C++ was not designed to work with bits, so
I had to use libraries like bitset which were confusing to use and involved a lot of type conversion.

-To work with bits I had to use casts which were also confusing but very interesting once learned.
Reinterpret cast is kind of like changing the file extension, the data stays the same but the way
the computer interprets it is different, which I find very cool.

-I forgot to make the Huffman tree and minheap use the chars as tiebreaker. This meant that if count
was equal sometimes it would choose different nodes, which caused my binary file to get decoded wrongly.
Thanks to the tests I quickly saw that the codes were different after remaking the tree, so I knew
something was causing some ambiguity there. I knew it was the chars causing ambiguity because I thought
about adding a tiebreaker as chars but decided it was unneeded. Turns out it was needed!

-There was a bad edge case involving the heap and spaces, it's happened because I used isstream which 
separates by space. So it skipped over my space char and caused the decoder to break in some cases.
Serializing and deserializing can be very tricky!

-There can be great space savings for large files without many unique chars, but when there are lots of
unique chars that are used equally, then the space savings greatly reduce. For tiny files with just
a few chars the compressed file might actually take up more space due to the fact that we have to
serialize the minheap.
