# Speaker notes

**What happens when you XOR a word twice?**

Target about 6 minutes and 15 seconds, including two short pauses. The italic lines are cues. Use the output on slides 4 and 5 if you prefer to stay in PowerPoint.

## Slide 1. The mystery word (0:00–0:50)

*Ask the question and give the room five seconds.*

Hi, I’m Amogh. I’ve taken a four-letter word and changed each letter using the same key. These four pairs are all I’m going to show you for now. Each pair stands for one letter that went into the program. What can you tell me about the original word just by looking at those pairs?

The two 15s in the middle stand out. Maybe you already have a guess for the word. Hang on to it. By the end, we’ll be able to say exactly which part of that guess the numbers support. First I want to show you how the program changes a letter, because the line of C that does it also works in reverse.

## Slide 2. What XOR does to a bit (0:50–1:50)

*Point to the input and output of one example in each column.*

XOR is short for exclusive OR. In C, we write it with the caret symbol. It compares two bits at the same position. If the bits differ, the answer is one. If they match, the answer is zero.

Look at the left side. I’ve kept the key bit at zero. Start with a one and the result is one. Start with a zero and the result is zero. Now look at the right. Changing the key bit to one flips either input. Imagine starting with a one and using that same key bit twice. On the first pass the one becomes zero. On the second pass it goes back to one. The program does that comparison at eight positions to process a whole byte.

## Slide 3. Follow the letter O (1:50–3:00)

*Trace the rightmost bit, then its neighbor. Point to the matching first and last rows.*

Let’s take the letter O. Computers need a number for each letter, and ASCII gives uppercase O the value 4F in hexadecimal. Hex is just a shorter way to write the bits. Each digit represents four bits, so two digits are enough for the byte on this slide.

The key is 5A. Look at the rightmost bit of the letter and the key. The letter ends in one and the key ends in zero, so the one stays. Move one place to the left. Now both bits are one, so that position becomes zero. Following that rule across the row gives us hex 15. That’s one of the mystery numbers we started with.

What happens if I take 15 and apply 5A again? The key picks out exactly the same positions to flip. The bottom row matches the top row bit for bit. We have our O back.

## Slide 4. Run the C demo (3:00–3:45)

*Run ./xor_demo, or point to the output.*

The mystery word was BOOK. Each time through the loop, i points to the next byte. The caret-equals line takes that byte, applies the key, and writes the result right back into the array. So when the loop reaches either O, it's doing the calculation we just did by hand.

The program prints those bytes in hex because some of them would be hard to see as characters. Then it calls the same function on that same array. The last line shows what the bytes spell after that second pass. Now let's try an input that makes one of those bytes disappear if we print it the wrong way.

## Slide 5. What happens to ZOO? (3:45–4:40)

*Trace the Z from 5A to 00. The output is on the slide if you skip the live demo.*

The first letter in ZOO has a special property. Uppercase Z has the value 5A, which happens to be our key. Imagine comparing each bit of a number with itself. Every pair matches, so XOR produces eight zeros. Both O's still give 15, so the encrypted message takes up three bytes just like before.

Here is where this matters in C. A string ends at the first zero byte. If I use strlen on this encoded array, it stops at the very first position and tells me the length is zero. But we can see three bytes on the slide. The program saves the length before it changes anything. That lets the second pass process all three positions and recover ZOO.

## Slide 6. Which word can you rule out? (4:40–5:25)

*Allow five seconds for a guess. During a recording, pause and then give the reasoning yourself.*

Here's a fresh output. Imagine the key is hidden and all we know is that one key byte was applied to every letter. Using just the pattern of repeated bytes, which of these three guesses can we rule out? Take a moment to look at the middle pair.

MATH drops out. A and T are different letters, but the two middle bytes here are identical. If I decode either copy of 1F with the same key, I get exactly the same letter. Both BOOK and FEED have the right pattern. The repeated pair alone doesn't tell us which one it was. For this run I used FEED.

## Slide 7. What the ciphertext gives away (5:25–6:15)

*Point back to the paired bytes, then invite questions.*

Compare these two runs using our original key. In BOOK, O turns into 15 each time. In MEET, E turns into 1F each time. We could cover up the words and still locate the double letters. That's already more information than we'd want a private message to give away.

There's another limit you can see from the size of the key. It has eight bits and each bit has two possibilities, so there are only 256 possible keys. Even choosing a different secret byte for this example would leave us with the same small set of possibilities. The reason BOOK comes back is that the same bits flip twice. The reason its double letter shows through is that both O's get the same flips on the first pass. What questions do you have?
