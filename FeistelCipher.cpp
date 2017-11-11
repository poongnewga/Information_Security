// By 보건정책관리학부 채희재
// 2012250416
// Feistel Cipher - 10 rounds
// Create 10 subkey with 32bit Key

#include <iostream>
#include <string>
#include <bitset>
using namespace std;


unsigned long long plainText;
unsigned long long cipherText;
unsigned int key;
unsigned int subkeys[11];
unsigned int arrForL[11];
unsigned int arrForR[11];
// Get Subkey with Li + Ri
unsigned int LE[12];
unsigned int RE[12];
// Arr for Round LEi, REi
unsigned int temp;
unsigned int temp2;
unsigned long long result;
unsigned int res;
unsigned int res2;
unsigned int im;
unsigned int w, x;


// Print Binary
void printBinary(int digit, unsigned long long word) {
    if (digit == 32)
        cout << bitset<32>(word) << '\n';
    else
        cout << bitset<64>(word) << '\n';
}

// S1
unsigned int S1[16] = {
    0xE, 0x4, 0xD, 0x1, 0x2, 0xF, 0xB, 0x8, 0x3, 0xA, 0x6, 0xC, 0x5, 0x9, 0x0, 0x7
};

// S2
unsigned int S2[16] = {
    0x5, 0x6, 0xC, 0xF, 0x8, 0xA, 0x0, 0x4, 0xB, 0x3, 0x7, 0xD, 0xE, 0x1, 0x2, 0x9
};

// Permutation Table
unsigned int pTable[32] = {
    29, 1, 17, 8,
    30, 22, 28, 6,
    18, 4, 12, 19,
    21, 26, 2, 20,
    31, 10, 9, 25,
    13, 0, 23, 15,
    3, 27, 5, 11,
    7, 14, 24, 16
};

// Get Permutation
unsigned int doPermutation(unsigned int &word) {
    return
    ((word & 0x80000000) >> 29) | ((word & 0x40000000) >> 0) | ((word & 0x20000000) >> 15) | ((word & 0x10000000) >> 5)
    | ((word & 0x08000000) >> 26) | ((word & 0x04000000) >> 17) | ((word & 0x02000000) >> 22) | ((word & 0x01000000) << 1)
    | ((word & 0x00800000) >> 10) | ((word & 0x00400000) << 5) | ((word & 0x00200000) >> 2) | ((word & 0x00100000) >> 8)
    | ((word & 0x00080000) >> 9) | ((word & 0x00040000) >> 13) | ((word & 0x00020000) << 12) | ((word & 0x00010000) >> 5)
    | ((word & 0x00008000) >> 15) | ((word & 0x00004000) << 7) | ((word & 0x00002000) << 9) | ((word & 0x00001000) >> 6)
    | ((word & 0x00000800) << 7) | ((word & 0x00000400) << 21) | ((word & 0x00000200) >> 1) | ((word & 0x00000100) << 8)
    | ((word & 0x00000080) << 21) | ((word & 0x00000040) >> 2) | ((word & 0x00000020) << 21) | ((word & 0x00000010) << 16)
    | ((word & 0x00000008) << 21) | ((word & 0x00000004) << 15) | ((word & 0x00000002) << 6) | ((word & 0x00000001) << 15);
}

unsigned int doF(unsigned int &input, unsigned int &subkey) {
    im = input ^ subkey;
    // Be initialized with 0
    res2 = 0;

    // shift for i*4
    for (int i = 7; i >= 0; i--) {
        temp2 = (im >> (i * 4)) & 0x0000000F;
        if ((i & 1) == 1) {
            res2 |= (S1[temp2] << (i * 4));
        }
        else {
            res2 |= (S2[temp2] << (i * 4));
        }
    }

    return doPermutation(res2);
}


// Do round with LE(32-bit), RE(32-bit)
// CipherText(64-bit) needs to additional process.
void doRound(int r, unsigned int &le, unsigned int &re) {

    // condition for exit recursion
    if (r == 11) {
        LE[11] = RE[10];
        RE[11] = LE[10];
        return;
    }

    // RE(i-1) => LE(i)
    LE[r] = RE[r - 1];

    // Round(i) : do F with RE(i-1) and Ki
    res = doF(RE[r - 1], subkeys[r]);

    // XOR : result of F (res) ^ LE(i-1) => RE(i)
    RE[r] = res ^ LE[r - 1];

    doRound(r + 1, LE[r], RE[r]);
}


// 1. Seperate Key with L & R
// 2. Shift R 10 times
int main() {
    ios_base::sync_with_stdio(false);
    cout << "Start!" << '\n';
    // sample
    // key: 0x0434EF71
    // plaintext: 0x1024AA9F473C58C1
    // ciphertext: 0x4FC83760C78F6EF0

    // Q1
    // plaintext:  0x40FF24330947F610
    // ciphertext: 0xEC2DE1305B5F5B02

    // Q2
    // plaintext:  0x2174C501AC12F9D1
    // ciphertext: 0xDF9FCC3FFE09809D

    // Set plaintext & key & ciphertext
    plainText = 0x2174C501AC12F9D1;
    key = 0x0434EF71;
    LE[0] = (plainText >> 32) & 0x00000000FFFFFFFF;
    RE[0] = plainText & 0x00000000FFFFFFFF;
    cipherText = 0xDF9FCC3FFE09809D;

    // brute force : 0x00000000 ~ 0xFFFFFFFF
//    int cnt = 0;
    for (unsigned int k = 0xF24CB904; k <= 0xFFFFFFFF; k++) {
//        cnt++;
//        cout << cnt << '\n';

        key = k;
        arrForL[0] = (key >> 16) & 0x0000FFFF;
        arrForR[0] = key & 0x0000FFFF;

        for (int i = 1; i <= 10; i++) {
            arrForL[i] = ((arrForL[0] << i) | (arrForL[0] >> (16 - i))) & 0x0000FFFF;
            arrForR[i] = ((arrForR[0] << i) | (arrForR[0] >> (16 - i))) & 0x0000FFFF;
        }

        // Get 10 Subkeys
        for (int i = 1; i <= 10; i++) {
            subkeys[i] = (arrForL[i] << 16) | arrForR[i];
        }

        doRound(1, LE[0], RE[0]);

        result = LE[11];
        result = (result << 32) | (RE[11]);

        if (cipherText == result) {
            cout << '\n';
            cout << "Found!" << '\n';
            cout << "Cipher Should be : " << '\n';
            printBinary(64, cipherText);
            cout << "Cipher by Key is : " << '\n';
            printBinary(64, result);
            cout << "Key is : " << k << '\n';
            cout << "Key in Hex : ";
            cout << uppercase << hex << "0x" << k;

            break;
        }
        else {
            //                        cout << k << '\n';
        }
    }
    cout << '\n';
    cout << '\n';
    cout << "Fin." << '\n';
    return 0;
}
