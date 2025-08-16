#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <algorithm>
using namespace std;

vector<string> loadwords()
{
    vector<string> words;
    string line;
    ifstream fin("wordslist.txt");
    if (!fin) {
        cerr << "Error: Could not open wordslist.txt" << endl;
        exit(1);
    }
    while (getline(fin, line))
    {
        if (line.length() > 0)
            words.push_back(line);
    }
    return words;
}

string choose_word(const vector<string>& words_list)
{
    if (words_list.empty()) {
        cerr << "Error: Word list is empty." << endl;
        exit(1);
    }
    int random_index = rand() % words_list.size();
    return words_list[random_index];
}

bool display_word(const string& word, const vector<char>& guessed_letters)
{
    bool winstatus = true;
    for (char c : word)
    {
        if (find(guessed_letters.begin(), guessed_letters.end(), c) != guessed_letters.end())
            cout << c << " ";
        else
        {
            cout << "_ ";
            winstatus = false;
        }
    }
    cout << endl;
    return winstatus;
}

int main()
{
    srand(time(0)); // Seed random once
    vector<string> words_list = loadwords();
    string word_to_guess = choose_word(words_list);
    vector<char> guessed_letters;
    bool winstatus = false;
    int lives = 5;
    cout << "Welcome to Hangman!" << endl;
    while (lives > 0)
    {
        cout << "Lives Remaining: " << lives << endl;
        winstatus = display_word(word_to_guess, guessed_letters);
        if (winstatus)
        {
            cout << "Congratulations! You guessed the word: " << word_to_guess << endl;
            break;
        }

        char guess;
        cout << "Guess a letter: ";
        cin >> guess;
        guess = tolower(guess);

        // Check for duplicate guess
        if (find(guessed_letters.begin(), guessed_letters.end(), guess) != guessed_letters.end()) {
            cout << "You already guessed that letter. Try again." << endl;
            continue;
        }

        guessed_letters.push_back(guess);
        if (word_to_guess.find(guess) != string::npos)
        {
            cout << "Correct Guess!" << endl;
        }
        else
        {
            cout << "Incorrect Guess!" << endl;
            lives--;
        }
    }
    if (lives == 0)
    {
        cout << "You Lost! The word was: " << word_to_guess << endl;
    }
    return 0;
}