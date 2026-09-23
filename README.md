# wordle-c ("Cordle")

A terminal version of Wordle written in C, with color-coded feedback and a dictionary of nearly 15,000 five-letter words.

## Features

- **Dictionary loaded at runtime:** reads `words.txt` into a dynamically resized array of strings, keeping only 5-letter words
- **Accurate Wordle scoring:** a two-pass algorithm marks exact matches first, then misplaced letters, so repeated letters are scored the way the real game scores them
- **Color output:** green for the right letter in the right spot, yellow for the right letter in the wrong spot, gray for letters not in the word
- **Input handling:** case-insensitive guesses, rejects guesses that aren't 5 letters without using up a turn, and caps input length to prevent buffer overflow
- Frees all allocated memory before exiting

## Build and run

Run it from this folder so it can find `words.txt`.

```
gcc -Wall -Wextra -o wordle wordle.c
./wordle
```

## How scoring works

For each guess, the first pass marks letters that match the target exactly and flags those target positions as used. The second pass checks the remaining letters against unused target positions only. This is what stops a guess like `SPEED` from showing two yellow E's when the target has only one.

## Next steps

- Reject guesses that aren't real words in the dictionary
- Show a keyboard of letters already used
