#include <iostream>
#include <string>
using namespace std;

int main () {
  string plain = "WGPKQQMVSQPJWTQIVMWPWMEYZKXG";
  // key hint : "I--"
  // A==0, ..., Z==25

  string cipher = "EGPKQQMVSQPJWTQIVMWPWMEYZKXG";
  string key;

  for (int m=0; m<=25; m++) {
    for (int n=0; n<=25; n++) {

      for (int i=0; i<cipher.size(); i+=3) {
        if (cipher[i] - ('I' - 'A') < 'A') {
          plain[i] = cipher[i] - ('I' - 'A') - 'A' + 'Z' + 1;
        } else {
          plain[i] = cipher[i] - ('I' - 'A');
        }

        if (i+1 < cipher.size()) {
          if (cipher[i+1] - m < 'A') {
            plain[i+1] = cipher[i+1] - m - 'A' + 'Z' + 1;
          } else {
            plain[i+1] = cipher[i+1] - m;
          }
        }

        if (i+2 < cipher.size()) {
          if (cipher[i+2] - n < 'A') {
            plain[i+2] = cipher[i+2] - n - 'A' + 'Z' + 1;
          } else {
            plain[i+2] = cipher[i+2] - n;
          }
        }

      }

      cout << plain << '\n';

    }
  }

  cout << '\n';
  key = "ICE";
  // do same process with key K == "ICE"
  for (int i=0; i<cipher.size(); i+=3) {
    if (cipher[i] - (key[0] - 'A') < 'A') {
      plain[i] = cipher[i] - (key[0] - 'A') - 'A' + 'Z' + 1;
    } else {
      plain[i] = cipher[i] - (key[0] - 'A');
    }

    if (i+1 < cipher.size()) {
      if (cipher[i+1] - (key[1] - 'A') < 'A') {
        plain[i+1] = cipher[i+1] - (key[1] - 'A') - 'A' + 'Z' + 1;
      } else {
        plain[i+1] = cipher[i+1] - (key[1] - 'A');
      }
    }

    if (i+2 < cipher.size()) {
      if (cipher[i+2] - (key[2] - 'A') < 'A') {
        plain[i+2] = cipher[i+2] - (key[2] - 'A') - 'A' + 'Z' + 1;
      } else {
        plain[i+2] = cipher[i+2] - (key[2] - 'A');
      }
    }

  }

  // key : ICE
  // plaintext : WELCOMETOINFORMATIONSECURITY

  cout << "key : " << key << '\n';
  cout << "plaintext : " << plain << '\n';

} 
