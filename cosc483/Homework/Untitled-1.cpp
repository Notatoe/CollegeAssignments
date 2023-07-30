// Padding
void padding(string& M)
{
    // converts the message into 8 bit chars
    vector<unsigned char> bytes;
    for(int i = 0; i < M.length(); i++)
        bytes.push_back(M.at(i));

    //gets the amount of trailing zeroes
    int zeroes = 448 - (M.length() * 8 + 1);

    // adds the 1 bit and 7 of the zeroes
    bytes.push_back(0x80);

    // adds the remaining zeros one byte at a time (mathmatically it will always be multiple of 8)
    for(int i = 0; i < zeroes - 7; i += 8)
        bytes.push_back(0x00);

    // creates the bit block and adds it to the bytes vector
    string bitBlock = bitset<64>(M.length() * 8).to_string();
    for(int i = 0; i < bitBlock.length(); i++)
        bytes.push_back(bitBlock.at(i));

    // emptys the message string and adds every char from the vector to it
    M = "";
    for(i = 0; i < bytes.lenth(); i++)
        M = M + bytes.at(i)
}

// Messaging Schedule
string messagingSchedule(string M, string W, int t, int i)
{
    if(t >= 0 && t <= 15)
        // returns the t'th word of the i'th message block
        return M[i].at(t)
    else if(t >= 16 && t <= 79)
        // returns rotl with n = 1 and w = 32
        return ((W[t-1] ^ W[t-8] ^ W[t-14] ^ W[t-16]) << 1) | ((W[t-1] ^ W[t-8] ^ W[t-14] ^ W[t-16]) >> 31)
    //else return nothing
    return 0
}