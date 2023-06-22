#include "encrypt.h"
#include "helper.h"
#include <iostream>

namespace pf
{
    /* Encrypting and Decrypting files (Used Tech Edu's Encrypt and Decrypt tutorial as a baseline) */
    void encrypt(string filename, int key, string dir)
    {
        fstream file;
        fstream temp;
        char char_;
        
        file.open(filename, fstream::in);
        temp.open(dir, fstream::out);

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
        temp.open(dir, fstream::in);

        while (temp >> noskipws >> char_)
        {
            file << char_;
        }

        file.close();
        temp.close();
        remove(dir.c_str());
    }
    
    ifstream decrypt(string filename, int key, string dir)
    {
        fstream file;
        fstream temp;
        ifstream ret;
        char char_;

        file.open(filename, fstream::in);
        temp.open(dir, fstream::out);

        while (file >> noskipws >> char_)
        {
            char_ = char_ - key;
            temp << char_;
        }

        file.close();
        temp.close();

        ret.open(dir);
        return ret;
    }
}
