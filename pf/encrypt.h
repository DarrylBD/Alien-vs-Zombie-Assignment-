#ifndef PF_ENCRYPT_H
#define PF_ENCRYPT_H

#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;
namespace pf
{
    void encrypt(string filename, int key);
    ifstream decrypt(string filename, int key);
    void delete_file(string directory);
}

#endif