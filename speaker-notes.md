# Speaker notes

**What happens when you XOR a word twice?**

Aim for about 5 minutes and 45 seconds, including time for one audience response. The italic lines are presentation cues.

## Slide 1. The mystery word (0:00–0:55)

*Ask the question and give the room five seconds.*

Hi, I’m Amogh. I’ve taken a four-letter word and changed each letter using the same key. These four pairs are all I’m going to show you for now. Each pair stands for one letter that went into the program. What can you tell me about the original word just by looking at those pairs?

The two 15s in the middle stand out. Maybe you already have a guess for the word. Hang on to it. By the end, we’ll be able to say exactly which part of that guess the numbers support. First I want to show you how the program changes a letter, because the line of C that does it also works in reverse.

## Slide 2. What XOR does to a bit (0:55–1:55)

*Point to the input and output of one example in each column.*

XOR is short for exclusive OR. In C, we write it with the caret symbol. It compares two bits at the same position. If the bits differ, the answer is one. If they match, the answer is zero.

Look at the left side. I’ve kept the key bit at zero. Start with a one and the result is one. Start with a zero and the result is zero. Now look at the right. Changing the key bit to one flips either input. Imagine starting with a one and using that same key bit twice. On the first pass the one becomes zero. On the second pass it goes back to one. The program does that comparison at eight positions to process a whole byte.

## Slide 3. Follow the letter O (1:55–3:10)

*Trace the rightmost bit, then its neighbor. Point to the matching first and last rows.*

Let’s take the letter O. Computers need a number for each letter, and ASCII gives uppercase O the value 4F in hexadecimal. Hex is just a shorter way to write the bits. Each digit represents four bits, so two digits are enough for the byte on this slide.

The key is 5A. Look at the rightmost bit of the letter and the key. The letter ends in one and the key ends in zero, so the one stays. Move one place to the left. Now both bits are one, so that position becomes zero. Following that rule across the row gives us hex 15. That’s one of the mystery numbers we started with.

What happens if I take 15 and apply 5A again? The key picks out exactly the same positions to flip. The bottom row matches the top row bit for bit. We have our O back.

## Slide 4. Run the C demo (3:10–4:30)

*Run ./xor_demo, or use the output on the slide. For a second example, run ./xor_demo ZOO.*

Here’s the whole word. It was BOOK. The line at the top takes one byte from the array, applies XOR with the key, and stores the result in that same spot. The loop repeats that for each byte. You can follow the two O’s in the output. Each one becomes 15, just like the letter we did by hand. When the program runs the same loop a second time, it prints BOOK again.

There’s a little C detail here that matters. Imagine the word starts with Z instead. Uppercase Z has the value 5A, exactly the same as our key. Every bit matches, so the encoded byte is zero. A C string function would take that zero as the end of the string. That’s why the demo remembers the original length and prints each encoded byte in hex. It can show that first zero and still recover the letters after it.

## Slide 5. What the ciphertext gives away (4:30–5:45)

*Point to the two middle bytes in each row. Leave time for questions.*

Let’s go back to the opening question. The two middle bytes match. Could two different letters have produced those two 15s? Think about what happens when we decode a 15. The key is fixed, so there’s only one answer it can give. That means the original letters in those positions have to match.

Here’s a different word, MEET. This time the middle letters turn into 1F. Even if I cover up the words, you can see where both of them have double letters. That clue alone won’t tell you whether the first word was BOOK or something else with a double letter. It still gives away information about the message. And because the key takes up only eight bits, there are only 256 possible keys.

So if you remember one thing, look at those two 15s. Applying the same key twice brings BOOK back. Reusing it across the word also leaves a clue that anyone can see. What questions do you have?
