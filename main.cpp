#include <iostream>
#include <sstream>
#include <ctype.h>
#include "parser.h"

using namespace std;

int main(int num_args, char **arg_strings)
{
    // Сhecking for the existence of an arguments as whole
    if (num_args < 2) 
    {
        cout << "[Error] Input argument is missing";
        return 0;
    }

    stringstream input_sstream(arg_strings[1]);
    string input[6];

    // Putting output values to the separate sstreams
    for (int i = 0; i < 6; i++)
    {
        input_sstream >> input[i]; 

        // Сhecking for the existence of every single argument
        if (input[i].empty())
        {
            printf("[Error] One or more arguments are missing");
        }
    }

    // Parsing
    parser parser(input[0], input[1], input[2], input[3], input[4], input[5]);
    
    // Formatting and printing
    parser.print();
}