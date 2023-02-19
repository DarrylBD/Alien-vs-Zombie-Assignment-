#include "arrays.h"
#include <iostream>

namespace pf
{
    bool search_array_string(string array[], int size, string value)
    {
        for(int i = 0; i < size; i++)
        {
            if (array[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    bool search_array_int(int array[], int size, int value)
    {
        for(int i = 0; i < size; i++)
        {
            if (array[i] == value)
            {
                return true;
            }
        }
        return false;
    }
}
