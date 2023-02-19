#include "encrypt.h"
#include "helper.h"
#include <iostream>

namespace pf
{
    /* Encrypting and Decrypting files (Used Tech Edu's Encrypt and Decrypt tutorial as a baseline) */
    void encrypt(string filename, int key)
    {
        fstream file;
        fstream temp;
        string directory_temp = "save/temp.tmp";
        char char_;
        file.open(filename, fstream::in);
        temp.open(directory_temp, fstream::out);

        if (!file)
        {
            cout << "Unable to find directory" << endl;
        }

        while (file >> noskipws >> char_)
        {
            char_ = char_ + key;
            temp << char_;
        }

        file.close();
        temp.close();

        file.open(filename, fstream::out);
        temp.open(directory_temp, fstream::in);

        while (temp >> noskipws >> char_)
        {
            file << char_;
        }

        file.close();
        temp.close();
    }
    
    ifstream decrypt(string filename, int key)
    {
        fstream file;
        fstream temp;
        ifstream ret;
        
        string directory_temp = "save/temp.tmp";
        char char_;

        file.open(filename, fstream::in);
        temp.open(directory_temp, fstream::out);

        while (file >> noskipws >> char_)
        {
            char_ = char_ - key;
            temp << char_;
        }

        file.close();
        temp.close();

        ret.open(directory_temp);
        return ret;
    }
}
