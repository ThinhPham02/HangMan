#include <iostream>
#include <fstream>
#include <string> 
#include <cstdlib>
#include <ctime>
using namespace std;

class Player {
    int lives;
    string form;
    vector<char> inputLetter;

    public:
        
        Player() {
            lives = 6;
            setForm();
        }

        int getLives() {
            return lives;
        }

        void minusLives() {
            lives--;
        }

        void getForm() {
            cout << form; 
        }

        void addInput(char c) {
            inputLetter.push_back(c);
        }

        bool checkInput(char c) {
            return (find(inputLetter.begin(), inputLetter.end(), c) != inputLetter.end());
        }

        void setForm() {
            switch(lives) {
                case 0:
                    form = " ________\n |      |\n |      o\n |     /|\\\n |     / \\\n/|\\\n";
                    break;
                case 1:
                    form = " ________\n |      |\n |      o\n |     /|\\\n |     /\n/|\\\n";
                    break;
                case 2:
                    form = " ________\n |      |\n |      o\n |     /|\\\n |\n/|\\\n";
                    break;
                case 3:
                    form = " ________\n |      |\n |      o\n |     /|\n |\n/|\\\n";
                    break;
                case 4:
                    form = " ________\n |      |\n |      o\n |     /\n |\n/|\\\n";
                    break;
                case 5:
                    form = " ________\n |      |\n |      o\n |\n |\n/|\\\n";
                    break;
                default:
                    form = " ________\n |      |\n |\n |\n |\n/|\\\n";
                    break;
            }
        }

        bool checkLose() {
            return lives == 0;
        }
};

class Word {
    string word;
    string wordForm;
    int length;
    int correctNum;

    public:
        Word(const string& word) {
            this->word = word;
            length = word.size();
            correctNum = 0;

            for (int i = 0; i < length; i++) {
                wordForm += " _";
            }
        }

        string getWord() {
            return word;
        }

        int getLength() {
            return length;
        }

        int getCorrectNum() {
            return correctNum;
        }

        string getWordForm() {
            return wordForm;
        }

        int checkWord(char c) {
            int num = count(word.begin(), word.end(), c);
            correctNum += num;
            if (num > 0) {
                setForm(c);
            }
            return num;
        }

        string setForm(char c) {
            for(int i = 0; i < length; i++) {
                if (c == word[i]) {
                    wordForm[(i * 2) + 1] = c;
                }
            }
            return wordForm;
        } 
        
        bool checkWin() {
            return correctNum == length;
        }
};


int main() {
    string word;
    int count = 0;
    int pickWord = 0;
    char inputLetter;
    ifstream file("Dictionary.txt");

    if (!file) {
        cerr << "Could not open file." << std::endl;
        return 1;
    }

    while (file >> word) {
        count++;
    }

    srand(time(nullptr)); 
    pickWord = rand() % count + 1;

    file.clear();                
    file.seekg(0, ios::beg);

    
    int current = 0;
    while (file >> word) {
        current++;
        if (current == pickWord) {
            break;
        }
    }

    Word gameWord(word);
    Player player;

    cout << "=====================================\n";
    cout << "     🎮 Welcome to HANGMAN! 🎮\n";
    cout << "=====================================\n\n";
    cout << "🕹️  A mysterious word awaits you...\n";
    cout << "📏  It has " << gameWord.getLength() << " letters. Can you guess it?\n\n";
    cout << "    " << gameWord.getWordForm();
    cout << "\n\n💡  Type a letter and press Enter to begin!\n\n";
    cout << "Good luck, challenger!\n";

    while (true) {
        cout << "\n🔤 What letter will you try next?\n";
        cin >> inputLetter;

        if (player.checkInput(inputLetter)) {
            cout << "⚠️  You've already guessed '" << inputLetter << "'. Try something new.\n";
            continue;
        }

        player.addInput(inputLetter);
        int num = gameWord.checkWord(inputLetter);

        if (num > 0) {
            cout << "✅ Nice! You found " << num << " '" << inputLetter << "' in the word!\n";
            cout << "🧩 Only " << (gameWord.getLength() - gameWord.getCorrectNum()) << " more to go. Keep it up!\n";
        } else {
            player.minusLives();
            player.setForm();
            cout << "❌ Oops! No '" << inputLetter << "' in the word.\n";
            cout << "💡 Don't give up - try again!\n";
        }

        player.getForm();
        cout << "\n  " << gameWord.getWordForm() << "\n";

        if (player.checkLose()) {
            cout << "\n The word is '" << gameWord.getWord() << "'.\n";
            cout << "\n💀 Game Over! You've run out of chances.\n";
            cout << "🔁 Better luck next time!\n\n";
            break;
        }

        if (gameWord.checkWin()) {
            cout << "\n🎉 Congratulations! You've guessed the word!\n";
            cout << "🏆 Victory is yours, word master!\n\n";
            break;
        }
    }   


    return 0;
}

