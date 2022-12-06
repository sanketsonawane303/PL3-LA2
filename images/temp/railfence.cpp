// C&NS Lab - Assignment 5A
// 2019BTECS00048 - Sanket Sonawane
// Implementation of Railfence Cipher

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RailfenceCipher {
 public:
  static string encrypt(const string& plaintext, int key) {
    vector<string> rows(key);
    int i = 0;
    bool down = true;

    for (char c : plaintext) {
      rows[i] += c;

      if (down) {
        i++;
        if (i == key) {
          i = key - 2;
          down = false;
        }
      } else {
        i--;
        if (i == -1) {
          i = 1;
          down = true;
        }
      }
    }

    string ciphertext;

    for (string& row : rows)
      ciphertext += row;

    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(),
              ::toupper);
    return ciphertext;
  }

  static string decrypt(const string& ciphertext, int key) {
    vector<int> rowCount(key);
    int i = 0;
    bool down = true;
    int n = ciphertext.size();

    while (n--) {
      rowCount[i]++;

      if (down) {
        i++;
        if (i == key) {
          i = key - 2;
          down = false;
        }
      } else {
        i--;
        if (i == -1) {
          i = 1;
          down = true;
        }
      }
    }

    vector<string> rows(key);
    i = 0;
    for (char c : ciphertext) {
      rows[i] += c;

      rowCount[i]--;
      if (rowCount[i] == 0)
        i++;
    }

    n = ciphertext.size();
    string plaintext;
    i = 0;
    down = true;

    while (n--) {
      plaintext += rows[i][rowCount[i]++];

      if (down) {
        i++;
        if (i == key) {
          i = key - 2;
          down = false;
        }
      } else {
        i--;
        if (i == -1) {
          i = 1;
          down = true;
        }
      }
    }

    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
    return plaintext;
  }
};

int main() {
  cout << "Railfence Cipher:\n\n"
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

      cout << "Enter key (int >= 2): ";
      int key;
      cin >> key;

      string ciphertext = RailfenceCipher::encrypt(plaintext, key);

      cout << "Plaintext:  " << plaintext << "\n"
           << "Ciphertext: " << ciphertext << "\n";
    } break;

    case 2: {
      cout << "Enter ciphertext (uppercase without spaces): ";
      string ciphertext;
      cin >> ciphertext;

      cout << "Enter key (int >= 2): ";
      int key;
      cin >> key;

      string plaintext = RailfenceCipher::decrypt(ciphertext, key);

      cout << "Ciphertext: " << ciphertext << "\n"
           << "Plaintext:  " << plaintext << "\n";
    } break;

    default:
      cout << "Invalid choice!!\n";
      break;
  }

  return 0;
}
