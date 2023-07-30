// Noah Morris
// AES.cpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<unsigned char>> sBox = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
	{0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
	{0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
	{0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
	{0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
	{0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
	{0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
	{0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
	{0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
	{0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
	{0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
	{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
	{0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
	{0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
	{0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
	{0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

vector<vector<unsigned char>> InvsBox = {
	{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb },
	{0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb },
	{0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e },
	{0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25 },
	{0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92 },
	{0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84 },
	{0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06 },
	{0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b },
	{0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73 },
	{0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e },
	{0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b },
	{0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4 },
	{0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f },
	{0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef },
	{0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61 },
	{0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d }};

vector<unsigned int> Rcon = {
    0x00000000, 0x01000000, 0x02000000, 0x04000000, 
    0x08000000, 0x10000000, 0x20000000, 0x40000000, 
    0x80000000, 0x1B000000, 0x36000000, 0x6C000000, 
    0xD8000000, 0xAB000000, 0x4D000000, 0x9A000000, 
    0x2F000000, 0x5E000000, 0xBC000000, 0x63000000, 
    0xC6000000, 0x97000000, 0x35000000, 0x6A000000, 
    0xD4000000, 0xB3000000, 0x7D000000, 0xFA000000, 
    0xEF000000, 0xC5000000, 0x91000000, 0x39000000, 
    0x72000000, 0xE4000000, 0xD3000000, 0xBD000000, 
    0x61000000, 0xC2000000, 0x9F000000, 0x25000000, 
    0x4A000000, 0x94000000, 0x33000000, 0x66000000, 
    0xCC000000, 0x83000000, 0x1D000000, 0x3A000000, 
    0x74000000, 0xE8000000, 0xCB000000, 0x8D000000};

// FINITE FIELD ARITHMETIC

// ffAdd simply XORs the two finite fields
unsigned char ffAdd(unsigned char ff1, unsigned char ff2)
{
    return ff1 ^ ff2;
}

// xtime multiplies a finite field by a value of x
unsigned char xtime(unsigned char ff)
{
    int temp = ff << 1 & 0x100;
    
    if(temp == 0x100)
        return (ff << 1) ^ 0x1b;
    return ff << 1;
}

// ffmultiply multiplies two finite fields
unsigned char ffMultiply(unsigned char ff1, unsigned char ff2)
{
    unsigned char temp, sum = 0x00;

    for(int i = 0; i < 8; i++)
    {
        // as the for loop progresses, goes through every bit in field 1
        temp = (ff1 >> i) & 0x01;

        // if a bit was found, add to the sum
        if(temp == 0x01)
            sum = ffAdd(sum, ff2);
        // multiply field 2 by a factor of x
        ff2 = xtime(ff2);
    }

    return sum;
}

// KEY EXPANSION

// substitutes a word with multiple corresponding values in sBox
unsigned int subWord(unsigned int word)
{
    unsigned int temp = 0;
    int temp2 = 24;

    for(int i = 0; i < 4; i++)
    {
        // obatains one byte from the word and splits it into two
        unsigned int temp3 = word >> temp2;
        unsigned int x = (temp3 >> 4) & 0xf;
        unsigned int y = temp3 & 0xf;

        // inserts the sBox value
        temp = temp | sBox[x][y];

        // shifts the values left if there is still more to be added
        if(i < 3)
            temp = temp << 8;

        temp2 = temp2 - 8;
    }
    return temp;
}

// takes a word and performs a cyclic permutation
unsigned int rotWord(unsigned int word)
{
    return (word << 8) | (word >> 24);
}

// generates a key schedule based on the cipher key
void KeyExpansion(vector<unsigned char> key, vector<unsigned int>& word, int Nk, int Nr)
{
    unsigned int temp = 0x0;
    
    int i = 0; 

    while(i < Nk) 
    {
        temp = (temp | key[4 * i]) << 8;
        temp = (temp | key[4 * i + 1]) << 8;
        temp = (temp | key[4 * i + 2]) << 8;
        temp = temp | key[4 * i + 3];   

        word[i] = temp;

        temp = 0x0;
        i++;
    }

    i = Nk;

    while(i < 4 * (Nr + 1)) 
    {
        temp = word[i - 1];

        if(i % Nk == 0)
            temp = subWord(rotWord(temp)) ^ Rcon[i / Nk];
        
        else if(Nk > 6 && i % Nk == 4) 
            temp = subWord(temp);
        
        word[i] = word[i - Nk] ^ temp;
        i++;
    }
}

// CIPHER FUNCTIONS

// subtitutes all bytes within a state with their corresponding values from sBox
void subBytes(vector<vector<unsigned char>>& state)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            unsigned char temp = state[i][j];

            int x = (temp >> 4) & 0xf;
            int y = temp & 0xF;

            state[i][j] = sBox[x][y];
        }
    }
}

// shifts bytes to the left on each row
void shiftRows(vector<vector<unsigned char>>& state)
{
    unsigned char temp1, temp2;
    for(int i = 1; i < 4; i++)
    {
        for(int j = 0; j < i; j++)
        {
            temp1 = state[i][0];
            temp2 = state[i][3];
            state[i][3] = temp1;
            temp1 = state[i][2];
            state[i][2] = temp2;
            temp2 = state[i][1];
            state[i][1] = temp1;
            state[i][0] = temp2;
        }
    }
}

// mixes the columns by preforming matrix algebra with a specific matrix
void mixColumns(vector<vector<unsigned char>>& state) 
{
    for(int i = 0; i < 4; i++)
    {
        unsigned char temp1 = state[0][i];
        unsigned char temp2 = state[1][i];
        unsigned char temp3 = state[2][i];
        unsigned char temp4 = state[3][i];

        state[0][i] = ffAdd(ffAdd(ffAdd(ffMultiply(0x02, temp1), ffMultiply(0x03, temp2)), temp3), temp4);
        state[1][i] = ffAdd(ffAdd(ffAdd(temp1, ffMultiply(0x02, temp2)), ffMultiply(0x03, temp3)), temp4);
        state[2][i] = ffAdd(ffAdd(ffAdd(temp1, temp2), ffMultiply(0x02, temp3)), ffMultiply(0x03, temp4));
        state[3][i] = ffAdd(ffAdd(ffAdd(ffMultiply(0x03, temp1), temp2), temp3), ffMultiply(0x02, temp4));
    }
}

// adds round keys to the state using XOR
void addRoundKey(vector<vector<unsigned char>>& state, vector<unsigned int> word) 
{    
    for(int i = 0; i < 4; i++)
    {
        state[0][i] = state[0][i] ^ (word[i] >> 24);
        state[1][i] = state[1][i] ^ (word[i] >> 16);
        state[2][i] = state[2][i] ^ (word[i] >> 8);
        state[3][i] = state[3][i] ^ word[i];
    }
}

// Encrypts using AES and displays all of the steps required for it. Follows the what was shown in FIPS with printing added to it
void cipher(vector<vector<unsigned char>>& in, vector<vector<unsigned char>>& out, vector<unsigned int>& word, vector<unsigned char> key, int Nk, int Nr) 
{
    vector<unsigned int> word2;

    KeyExpansion(key, word, Nk, Nr);

    word2.assign(word.begin(), next(word.begin(), 4));

    cout << "round[ 0].input     ";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            printf("%02x", in[j][i]);

    cout << endl << "round[ 0].k_sch     ";

    for(int i = 0; i < 4; i++)
        printf("%08x", word2[i]);
    cout << endl;

    addRoundKey(in, word2);
    
    for(int round = 1; round < Nr; round++)
    {   
        cout << "round[" << setw(2) << round << "].start     ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);

        cout <<  endl;
        
        subBytes(in);

        cout << "round[" << setw(2) << round << "].s_box     ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
        cout << endl;
        
        shiftRows(in);

        cout << "round[" << setw(2) << round << "].s_row     ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
        cout << endl;

        mixColumns(in);
        cout << "round[" << setw(2) << round << "].m_col     ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
        cout << endl;

        word2.assign(next(word.begin(), round * 4), next(word.begin(), (round + 1) * 4));

        cout << "round[" << setw(2) << round << "].k_sch     ";
        for(int i = 0; i < 4; i++)
            printf("%08x", word2[i]);
        cout << endl;

        addRoundKey(in, word2);
    }

    word2.assign(next(word.begin(), Nr * 4), next(word.begin(), (Nr + 1) * 4));

    cout << "round[" << setw(2) << Nr << "].start     ";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            printf("%02x", in[j][i]);
    cout <<  endl;

    subBytes(in);

    cout << "round[" << setw(2) << Nr << "].s_box     ";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            printf("%02x", in[j][i]);
    cout << endl;

    shiftRows(in);

    cout << "round[" << setw(2) << Nr << "].s_row     ";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            printf("%02x", in[j][i]); 
    cout << endl;

    addRoundKey(in, word2);

    cout << "round[" << setw(2) << Nr << "].k_sch     ";
    for(int i = 0; i < 4; i++)
        printf("%08x", word2[i]);
    cout << endl;

    out = in;

    cout << "round[" << setw(2) << Nr << "].output    ";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            printf("%02x", out[j][i]);  
    cout << endl;
}

// INVCIPHER FUNCTIONS

// substitutes the bytes from the encrypted state with corresponding InvsBox value
void invSubBytes(vector<vector<unsigned char>>& state)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            unsigned char temp = state[i][j];

            int x = (temp >> 4) & 0xf;
            int y = temp & 0xF;

            state[i][j] = InvsBox[x][y];
        }
    }
}

// shifts bytes to the right on each row
void invShiftRows(vector<vector<unsigned char>>& state)
{
    unsigned char temp1, temp2;
    for(int i = 1; i < 4; i++)
    {
        for(int j = 0; j < i; j++)
        {
            temp1 = state[i][0];
            temp2 = state[i][1];
            state[i][1] = temp1;
            temp1 = state[i][2];
            state[i][2] = temp2;
            temp2 = state[i][3];
            state[i][3] = temp1;
            state[i][0] = temp2;
        }
    }
}

// mixes the columns by preforming matrix algebra with a specific matrix from mixColumns()
void invMixColumns(vector<vector<unsigned char>>& state) 
{
    for(int i = 0; i < 4; i++)
    {
        unsigned char temp1 = state[0][i];
        unsigned char temp2 = state[1][i];
        unsigned char temp3 = state[2][i];
        unsigned char temp4 = state[3][i];

        state[0][i] = ffAdd(ffAdd(ffAdd(ffMultiply(0x0e, temp1), ffMultiply(0x0b, temp2)), ffMultiply(0x0d, temp3)), ffMultiply(0x09, temp4));
        state[1][i] = ffAdd(ffAdd(ffAdd(ffMultiply(0x09, temp1), ffMultiply(0x0e, temp2)), ffMultiply(0x0b, temp3)), ffMultiply(0x0d, temp4));
        state[2][i] = ffAdd(ffAdd(ffAdd(ffMultiply(0x0d, temp1), ffMultiply(0x09, temp2)), ffMultiply(0x0e, temp3)), ffMultiply(0x0b, temp4));
        state[3][i] = ffAdd(ffAdd(ffAdd(ffMultiply(0x0b, temp1), ffMultiply(0x0d, temp2)), ffMultiply(0x09, temp3)), ffMultiply(0x0e, temp4));
    }
}

// decrypts using AES and displays all of the steps required for it. Follows the what was shown in FIPS with printing added to it
void invCipher(vector<vector<unsigned char>> in, vector<vector<unsigned char>>& out, vector<unsigned int> word, int Nk, int Nr) 
{
    vector<unsigned int> word2;

    word2.assign(next(word.begin(), Nr * 4), next(word.begin(), (Nr + 1) * 4));

    cout << "round[ 0].iinput    ";
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            printf("%02x", in[j][i]);
    cout << endl;

    cout << "round[ 0].ik_sch    ";
    for(int i = 0; i < 4; i++)
        printf("%08x", word2[i]);
    cout << endl;

    addRoundKey(in, word2);

    for(int round = Nr - 1; round > 0; round--)
    {
        cout << "round[" << setw(2) << Nr-round << "].istart    ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
        cout <<  endl;

        invShiftRows(in);

        cout << "round[" << setw(2) << Nr-round << "].is_row    ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
        cout << endl;

        invSubBytes(in);

        cout << "round[" << setw(2) << Nr-round << "].is_box    ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]); 
        cout << endl;

        word2.assign(next(word.begin(), round * 4 ), next(word.begin(), (round + 1) * 4));

        cout << "round[" << setw(2) << Nr-round << "].ik_sch    ";
        for(int i = 0; i < 4; i++)
            printf("%08x", word2[i]);
        cout << endl;

        addRoundKey(in, word2);

        cout << "round[" << setw(2) << Nr-round << "].ik_add    ";
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
        cout << endl;

        invMixColumns(in);
    }

    cout << "round[" << setw(2) << Nr << "].istart    ";
    for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
    cout <<  endl;

    invShiftRows(in);

    cout << "round[" << setw(2) << Nr << "].is_row    ";
    for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
    cout << endl;

    invSubBytes(in);

    cout << "round[" << setw(2) << Nr << "].is_box    ";
    for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", in[j][i]);
    cout << endl;

    word2.assign(word.begin(), next(word.begin(), 4));

    cout << "round[" << setw(2) << Nr << "].ik_sch    ";
    for(int i = 0; i < 4; i++)
            printf("%08x", word2[i]);
    cout << endl;
    
    addRoundKey(in, word2);

    out = in;

    cout << "round[" << setw(2) << Nr << "].ioutput   ";
    for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                printf("%02x", out[j][i]);
    cout << endl << endl;
}

int main(int argc, char *argv[])
{
    // First key size
    int Nk = 4;
    int Nr = 10;
    string plaintext = "00112233445566778899aabbccddeeff";
    string key = "000102030405060708090a0b0c0d0e0f";

    vector<unsigned char> keyVector;

    for(unsigned int i = 0; i < key.length(); i += 2) 
    {
        string temp = key.substr(i, 2);
        unsigned char temp2 = (unsigned char) strtol(temp.c_str(), NULL, 16);
        keyVector.push_back(temp2);
    }

    vector<unsigned char> plaintextInsert;

    for(unsigned int i = 0; i < plaintext.length(); i += 2) {
        string temp1 = plaintext.substr(i, 2);
        unsigned char temp2 = (unsigned char) strtol(temp1.c_str(), NULL, 16);
        plaintextInsert.push_back(temp2);
    }

    vector<vector<unsigned char>> plaintextVector(4, vector<unsigned char>(4, 0x0));
    int counter = 0;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            plaintextVector[j][i] = plaintextInsert[counter];
            counter++;
        }
    }

    cout << "C.1   AES-128 (Nk=4, Nr=10)" << endl << endl;
    cout << "PLAINTEXT:          00112233445566778899aabbccddeeff" << endl;
    cout << "KEY:                000102030405060708090a0b0c0d0e0f" << endl << endl;
    cout << "CIPHER (ENCRYPT):"  << endl;

    vector<vector<unsigned char>> outputVector;
    vector<unsigned int> keySchedule(4 * (Nr +1 ), 0x0);

    cipher(plaintextVector, outputVector ,keySchedule , keyVector, Nk, Nr);
    cout << endl << "INVERSE CIPHER (DECRYPT):"  << endl;
    invCipher(plaintextVector, outputVector ,keySchedule , Nk, Nr);

    keyVector.clear();
    plaintextInsert.clear();
    counter = 0;

    // Second key size
    Nk = 6;
    Nr = 12;
    plaintext = "00112233445566778899aabbccddeeff";
    key = "000102030405060708090a0b0c0d0e0f1011121314151617";

    for(unsigned int i = 0; i < key.length(); i += 2) 
    {
        string temp = key.substr(i, 2);
        unsigned char temp2 = (unsigned char) strtol(temp.c_str(), NULL, 16);
        keyVector.push_back(temp2);
    }

    for(unsigned int i = 0; i < key.length(); i += 2) 
    {
        string temp = key.substr(i, 2);
        unsigned char temp2 = (unsigned char) strtol(temp.c_str(), NULL, 16);
        keyVector.push_back(temp2);
    }

    for(unsigned int i = 0; i < plaintext.length(); i += 2) {
        string temp1 = plaintext.substr(i, 2);
        unsigned char temp2 = (unsigned char) strtol(temp1.c_str(), NULL, 16);
        plaintextInsert.push_back(temp2);
    }

    vector<vector<unsigned char>> plaintextVector2(4, vector<unsigned char>(4, 0x0));

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            plaintextVector2[j][i] = plaintextInsert[counter];
            counter++;
        }
    }

    cout << "C.2   AES-192 (Nk=6, Nr=12)" << endl << endl;
    cout << "PLAINTEXT:          00112233445566778899aabbccddeeff" << endl;
    cout << "KEY:                000102030405060708090a0b0c0d0e0f1011121314151617" << endl << endl;
    cout << "CIPHER (ENCRYPT):"  << endl;

    vector<vector<unsigned char>> outputVector2;
    vector<unsigned int> keySchedule2(4*(Nr+1), 0x0);

    cipher(plaintextVector2, outputVector2 ,keySchedule2 , keyVector, Nk, Nr);
    cout << endl << "INVERSE CIPHER (DECRYPT):"  << endl;
    invCipher(plaintextVector2, outputVector2 ,keySchedule2 , Nk, Nr);

    keyVector.clear();
    plaintextInsert.clear();
    counter = 0;

    // Third key size
    Nk = 8;
    Nr = 14;
    plaintext = "00112233445566778899aabbccddeeff";
    key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";

    for(unsigned int i = 0; i < key.length(); i += 2) 
    {
        string temp = key.substr(i, 2);
        unsigned char temp2 = (unsigned char) strtol(temp.c_str(), NULL, 16);
        keyVector.push_back(temp2);
    }

    for(unsigned int i = 0; i < key.length(); i += 2) 
    {
        string temp = key.substr(i, 2);
        unsigned char temp2 = (unsigned char) strtol(temp.c_str(), NULL, 16);
        keyVector.push_back(temp2);
    }

    for(unsigned int i = 0; i < plaintext.length(); i += 2) {
        string temp1 = plaintext.substr(i, 2);
        unsigned char temp2 = (unsigned char) strtol(temp1.c_str(), NULL, 16);
        plaintextInsert.push_back(temp2);
    }

    vector<vector<unsigned char>> plaintextVector3(4, vector<unsigned char>(4, 0x0));

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            plaintextVector3[j][i] = plaintextInsert[counter];
            counter++;
        }
    }

    cout << "C.3   AES-256 (Nk=8, Nr=14)" << endl << endl;
    cout << "PLAINTEXT:          00112233445566778899aabbccddeeff" << endl;
    cout << "KEY:                000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f" << endl << endl;
    cout << "CIPHER (ENCRYPT):"  << endl;

    vector<vector<unsigned char>> outputVector3;
    vector<unsigned int> keySchedule3(4*(Nr+1), 0x0);

    cipher(plaintextVector3, outputVector3 ,keySchedule3 , keyVector, Nk, Nr);
    cout << endl << "INVERSE CIPHER (DECRYPT):"  << endl;
    invCipher(plaintextVector3, outputVector3 ,keySchedule3 , Nk, Nr);

    return 0;
}