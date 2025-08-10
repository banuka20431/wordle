
# Wordle - C Version

A simple terminal-based implementation of the popular Wordle game written in C.

---

## Overview

This program lets the user guess a randomly selected 5-letter word within a limited number of tries.  
Each guess is evaluated, and feedback is given in color-coded form:
- **Green**: Correct letter in the correct position.
- **Yellow**: Correct letter but in the wrong position.
- **Red**: Letter not present in the target word.

The game reads possible words from a file, picks one randomly, and allows the user to guess until the word is found or the tries run out.

---

## Features

- Loads up to 302 five-letter words from a file (`words.txt`).
- Randomly selects a word using the process ID to seed randomness.
- Checks the guessed word against the selected word and provides color-coded feedback.
- Tracks progress visually by showing correctly guessed letters.
- Limits number of attempts to 10 by default.
- Displays appropriate messages for win or loss.

---

## Constants and Macros

| Name         | Value        | Description                    |
|--------------|--------------|--------------------------------|
| `ResultGreen`| 1            | Letter correct and in correct position (Green) |
| `ResultYellow`| 2           | Letter present but wrong position (Yellow)     |
| `ResultRed`  | 3            | Letter not in the word (Red)                    |
| `BufferSize` | 8            | Buffer size for reading words from file         |
| `MaxWordCount`| 302          | Maximum number of words to load from file       |

Color macros for terminal output:

- `ClrGreen` - Green background color for correct letters.
- `ClrYellow` - Yellow background color for misplaced letters.
- `ClrRed` - Red background color for incorrect letters.
- `ClrTrm` - Reset terminal colors.
- `ClrHeader` - Color for header text.

---

## Files

- `wordle.c` — main program source code.
- `words.txt` — text file containing the list of possible 5-letter words, one per line.

---

## How it works

1. **Loading Words**  
   The program reads up to 302 five-letter words from `words.txt` into memory.

2. **Word Selection**  
   A random word is selected using the process ID to seed the random number generator.

3. **Gameplay Loop**  
   - User inputs a 5-letter guess.
   - The program checks each character of the guess against the selected word.
   - Results are returned as an array indicating Green, Yellow, or Red status for each letter.
   - Colored feedback is displayed.
   - Correct letters are progressively revealed.
   - The loop continues until the word is guessed or tries run out.

---

## Usage

Compile the program with:

```bash
gcc wordle.c -o wordle
```

Run the game:

```bash
./wordle
```

Ensure `words.txt` is present in the same directory with valid 5-letter words.

---

## Function Summary

| Function           | Description                                          |
|--------------------|------------------------------------------------------|
| `int readfile(char *filename)` | Loads words from the given file into memory. Returns number of words loaded. |
| `void setword(int max)`         | Randomly selects a target word from the loaded list.                   |
| `Result check_char(int idx, char guess_c)` | Checks a single character against the target word, returns color code. |
| `Result *check_word(char *guess_word)`      | Checks the entire guessed word, returns array of color codes.          |
| `void print_results(Result *res, char *guessed_word)` | Prints the guess with colored feedback.                                |
| `void prompt_guess_progress(bool *correct_indexes)` | Shows progress by revealing correctly guessed letters.                 |
| `bool words_matched(bool *arr)` | Returns true if all letters are correctly guessed.                     |
| `void mainloop()`                | Main game loop handling user input and result display.                |

---

## Example Output

```
  ______ _     _ _______ _______ _______      _______ _     _ _______      _  _  _  _____   ______ ______ 
 |  ____ |     | |______ |______ |______         |    |_____| |______      |  |  | |     | |_____/ |     
 |_____| |_____| |______ ______| ______|         |    |     | |______      |__|__| |_____| |    \_ |_____/

 - Guess the 5 letter word [ _ _ _ _ _ ]

 - Hint :

         Red -> Character doesn't contain in the correct word
         Yellow -> Character contains in the correct word
         Green -> Character matches with the correct word

 - You have 10 tries to figure it out. Go!

 >_ apple
Result : 🟩🟨🟥🟥🟥

Progress : [ a _ _ _ _ ]

Tried 1 / 10

 >_ ...
```

---

## Notes

- The game uses terminal color codes and may not display colors correctly on all terminals.
- The word list must contain only valid five-letter words, one word per line.
- The program expects exactly 5 characters per word (no newline or trailing spaces).

---

## License

This project is open-source. You may use and modify it as you like.

---

Enjoy playing Wordle in your terminal!
