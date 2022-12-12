#include <string>
#include <sstream>
#include <iostream>

#include "parser.h"

#define IS_TRUE(x)                                                                    \
    {                                                                                 \
        if (!(x))                                                                     \
            std::cout << __FUNCTION__ << " failed, line " << __LINE__ << std::endl;   \
        else                                                                          \
            std::cout << __FUNCTION__ << " is passed " << std::endl;                     \
    }

std::string parser_test(std::string min, std::string hou, std::string dom, std::string mon, std::string dow, std::string cmd)
{
    parser parser(min, hou, dom, mon, dow, cmd);
    return parser.output();
}

//OUTPUT FROM TECHNICAL TASK
void test1()
{
    std::string input[6];
    std::stringstream sstream("*/15 0 1,15 * 1-5 /usr/bin/find");

    for (int i = 0; i < 6; i++)
    {
        sstream >> input[i];
    }

    IS_TRUE(parser_test(input[0],input[1],input[2],input[3],input[4],input[5]) == "0 15 30 45\n0\n1 15\n1 2 3 4 5 6 7 8 9 10 11 12\n1 2 3 4 5\n/usr/bin/find\n");
}

//TECHNICAL INTERVIEW
void test2()
{
    std::string input[6];
    std::stringstream sstream("*/15 0 1,15 NOV-MAR 1-5 /usr/bin/find");

    for (int i = 0; i < 6; i++)
    {
        sstream >> input[i];
    }

    IS_TRUE(parser_test(input[0],input[1],input[2],input[3],input[4],input[5]) == "0 15 30 45\n0\n1 15\n11 12 1 2 3\n1 2 3 4 5\n/usr/bin/find\n");
}

int main()
{
    test1();
    test2();
}