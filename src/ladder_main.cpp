#include "ladder.h"
#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    string begin_word, end_word;
    cout << "Enter the start word: ";
    cin >> begin_word;
    cout << "Enter the end word: ";
    cin >> end_word;
    
    if (begin_word == end_word) {
        cout << "Error: Start and end words must be different." << endl;
        return 1;
    }
    
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
    
    return 0;
}