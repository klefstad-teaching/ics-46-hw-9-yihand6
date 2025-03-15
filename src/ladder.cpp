#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
    exit(1);
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;
    
    int i = 0, j = 0, diff = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++diff > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return diff + abs((len1 - i) - (len2 - j)) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {begin_word};
    
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) return new_ladder;
                
                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Could not open file " << file_name << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); ++i) {
            if (i > 0) cout << " -> ";
            cout << ladder[i];
        }
        cout << endl;
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    cout << "Verifying Word Ladders:" << endl;
    vector<string> result;
    
    result = generate_word_ladder("cat", "dog", word_list);
    cout << "cat -> dog: " << (result.size() == 4 ? "passed" : "failed") << endl;
    
    result = generate_word_ladder("marty", "curls", word_list);
    cout << "marty -> curls: " << (result.size() == 6 ? "passed" : "failed") << endl;
    
    result = generate_word_ladder("code", "data", word_list);
    cout << "code -> data: " << (result.size() == 6 ? "passed" : "failed") << endl;
    
    result = generate_word_ladder("work", "play", word_list);
    cout << "work -> play: " << (result.size() == 6 ? "passed" : "failed") << endl;
    
    result = generate_word_ladder("sleep", "awake", word_list);
    cout << "sleep -> awake: " << (result.size() == 8 ? "passed" : "failed") << endl;
    
    result = generate_word_ladder("car", "cheat", word_list);
    cout << "car -> cheat: " << (result.size() == 4 ? "passed" : "failed") << endl;
}