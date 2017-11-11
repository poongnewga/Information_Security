#include <iostream>
#include <string>
using namespace std;

int main () {

  string plain = "WTAADLDGASXCUDGBPIXDCHTRJGXIN";
  string cipher = "WTAADLDGASXCUDGBPIXDCHTRJGXIN";

  int k = 0;

  for (int i=0; i<=25; i++) {
    k = i;

    for (int j=0; j<cipher.size(); j++) {

      if (cipher[j]-k < 'A') {
        plain[j] = (cipher[j]-k - 'A') + 'Z' + 1;
      } else {
        plain[j] = cipher[j]-k;
      }

    }

    cout << plain << '\n';
  }

  cout << '\n';

  k = 15;
  // do same process with key K==15
  for (int j=0; j<cipher.size(); j++) {

    if (cipher[j]-k < 'A') {
      plain[j] = (cipher[j]-k - 'A') + 'Z' + 1;
    } else {
      plain[j] = cipher[j]-k;
    }

  }

  // key : 15
  // plaintext : HELLOWORLDINFORMATIONSECURITY

  cout << "key : " << k << '\n';
  cout << "plaintext : " << plain << '\n';

}
