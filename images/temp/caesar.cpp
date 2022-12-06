// C&NS Lab - Assignment 1
// 2019BTECS00048 - Sanket Sonawane
// Implementation of Caesar Cipher

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class CaesarCipher {
 public:
  static string encrypt(const string& plaintext, int key) {
    string ciphertext;

    for (char c : plaintext)
      ciphertext += ('A' + (c - 'a' + key) % 26);

    return ciphertext;
  }

  static string decrypt(const string& ciphertext, int key) {
    string plaintext;

    for (char c : ciphertext)
      plaintext += ('a' + (c - 'A' + 26 - key) % 26);

    return plaintext;
  }
};

int main() {
  cout << "Caeser Cipher:\n\n"
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

      cout << "Enter key (int): ";
      int key;
      cin >> key;

      string ciphertext = CaesarCipher::encrypt(plaintext, key);

      cout << "Plaintext:  " << plaintext << "\n"
           << "Ciphertext: " << ciphertext << "\n";
    } break;

    case 2: {
      cout << "Enter ciphertext (uppercase without spaces): ";
      string ciphertext;
      cin >> ciphertext;

      cout << "Enter key (int): ";
      int key;
      cin >> key;

      string plaintext = CaesarCipher::decrypt(ciphertext, key);

      cout << "Ciphertext: " << ciphertext << "\n"
           << "Plaintext:  " << plaintext << "\n";
    } break;

    default:
      cout << "Invalid choice!!\n";
      break;
  }

  return 0;
}
