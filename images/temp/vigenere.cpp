// C&NS Lab - Assignment 4
// 2019BTECS00048 - Sanket Sonawane
// Implementation of Vigenere Cipher

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class VigenereCipher {
 public:
  static string encrypt(const string& plaintext, const string& key) {
    string ciphertext;
    int k = key.size();
    int i = 0;

    for (char c : plaintext) {
      ciphertext += 'A' + ((c - 'a') + (key[i] - 'a')) % 26;
      i = (i + 1) % k;
    }

    return ciphertext;
  }

  static string decrypt(const string& ciphertext, const string& key) {
    string plaintext;
    int k = key.size();
    int i = 0;

    for (char c : ciphertext) {
      plaintext += 'a' + ((c - 'A') - (key[i] - 'a') + 26) % 26;
      i = (i + 1) % k;
    }

    return plaintext;
  }
};

int main() {
  cout << "Vigenere Cipher:\n\n"
       << "Enter your choice:\n"
       << "1. Encrypt\n"
       << "2. Decrypt\n"
       << "> ";

  int choice;
  cin >> choice;

  switch (choice) {
    case 1: {
      cout << "Enter plaintext (lowercase): ";
      string plaintext;
      getline(cin, plaintext);  // buffer reset
      getline(cin, plaintext);
      plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::isspace),
                      plaintext.end());

      cout << "Enter key (lowercase): ";
      string key;
      cin >> key;

      string ciphertext = VigenereCipher::encrypt(plaintext, key);

      cout << "Plaintext:  " << plaintext << "\n"
           << "Ciphertext: " << ciphertext << "\n";
    } break;

    case 2: {
      cout << "Enter ciphertext (uppercase without spaces): ";
      string ciphertext;
      cin >> ciphertext;

      cout << "Enter key (lowercase): ";
      string key;
      cin >> key;

      string plaintext = VigenereCipher::decrypt(ciphertext, key);

      cout << "Ciphertext: " << ciphertext << "\n"
           << "Plaintext:  " << plaintext << "\n";
    } break;

    default:
      cout << "Invalid choice!!\n";
      break;
  }

  return 0;
}
