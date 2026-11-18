# What happens when you XOR a word twice?

A COMP 211 experiment in C. The program applies the same one-byte key to every byte of a word, prints the result in hexadecimal, then runs the same function again to recover the word.

[PowerPoint presentation](xor-slides.pptx) · [Speaker notes](speaker-notes.md) · [C source](xor_demo.c)

## Run the demo

From the project directory, use a C11 compiler such as Clang or GCC.

```sh
cc -std=c11 -Wall -Wextra -Wpedantic xor_demo.c -o xor_demo
./xor_demo
```

The default input is `BOOK`.

```text
Plaintext:  BOOK
Key:        5A
Ciphertext: 18 15 15 11
Recovered:  BOOK
```

## Follow one letter

In C, `^` means bitwise exclusive OR. A key bit of zero leaves the corresponding input bit alone. A key bit of one flips it. In the table, each group of four binary digits corresponds to one hexadecimal digit.

| Operation | Input byte | Key byte | Output byte |
| --- | --- | --- | --- |
| Encode the ASCII letter O | 0100 1111 (4F) | 0101 1010 (5A) | 0001 0101 (15) |
| Decode the result | 0001 0101 (15) | 0101 1010 (5A) | 0100 1111 (4F) |

The second pass flips exactly the same bits back. This works for every byte. In C, the loop only needs one operation, `bytes[i] ^= key;`, for both passes.

## What can someone see without the key?

In `18 15 15 11`, the two middle bytes match. With a fixed key, equal input bytes always give equal output bytes. Different inputs must give different outputs because applying the key a second time recovers each original byte. Someone who knows this scheme can therefore tell that the middle letters match, even without knowing which letter they are. A one-byte key also has just 256 possible values. These properties make this scheme unsuitable for protecting private messages.

## Try two predictions

```sh
./xor_demo MEET
./xor_demo "ZOO"
```

- Which positions will match for `MEET`? The middle letters again match, but E gives a different byte than O. The result is `17 1F 1F 0E`.
- What happens when the input byte equals the key? Z is `5A` in ASCII, so the output starts with `00`. The result is `00 15 15`. A C string function would treat that first zero as the end of the string. The program keeps the original byte count so it can recover all of `ZOO`.

## References

- [GNU C Reference Manual, bitwise logical operators](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Bitwise-Logical-Operators)
- [RFC 20, ASCII character table](https://www.rfc-editor.org/rfc/rfc20.html)
