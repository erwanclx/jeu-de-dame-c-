#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
using namespace std;

struct Color
{
    string reset = "\033[0m";
    string black = "\033[1;30m";
    string red = "\033[1;31m";
    string green = "\033[1;32m";
    string yellow = "\033[1;33m";
    string blue = "\033[1;34m";
    string magenta = "\033[1;35m";
    string cyan = "\033[1;36m";
    string white = "\033[1;37m";

    string bgBlack = "\033[1;40m";
    string bgRed = "\033[1;41m";
    string bgGreen = "\033[1;42m";
    string bgYellow = "\033[1;43m";
    string bgBlue = "\033[1;44m";
    string bgMagenta = "\033[1;45m";
    string bgCyan = "\033[1;46m";
    string bgWhite = "\033[1;47m";
};

Color palette;

#endif