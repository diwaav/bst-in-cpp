/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA7
* DictionaryTest.cpp
* Dictionary ADT tester
**********************************************************************************/


#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    Dictionary words;
    string guess = "";
    int count = 0;

    cout << "Guess the word\nHINT 1: I'm thinking of a fruit.\nGUESS: ";
    cin >> guess;
    words.setValue(guess, count);
    count += 1;

    cout << "Nope... HINT 2: It's red!\nGUESS: ";
    cin >> guess;
    words.setValue(guess, count);
    count += 1;

    cout << "Alright I'll give you three more guesses let's see if you get it...\n";
    for (int i = 0; i < 3; i += 1) {
        cout << "GUESS: ";
        cin >> guess;
        words.setValue(guess, count);
        count += 1;
    }
    cout << "\nAll your guesses are wrong. The correct answer is ANXIETY.\n";
    cout << "Just kidding. There is no answer. I was just adding to the tree :)\n";

    cout << "Here are your " << words.size() << " guesses in aphabetical order:\n" << words;

    cout << "\n- - - - - -\nSTATS:\n- - - - - -\n";
    words.begin();
    cout << "tree starts with " << words.currentKey();
    words.next();
    cout << "\nnext we have " << words.currentKey();
    words.end();
    cout << "\nand tree ends with " << words.currentKey();
    words.prev();
    cout << "\nbut before that is " << words.currentKey();

    cout << "\nCheck: is this value in the dictionary: ";
    cin >> guess;
    cout << (words.contains(guess)?"true\n":"false\n");

    cout << "\nCheck: remove this from the dictionary: ";
    cin >> guess;
    if (words.contains(guess)) {
        words.remove(guess);
        cout << "\nNew dictionary (after removal)\n" << words << "\n";
    } else {
        cout << "\nAre you trying to trick me? That's not even in the dictionary!\n";
    }

    Dictionary cpy = words;
    cout << "I made a copy of your list words:\n" << words;
    cout << "\n... and it looks like this:\n" << cpy;

    cout << "\nAre they equal?\n" << (words==cpy?"yes\n":"nope\n");

    return 0;
}
