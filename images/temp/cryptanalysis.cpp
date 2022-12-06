// C&NS Lab - Assignment 2
// 2019BTECS00048 - Sanket Sonawane
// Cryptanalysis of Caesar Cipher

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class CaesarCipher {
 public:
  static string decrypt(const string& ciphertext, int key) {
    string plaintext;

    for (char c : ciphertext) {
      if (c == ' ')
        plaintext += ' ';
      else
        plaintext += ('a' + (c - 'A' + 26 - key) % 26);
    }

    return plaintext;
  }
};

class TrieNode {
 private:
  char curr;
  unordered_map<char, TrieNode*> link;
  bool end;

 public:
  TrieNode(char c) {
    curr = c;
    end = false;
  }

  void insert(const string& str) {
    TrieNode* ptr = this;

    for (char c : str) {
      if (ptr->link.find(c) == ptr->link.end())
        ptr->link[c] = new TrieNode(c);

      ptr = ptr->link[c];
    }

    ptr->end = true;
  }

  bool find(const string& str) {
    TrieNode* ptr = this;

    for (char c : str) {
      if (ptr->link.find(c) == ptr->link.end())
        return false;

      ptr = ptr->link[c];
    }

    return ptr->end;
  }
};

TrieNode generateTrie() {
  ifstream file("dictionary.txt");
  string word;
  TrieNode trie('_');

  while (getline(file, word))
    trie.insert(word);

  file.close();
  return trie;
}

void word(const vector<string>& options, TrieNode& trie) {
  cout << "Possible decrypted values:\n";
  int count = 0;

  for (int i = 0; i < 25; i++) {
    if (trie.find(options[i])) {
      cout << "Key: " << i + 1 << ";\tText: " << options[i] << "\n";
      count++;
    }
  }

  if (count == 0)
    cout << "Ciphertext could not be decrypted with the available "
            "dictionary\n";
  cout << "\n\n";
}

void sentenceWithSpaces(const vector<string>& options, TrieNode& trie) {
  priority_queue<pair<int, int>> pq;  // score, index

  for (int i = 0; i < 25; i++) {
    int score = 0;

    stringstream ss(options[i]);
    string word;
    while (ss >> word) {
      if (trie.find(word))
        score += word.size();
    }

    if (score > 0)
      pq.push({score, i});
  }

  cout << "Possible decrypted values:\n";
  int j;
  for (j = 0; j < 5; j++) {
    if (pq.empty())
      break;

    int score = pq.top().first;

    int i = pq.top().second;
    cout << "Score: " << score << ";\tKey: " << i + 1
         << ";\tText: " << options[i] << "\n";
    pq.pop();
  }

  if (j == 0)
    cout << "Ciphertext could not be decrypted with the available "
            "dictionary\n";
  cout << "\n\n";
}

int DFS(const string& sentence, string word, int i, int n, TrieNode& trie) {
  word += sentence[i++];

  while (!trie.find(word) && i < n)
    word += sentence[i++];

  if (i == n) {
    if (trie.find(word))
      return word.size();
    else
      return 0;
  }

  int score =
      max(DFS(sentence, word, i, n, trie), DFS(sentence, "", i, n, trie));

  if (score == 0)
    return 0;
  return word.size() + score;
}

void sentenceWithoutSpaces(const vector<string>& options, TrieNode& trie) {
  priority_queue<pair<int, int>> pq;  // score, index

  for (int i = 0; i < 25; i++) {
    int score = DFS(options[i], "", 0, options[i].size(), trie);
    pq.push({score, i});
  }

  cout << "Possible decrypted values:\n";
  int j;
  for (j = 0; j < 5; j++) {
    int score = pq.top().first;
    if (score == 0)
      break;

    int i = pq.top().second;
    cout << "Score: " << score << ";\tKey: " << i + 1
         << ";\tText: " << options[i] << "\n";
    pq.pop();
  }

  if (j == 0)
    cout << "Ciphertext could not be decrypted with the available "
            "dictionary\n";
  cout << "\n\n";
}

int main() {
  cout << "Cryptanalysis of Caeser Cipher:\n\n";

  cout << "Loading dictionary of words...\n";
  TrieNode trie = generateTrie();
  cout << "Done!\n\n";

  while (true) {
    cout << "Enter choice:\n"
            "1: word\n"
            "2: sentence with spaces\n"
            "3: sentence without spaces\n"
            "anything other: exit\n"
            "> ";

    int choice;
    cin >> choice;

    if (choice != 1 && choice != 2 && choice != 3) {
      cout << "Thank you!\n";
      break;
    }

    cout << "Enter ciphertext: ";
    string ciphertext;
    getline(cin, ciphertext);  // reset input buffer
    getline(cin, ciphertext);

    vector<string> options;

    for (int key = 1; key <= 25; key++) {
      string plaintext = CaesarCipher::decrypt(ciphertext, key);
      options.push_back(plaintext);
    }

    switch (choice) {
      case 1:
        word(options, trie);
        break;

      case 2:
        sentenceWithSpaces(options, trie);
        break;

      case 3:
        sentenceWithoutSpaces(options, trie);
        break;
    }
  }

  return 0;
}
