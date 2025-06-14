# Hangman

A classic **Hangman** game implemented in C++. The program randomly selects a word from a dictionary file and challenges the player to guess it one letter at a time before running out of lives.

---

## Features

- Random word selection from a dictionary file (`Dictionary.txt`).
- Lives represented visually by a hangman figure.
- Input validation to prevent repeated guesses.
- Progress display with underscores for unguessed letters.
- Win and lose conditions with appropriate messages.

---

## How to Use

1. **Prepare the dictionary file:**

   Create a text file named `Dictionary.txt` in the same directory as the executable. This file should contain a list of words (one word per line) for the game to pick from.

2. **Compile the program:**

   ```bash
   g++ -o hangman hangman.cpp
