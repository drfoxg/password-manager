#pragma once

#include <string>
#include <vector>
#include <regex>
#include <string_view>

using namespace std;

class Core
{
private:
    string square;
    size_t square_side;

public:
    Core(const string& square, const size_t square_side);

    string encrypt(const string& msg);
    string decrypt(const string& msg);

    string encrypt(const string& msg, const string& square, const size_t square_side);
    string decrypt(const string& msg, const string& square, const size_t square_side);

    const size_t get_square_side();

private:
    const int strchr_get_index(const string& square, const char msg);
    vector<string> split(const string& str, string_view pattern);
};

